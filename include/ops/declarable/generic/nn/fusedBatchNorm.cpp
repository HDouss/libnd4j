//
// Created by raver119 on 29/10/17.
//

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
namespace ops {

CUSTOM_OP_IMPL(fused_batch_norm, 3, 1, false, 0, 2) {

    NDArray<T>* x      = INPUT_VARIABLE(0);                 // [bS,iH,iW,iD] (NHWC) or [bS,iD,iH,iW] (NCHW)
    NDArray<T>* scale  = INPUT_VARIABLE(1);                 // [iD]
    NDArray<T>* offset = INPUT_VARIABLE(2);                 // [iD]

    NDArray<T>* y = OUTPUT_VARIABLE(0);                     // [bS,iH,iW,iD] (NHWC) or [bS,iD,iH,iW] (NCHW)
    NDArray<T>* batchMean = OUTPUT_VARIABLE(1);             // [iD]
    NDArray<T>* batchVar  = OUTPUT_VARIABLE(2);             // [iD]

    const bool dataFormat = (bool)INT_ARG(0);               // 0->NHWC, 1->NCHW
    const bool isTraining = (bool)INT_ARG(1);    

    REQUIRE_TRUE(x->rankOf() == 4, 0, "CUSTOM_OP fused_batch_norm: the rank of input x array must be equal to 4 !");    

    int bS = x->sizeAt(0);              // batch size
    int iH, iW, iD;                     // input height, input width, input depth(number of channels)        
    if(dataFormat) {
        iD = x->sizeAt(1);
        iH = x->sizeAt(2);
        iW = x->sizeAt(3);
    }
    else {
        iH = x->sizeAt(1);
        iW = x->sizeAt(2);
        iD = x->sizeAt(3);   
    }    

    REQUIRE_TRUE(scale->rankOf() == 1  && scale->sizeAt(0)  == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input scale array !");
    REQUIRE_TRUE(offset->rankOf() == 1 && offset->sizeAt(0) == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input offset array !");        

    NDArray<T>* mean(nullptr), *variance(nullptr);
    if(!isTraining){
        mean     = INPUT_VARIABLE(3);   
        variance = INPUT_VARIABLE(4);   
        REQUIRE_TRUE(mean->rankOf() == 1     && mean->sizeAt(0) == iD,     0, "CUSTOM_OP fused_batch_norm: wrong shape of input mean array !");
        REQUIRE_TRUE(variance->rankOf() == 1 && variance->sizeAt(0) == iD, 0, "CUSTOM_OP fused_batch_norm: wrong shape of input variance array !");        
    }
    else {
        REQUIRE_TRUE(block.width() == 3, 0, "CUSTOM_OP fused_batch_norm: when isTraining=true then number of input arrays must be equal to 3 !");   
        std::vector<int> shape = {iD};
        mean = new NDArray<T>(scale->ordering(), shape, block.getWorkspace());
        variance = new NDArray<T>(scale->ordering(), shape, block.getWorkspace());        
    }

    T epsilon;
    if(block.getTArguments()->size() > 0)         
        epsilon = T_ARG(0) > (T)1.001e-5 ? T_ARG(0) : (T)1.001e-5;    
    else 
        epsilon = 0.001;
    
    const int restSize = x->lengthOf() / iD;    
    NDArray<T> xAffected(x->ordering(), {restSize, iD}, block.getWorkspace());
    xAffected.assign(x);

    const int restSizeMinusOne = (restSize > 1) ? (restSize - 1) : 1;
    const T restSizeInv = (T)1.0 / restSize;
    const T restSizeAdjust = (T)restSize / restSizeMinusOne;

    if(isTraining) {
        NDArray<T>* sum = xAffected.sum({0});
        mean->assign((*sum) * restSizeInv);
        *batchMean = *mean;
        delete sum;
    }
    else 
        *batchMean = 0.;
    
    xAffected -= *mean;

    if(isTraining) {        
        T power = 2.;
        NDArray<T>* sum = xAffected.template transform<simdOps::Pow<T>>(&power).sum({0});
        variance->assign((*sum) * restSizeInv);
        *batchVar  = (*variance) * restSizeAdjust;
        delete sum;
    }
    else 
        *batchVar  = 0.;      

    y->assign( xAffected * (*variance + epsilon).template transform<simdOps::RSqrt<T>>() * (*scale) + (*offset) );    

    if(isTraining) {
        delete mean;
        delete variance;
    }

    return Status::OK();
}



DECLARE_SHAPE_FN(fused_batch_norm) {

    int* xShapeInfo     = inputShape->at(0);
    int* scaleShapeInfo = inputShape->at(1);
    
    int* outShapeInfo(nullptr), *batchMeanShapeInfo(nullptr), *batchVarShapeInfo(nullptr);
    
    COPY_SHAPE(xShapeInfo, outShapeInfo);
    COPY_SHAPE(scaleShapeInfo, batchMeanShapeInfo);
    COPY_SHAPE(scaleShapeInfo, batchVarShapeInfo);    
    
    return SHAPELIST(outShapeInfo, batchMeanShapeInfo, batchVarShapeInfo);
}




}
}
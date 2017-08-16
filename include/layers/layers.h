//
//
// @author raver119@gmail.com
//
#ifndef PROJECT_LAYERS_H
#define PROJECT_LAYERS_H

// the list of errors codes for layer data
#define ND4J_STATUS_OK            0
#define ND4J_STATUS_BAD_INPUT     1
#define ND4J_STATUS_BAD_SHAPE     2
#define ND4J_STATUS_BAD_RANK      3
#define ND4J_STATUS_BAD_PARAMS    4
#define ND4J_STATUS_BAD_OUTPUT    5
#define ND4J_STATUS_BAD_RNG       6
#define ND4J_STATUS_BAD_EPSILON   7
#define ND4J_STATUS_BAD_GRADIENTS 8
#define ND4J_STATUS_BAD_BIAS      9


namespace nd4j {
namespace layers {

template <typename T> class INativeLayer {    
    protected:
        NDArray<T> *_params;                 // flattened rectangle matrix with parameters (weights)
        NDArray<T> *_bias;                   // flattened multidimensional matrix of biases
        NDArray<T> *_input;                  // flattened multidimensional matrix of inputs
        NDArray<T> *_epsilon;                // flattened multidimensional matrix of epsilons = dL/da, L - loss function, a - input/activation
        NDArray<T> *_mask;                   // the matrix of zeros and unities, takes into account possible different size of inputs, outer pixels are set to zeros in order to suit smaller inputs, the rest is unities
        NDArray<T> *_output;                // flattened multidimensional matrix of outputs
        NDArray<T> *_epsilonNext;           // holder for epsilonNext
        NDArray<T> *_preOutput;             // optional holder for FF activations
        NDArray<T> *_gradientW;              // flattened multidimensional matrix of weights gradients used in BP
        NDArray<T> *_gradientB;              // flattened multidimensional matrix of bias gradients used in BP        
        Nd4jIndex _allocated;               // memory amount which is already used from workspace, more probably it would be just 0
        Nd4jIndex _length;                  // memory amount which is still available from workspace, (allocated + length) = total size of workspace
        void *_workspace;                   // if one is going to use additional memory, take it from workspace
        nd4j::random::RandomBuffer* _rng;   // rng helper
        bool _dropOut;                      // corresponds to dropout applying
        bool _dropConnect;                  // corresponds to dropConnect applying        
        T _pDropOut;                        // dropout probabilities (if used)
        T _pDropConnect;                    // dropconnect probabilities (if used)
                
    public:
    
        // default constructor, sets all pointers to be empty
        INativeLayer();
        
        virtual ~INativeLayer();

        // copy constructor
        // creation of this class objects by copying is not expected, therefore disable copy constructor 
        INativeLayer(const INativeLayer& ) = delete;
        
        // assignment operator
        // the assignment operations are not expected for this class objects, therefore disable assignment operator
        INativeLayer& operator=(const INativeLayer& ) = delete;   

        // This method "allocates" memory chunk from workspace
        virtual T* allocate(long bytes) = 0; 
        
        // This method should validate parameters & bias, and return TRUE if everything ok. False otherwise
        virtual int validateParameters() const = 0;

        // this method should validate memory/holders for BP pass
        virtual int validateGradients() const = 0;

        // This method should validate input parameters, and return corresponding codes errors if mistake is present
        virtual int validateInput() const = 0;

        // This method should validate output parameters, and return TRUE if everything is ok, FALSE otherwise
        virtual int validateOutput() const = 0;
       
        // DropOut & DropConnect helpers are platform-specific too
        virtual void dropOutHelper(NDArray<T> *input) = 0;
        virtual void dropConnectHelper(NDArray<T> *input) = 0;

        void setParams(NDArray<T>* other) 
        { _params->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getParams() const
        { return _params; }

        void setInput(NDArray<T>* other) 
        { _input->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getInput() const
        { return _input; }

        void setOutput(NDArray<T>* other) 
        { _output->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getOutput() const
        { return _output; }

        void setBias(NDArray<T>* other) 
        { _bias->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getBias() const
        { return _bias; }        

        void setEpsilon(NDArray<T>* other) 
        { _epsilon->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getEpsilon() const
        { return _epsilon; }        
        
        void setMask(NDArray<T>* other) 
        { _mask->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getMask() const
        { return _mask; }        

        void setEpsilonNext(NDArray<T>* other) 
        { _epsilonNext->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getEpsilonNext() const
        { return _epsilonNext; }        
        
        void setPreOutput(NDArray<T>* other) 
        { _preOutput->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getPreOutput() const
        { return _preOutput; }

        void setGradientW(NDArray<T>* other) 
        { _gradientW->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getGradientW() const
        { return _gradientW; }

        void setGradientB(NDArray<T>* other) 
        { _gradientB->replacePointers(other->getBuff(), other->getShapeInfo()); }

        NDArray<T>* getGradientB() const
        { return _gradientB; }          
        
        void setDropOut(const bool other) 
        { _dropOut = other; }

        bool getDropOut() const
        { return _dropOut; }          
        
        void setDropConnect(const bool other) 
        { _dropConnect = other; }

        bool getDropConnect() const
        { return _dropConnect; }   

        void setpDropOut(const T& other) 
        { _pDropOut = other; }
        
        T getpDropOut() const
        { return _pDropOut; } 

        void setpDropConnect(const T& other) 
        { _pDropConnect = other; }

        T getpDropConnect() const
        { return _pDropConnect; }
        
        void setRng(nd4j::random::RandomBuffer* other) 
        { _rng = other; }

        nd4j::random::RandomBuffer* getRng() const
        { return _rng; }
            
        // this inline method attaches layer to workspace memory
        void setWorkspace(const void *memory, const Nd4jIndex length) {
            this->_length    = length;
            this->_workspace = memory;
        };

        // this method returns number of bytes used
        Nd4jIndex inline getUsedMemory() const {
            return _allocated;           // usually just 0
        }

        // This inline method allows to set parameters/biases for current layer
        // this input will be either activation from previous layer, or error coming from next layer
        int setParameters(T *params, int *paramsShapeInfo, T *bias, int *biasShapeInfo) {
            this->_params->replacePointers(params, paramsShapeInfo);
            this->_bias->replacePointers(bias, biasShapeInfo);

            return validateParameters();
        }

        // We have some options to be configured in layer: dropout, dropconnect, lr, etc 
        // This method should handle that. Maybe map (key-value), or something like that?           
        int configureLayerFF(T *input, int *inputShapeInfo, T*output, int *outputShapeInfo, T pDropOut, T pDropConnect, Nd4jPointer rngPointer);

        int configureLayerBP(T *output, int *outputShapeInfo, T* gradientW, int *gradientWShapeInfo, T* gradientB, int *gradientBShapeInfo, T *epsilonPrev, int *epsilonShapeInfo, T *preOutput = nullptr, int *preOutputShapeInfo = nullptr);

        // This inline method allows to specify input data for layer
        // this output will be either activation of this layer, or error from next layer        
        int setInput(T *input, int *inputShapeInfo, T *mask, int *maskShapeInfo) {
            this->_input->replacePointers(input, inputShapeInfo);
            this->_mask->replacePointers(mask, maskShapeInfo);
            return validateInput();
        }

        // This inline method allows to specify output pointer for layer
        int setOutput(T *output, int *shapeInfo) {
            this->_output->replacePointers(output, shapeInfo);
            return validateOutput();
        }

        // This method executes feed-forward pass on this layer
        virtual int feedForward() = 0;

        // This method executes back-propagation pass on this layer
        virtual int backPropagate() = 0;

        // gemv should be used here
        void gemvHelper(const T *A, int *aShapeInfo, const T *B, int *bShapeInfo, T *C, int *cShapeInfo, const T alpha, const T beta);

        void gemmHelper(const NDArray<T> *A, const NDArray<T> *B, NDArray<T> *C, const T alpha, const T beta);

        void gemmHelper(const NDArray<T> *A, const NDArray<T> *B, NDArray<T> *C, const T alpha, const T beta, bool transA, bool transB);
        // extracts shapes info and perform gemm 
        void gemmHelper(T *A, int *aShapeInfo, T *B, int *bShapeInfo, T *C, int *cShapeInfo, const T alpha, const T beta);

};
    
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////////////////// implementation part ////////////////////////////
    
// default constructor sets all pointers to be empty
template <typename T> INativeLayer<T>::INativeLayer() {
    
    _params      = new NDArray<T>();
    _bias        = new NDArray<T>();
    _input       = new NDArray<T>();
    _epsilon     = new NDArray<T>();
    _mask        = new NDArray<T>();
    _output      = new NDArray<T>();
    _gradientW   = new NDArray<T>();
    _gradientB   = new NDArray<T>();
    _epsilonNext = new NDArray<T>();
    _preOutput   = new NDArray<T>();

    _workspace    = nullptr;
    _rng          = nullptr;
    _allocated    = 0;
    _length       = 0;
    _dropOut      = false;                   
    _dropConnect  = false;                       
    _pDropOut     = 0.;   
    _pDropConnect = 0.;    
}

template <typename T> INativeLayer<T>::~INativeLayer() {
    delete _params;
    delete _bias;
    delete _input;
    delete _gradientW;
    delete _gradientB;
    delete _mask;
    delete _output;
    delete _epsilon;
    delete _epsilonNext;
    delete _preOutput;
}

template <typename T> void INativeLayer<T>::gemmHelper(const NDArray<T> *A, const NDArray<T> *B, NDArray<T> *C, const T alpha, const T beta) {
    gemmHelper(A->getBuff(), A->getShapeInfo(), B->getBuff(), B->getShapeInfo(), C->getBuff(), C->getShapeInfo(), alpha, beta);
}

// perform C = alpha*A*B + beta*C
template <typename T> void INativeLayer<T>::gemmHelper(T *A, int *aShapeInfo, T *B, int *bShapeInfo, T *C, int *cShapeInfo, const T alpha, const T beta) {
            /**
             * PLEASE NOTE: Return order will be F always
             */
    char aOrder = shape::order(aShapeInfo);
    char bOrder = shape::order(bShapeInfo);
    char cOrder = shape::order(cShapeInfo);

    int *aShape = shape::shapeOf(aShapeInfo);
    int *bShape = shape::shapeOf(bShapeInfo);
    int *cShape = shape::shapeOf(cShapeInfo);

    char rOrder;

    int M, N, K, lda, ldb, ldc;
    char transA, transB;

    NDArray<T> *_A, *_B, *_C;

    //_C = new NDArray<T>(C, cShapeInfo);

    auto *tA = new NDArray<T>(A, aShapeInfo);
    auto *tB = new NDArray<T>(B, bShapeInfo);
    auto *tC = new NDArray<T>(C, cShapeInfo);

    if (cOrder != 'f') {
        _C = tC->dup('f');
    } else {
        _C = tC;
    }

    if (aOrder == bOrder) {
        //printf("Going dRoute here\n");

        if (aOrder == 'c') {
            // we might need to transpose matrices,     
            // todo: we need dup(c/f) helper here
            _A = tA->dup('f');
            _B = tB->dup('f');
        } else {
            _A = tA;
            _B = tB;
        }

        rOrder = 'f';

        M = cShape[0];
        N = cShape[1];
        K = aShape[1];

        lda = aShape[0];
        ldb = bShape[0];
        ldc = cShape[0];

        transA = 'N';
        transB = 'N';
    } else {
        //printf("Going tRoute here\n");
        if (aOrder == 'c') {
            // dup(F) A here
            _A = tA->dup('f');
            _B = tB;
        } else {
            // dup(F) B here
            _A = tA;
            _B = tB->dup('f');
        }

       // _C = tC->dup('f');

        M = cShape[0];
        N = cShape[1];
        K = aShape[1]; 

        rOrder = aOrder;

        lda = aShape[0];
        ldb = bShape[0];
        ldc = cShape[0];

        transA = 'N';
        transB = 'N';
    }

    // we'll use platform-specific gemm here eventually. maybe tomorrow.
    // TODO: put proper _gemm here
    nd4j::blas::GEMM<T>::op(rOrder, transA, transB, M, N, K, alpha, _A->getBuff(), lda, _B->getBuff(), ldb, beta, _C->getBuff(), ldc);

    if (cOrder != 'f') {
        tC->assign(_C);
    }

    if (tA != _A)
        delete _A;

    if (tB != _B)
        delete _B;

    if (tC != _C)
        delete _C;


    delete tA;
    delete tB;
    delete tC;
}


template <typename T>
int INativeLayer<T>::configureLayerBP(T *epsilonNext, int *epsilonNextShapeInfo, T* gradientW, int *gradientWShapeInfo, T* gradientB, int *gradientBShapeInfo, T *epsilonPrev, int *epsilonShapeInfo, T *preOutput, int *preOutputShapeInfo) {
    _epsilonNext->replacePointers(epsilonNext, epsilonNextShapeInfo);
    _preOutput->replacePointers(preOutput, preOutputShapeInfo);
    _gradientW->replacePointers(gradientW, gradientWShapeInfo);
    _gradientB->replacePointers(gradientB, gradientBShapeInfo);
    _epsilon->replacePointers(epsilonPrev, epsilonShapeInfo);

    // TODO: add gradient/epsilon valdiation here
    if (validateGradients() != ND4J_STATUS_OK)
        return validateGradients();

    return ND4J_STATUS_OK;
}



// We have some options to be configured in layer: dropout, dropconnect, lr, etc 
// This method should handle that. Maybe map (key-value), or something like that?           
template <typename T>
int INativeLayer<T>::configureLayerFF(T *input, int *inputShapeInfo, T *output, int *outputShapeInfo, T pDropOut, T pDropConnect, Nd4jPointer ptrRng) {

    if (ptrRng != nullptr)
        _rng = reinterpret_cast<nd4j::random::RandomBuffer *> (ptrRng);

    _pDropOut = pDropOut > (T) 0.0f ? pDropOut : (T) 0.0f;
    _pDropConnect = pDropConnect > (T) 0.0f ? pDropConnect : (T) 0.0f;

    _dropOut = _pDropOut > (T) 0.0f;
    _dropConnect = _pDropConnect > (T) 0.0f;

    if ((_dropOut || _dropConnect) && _rng == nullptr)
        return ND4J_STATUS_BAD_RNG;

    _input->replacePointers(input, inputShapeInfo);


    if (validateInput() != ND4J_STATUS_OK)
        return ND4J_STATUS_BAD_INPUT;


    _output->replacePointers(output, outputShapeInfo);

    if (validateOutput() != ND4J_STATUS_OK)
        return ND4J_STATUS_BAD_OUTPUT;

    /*
     * TODO: define ERROR_CODES here, and return them instead of bool
     */

    return ND4J_STATUS_OK;
}          


// end of namespace brackets
}
}    
#endif //PROJECT_LAYERS_H


//
//  @author raver119@gmail.com
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(__hardtanh)

#include <ops/declarable/CustomOperations.h>

namespace nd4j {
    namespace ops {
        CONFIGURABLE_OP_IMPL(hardtanh, 1, 1, true, 0, 0) {
            auto input = INPUT_VARIABLE(0);
            auto output = OUTPUT_VARIABLE(0);

            input->template applyTransform<simdOps::HardTanh<T>>(output, nullptr);
            STORE_RESULT(output);
            
            return ND4J_STATUS_OK;
        }

        CONFIGURABLE_OP_IMPL(hardtanh_bp, 2, 1, true, 0, 0) {
            NDArray<T>* input = INPUT_VARIABLE(0);
            NDArray<T>* epsilon = INPUT_VARIABLE(1);

            auto z = OUTPUT_VARIABLE(0);

            auto lambda = LAMBDA_TT(_x, _e) {
                return _e * simdOps::HardTanhDerivative<T>::op(_x, nullptr);
            };

            input->applyPairwiseLambda(epsilon, lambda, z);  

            return ND4J_STATUS_OK;
        }
    }
}

#endif
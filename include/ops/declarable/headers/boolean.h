//
//  @author raver119@gmail.com
//

#ifndef LIBND4J_HEADERS_BOOLEAN_H
#define LIBND4J_HEADERS_BOOLEAN_H

#include <ops/declarable/headers/common.h>

namespace nd4j {
    namespace ops {

        /**
         * This is scalar boolean op.
         * Both operands should be scalars.
         * 
         * Returns true if x < y
         */
        #if NOT_EXCLUDED(__lt_scalar)
        DECLARE_BOOLEAN_OP(lt_scalar, 2, true);
        #endif

        /**
         * This is scalar boolean op.
         * Both operands should be scalars.
         * 
         * Returns true if x > y
         */
        #if NOT_EXCLUDED(__gt_scalar)
        DECLARE_BOOLEAN_OP(gt_scalar, 2, true);
        #endif

        /**
         * This is scalar boolean op.
         * Both operands should be scalars.
         * 
         * Returns true if x <= y
         */
        #if NOT_EXCLUDED(__lte_scalar)
        DECLARE_BOOLEAN_OP(lte_scalar, 2, true);
        #endif

        /**
         * This is scalar boolean op.
         * Both operands should be scalars.
         * 
         * Returns true if x >= y
         */
        #if NOT_EXCLUDED(__gte_scalar)
        DECLARE_BOOLEAN_OP(gte_scalar, 2, true);
        #endif

        /**
         * This is scalar boolean op.
         * Both operands should be scalars.
         * 
         * Returns true if both operands are equal.
         */
        #if NOT_EXCLUDED(__eq_scalar)
        DECLARE_BOOLEAN_OP(eq_scalar, 2, true);
        #endif

        /**
         * This is scalar boolean op.
         * Both operands should be scalars.
         * 
         * Returns true if x != y
         */
        #if NOT_EXCLUDED(__neq_scalar)
        DECLARE_BOOLEAN_OP(neq_scalar, 2, true);
        #endif

        /**
         * This op takes 2 equally shaped arrays as input, and provides binary matrix as output.
         * Math is: _x == _y ? (T) 1.0f : (T) 0.0f;
         * 
         */
        #if NOT_EXCLUDED(__equals)
        DECLARE_OP(equals, 2, 1, true);
        #endif

        /**
         * This op takes 2 equally shaped arrays as input, and provides binary matrix as output.
         * Math is: _x != _y ? (T) 1.0f : (T) 0.0f;
         */
        #if NOT_EXCLUDED(__not_equals)
        DECLARE_OP(not_equals, 2, 1, true);
        #endif

        /**
         * This op takes 2 equally shaped arrays as input, and provides binary matrix as output.
         * Math is: _x <= _y ? (T) 1.0f : (T) 0.0f;
         */
        #if NOT_EXCLUDED(__less_equal)
        DECLARE_OP(less_equal, 2, 1, true);
        #endif

        /**
         * This op takes 2 equally shaped arrays as input, and provides binary matrix as output.
         * Math is: _x >= _y ? (T) 1.0f : (T) 0.0f;
         */
        #if NOT_EXCLUDED(__greater_equal)
        DECLARE_OP(greater_equal, 2, 1, true);
        #endif

        /**
         * This op takes 2 equally shaped arrays as input, and provides binary matrix as output.
         * Math is: _x < _y ? (T) 1.0f : (T) 0.0f;
         */
        #if NOT_EXCLUDED(__less)
        DECLARE_OP(less, 2, 1, true);
        #endif

        /**
         * This op takes 2 equally shaped arrays as input, and provides binary matrix as output.
         * Math is: _x > _y ? (T) 1.0f : (T) 0.0f;
         */
        #if NOT_EXCLUDED(__greater)
        DECLARE_OP(greater, 2, 1, true);
        #endif

        /**
         * This op takes 2 n-dimensional arrays as input, and return 
         * array of the same shape, with elements, either from x or y, depending on the condition.
         */
        #if NOT_EXCLUDED(__where)
        DECLARE_CUSTOM_OP(Where, 1, 1, false, 0, 0);
        #endif

        #if NOT_EXCLUDED(__where_np)
        DECLARE_CUSTOM_OP(where_np, 1, 1, false, 0, 0);
        #endif

        /**
         * This op takes 2 n-dimensional arrays as input, and return
         * array of the same shape, with elements, either from x or y, depending on the condition.
         */
        #if NOT_EXCLUDED(__select)
        DECLARE_CUSTOM_OP(select, 3, 1, false, 0, 0);
        #endif

        /**
         * This op takes either 1 argument and 1 scalar
         * or 1 argument and another comparison array
         * and runs a pre defined conditional op.
         *
         *  The output of the op is dynamic in size and returns a flat vector of elements
         *  that return true on the given condition.
         *  In numpy parlance, most people might understand:
         *  a[a > 2]
         *  where a is a numpy array and the condition is true when an element is
         *  > 2. Libnd4j already implements a number of pre defined conditions.
         * @tparam T
         */
        #if NOT_EXCLUDED(__choose)
        DECLARE_CUSTOM_OP(choose, -1, 1, false, -1, -1);
        #endif

        /**
        * This op takes 1 n-dimensional array as input, and returns true if for every adjacent pair we have x[i] <= x[i+1].
         */
        #if NOT_EXCLUDED(__is_non_decreasing)
        DECLARE_BOOLEAN_OP(is_non_decreasing, 1, true);
        #endif

        /**
         * This op takes 1 n-dimensional array as input, and returns true if for every adjacent pair we have x[i] < x[i+1].
         */
        #if NOT_EXCLUDED(__is_strictly_increasing)
        DECLARE_BOOLEAN_OP(is_strictly_increasing, 1, true);
        #endif

        /**
         * This op takes 1 n-dimensional array as input, and returns true if input is a numeric array.
         */
        #if NOT_EXCLUDED(__is_numeric_tensor)
        DECLARE_BOOLEAN_OP(is_numeric_tensor, 1, true);
        #endif
    }
}

#endif
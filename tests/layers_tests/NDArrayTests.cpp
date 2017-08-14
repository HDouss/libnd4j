//
// Created by raver119 on 04.08.17.
//

#include "testlayers.h"

class NDArrayTest : public testing::Test {
public:
    int alpha = 0;

    int *cShape = new int[8]{2, 2, 2, 2, 1, 0, 1, 99};
    int *fShape = new int[8]{2, 2, 2, 1, 2, 0, 1, 102};
};


TEST_F(NDArrayTest, AssignScalar1) {
    auto *array = new NDArray<float>(10, 'c');

    array->assign(2.0f);

    for (int i = 0; i < array->lengthOf(); i++) {
        ASSERT_EQ(2.0f, array->getScalar(i));
    }
}



TEST_F(NDArrayTest, NDArrayOrder1) {
    // original part
    float *c = new float[4] {1, 2, 3, 4};

    // expected part
    float *f = new float[4] {1, 3, 2, 4};

    auto *arrayC = new NDArray<float>(c, cShape);
    auto *arrayF = arrayC->dup('f');
    auto *arrayC2 = arrayF->dup('c');

    ASSERT_EQ('c', arrayC->ordering());
    ASSERT_EQ('f', arrayF->ordering());
    ASSERT_EQ('c', arrayC2->ordering());

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(f[i], arrayF->getBuff()[i]);
    }

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(fShape[i], arrayF->getShape()[i]);
    }

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(c[i], arrayC2->getBuff()[i]);
    }

    for (int i = 0; i < 8; i++) {
        ASSERT_EQ(cShape[i], arrayC2->getShape()[i]);
    }
}

TEST_F(NDArrayTest, TestGetScalar1) {
    float *c = new float[4] {1, 2, 3, 4};
    int *cShape = new int[8]{2, 2, 2, 2, 1, 0, 1, 99};

    auto *arrayC = new NDArray<float>(c, cShape);

    ASSERT_EQ(3.0f, arrayC->getScalar(1, 0));
    ASSERT_EQ(4.0f, arrayC->getScalar(1, 1));

    auto *arrayF = arrayC->dup('f');

    ASSERT_EQ(3.0f, arrayF->getScalar(1, 0));
    ASSERT_EQ(4.0f, arrayF->getScalar(1, 1));


    arrayF->putScalar(1, 0, 7.0f);
    ASSERT_EQ(7.0f, arrayF->getScalar(1, 0));


    arrayC->putScalar(1, 1, 9.0f);
    ASSERT_EQ(9.0f, arrayC->getScalar(1, 1));

}


TEST_F(NDArrayTest, EqualityTest1) {
    auto *arrayA = new NDArray<float>(3, 5, 'f');
    auto *arrayB = new NDArray<float>(3, 5, 'f');
    auto *arrayC = new NDArray<float>(3, 5, 'f');

    auto *arrayD = new NDArray<float>(2, 4, 'f');
    auto *arrayE = new NDArray<float>(15, 'f');

    for (int i = 0; i < arrayA->rows(); i++) {
        for (int k = 0; k < arrayA->columns(); k++) {
            arrayA->putScalar(i, k, (float) i);
        }
    }

    for (int i = 0; i < arrayB->rows(); i++) {
        for (int k = 0; k < arrayB->columns(); k++) {
            arrayB->putScalar(i, k, (float) i);
        }
    }

    for (int i = 0; i < arrayC->rows(); i++) {
        for (int k = 0; k < arrayC->columns(); k++) {
            arrayC->putScalar(i, k, (float) i+1);
        }
    }



    ASSERT_TRUE(arrayA->equalsTo(arrayB, 1e-5));

    ASSERT_FALSE(arrayC->equalsTo(arrayB, 1e-5));

    ASSERT_FALSE(arrayD->equalsTo(arrayB, 1e-5));

    ASSERT_FALSE(arrayE->equalsTo(arrayB, 1e-5));
}



TEST_F(NDArrayTest, TestSum1) {
    float *c = new float[4] {1, 2, 3, 4};

    auto *array = new NDArray<float>(c, cShape);

    ASSERT_EQ(10.0f, array->sumNumber());
    ASSERT_EQ(2.5f, array->meanNumber());
}

TEST_F(NDArrayTest, TestAddiRowVector) {
    float *c = new float[4] {1, 2, 3, 4};
    float *e = new float[4] {2, 3, 4, 5};

    auto *array = new NDArray<float>(c, cShape);
    auto *row = new NDArray<float>(2, 'c');
    auto *exp = new NDArray<float>(e, cShape);
    row->assign(1.0f);

    array->addiRowVector(row);

    ASSERT_TRUE(exp->equalsTo(array));
}

TEST_F(NDArrayTest, Test3D_1) {
    auto arrayC = new NDArray<double>('c', {2, 5, 10});
    auto arrayF = new NDArray<double>('f', {2, 5, 10});

    ASSERT_EQ(100, arrayC->lengthOf());
    ASSERT_EQ(100, arrayF->lengthOf());

    ASSERT_EQ('c', arrayC->ordering());
    ASSERT_EQ('f', arrayF->ordering());
}

TEST_F(NDArrayTest, TestTranspose1) {
    auto *arrayC = new NDArray<double>('c', {2, 5, 10});

    int *expC = new int[10] {3, 2, 5, 10, 50, 10, 1, 0, 1, 99};
    int *expT = new int[10] {3, 10, 5, 2, 1, 10, 50, 0, 1, 102};

    auto *arrayT = arrayC->transpose();


    for (int e = 0; e < arrayC->rankOf() * 2 + 4; e++) {
        ASSERT_EQ(expC[e], arrayC->getShape()[e]);
        ASSERT_EQ(expT[e], arrayT->getShape()[e]);
    }

}

TEST_F(NDArrayTest, TestTranspose2) {
    auto *arrayC = new NDArray<double>('c', {2, 5, 10});

    int *expC = new int[10] {3, 2, 5, 10, 50, 10, 1, 0, 1, 99};
    int *expT = new int[10] {3, 10, 5, 2, 1, 10, 50, 0, 1, 102};

    arrayC->transposei();


    for (int e = 0; e < arrayC->rankOf() * 2 + 4; e++) {
        ASSERT_EQ(expT[e], arrayC->getShape()[e]);
    }

}

TEST_F(NDArrayTest, TestSumAlongDimension1) {
    float *c = new float[4] {1, 2, 3, 4};
    auto *array = new NDArray<float>(c, cShape);

    auto *res = array->sum({0});

    ASSERT_EQ(2, res->lengthOf());

    ASSERT_EQ(4.0f, res->getScalar(0));
    ASSERT_EQ(6.0f, res->getScalar(1));
}

TEST_F(NDArrayTest, TestSumAlongDimension2) {
    float *c = new float[4] {1, 2, 3, 4};
    auto *array = new NDArray<float>(c, cShape);

    auto *res = array->sum({1});

    ASSERT_EQ(2, res->lengthOf());

    ASSERT_EQ(3.0f, res->getScalar(0));
    ASSERT_EQ(7.0f, res->getScalar(1));
}

TEST_F(NDArrayTest, TestReduceAlongDimension1) {
    float *c = new float[4] {1, 2, 3, 4};
    auto *array = new NDArray<float>(c, cShape);

    auto *exp = array->sum({1});
    auto *res = array->reduceAlongDimension<simdOps::Sum<float>>({1});



    ASSERT_EQ(2, res->lengthOf());

    ASSERT_EQ(3.0f, res->getScalar(0));
    ASSERT_EQ(7.0f, res->getScalar(1));

}


TEST_F(NDArrayTest, TestTransform1) {
    float *c = new float[4] {-1, -2, -3, -4};
    auto *array = new NDArray<float>(c, cShape);

    float *e = new float[4] {1, 2, 3, 4};
    auto *exp = new NDArray<float>(e, cShape);

    array->applyTransform<simdOps::Abs<float>>();

    ASSERT_TRUE(exp->equalsTo(array));
}

TEST_F(NDArrayTest, TestReduceScalar1) {
    float *c = new float[4] {-1, -2, -3, -4};
    auto *array = new NDArray<float>(c, cShape);

    ASSERT_EQ(-4, array->reduceNumber<simdOps::Min<float>>(nullptr));
}
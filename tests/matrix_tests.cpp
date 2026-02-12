
#include <gtest/gtest.h>
#include "matrix.hpp"
#include "utils.hpp"

class TestMatrix : public ::testing::Test {
protected:
    using matrix_ft = matrix::Matrix<double>;
    using matrix_it = matrix::Matrix<int>;

    double eps_ = matrix::epsilon<double>();

    bool feq(double val1, double val2) {
        return std::abs(val2 - val1) < eps_;
    }

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestMatrix, DefaultInitSizeVal) {
    matrix_ft m (2, 1.3);
    ASSERT_TRUE(m[0][0] == 1.3);
    ASSERT_TRUE(m[0][1] == 1.3);
    ASSERT_THROW(m[0][2], std::out_of_range);

    ASSERT_TRUE(m[1][0] == 1.3);
    ASSERT_TRUE(m[1][1] == 1.3);
    ASSERT_THROW(m[2][0], std::out_of_range);
}

TEST_F(TestMatrix, DefaultInitRowWColVal) {
    matrix_ft m (2, 3, 1.3);
    ASSERT_TRUE(m[0][0] == 1.3);
    ASSERT_TRUE(m[0][1] == 1.3);
    ASSERT_TRUE(m[0][2] == 1.3);
    ASSERT_THROW(m[0][3], std::out_of_range);

    ASSERT_TRUE(m[1][0] == 1.3);
    ASSERT_TRUE(m[1][1] == 1.3);
    ASSERT_TRUE(m[1][2] == 1.3);
    ASSERT_THROW(m[1][3], std::out_of_range);

    ASSERT_THROW(m[2][0], std::out_of_range);
}

TEST_F(TestMatrix, DefaultInitInitializerList) {
    matrix_ft m {{1, 2, 3}, {4, 5, 6}};

    ASSERT_TRUE(m[0][0] == 1);
    ASSERT_TRUE(m[0][1] == 2);
    ASSERT_TRUE(m[0][2] == 3);
    ASSERT_THROW(m[0][3], std::out_of_range);

    ASSERT_TRUE(m[1][0] == 4);
    ASSERT_TRUE(m[1][1] == 5);
    ASSERT_TRUE(m[1][2] == 6);
    ASSERT_THROW(m[1][3], std::out_of_range);

    ASSERT_THROW(m[2][0], std::out_of_range);
}

TEST_F(TestMatrix, NonSymmetricMatrixDeterminant) {
    matrix_it mi {{1, 2, 3}, {4, 5, 6}};
    ASSERT_THROW(mi.determinant(), std::runtime_error);

    mi = matrix_it{{1, 2}, {3, 4}, {5, 6}};
    ASSERT_THROW(mi.determinant(), std::runtime_error);

    mi = matrix_it{{1}, {2}, {3}, {4}};
    ASSERT_THROW(mi.determinant(), std::runtime_error);

    mi = matrix_it{{1, 2, 3, 4}};
    ASSERT_THROW(mi.determinant(), std::runtime_error);


    matrix_ft mf {{1.1, 2.1, 3.1}, {4.1, 5.1, 6.1}};
    ASSERT_THROW(mf.determinant(), std::runtime_error);

    mf = matrix_ft{{1.1, 2.1}, {3.1, 4.1}, {5.1, 6.1}};
    ASSERT_THROW(mf.determinant(), std::runtime_error);

    mf = matrix_ft{{1.1}, {2.1}, {3.1}, {4.1}};
    ASSERT_THROW(mf.determinant(), std::runtime_error);

    mf = matrix_ft{{1.1, 2.1, 3.1, 4.1}};
    ASSERT_THROW(mf.determinant(), std::runtime_error);
}

TEST_F(TestMatrix, IntegralDeterminant1x1) {
    matrix_it m {{1}};
    ASSERT_TRUE(m.determinant() == 1);

    m = matrix_it {{0}};
    ASSERT_TRUE(m.determinant() == 0);
}

TEST_F(TestMatrix, IntegralDeterminant2x2) {
    matrix_it m {{1, 2}, {3, 4}};
    ASSERT_TRUE(m.determinant() == -2);

    m = matrix_it {{1, 2}, {0, 4}};
    ASSERT_TRUE(m.determinant() == 4);

    m = matrix_it {{0, 2}, {0, 4}};
    ASSERT_TRUE(m.determinant() == 0);

    m = matrix_it {{0, 0}, {0, 0}};
    ASSERT_TRUE(m.determinant() == 0);

    m = matrix_it {{0, 0}, {3, 4}};
    ASSERT_TRUE(m.determinant() == 0);
}

TEST_F(TestMatrix, IntegralDeterminant3x3) {
    matrix_it m {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    ASSERT_TRUE(m.determinant() == 0);

    m = matrix_it {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    ASSERT_TRUE(m.determinant() == -3);

    m = matrix_it {{1, 0, 3}, {4, 0, 6}, {0, 8, 10}};
    ASSERT_TRUE(m.determinant() == 48);

    m = matrix_it {{0, 0, 0}, {4, 5, 6}, {7, 8, 9}};
    ASSERT_TRUE(m.determinant() == 0);

    m = matrix_it {{1, 0, 3}, {4, 0, 6}, {7, 0, 9}};
    ASSERT_TRUE(m.determinant() == 0);
}

TEST_F(TestMatrix, IntegralDeterminant5x5) {
    matrix_it m {
        {1, 2, 0, 2, 1},
        {2, 1, 1, 1, 2},
        {1, 3, 2, 1, 2},
        {3, 2, 1, 1, 2},
        {2, 2, 1, 2, 1}
    };
    ASSERT_TRUE(m.determinant() == -12);

    m = matrix_it {
        {1, 2, 3, 4, 5},
        {0, 2, 3, 4, 5}, 
        {0, 0, 3, 4, 5},
        {0, 0, 0, 4, 5}, 
        {0, 0, 0, 0, 5}, 
     };
    ASSERT_TRUE(m.determinant() == 120);

    m = matrix_it {
        {1, 2, 0, 4, 5},
        {6, 7, 0, 9, 10}, 
        {11, 12, 0, 14, 15},
        {16, 17, 0, 19, 20}, 
        {21, 22, 0, 24, 25}, 
     };
    ASSERT_TRUE(m.determinant() == 0);

    m = matrix_it {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10}, 
        {11, 12, 13, 14, 15},
        {0, 0, 0, 0, 0}, 
        {21, 22, 23, 24, 25}, 
     };
    ASSERT_TRUE(m.determinant() == 0);
}


TEST_F(TestMatrix, FloatingDeterminant1x1) {
    matrix_ft m {{1.5}};
    ASSERT_TRUE(feq(m.determinant(), 1.5));

    m = matrix_ft {{0.3}};
    ASSERT_TRUE(feq(m.determinant(), 0.3));
}

TEST_F(TestMatrix, FloatingDeterminant2x2) {
    matrix_ft m {{1.2, 2.5}, {3.5, 4.1}};
    ASSERT_TRUE(feq(m.determinant(), -3.83));

    m = matrix_ft {{1.7, 2.0}, {-0.0, 4.3}};
    ASSERT_TRUE(feq(m.determinant(), 7.31));

    m = matrix_ft {{0.01, 2.2}, {0, 4.5}};
    ASSERT_TRUE(feq(m.determinant(), 0.045));

    m = matrix_ft {{0.0, 2.2}, {0, 4.5}};
    ASSERT_TRUE(feq(m.determinant(), 0));

    m = matrix_ft {{0.0, 0.0}, {0.0, -0.0}};
    ASSERT_TRUE(feq(m.determinant(), 0));

    m = matrix_ft {{0.0, 0.0}, {3.2, 4.9}};
    ASSERT_TRUE(feq(m.determinant(), 0));
}

TEST_F(TestMatrix, FloatingDeterminant3x3) {
    matrix_ft m {{1.2, 2.3, 3.4}, {4.0, 5.4, 6.5}, {7.1, 8.5, 9.2}};
    std::cout << m.determinant() << '\n';
    ASSERT_TRUE(feq(m.determinant(), 0.065));

    m = matrix_ft {{1.1, 2.1, 3.1}, {4.4, 5.2, 6.7}, {7.1, 8.2, 10.1}};
    ASSERT_TRUE(feq(m.determinant(), 1.307));

    m = matrix_ft {{1.1, 0.0, 3.3}, {4.4, 0.0, 6.6}, {0.0, 8.2, 10.1}};
    ASSERT_TRUE(feq(m.determinant(), 59.532));

    m = matrix_ft {{0.0, 0.0, 0.001}, {4.1, 5.2, 6.3}, {7.4, 8.5, 9.6}};
    ASSERT_TRUE(feq(m.determinant(), -0.00363));

    m = matrix_ft {{0.0, 0.0, 0.0}, {4.1, 5.2, 6.3}, {7.4, 8.5, 9.6}};
    ASSERT_TRUE(feq(m.determinant(), 0));

    m = matrix_ft {{1.2, 0.0, 3.3}, {4.1, 0.0001, 6.4}, {7.2, 0, 9.3}};
    ASSERT_TRUE(feq(m.determinant(), -0.00126));

    m = matrix_ft {{1.2, 0.0, 3.3}, {4.1, 0, 6.4}, {7.2, 0, 9.3}};
    ASSERT_TRUE(feq(m.determinant(), 0));
}

TEST_F(TestMatrix, FloatingDeterminant5x5) {
    matrix_ft m {
        {1.2, 2.1, 0, 2.5, 1.3},
        {2.4, 1.1, 1.2, 1.4, 2.7},
        {1.8, 3.1, 2.2, 1.3, 2.2},
        {3.4, 2.1, 1.3, 1.4, 2.5},
        {2.3, 2.3, 1.3, 2.5, 1.7}
    };
    ASSERT_TRUE(feq(m.determinant(), -14.82351));

    m = matrix_ft {
        {1.1, 2, 3, 4, 5},
        {0, 2.2, 3, 4, 5}, 
        {0, 0, 3.3, 4, 5},
        {0, 0, 0, 4.4, 5}, 
        {0, 0, 0, 0, 5.5}, 
     };
    ASSERT_TRUE(feq(m.determinant(), 193.2612));

    m = matrix_ft {
        {1.2, 2.1, 0, 2.5, 1.3},
        {2.4, 1.1, 0, 1.4, 2.7},
        {1.8, 3.1, 0, 1.3, 2.2},
        {3.4, 2.1, 0.0001, 1.4, 2.5},
        {2.3, 2.3, 0, 2.5, 1.7}
    };
    std::cout << m.determinant() << '\n';
    ASSERT_TRUE(feq(m.determinant(), 0.00078059));

    m = matrix_ft {
        {1.2, 2.1, 0, 2.5, 1.3},
        {2.4, 1.1, 0, 1.4, 2.7},
        {1.8, 3.1, 0, 1.3, 2.2},
        {3.4, 2.1, 0, 1.4, 2.5},
        {2.3, 2.3, 0, 2.5, 1.7}
    };
    ASSERT_TRUE(feq(m.determinant(), 0));

    m = matrix_ft {
        {1.2, 2.1, 0, 2.5, 1.3},
        {122.4, 21.1, 71.2, 1.4, 2.7},
        {1.8, 3.1, 2.2, 1.3, 2.2},
        {21, 22.4, 21.3, 51.4, 32.5},
        {0, 0, 0, 0, 0}
    };
    ASSERT_TRUE(feq(m.determinant(), 0));
}
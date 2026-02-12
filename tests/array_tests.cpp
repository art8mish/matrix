
#include "array.hpp"
#include <gtest/gtest.h>
#include <vector>

class TestArray : public ::testing::Test {
protected:
    using array_t = matrix::Array<double>;

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestArray, DefaultInitSizeVal) {
    array_t arr(3, 1.3);
    ASSERT_TRUE(arr[0] == 1.3);
    ASSERT_TRUE(arr[1] == 1.3);
    ASSERT_TRUE(arr[2] == 1.3);
    ASSERT_THROW(arr[3], std::out_of_range);
}

TEST_F(TestArray, DefaultInitIterator) {
    std::vector<double> vec{1.1, 2.2, 3.3};
    array_t arr(vec.begin(), vec.end());

    ASSERT_TRUE(arr[0] == 1.1);
    ASSERT_TRUE(arr[1] == 2.2);
    ASSERT_TRUE(arr[2] == 3.3);
    ASSERT_THROW(arr[3], std::out_of_range);
}

TEST_F(TestArray, DefaultInitInitializerList) {
    array_t arr{1.1, 2.2, 3.3};

    ASSERT_TRUE(arr[0] == 1.1);
    ASSERT_TRUE(arr[1] == 2.2);
    ASSERT_TRUE(arr[2] == 3.3);
    ASSERT_THROW(arr[3], std::out_of_range);
}

TEST_F(TestArray, Eq) {
    array_t arr1{1, 2, 3};
    array_t arr2 = arr1;

    ASSERT_TRUE(arr1 == arr2);
    ASSERT_TRUE(arr2 == arr1);

    array_t arr3{1, 2, 3};
    ASSERT_TRUE(arr1 == arr3);
    ASSERT_TRUE(arr2 == arr3);

    array_t arr_not_eq{1, 2, 0};
    ASSERT_TRUE(arr_not_eq != arr1);
    ASSERT_TRUE(arr_not_eq != arr2);
    ASSERT_TRUE(arr_not_eq != arr3);

    array_t arr_err1{1, 2};
    ASSERT_THROW(arr1 == arr_err1, std::invalid_argument);

    array_t arr_err2{1, 2, 3, 4};
    ASSERT_THROW(arr1 == arr_err2, std::invalid_argument);
}

TEST_F(TestArray, AddAssign) {
    array_t arr1{1, 2, 3};
    array_t arr2{4, 2, 3};

    arr1 += arr2;
    ASSERT_TRUE(arr1[0] == 5);
    ASSERT_TRUE(arr1[1] == 4);
    ASSERT_TRUE(arr1[2] == 6);

    arr2 += arr1;
    ASSERT_TRUE(arr2[0] == 9);
    ASSERT_TRUE(arr2[1] == 6);
    ASSERT_TRUE(arr2[2] == 9);

    array_t arr_err1{4, 2};
    ASSERT_THROW(arr1 += arr_err1, std::invalid_argument);

    array_t arr_err2{4, 2, 3, 4};
    ASSERT_THROW(arr1 += arr_err2, std::invalid_argument);
}

TEST_F(TestArray, Add) {
    array_t arr1{1, 2, 3};
    array_t arr2{4, 2, 3};

    array_t arr3 = arr1 + arr2;
    ASSERT_TRUE(arr3[0] == 5);
    ASSERT_TRUE(arr3[1] == 4);
    ASSERT_TRUE(arr3[2] == 6);

    array_t arr4 = arr2 + arr1;
    ASSERT_TRUE(arr3 == arr4);

    array_t arr_err1{4, 2};
    ASSERT_THROW(arr1 + arr_err1, std::invalid_argument);

    array_t arr_err2{4, 2, 3, 4};
    ASSERT_THROW(arr1 + arr_err2, std::invalid_argument);
}

TEST_F(TestArray, SubAssign) {
    array_t arr1{4, 2, 3};
    array_t arr2{1, 2, 1};

    arr1 -= arr2;
    ASSERT_TRUE(arr1[0] == 3);
    ASSERT_TRUE(arr1[1] == 0);
    ASSERT_TRUE(arr1[2] == 2);

    arr2 -= arr1;
    ASSERT_TRUE(arr2[0] == -2);
    ASSERT_TRUE(arr2[1] == 2);
    ASSERT_TRUE(arr2[2] == -1);

    array_t arr_err1{4, 2};
    ASSERT_THROW(arr1 -= arr_err1, std::invalid_argument);

    array_t arr_err2{4, 2, 3, 4};
    ASSERT_THROW(arr1 -= arr_err2, std::invalid_argument);
}

TEST_F(TestArray, Sub) {
    array_t arr1{4, 2, 3};
    array_t arr2{1, 2, 1};

    array_t arr3 = arr1 - arr2;
    ASSERT_TRUE(arr3[0] == 3);
    ASSERT_TRUE(arr3[1] == 0);
    ASSERT_TRUE(arr3[2] == 2);

    array_t arr4 = arr2 - arr1;
    ASSERT_TRUE(arr4[0] == -3);
    ASSERT_TRUE(arr4[1] == 0);
    ASSERT_TRUE(arr4[2] == -2);

    array_t arr_err1{4, 2};
    ASSERT_THROW(arr1 - arr_err1, std::invalid_argument);

    array_t arr_err2{4, 2, 3, 4};
    ASSERT_THROW(arr1 - arr_err2, std::invalid_argument);
}

TEST_F(TestArray, MulAssign) {
    array_t arr{1, 2, 3};
    double val = 5.5;

    arr *= val;
    ASSERT_TRUE(arr[0] == 5.5);
    ASSERT_TRUE(arr[1] == 11);
    ASSERT_TRUE(arr[2] == 16.5);

    arr *= 0;
    ASSERT_TRUE(arr[0] == 0);
    ASSERT_TRUE(arr[1] == 0);
    ASSERT_TRUE(arr[2] == 00);
}

TEST_F(TestArray, Mul) {
    array_t arr1{1, 2, 3};
    double val = 5.5;

    array_t arr2 = arr1 * val;
    ASSERT_TRUE(arr2[0] == 5.5);
    ASSERT_TRUE(arr2[1] == 11);
    ASSERT_TRUE(arr2[2] == 16.5);

    array_t arr3 = val * arr1;
    ASSERT_TRUE(arr3 == arr2);
}

// TEST_F(TestArray, DivAssign) {
//     array_t arr {9, 7, 4};
//     double val = 2;

//     arr /= val;
//     ASSERT_TRUE(arr[0] == 4.5);
//     ASSERT_TRUE(arr[1] == 3.5);
//     ASSERT_TRUE(arr[2] == 2);
// }

// TEST_F(TestArray, Div) {
//     array_t arr1 {9, 7, 4};
//     double val = 2;

//     array_t arr2 = arr1 / val;
//     ASSERT_TRUE(arr2[0] == 4.5);
//     ASSERT_TRUE(arr2[1] == 3.5);
//     ASSERT_TRUE(arr2[2] == 2);
// }

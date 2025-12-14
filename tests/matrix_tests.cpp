
#include <gtest/gtest.h>

class TestMatrix : public ::testing::Test {
protected:
    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestMatrix, Default1) {
    ASSERT_TRUE(true);
}

TEST_F(TestMatrix, Default2) {
    ASSERT_TRUE(true);
}
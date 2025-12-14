
#include <gtest/gtest.h>

class TestMatrix : public ::testing::Test {
protected:
    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestMatrix, Default) {
    ASSERT_TRUE(true);
}
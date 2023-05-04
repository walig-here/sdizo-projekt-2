#include "gtest/gtest.h"

// Sprawdzenie działania funkcji swap
TEST(Test, dummy){

    ASSERT_TRUE(true);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

//
// Created by Don Goodman-Wilson on 01/06/2017.
//

#include <gtest/gtest.h>

class Environment :
        public ::testing::Environment
{
public:
    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::AddGlobalTestEnvironment(new Environment());

    return RUN_ALL_TESTS();
}

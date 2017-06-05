//
// Created by Don Goodman-Wilson on 03/06/2017.
//

#include <gtest/gtest.h>
#include <chancypolyhedra/chancypolyhedra.h>

TEST(distributions, smoketest)
{
    double accum{0.0};
    long throws{1000};
    std::string expr{"1"};
    for(auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }
    ASSERT_EQ(accum / throws, 1.0);
}


TEST(distributions, 1d6)
{
    double accum{0.0};
    long throws{10000};
    std::string expr{"1d6"};
    for(auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }
    auto mean = accum / throws;
    auto delta = 0.1;
    ASSERT_GE(mean, 3.5-delta);
    ASSERT_LE(mean, 3.5+delta);
}

TEST(distributions, 2d6)
{
    double accum{0.0};
    long throws{10000};
    std::string expr{"2d6"};
    for(auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }

    auto expected_mean = 7.0;
    auto delta = 0.1;
    auto mean = accum / throws;

    ASSERT_GE(mean, expected_mean-delta);
    ASSERT_LE(mean, expected_mean+delta);
}

TEST(basic_functioning, d2pow3)
{
//same as rolling a d8
    double accum{0.0};
    long throws{10000};
    std::string expr{"d2**3"};
    for(auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }

    auto expected_mean = 4.5;
    auto delta = 0.1;
    auto mean = accum / throws;

    ASSERT_GE(mean, expected_mean-delta);
    ASSERT_LE(mean, expected_mean+delta);
}
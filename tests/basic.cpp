//
// Created by Don Goodman-Wilson on 01/06/2017.
//

#include <gtest/gtest.h>
#include <chancypolyhedra/chancypolyhedra.h>

TEST(basic_functioning, smoketest_1)
{
    auto result = chancypolyhedra::roll("1");
    ASSERT_EQ(result, 1);
}

TEST(basic_functioning, smoketest_2)
{
    auto result = chancypolyhedra::roll("1d1");
    ASSERT_EQ(result, 1);
}

TEST(basic_functioning, negatives_1)
{
    auto result = chancypolyhedra::roll("-1d1");
    ASSERT_EQ(result, -1);
}

TEST(basic_functioning, negatives_2)
{
    auto result = chancypolyhedra::roll("1d-1");
    ASSERT_EQ(result, -1);
}

TEST(basic_functioning, negatives_3)
{
    auto result = chancypolyhedra::roll("-1d-1");
    ASSERT_EQ(result, 1);
}


TEST(basic_functioning, unary_1)
{
    auto result = chancypolyhedra::roll("d1");
    ASSERT_EQ(result, 1);
}

TEST(basic_functioning, powers_1)
{
    auto result = chancypolyhedra::roll("2**3");
    ASSERT_EQ(result, 8);
}
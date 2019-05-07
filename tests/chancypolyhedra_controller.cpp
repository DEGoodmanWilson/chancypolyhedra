//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include <catch2/catch.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "env.hpp"

TEST_CASE("smoketest 1")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(1 == obj["result"]);
}

TEST_CASE("smoketest 2")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/1d1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(1 == obj["result"]);
}

TEST_CASE("negatives 1")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/-1d1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(-1 == obj["result"]);
}

TEST_CASE("negatives 2")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/1d-1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(-1 == obj["result"]);
}

TEST_CASE("negatives 3")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/-1d-1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(1 == obj["result"]);
}


TEST_CASE("unary 1")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/d1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(1 == obj["result"]);
}

TEST_CASE("powers 1")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/2**3"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(8 == obj["result"]);
}

/******/

#include "../chancypolyhedra/chancypolyhedra.hpp"

TEST_CASE("distributions, smoketest")
{
    double accum{0.0};
    const long throws{10000};
    std::string expr{"1"};

    int successes;
    for (auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }

    REQUIRE(1.0 == accum / throws);
}


TEST_CASE("distributions, 1d6")
{
    double accum{0.0};
    const long throws{10000};
    std::string expr{"1d6"};
    for (auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }

    auto mean = accum / throws;
    auto delta = 0.1;
    REQUIRE(mean >= 3.5 - delta);
    REQUIRE(mean <= 3.5 + delta);
}

TEST_CASE("distributions, 2d6")
{
    double accum{0.0};
    const long throws{10000};
    std::string expr{"2d6"};
    for (auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }


    auto expected_mean = 7.0;
    auto delta = 0.1;
    auto mean = accum / throws;

    REQUIRE(mean >= expected_mean - delta);
    REQUIRE(mean <= expected_mean + delta);
}

TEST_CASE("distributions, d2pow3")
{
//same as rolling a d8
    double accum{0.0};
    const long throws{10000};
    std::string expr{"d2**3"};
    for (auto i = 0; i < throws; ++i)
    {
        accum += chancypolyhedra::roll(expr);
    }


    auto expected_mean = 4.5;
    auto delta = 0.1;
    auto mean = accum / throws;

    REQUIRE(mean >= expected_mean - delta);
    REQUIRE(mean <= expected_mean + delta);
}
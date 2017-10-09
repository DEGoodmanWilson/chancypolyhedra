//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include <catch.hpp>
#include <cpr/cpr.h>
#include <json.hpp>
#include "env.hpp"

TEST_CASE("webserver basic functioning")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/1"});
    REQUIRE(result.status_code == 200);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(obj["ok"] == true);
    REQUIRE(obj["expression"] == "1");
    REQUIRE(obj["result"] == 1);
}

TEST_CASE("webserver basic failure")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/a"});
    REQUIRE(result.status_code == 400);
    auto obj = nlohmann::json::parse(result.text);
    REQUIRE(obj["ok"] == false);
    REQUIRE(obj["expression"] == "a");
    REQUIRE(obj["message"] == "Malformed dice expression.");
}

TEST_CASE("webserver 404")
{
    auto result = cpr::Get(cpr::Url{hostname + "/"});
    REQUIRE(result.status_code == 404);
}
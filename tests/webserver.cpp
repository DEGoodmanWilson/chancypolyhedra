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

TEST_CASE("webserver headers")
{
    auto result = cpr::Get(cpr::Url{hostname + "/v1/1"});
    REQUIRE(result.status_code == 200);
    REQUIRE(result.header.at("Strict-Transport-Security") == "max-age=31536000");
    REQUIRE(result.header.at("X-XSS-Protection") == "1");
    REQUIRE(result.header.at("Content-Security-Policy") == "default-src 'self'");
}
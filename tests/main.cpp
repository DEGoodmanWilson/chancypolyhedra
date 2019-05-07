//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

std::string hostname{"http://localhost"};

int main( int argc, char* argv[] )
{
    if (auto port = std::getenv("PORT"))
    {
        hostname = hostname + ":" + port;
    }
    else
    {
        hostname = hostname + ":8080";
    }

    int result = Catch::Session().run( argc, argv );

    return ( result < 0xff ? result : 0xff );
}
//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include <iostream>
#include <luna/luna.h>
#include <json.hpp>
#include "logger.hpp"
#include "controllers/chancypolyhedra_controller.hpp"

int main()
{
    // set up the loggers
    luna::set_access_logger(access_logger);
    luna::set_error_logger(error_logger);

    // determine which port to run on, default to 8080
    auto port = 8080;
    if (auto port_str = std::getenv("PORT"))
    {
        try
        {
            port = std::atoi(port_str);
        }
        catch (const std::invalid_argument &e)
        {
            error_logger(luna::log_level::FATAL, "Invalid port specified in env $PORT.");
            return 1;
        }
        catch (const std::out_of_range &e)
        {
            error_logger(luna::log_level::FATAL, "Port specified in env $PORT is too large.");
            return 1;
        }
    }


    // add endpoints
    luna::router api;

    // Here is an endpoint handled by a controller class, in controllers/chancypolyhedra_controller.hpp
    chancypolyhedra_controller.add(api);

    // launch server
    luna::server server;

    server.add_router(api);

    if(!server.start(port))
    {
        return 1;
    }



    return 0;
}
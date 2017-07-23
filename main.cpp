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
#include "app.hpp"
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

    // launch server
    auto ok = app::launch(port);
    if(!ok)
    {
        return 1;
    }

    // add endpoints

    // Here is an endpoint handled by a controller class, in controllers/chancypolyhedra_controller.hpp
    app::add_route("/v1", chancypolyhedra_controller);

    // Here is an endpoint for serving static assets not being managed by vue
    app::add_route("/assets", "assets");


    // Here is an endpoint for serving static files. Any request to "/foobar.html" will look in the folder "assets" for a file called "foobar.html"
    app::add_route("/", "frontend/dist");

    // yield to server
    app::await();

    return 0;
}
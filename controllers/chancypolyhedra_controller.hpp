//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include <luna/luna.h>
#include <json.hpp>
#include "../chancypolyhedra/chancypolyhedra.hpp"
#include "controller.hpp"

#pragma once

controller chancypolyhedra_controller{
        luna::request_method::GET,
        R"(/(.*))",
        [](const luna::request &request) -> luna::response
        {
            try
            {
                auto result = chancypolyhedra::roll(request.matches[1]);
                return {200, nlohmann::json{{"ok",         true},
                                            {"expression", request.matches[1]},
                                            {"result",     result}}.dump()};
            }
            catch (std::runtime_error e)
            {
                error_logger(luna::log_level::INFO, "Malformed dice expression.");
                return {400, nlohmann::json{{"ok",         false},
                                            {"expression", request.matches[1]},
                                            {"message",    "Malformed dice expression."}}.dump()};
            }
        }
};
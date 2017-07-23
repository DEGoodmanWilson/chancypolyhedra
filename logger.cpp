//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include "logger.hpp"

// Keep it simple for now
#include <iostream>

void error_logger(luna::log_level level, const std::string &message)
{
    switch (level)
    {
//        case luna::log_level::DEBUG:
//            std::cerr << "[  DEBUG] " << message << std::endl;
//            break;
        case luna::log_level::INFO:
            std::cerr << "[   INFO] " << message << std::endl;;
            break;
        case luna::log_level::WARNING:
            std::cerr << "[WARNING] " << message << std::endl;;
            break;
        case luna::log_level::ERROR:
            std::cerr << "[  ERROR] " << message << std::endl;;
            break;
        case luna::log_level::FATAL:
            std::cerr << "[  FATAL] " << message << std::endl;;
            break;
    }
}

void access_logger(const luna::request &request, const luna::response &response)
{
    std::cout << request.ip_address << ": " << luna::to_string(request.method) << " [" << response.status_code << "] "
              << request.path << " " << request.http_version << " " << request.headers.at("user-agent") << std::endl;
}
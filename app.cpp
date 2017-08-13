//    ________                           ____        __      __             __
//   / ____/ /_  ____ _____  _______  __/ __ \____  / /_  __/ /_  ___  ____/ /________ _
//  / /   / __ \/ __ `/ __ \/ ___/ / / / /_/ / __ \/ / / / / __ \/ _ \/ __  / ___/ __ `/
// / /___/ / / / /_/ / / / / /__/ /_/ / ____/ /_/ / / /_/ / / / /  __/ /_/ / /  / /_/ /
// \____/_/ /_/\__,_/_/ /_/\___/\__, /_/    \____/_/\__, /_/ /_/\___/\__,_/_/   \__,_/
//                             /____/              /____/
//
// Copyright © 2017 D.E. Goodman-Wilson
//

#include <unistd.h>
#include <luna/luna.h>
#include <json.hpp>
#include "logger.hpp"
#include "app.hpp"

namespace app
{

static std::unique_ptr<luna::server> server;

bool launch(int port)
{
    server = std::make_unique<luna::server>(luna::server::port{port}, luna::server::use_thread_per_connection{true});

    if(!server)
    {
        error_logger(luna::log_level::FATAL, "Failed to allocate webserver.");
        return false;
    }

    if (!static_cast<bool>(*server))
    {
        error_logger(luna::log_level::FATAL, "Failed to stand up webserver.");
        return false;
    }

    // Add security headers
    server->add_global_header("Strict-Transport-Security", "max-age=31536000");
    server->add_global_header("X-XSS-Protection", "1");
    server->add_global_header("X-Frame-Options", "DENY");
    server->add_global_header("X-Content-Type-Options", "nosniff");
    server->add_global_header("Content-Security-Policy", "style-src https://fonts.google-apis.com https://fonts.googleapis.com 'self'; font-src https://fonts.gstatic.com; script-src 'self' 'unsafe-eval'; default-src 'self'; report-uri http://localhost:8080/csp");

    server->handle_request(luna::request_method::POST, "/csp", [](const luna::request &request) -> luna::response
    {
        std::cout << request.body << std::endl;
        return {200};
    });

    return true;
}


void add_route(std::string &&base, const controller& controller)
{
    if(!server) return;

    base += controller.path;

    if(base[base.size()-1] == '/')
    {
        base = base.substr(0, base.size()-1);
    }

    server->handle_request(controller.method, std::regex{base}, controller.handler);
}

std::string get_path_to_serve_files_from()
{
    std::string cwd{getcwd(nullptr, 0)};
    if (auto asset_path = std::getenv("STATIC_ASSET_PATH"))
    {
        cwd = asset_path;
    }
    if(cwd[cwd.size()-1] != '/')
    {
        cwd += "/";
    }
    return cwd;
}

void add_route(std::string &&base, std::string &&folder)
{
    // we require a trailing '/' for the filesystem folder containing our static assets
    if(base[base.size()-1] != '/')
    {
        base += "/"; // TODO this needs to be fixed in Luna itself.
    }

    // we presuppose that this is being run from the folder that contains the static assets to serve
    static std::string cwd{get_path_to_serve_files_from()};

    std::cout << cwd+folder << std::endl;

    server->serve_files(std::move(base), cwd+folder);
}

void await()
{
    server->await();
}

} // namespace app
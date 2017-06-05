#include <iostream>
#include <luna/luna.h>
#include <chancypolyhedra/chancypolyhedra.h>
#include <json.hpp>
#define ELPP_LOGGING_FLAGS_FROM_ARG
#define ELPP_STACKTRACE_ON_CRASH
#define ELPP_THREAD_SAFE
#define ELPP_FORCE_USE_STD_THREAD
#include <easylogging++.h>
INITIALIZE_EASYLOGGINGPP

void luna_logger(luna::log_level level, const std::string &message)
{
    switch(level)
    {
        case luna::log_level::DEBUG:
            LOG(DEBUG) << message;
            break;
        case luna::log_level::INFO:
            LOG(INFO) << message;
            break;
        case luna::log_level::WARNING:
            LOG(WARNING) << message;
            break;
        case luna::log_level::ERROR:
            LOG(ERROR) << message;
            break;
        case luna::log_level::FATAL:
            LOG(FATAL) << message;
            break;
    }
}

/****** ******/

int main(void)
{
    luna::set_logger(luna_logger);

    uint16_t port = 8080;
    if (auto port_str = std::getenv("PORT"))
    {
        port = atoi(port_str);
    }

    luna::server server{luna::server::port{port}, luna::server::use_epoll_if_available{true}};

    if (!server)
    {
        LOG(FATAL) << "Failed to stand up webserver!";
        return -1;
    }

    server.handle_request(luna::request_method::GET, R"(/v1/(.*))", [](auto & req) -> luna::response {
        try
        {
            auto result = chancypolyhedra::roll(req.matches[1]);
            return {200, nlohmann::json{ {"ok", true}, {"expression", req.matches[1]}, {"result", result} }.dump() };
        }
        catch(std::runtime_error e)
        {
            luna_logger(luna::log_level::INFO, "Malformed dice expression.");
            return {400, nlohmann::json{ {"ok", false}, {"expression", req.matches[1]}, {"message", "Malformed dice expression."} }.dump() };
        }

    });

    LOG(INFO) << "Server started on port " << std::to_string(server.get_port());

    server.await();

    return 0;
}
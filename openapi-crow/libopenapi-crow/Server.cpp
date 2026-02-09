#include "Server.hpp"

#include "route/Docs.hpp"
#include "route/OpenapiJson.hpp"

using namespace openapi;

Server::Server(spec::Info info, int port, const std::string_view host)
    : info(info)
    , port(port)
    , host(host)
{
    addRoute(std::make_shared<route::OpenapiJson>(*this));
    addRoute(std::make_shared<route::Docs>("/docs", *this));
    addRoute(std::make_shared<route::Docs>("/api-docs", *this));
}

void Server::addRoute(const std::shared_ptr<route::Base>& route)
{
    routes.push_back(route);
    app.route_dynamic(route->getPath()).methods(route->getMethod())(
        [route](const crow::request& req) {
            return (*route)(req);
        });
}

void Server::setDescription(const std::string_view description)
{
    this->description = description;
}

void Server::run()
{
    std::cout << "Starting " << info.title << " server on port " << port << "..." << std::endl;

    app.port(port)
        .multithreaded()
        .server_name(info.title + " v" + info.version)
        .run();
}

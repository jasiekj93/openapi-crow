#pragma once

/**
 * @file Server.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <memory>
#include <string>
#include <vector>
#include <optional>

#include <crow.h>

#include <libopenapi-crow/route/Base.hpp>
#include <libopenapi-crow/spec/Info.hpp>

namespace openapi
{
    class Server
    {
    public:
        Server(spec::Info, int port = 18080, const std::string_view host = "localhost");

        void addRoute(const std::shared_ptr<route::Base>& route);
        void setDescription(const std::string_view description); 
        void run();

        inline auto getPort() const { return port; }
        inline auto& getHost() const { return host; }

        inline const auto& getRoutes() const { return routes; }
        inline const auto& getInfo() const { return info; }
        inline const auto& getDescription() const { return description; }

    private:
        crow::SimpleApp app;
        std::vector<std::shared_ptr<route::Base>> routes;

        int port;
        std::string host;
        std::optional<std::string> description;
        spec::Info info;
    };
}
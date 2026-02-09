#pragma once

/**
 * @file OpenapiJson.hpp
 * @author Adrian Szczepanski
 * @date 09-02-2026
 */

#include <libopenapi-crow/route/Base.hpp>
#include <libopenapi-crow/Server.hpp>

namespace openapi::route 
{
    class OpenapiJson : public Base
    {
    public:
        explicit OpenapiJson(Server&); 

        crow::response operator()(const crow::request&) const override;
        crow::HTTPMethod getMethod() const override { return crow::HTTPMethod::GET; }

    protected:
        std::string getSpecification() const; 
        void addInfo(crow::json::wvalue& spec) const;
        void addServers(crow::json::wvalue& spec) const;
        void addPaths(crow::json::wvalue& spec) const;
        void addGetPath(crow::json::wvalue& specification, const std::shared_ptr<Base>&) const;
        void addPostPath(crow::json::wvalue& specification, const std::shared_ptr<Base>&) const;

    private:
        Server& server;
    };
}
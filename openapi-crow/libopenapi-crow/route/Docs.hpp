#pragma once

/**
 * @file Docs.hpp
 * @author Adrian Szczepanski
 * @date 09-02-2026
 */

#include <libopenapi-crow/route/Base.hpp>
#include <libopenapi-crow/Server.hpp>

namespace openapi::route 
{
    class Docs : public Base
    {
    public:
        Docs(std::string_view path, Server& server); 

        crow::response operator()(const crow::request&) const override;
        crow::HTTPMethod getMethod() const override { return crow::HTTPMethod::GET; }

    protected:
        std::string getBody() const; 

    private:
        Server& server;
    };
}
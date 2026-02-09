#pragma once

/**
 * @file Post.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>

#include <libopenapi-crow/spec/Post.hpp>
#include <libopenapi-crow/route/Base.hpp>

namespace openapi::route 
{
    class Post : public Base
    {
    public:
        explicit Post(std::string_view path) : Base(path) {}
        virtual ~Post() = default;

        virtual crow::response operator()(const crow::request&) const = 0;
        crow::HTTPMethod getMethod() const override { return crow::HTTPMethod::POST; }

        virtual spec::Post getSpecification() const = 0;
        virtual crow::json::wvalue getSchema(std::string_view name) const = 0;
    };
}
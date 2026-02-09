#pragma once

/**
 * @file Get.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>

#include <libopenapi-crow/spec/Get.hpp>
#include <libopenapi-crow/route/Base.hpp>

namespace openapi::route 
{
    class Get : public Base
    {
    public:
        explicit Get(std::string_view path) : Base(path) {}
        virtual ~Get() = default;

        virtual crow::response operator()(const crow::request&) const = 0;
        crow::HTTPMethod getMethod() const override { return crow::HTTPMethod::GET; }

        virtual spec::Get getSpecification() const = 0;
        virtual crow::json::wvalue getSchema(std::string_view name) const = 0;
    };
}
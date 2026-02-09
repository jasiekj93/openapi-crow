#pragma once

/**
 * @file Base.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>

#include <crow.h>

namespace openapi::route 
{
    class Base
    {
    public:
        explicit Base(std::string_view path) : path(path) {}
        virtual ~Base() = default;

        virtual crow::response operator()(const crow::request&) const = 0;
        virtual crow::HTTPMethod getMethod() const = 0;

        inline const auto& getPath() const { return path; }

    private:
        const std::string path;
    };
}
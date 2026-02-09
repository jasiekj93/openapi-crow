#pragma once

/**
 * @file Get.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>
#include <optional>

#include <libopenapi-crow/spec/Response.hpp>

namespace openapi::spec 
{
    struct Get 
    {
        std::string summary;
        std::string description;
        std::optional<Responses> responses;
    };
}
#pragma once

/**
 * @file Post.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>
#include <optional>

#include <libopenapi-crow/spec/Response.hpp>

namespace openapi::spec 
{
    struct RequestBody
    {
        bool isRequired;
        std::optional<std::string> contentSchema;
    };

    struct Post 
    {
        std::string summary;
        std::string description;
        std::optional<RequestBody> requestBody;
        std::optional<Responses> responses;
    };
}
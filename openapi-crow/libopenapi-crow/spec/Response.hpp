#pragma once

/**
 * @file Response.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>
#include <optional>
#include <vector>

namespace openapi::spec 
{
    struct Response
    {
        int code;
        std::string description;
        std::optional<std::string> contentSchema;
    };

    using Responses = std::vector<Response>;
}
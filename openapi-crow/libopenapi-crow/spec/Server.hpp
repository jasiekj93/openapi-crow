#pragma once

#include <string>
#include <optional>
#include <vector>

namespace openapi::spec 
{
    struct Server 
    {
        std::string url;
        std::optional<std::string> description;
    };
}
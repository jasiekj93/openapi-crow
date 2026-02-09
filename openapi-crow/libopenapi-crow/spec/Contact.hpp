#pragma once

/**
 * @file Contact.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>
#include <optional>

namespace openapi::spec 
{
    struct Contact
    {
        std::string name;
        std::optional<std::string> url;
        std::optional<std::string> email;
    };
}
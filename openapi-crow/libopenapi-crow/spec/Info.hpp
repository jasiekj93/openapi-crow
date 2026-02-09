#pragma once

/**
 * @file Info.hpp
 * @author Adrian Szczepanski
 * @date 06-02-2026
 */

#include <string>
#include <optional>

#include <libopenapi-crow/spec/Contact.hpp>

namespace openapi::spec 
{
    struct Info
    {
        std::string title;
        std::string version;
        std::optional<std::string> description;
        std::optional<Contact> contact;
    };
}
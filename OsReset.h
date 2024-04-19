//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     OsReset data = nlohmann::json::parse(jsonString);

#pragma once

#include "json.hpp"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>

namespace quicktype {
    using nlohmann::json;

#ifndef NLOHMANN_UNTYPED_quicktype_HELPER
#define NLOHMANN_UNTYPED_quicktype_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
#endif

    class OsReset {
    public:
        OsReset() = default;
        virtual ~OsReset() = default;

    private:
        std::string command_type;
        bool force;

    public:
        const std::string & get_command_type() const { return command_type; }
        std::string & get_mutable_command_type() { return command_type; }
        void set_command_type(const std::string & value) { this->command_type = value; }

        const bool & get_force() const { return force; }
        bool & get_mutable_force() { return force; }
        void set_force(const bool & value) { this->force = value; }
    };
}

namespace quicktype {
    void from_json(const json & j, OsReset & x);
    void to_json(json & j, const OsReset & x);

    inline void reset_from_json(const json & j, OsReset& x) {
        x.set_command_type(j.at("commandType").get<std::string>());
        x.set_force(j.at("force").get<bool>());
    }

    inline void reset_to_json(json & j, const OsReset & x) {
        j = json::object();
        j["commandType"] = x.get_command_type();
        j["force"] = x.get_force();
    }
}

//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Connect data = nlohmann::json::parse(jsonString);

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

    class Connect {
    public:
        Connect() = default;
        virtual ~Connect() = default;

    private:
        std::string command_type;
        std::string address;

    public:
        const std::string & get_command_type() const { return command_type; }
        std::string & get_mutable_command_type() { return command_type; }
        void set_command_type(const std::string & value) { this->command_type = value; }

        const std::string & get_address() const { return address; }
        std::string & get_mutable_address() { return address; }
        void set_address(const std::string & value) { this->address = value; }
    };
}

namespace quicktype {
    void connect_from_json(const json & j, Connect & x);
    void connect_to_json(json & j, const Connect & x);

    inline void connect_from_json(const json & j, Connect& x) {
        x.set_command_type(j.at("commandType").get<std::string>());
        x.set_address(j.at("address").get<std::string>());
    }

    inline void connect_to_json(json & j, const Connect & x) {
        j = json::object();
        j["commandType"] = x.get_command_type();
        j["address"] = x.get_address();
    }
}

//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Connect data = nlohmann::json::parse(jsonString);
//     Connected data = nlohmann::json::parse(jsonString);
//     DeviceDiscovered data = nlohmann::json::parse(jsonString);
//     Disconnect data = nlohmann::json::parse(jsonString);
//     Disconnected data = nlohmann::json::parse(jsonString);
//     GetImages data = nlohmann::json::parse(jsonString);
//     Reset data = nlohmann::json::parse(jsonString);
//     ResetCompleted data = nlohmann::json::parse(jsonString);
//     ServiceDiscovered data = nlohmann::json::parse(jsonString);
//     ServiceDiscoveryFinished data = nlohmann::json::parse(jsonString);

#pragma once

#include "json.hpp"

#include <optional>
#include <stdexcept>
#include <regex>

namespace qtmcumgr {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_qtmcumgr_HELPER
    #define NLOHMANN_UNTYPED_qtmcumgr_HELPER
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

    class GetImages {
        public:
        GetImages() = default;
        virtual ~GetImages() = default;

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

    class ServiceDiscoveryFinished {
        public:
        ServiceDiscoveryFinished() = default;
        virtual ~ServiceDiscoveryFinished() = default;

        private:
        std::string event_type;
        std::string address;

        public:
        const std::string & get_event_type() const { return event_type; }
        std::string & get_mutable_event_type() { return event_type; }
        void set_event_type(const std::string & value) { this->event_type = value; }

        const std::string & get_address() const { return address; }
        std::string & get_mutable_address() { return address; }
        void set_address(const std::string & value) { this->address = value; }
    };

    class DeviceDiscovered {
        public:
        DeviceDiscovered() = default;
        virtual ~DeviceDiscovered() = default;

        private:
        std::string event_type;
        std::string address;
        std::string name;
        bool cached;
        bool valid;
        int64_t rssi;
        std::string major_device_class;
        int64_t minor_device_class;

        public:
        const std::string & get_event_type() const { return event_type; }
        std::string & get_mutable_event_type() { return event_type; }
        void set_event_type(const std::string & value) { this->event_type = value; }

        const std::string & get_address() const { return address; }
        std::string & get_mutable_address() { return address; }
        void set_address(const std::string & value) { this->address = value; }

        const std::string & get_name() const { return name; }
        std::string & get_mutable_name() { return name; }
        void set_name(const std::string & value) { this->name = value; }

        const bool & get_cached() const { return cached; }
        bool & get_mutable_cached() { return cached; }
        void set_cached(const bool & value) { this->cached = value; }

        const bool & get_valid() const { return valid; }
        bool & get_mutable_valid() { return valid; }
        void set_valid(const bool & value) { this->valid = value; }

        const int64_t & get_rssi() const { return rssi; }
        int64_t & get_mutable_rssi() { return rssi; }
        void set_rssi(const int64_t & value) { this->rssi = value; }

        const std::string & get_major_device_class() const { return major_device_class; }
        std::string & get_mutable_major_device_class() { return major_device_class; }
        void set_major_device_class(const std::string & value) { this->major_device_class = value; }

        const int64_t & get_minor_device_class() const { return minor_device_class; }
        int64_t & get_mutable_minor_device_class() { return minor_device_class; }
        void set_minor_device_class(const int64_t & value) { this->minor_device_class = value; }
    };

    class Reset {
        public:
        Reset() = default;
        virtual ~Reset() = default;

        private:
        std::string command_type;
        std::string address;
        bool force;

        public:
        const std::string & get_command_type() const { return command_type; }
        std::string & get_mutable_command_type() { return command_type; }
        void set_command_type(const std::string & value) { this->command_type = value; }

        const std::string & get_address() const { return address; }
        std::string & get_mutable_address() { return address; }
        void set_address(const std::string & value) { this->address = value; }

        const bool & get_force() const { return force; }
        bool & get_mutable_force() { return force; }
        void set_force(const bool & value) { this->force = value; }
    };

    class ServiceDiscovered {
        public:
        ServiceDiscovered() = default;
        virtual ~ServiceDiscovered() = default;

        private:
        std::string event_type;
        std::string address;
        std::string service;
        std::string service_description;

        public:
        const std::string & get_event_type() const { return event_type; }
        std::string & get_mutable_event_type() { return event_type; }
        void set_event_type(const std::string & value) { this->event_type = value; }

        const std::string & get_address() const { return address; }
        std::string & get_mutable_address() { return address; }
        void set_address(const std::string & value) { this->address = value; }

        const std::string & get_service() const { return service; }
        std::string & get_mutable_service() { return service; }
        void set_service(const std::string & value) { this->service = value; }

        const std::string & get_service_description() const { return service_description; }
        std::string & get_mutable_service_description() { return service_description; }
        void set_service_description(const std::string & value) { this->service_description = value; }
    };
}

namespace qtmcumgr {
    void from_json(const json & j, GetImages & x);
    void to_json(json & j, const GetImages & x);

    void from_json(const json & j, ServiceDiscoveryFinished & x);
    void to_json(json & j, const ServiceDiscoveryFinished & x);

    void from_json(const json & j, DeviceDiscovered & x);
    void to_json(json & j, const DeviceDiscovered & x);

    void from_json(const json & j, Reset & x);
    void to_json(json & j, const Reset & x);

    void from_json(const json & j, ServiceDiscovered & x);
    void to_json(json & j, const ServiceDiscovered & x);

    inline void from_json(const json & j, GetImages& x) {
        x.set_command_type(j.at("commandType").get<std::string>());
        x.set_address(j.at("address").get<std::string>());
    }

    inline void to_json(json & j, const GetImages & x) {
        j = json::object();
        j["commandType"] = x.get_command_type();
        j["address"] = x.get_address();
    }

    inline void from_json(const json & j, ServiceDiscoveryFinished& x) {
        x.set_event_type(j.at("eventType").get<std::string>());
        x.set_address(j.at("address").get<std::string>());
    }

    inline void to_json(json & j, const ServiceDiscoveryFinished & x) {
        j = json::object();
        j["eventType"] = x.get_event_type();
        j["address"] = x.get_address();
    }

    inline void from_json(const json & j, DeviceDiscovered& x) {
        x.set_event_type(j.at("eventType").get<std::string>());
        x.set_address(j.at("address").get<std::string>());
        x.set_name(j.at("name").get<std::string>());
        x.set_cached(j.at("cached").get<bool>());
        x.set_valid(j.at("valid").get<bool>());
        x.set_rssi(j.at("rssi").get<int64_t>());
        x.set_major_device_class(j.at("majorDeviceClass").get<std::string>());
        x.set_minor_device_class(j.at("minorDeviceClass").get<int64_t>());
    }

    inline void to_json(json & j, const DeviceDiscovered & x) {
        j = json::object();
        j["eventType"] = x.get_event_type();
        j["address"] = x.get_address();
        j["name"] = x.get_name();
        j["cached"] = x.get_cached();
        j["valid"] = x.get_valid();
        j["rssi"] = x.get_rssi();
        j["majorDeviceClass"] = x.get_major_device_class();
        j["minorDeviceClass"] = x.get_minor_device_class();
    }

    inline void from_json(const json & j, Reset& x) {
        x.set_command_type(j.at("commandType").get<std::string>());
        x.set_address(j.at("address").get<std::string>());
        x.set_force(j.at("force").get<bool>());
    }

    inline void to_json(json & j, const Reset & x) {
        j = json::object();
        j["commandType"] = x.get_command_type();
        j["address"] = x.get_address();
        j["force"] = x.get_force();
    }

    inline void from_json(const json & j, ServiceDiscovered& x) {
        x.set_event_type(j.at("eventType").get<std::string>());
        x.set_address(j.at("address").get<std::string>());
        x.set_service(j.at("service").get<std::string>());
        x.set_service_description(j.at("serviceDescription").get<std::string>());
    }

    inline void to_json(json & j, const ServiceDiscovered & x) {
        j = json::object();
        j["eventType"] = x.get_event_type();
        j["address"] = x.get_address();
        j["service"] = x.get_service();
        j["serviceDescription"] = x.get_service_description();
    }
}

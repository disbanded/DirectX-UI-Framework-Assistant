#include "json.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace json_manager {
    void save(const std::string& file_name, const assistant::config_store& config) {
        json j; // stores values into the json
        j["button_amount"] = config.button_amount;
        j["slider_amount"] = config.slider_amount;
        j["has_checkbox"] = config.has_checkbox;
        j["button_labels"] = config.button_labels;

        std::ofstream file(file_name);
		file << j.dump(4); // writes formatted json

        printf("[+] layout saved to %s\n", file_name.c_str());
    }

    assistant::config_store load(const std::string& file_name) {
        assistant::config_store config;

        std::ifstream file(file_name);
		if (!file.is_open()) { // checks if file opened/existing
            printf("[-] could not open %s\n", file_name.c_str());
            return config;
        }

        json j;
		file >> j; // load json

        config.button_amount = j["button_amount"];
        config.slider_amount = j["slider_amount"];
        config.has_checkbox = j["has_checkbox"];
        config.button_labels = j["button_labels"].get<std::vector<std::string>>(); // load the button labels in vector

        printf("[+] layout loaded from %s\n", file_name.c_str());

        return config;
    }
}
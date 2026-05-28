#pragma once
#include <string>
#include "../assistant/assistant.h"

namespace json_manager {
    void save(const std::string& file_name, const assistant::config_store& config);
    assistant::config_store load(const std::string& file_name);
}
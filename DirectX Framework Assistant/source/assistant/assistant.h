#pragma once
#include <vector>
#include <string>

namespace assistant {
    struct config_store { // struct for config data layout
        int button_amount = 0;
        int slider_amount = 0;
        bool has_checkbox = false;
        std::vector<std::string> button_labels;
    };

    config_store generate_layout();
}
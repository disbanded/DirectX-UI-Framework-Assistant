#include "assistant.h"
#include "../utility/json.h"
#include <cstdio>

// potential improvement: in future add multiple checkboxes not just one

namespace assistant {
    config_store generate_layout() {
        config_store config; //  user layout selection

        printf("[UI Assistant]\n");
        printf("--------------\n");
        printf("load an existing layout? (1 = yes, 0 = no): ");

        int load_choice = 0;
        scanf_s("%d", &load_choice);

        if (load_choice == 1) { // if user wants to preload/load a previous layout then load from json file
            return json_manager::load("layout.json");
        }

        printf("how many buttons do you want? ");
        scanf_s("%d", &config.button_amount);

        for (int i = 0; i < config.button_amount; i++) {
            char label[64];
            printf("enter label for button (%d): ", i + 1);
            scanf_s("%s", label, (unsigned)sizeof(label));
            config.button_labels.push_back(std::string(label)); // stores button labels in config for saving
        }

        printf("how many sliders do you want? ");
        scanf_s("%d", &config.slider_amount);

        int cb = 0;
        printf("add a checkbox? (1 = yes, 0 = no): ");
        scanf_s("%d", &cb);
		config.has_checkbox = cb == 1; // basically if they say yes set checkbox to true for saving in json

        printf("save this layout? (1 = yes, 0 = no): ");
        int save_choice = 0;
        scanf_s("%d", &save_choice);

		if (save_choice == 1) // stores layout in json for loading
            json_manager::save("layout.json", config);

        printf("\n[+] generating layout..\n\n");

		return config; // returns config with layout data for ui to use
    }
}
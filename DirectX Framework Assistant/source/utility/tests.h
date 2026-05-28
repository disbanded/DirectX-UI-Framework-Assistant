#pragma once
#include <cassert>
#include <cstdio>
#include "../assistant/assistant.h"
#include "json.h"

namespace unit_test {
    inline void test_json_save_load() {
        assistant::config_store cfg;
        cfg.button_amount = 2;
        cfg.slider_amount = 1;
        cfg.has_checkbox = true;
        cfg.button_labels = { "hello", "world" };

        json_manager::save("test_layout.json", cfg);

        assistant::config_store load = json_manager::load("test_layout.json");
        assert(load.button_amount == 2);
        assert(load.slider_amount == 1);
        assert(load.has_checkbox == true);
        printf("[+] json save/load test passed!\n");
    }

    inline void test_button_amount() {
        assistant::config_store cfg;
        cfg.button_amount = 3;
        assert(cfg.button_amount == 3);

        printf("[+] button count test passed!\n");
    }

    inline void test_label_store() {
        assistant::config_store cfg;
		cfg.button_labels.push_back("test");
        assert(cfg.button_labels[0] == "test");

        printf("[+] button label test passed!\n");
    }

    inline void test_multiple_buttons() {
        assistant::config_store cfg;
		const char* labels[] = { "1", "2", "3" };

		for (int i = 0; i < std::size(labels); i++) {
			cfg.button_labels.push_back(labels[i]);
		}

		assert(cfg.button_labels.size() == 3); // checks label count

		for (int i = 0; i < std::size(labels); i++) {
			assert(cfg.button_labels[i] == labels[i]);
		}

        printf("[+] multiple button label test passed!\n");
    }

    inline void test_checkbox() {
        bool val = false;
        val = !val;
        assert(val == true);
		val = !val;
        assert(val == false);

        printf("[+] checkbox toggling test passed!\n");
    }

    inline void run_tests() {
        printf("\n[+] unit tests [+]\n\n[+] running unit tests\n\n");
        test_json_save_load();
		test_button_amount();
        test_label_store();
        test_multiple_buttons();
        test_checkbox(); // runs all tests

        printf("[+] all tests were successfully passed\n\n--------------\n");
    }
}
#include "ui.h"
#include "../ui/widgets/panel/panel.h"

namespace ui {
    int user_interface::init(assistant::config_store config) {
		if (!create_window() || !renderer.init(window)) // checks if render init + window creation were successful
            return -1;

		context = new ui::draw::draw_list(&renderer); // create draw list context

        if (!context) {
            renderer.shutdown();
            return -1;
        }

        ShowWindow(window, SW_SHOW);
		UpdateWindow(window); // display window

        msg(config); // starts msg loop

        delete context;
		context = nullptr; // cleanup the draw_list

		renderer.shutdown();
        return 0;
    }

    bool user_interface::create_window() {
        WNDCLASSEXA window_class = {};
        window_class.cbSize = sizeof(WNDCLASSEXA);
        window_class.style = CS_HREDRAW | CS_VREDRAW;
		window_class.lpfnWndProc = wnd_proc; // window procedure for handling messages/events
        window_class.hInstance = GetModuleHandleA(nullptr);
        window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
        window_class.lpszClassName = "window_class";

        if (!RegisterClassExA(&window_class))
            return false;

        window = CreateWindowExA(0, window_class.lpszClassName, "user interface", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
            500, 350, nullptr, nullptr, window_class.hInstance, nullptr);

        if (!window) // checks if window was created
            return false;

        printf("[+] window created\n");

        return window != nullptr;
    }

    void user_interface::msg(assistant::config_store config) {
        MSG message = {};

        while (message.message != WM_QUIT) { // runs app til closed

            if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) { 
                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            else {
				renderer.begin(); // begin rendering

                static bool enabled = false;
				static float values[8] = { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f }; // slider values

                static ui::widgets::panel main_panel(20.0f, 20.0f, 200.0f, 250.0f);

                static bool created = false; // create widgets once

                if (!created) {
                    for (int i = 0; i < config.button_amount; i++) { // add buttons from config
                        const char* label = i < config.button_labels.size() ?
                            config.button_labels[i].c_str() : "our label";
                        main_panel.add_button(label);
                    }

                    for (int i = 0; i < config.slider_amount; i++) // add sliders from config
                        main_panel.add_slider("slider", 0.0f, 100.0f, &values[i]);

                    if (config.has_checkbox) // add checkbox from config
                        main_panel.add_checkbox("enabled", &enabled);

					created = true;
                }

				main_panel.draw(draw(), window); // draws panel and widgets

				renderer.end(); // finish rendering
            }
        }
    }

    ui::draw::draw_list* user_interface::draw() {
        return context; // return draw context
    }

    LRESULT CALLBACK user_interface::wnd_proc(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
        switch (message) {
        case WM_DESTROY: // closes app
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProcA(window, message, w_param, l_param); 
    }
}
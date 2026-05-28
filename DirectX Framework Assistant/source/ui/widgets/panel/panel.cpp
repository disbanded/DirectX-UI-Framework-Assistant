#include "panel.h"

// future idea is to calc widgets heights dynamically for better positioning

namespace ui::widgets {
	panel::panel(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) { // constructor to init panel
		position_y = y + padding; // beginning widget pos
	}

	void panel::add_checkbox(const char* label, bool* value) { // add checkbox
		checkboxes.emplace_back(label, x + padding, position_y, value);
		position_y += 22.0f + padding; // move for next widget
	}

	void panel::add_slider(const char* label, float minimum, float maximum, float* value) { // add slider
		sliders.emplace_back(label, x + padding, position_y, minimum, maximum, value);
		position_y += 22.0f + padding;
	}

	void panel::add_button(const char* label) { // add button
		buttons.emplace_back(label, x + padding, position_y, (w / 1.75) - padding * 2.0f, 28.0f);
		position_y += 22.0f + padding;
	}

	void panel::draw(::ui::draw::draw_list* draw_list, HWND window) {
		static bool border = true; // border for now

		if (border) {
			draw_list->rectangle_filled(x, y, w, h, renderer::border_colour);
			draw_list->rectangle_filled(x + 1, y + 1, w - 2, h - 2, renderer::colour(25, 25, 25, 255));
		}

		if (!border) // if no border just draw the panel background
			draw_list->rectangle_filled(x, y, w, h, renderer::colour(25, 25, 25, 255));

		for (auto& checkbox : checkboxes) // draw checkboxes
			checkbox.draw(draw_list, window);

		for (auto& slider : sliders) // draw sliders
			slider.draw(draw_list, window);

		for (auto& button : buttons) { // draw buttons
			if (button.draw(draw_list, window)) { 
				printf("[+] panel button clicked\n");
			}
		}
	}
}
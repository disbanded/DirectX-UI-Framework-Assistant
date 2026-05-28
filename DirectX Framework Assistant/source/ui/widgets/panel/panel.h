#pragma once
#include <windows.h>
#include "../../draw/draw_list.h"
#include "../button/button.h"
#include "../checkbox/checkbox.h"
#include "../slider/slider.h"
#include <vector>

namespace ui::widgets {
	class panel {
	public:
		panel(float x, float y, float w, float h); // constructor to init panel

		void add_checkbox(const char* label, bool* value); // widgets for panel
		void add_slider(const char* label, float minimum, float maximum, float* value);
		void add_button(const char* label);

		void draw(::ui::draw::draw_list* draw_list, HWND window); // to draw our panel and child widgets

	private:
		float x = 0.0f; // panel position and dimensions
		float y = 0.0f;
		float w = 0.0f;
		float h = 0.0f;

		float padding = 10.0f;
		float position_y = 0.0f; // for next widget y position

		std::vector<checkbox> checkboxes;
		std::vector<slider> sliders;
		std::vector<button> buttons;
	};
}
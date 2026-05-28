#pragma once
#include <windows.h>
#include "../../draw/draw_list.h"

namespace ui::widgets {
	class slider {
	public:
		slider(const char* label, float x, float y, float minimum, float maximum, float* value); // slider and stored value + value range

		void draw(::ui::draw::draw_list* draw_list, HWND window); // pass draw list and window for input handling

	private:
		const char* label = nullptr;

		float x = 0.0f;
		float y = 0.0f;

		float w = 100.0f;
		float h = 5.0f;

		float minimum = 0.0f;
		float maximum = 100.0f;

		float* value = nullptr;

		bool dragging = false;
	};
}
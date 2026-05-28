#pragma once
#include <windows.h>
#include "../../draw/draw_list.h"

namespace ui::widgets {
	class checkbox {
	public:
		checkbox(const char* label, float x, float y, bool* value); // checkbox with a stored value

		bool draw(::ui::draw::draw_list* draw_list, HWND window); // pass draw list and window so can handle input

	private:
		const char* label = nullptr;

		float x, y; // checkbox pos + dimensions
		float w = 10.0f;
		float h = 10.0f;

		bool* value = nullptr;
		bool was_down = false; // mouse state for click detection
	};
}
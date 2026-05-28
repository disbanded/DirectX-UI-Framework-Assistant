#pragma once
#include <windows.h>
#include "../../draw/draw_list.h"

namespace ui::widgets {
	class button {
	public:
		button(const char* label, float x, float y, float w, float h); // button create

		bool draw(::ui::draw::draw_list* draw_list, HWND window); // button draw and input handling

	private:
		const char* label = nullptr;

		float x, y, w, h; // pos + dimensions
		bool was_down = false; // click detection
	};
}
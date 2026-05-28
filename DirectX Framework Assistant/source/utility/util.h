#pragma once
#include <Windows.h>

namespace util {
	struct vec2 {
		float x;
		float y;
	};

	inline vec2 mouse_position(HWND window) {
		POINT point;
		GetCursorPos(&point); // get mouse position
		ScreenToClient(window, &point); // converts to window coords
		return { static_cast<float>(point.x), static_cast<float>(point.y) }; // stores as vec2 for coords
	}

	inline bool is_hovering(HWND window, float x, float y, float w, float h) {
		vec2 mouse = mouse_position(window);

		return mouse.x >= x && // if mouse is within the bounds x, y, w, h
			mouse.x <= x + w &&
			mouse.y >= y &&
			mouse.y <= y + h;
	}

	inline bool is_mouse_down() {
		return GetAsyncKeyState(VK_LBUTTON) & 0x8000; // left click held
	}
}
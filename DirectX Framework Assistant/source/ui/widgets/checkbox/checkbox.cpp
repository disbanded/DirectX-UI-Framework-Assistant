#include "checkbox.h"
#include "../../../utility/util.h"

namespace ui::widgets {
	checkbox::checkbox(const char* label, float x, float y, bool* value) : label(label), x(x), y(y), value(value) {} // default constructor for checkbox

	bool checkbox::draw(::ui::draw::draw_list* draw_list, HWND window) {
		bool hovered = util::is_hovering(window, x, y, w, h); // checks if checkbox hovered
		bool mouse_down = util::is_mouse_down();

		renderer::colour colour = renderer::colour(30, 30, 30, 255); // default colour for checkbox

		if (hovered)
			colour = renderer::colour(35, 35, 35, 255); // change colour hovered

		if (hovered && mouse_down)
			colour = renderer::colour(45, 45, 45, 255); // change colour when clicked

		static bool border = true;

		if (border) { // draw border
			draw_list->rectangle_filled(x, y, w, h, renderer::border_colour);
			draw_list->rectangle_filled(x + 1, y + 1, w - 2, h - 2, colour);
		}

		if (!border) // draw no border
			draw_list->rectangle_filled(x, y, w, h, colour);

		if (label) // draw text label
			draw_list->text(label, x + w + 6.0f, y - 4, renderer::colour(255, 255, 255, 255));

		bool clicked = false;

		if (hovered && !mouse_down && was_down) // check for click release
			clicked = true;

		was_down = mouse_down;

		if (clicked && value) // checkbox toggle 
			*value = !*value;

		if (value && *value)
			draw_list->rectangle_filled(x + 1.0f, y + 1.0f, w - 2.0f, h - 2.0f, renderer::accent_colour); // draw indicator when active

		return clicked;
	}
}
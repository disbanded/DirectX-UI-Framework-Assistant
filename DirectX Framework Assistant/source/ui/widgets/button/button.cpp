#include "button.h"
#include "../../../utility/util.h"

namespace ui::widgets {
	button::button(const char* label, float x, float y, float w, float h) : label(label), x(x), y(y), w(w), h(h) { } // default construct for button

	bool button::draw(::ui::draw::draw_list* draw_list, HWND window) {
		bool hovered = util::is_hovering(window, x, y, w, h); // checks if mouse hovering button
		bool mouse_down = util::is_mouse_down();

		renderer::colour colour = renderer::colour(30, 30, 30, 255); // default button colour

		if (hovered)
			colour = renderer::colour(35, 35, 35, 255); // change colour if hovered

		if (hovered && mouse_down)
			colour = renderer::colour(45, 45, 45, 255); // if clicked colour

		static bool border = true;

		if (border) {
			draw_list->rectangle_filled(x, y, w, h, renderer::border_colour);
			draw_list->rectangle_filled(x + 1, y + 1, w - 2, h - 2, colour); // draw our rect with border
		}

		if (!border)
			draw_list->rectangle_filled(x, y, w, h, colour);

		if (label)
			draw_list->text(label, x + 8.0f, y + (h / 2) - 8.0f, renderer::colour(255, 255, 255, 255));

		bool clicked = false;

		if (hovered && !mouse_down && was_down) // check for click release
			clicked = true;

		was_down = mouse_down;

		return clicked;
	}
}
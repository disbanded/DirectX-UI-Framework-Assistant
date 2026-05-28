#include "slider.h"
#include "../../../utility/util.h"

namespace ui::widgets {
	slider::slider(const char* label, float x, float y, float minimum, float maximum, float* value) : x(x), y(y), minimum(minimum), maximum(maximum), value(value), label(label) { } // slider constructor

    void slider::draw(::ui::draw::draw_list* draw_list, HWND window) {
        if (!value) // failsafe prevents crash from nullptr
            return;

        util::vec2 mouse = util::mouse_position(window); // gather mouse position from window

        float bar_y = y + 16.0f;

		bool hovered = util::is_hovering(window, x, bar_y - 4.0f, w, h + 8.0f); // bigger hover area for better usability
        bool mouse_down = util::is_mouse_down();

        if (hovered && mouse_down) // start dragging
            dragging = true;

        if (!mouse_down) // stop dragging
            dragging = false;

		if (dragging) { // update slider value while dragging
            float mouse_percent = (mouse.x - x) / w;

            if (mouse_percent < 0.0f) mouse_percent = 0.0f;
            if (mouse_percent > 1.0f) mouse_percent = 1.0f;

			*value = minimum + ((maximum - minimum) * mouse_percent); // calc slider value from the mouse pos
        }

		float percent = (*value - minimum) / (maximum - minimum); // calculate percent of slider filled from value, min, max

        if (percent < 0.0f)
            percent = 0.0f; // failsafe clamp so no out of bounds

        if (percent > 1.0f)
            percent = 1.0f;

        float fill_width = w * percent;

        bool border = true; // exists for future modifications

        if (border) {
            draw_list->rectangle_filled(x, bar_y, w, h, renderer::border_colour);
            draw_list->rectangle_filled(x + 1, bar_y + 1, w - 2, h - 2, renderer::colour(35, 35, 35, 255));
        }

		draw_list->rectangle_filled(x, bar_y, fill_width, h, renderer::accent_colour); // draw slider fill based on percent

        if (label)
            draw_list->text(label, x, y, renderer::colour(255, 255, 255, 255));

        if (value) {
            char val_buf[32]; // buffer to hold our value as text
            snprintf(val_buf, sizeof(val_buf), "%.0f", *value);
			draw_list->text(val_buf, x + w + 5.0f, bar_y - 7.0f, renderer::colour(255, 255, 255, 255)); // draws value next to slider
        }
    }
}
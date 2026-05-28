#include "draw_list.h"

namespace ui::draw {

	draw_list::draw_list(renderer::renderer* renderer) : renderer(renderer) { } // points to renderer for drawing functions

    void draw_list::rectangle_filled(float x, float y, float w, float h, renderer::colour colour) { // rectangle filled wrapper
        renderer->draw_rectangle(x, y, w, h, colour);
    }

	void draw_list::text(const char* text, float x, float y, renderer::colour col) { // text draw wrapper
        renderer->draw_text(text, x, y, col);
    }
}
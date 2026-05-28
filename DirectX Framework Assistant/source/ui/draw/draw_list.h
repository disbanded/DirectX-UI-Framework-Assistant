#pragma once
#include "../../renderer/renderer.h"

namespace ui {

    namespace draw {

        class draw_list {
        public:
            draw_list(renderer::renderer* renderer); // create draw list with renderer

            void rectangle_filled(float x, float y, float w, float h, renderer::colour); // draw filled rectangle
            void text(const char* text, float x, float y, renderer::colour col); // draw text

        private:
            renderer::renderer* renderer = nullptr; // used for drawing
        };

    }
}
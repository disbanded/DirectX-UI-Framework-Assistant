#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include "../includes.h"
#include "../colour.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

namespace renderer {
	class text_renderer {
	public:
		bool init(IDXGISwapChain* swap_chain); // init D2D + DirectWrite

		void begin(); // begin text renderer
		void end(); // end text renderer

		void draw_text(const char* text, float x, float y, colour colour); // draws text to screen

		void shutdown();

	private:
		ID2D1Factory* d2d_factory = nullptr;
		IDWriteFactory* write_factory = nullptr;

		ID2D1RenderTarget* render_target = nullptr;

		ID2D1SolidColorBrush* brush = nullptr;

		IDWriteTextFormat* text_format = nullptr;
	};
}
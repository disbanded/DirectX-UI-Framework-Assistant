#include "text_renderer.h"

namespace renderer {
	bool text_renderer::init(IDXGISwapChain* swap_chain) {
		if (!swap_chain)
			return false;

		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory); // create Direct2D factory

		if (FAILED(hr))
			return false;

		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&write_factory)); // create DirectWrite factory

		if (FAILED(hr))
			return false;

		hr = write_factory->CreateTextFormat(L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-us", &text_format); // create text format for drawing text, using Segoe UI

		if (FAILED(hr))
			return false;

		IDXGISurface* surface = nullptr;

		hr = swap_chain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(&surface)); // get back buffer surface from swap chain to draw on it

		if (FAILED(hr) || !surface)
			return false;

		D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, 
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

		hr = d2d_factory->CreateDxgiSurfaceRenderTarget(surface, &properties, &render_target); // create D2D render target from surface

		surface->Release();

		if (FAILED(hr))
			return false;

		hr = render_target->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1), &brush); // brush for drawing text which is white by default

		if (FAILED(hr))
			return false;

		return true;
	}

	void text_renderer::begin() { // start D2D text rendering
		if (render_target)
			render_target->BeginDraw();
	}

	void text_renderer::end() { // end D2D text rendering
		if (render_target)
			render_target->EndDraw();
	}

	void text_renderer::draw_text(const char* text, float x, float y, colour col) {
		if (!render_target || !brush || !text_format)
			return;

		wchar_t wide_text[256]; // for converting our characters to wide characters for DirectWrite, can be increased if necessary

		MultiByteToWideChar(CP_ACP, 0, text, -1, wide_text, 256);
		brush->SetColor(D2D1::ColorF(col.r, col.g, col.b, col.a)); // text colour set

		render_target->DrawTextW(wide_text,wcslen(wide_text), text_format, D2D1::RectF(x, y, x + 500.0f, y + 50.0f), brush); // draw the text
	}

	void text_renderer::shutdown() {
		if (brush) brush->Release();
		if (text_format) text_format->Release();
		if (render_target) render_target->Release();
		if (write_factory) write_factory->Release();
		if (d2d_factory) d2d_factory->Release(); // release all D2D and DirectWrite resources

		brush = nullptr;
		text_format = nullptr;
		render_target = nullptr;
		write_factory = nullptr;
		d2d_factory = nullptr;
	}
}
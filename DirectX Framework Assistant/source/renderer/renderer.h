#pragma once
#include "../includes.h"
#include <d3dcompiler.h>
#include "../colour.h"
#include "text_renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace renderer {
	struct vertex {
		float x, y, z; // pos + depth
		float r, g, b, a; // vertex colour
	};

	const static colour accent_colour = colour(255, 205, 255, 255); // menu colours
	const static colour border_colour = colour(40, 40, 40, 255);

	class renderer {
	public:
		bool init(HWND window);
		void shutdown();

		void begin();

		void draw_rectangle(float x, float y, float w, float h, colour colour);
		void draw_text(const char* text, float x, float y, colour col);

		void end();

	private:
		HWND window = nullptr; // our window handle for app

		ID3D11Device* device = nullptr; // our DirectX 11 objects
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swap_chain = nullptr;
		ID3D11RenderTargetView* render_target_view = nullptr;

		ID3D11Buffer* vertex_buffer = nullptr;
		ID3D11VertexShader* vertex_shader = nullptr;
		ID3D11PixelShader* pixel_shader = nullptr;
		ID3D11InputLayout* input_layout = nullptr;

		text_renderer text;
	};
}
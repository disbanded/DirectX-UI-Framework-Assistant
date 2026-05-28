#include "renderer.h"

namespace renderer {
	bool renderer::init(HWND window) {
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		
		swap_chain_desc.BufferCount = 1; // back buffer count for double buffering
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // colour formatting
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // so can actually render the back buffer
		swap_chain_desc.OutputWindow = window; // our window
		swap_chain_desc.SampleDesc.Count = 1; // dont want multi sampling
		swap_chain_desc.Windowed = true; // windowed mode, could set to false for fullscreen but would have to make buttons for closing and minimise since no styling on window

		HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0,
			D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain, &device, nullptr, &context); // device, swapchain, context creation, hardware accel for performance

		if (FAILED(hr)) // if failed cant render so return false
			return false;
		
		ID3D11Texture2D* back_buffer = nullptr;
		swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer); // gather back buffer

		if (!back_buffer) // cant render if fail so bye bye
			return false;

		this->window = window; // store our window

		printf("[+] back buffer ok\n");

		device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view); // create the render target
		back_buffer->Release(); // render target view is reference so dont need back buffer texture no more

		const char* shader_code = // simple vertex/pixel shader for widget rendering, future addition: add cool shaders in future for effects
			"struct VS_IN { float3 pos : POSITION; float4 col : COLOR; };"
			"struct PS_IN { float4 pos : SV_POSITION; float4 col : COLOR; };"
			"PS_IN vs_main(VS_IN input) {"
			"   PS_IN output;"
			"   output.pos = float4(input.pos, 1.0f);"
			"   output.col = input.col;"
			"   return output;"
			"}"
			"float4 ps_main(PS_IN input) : SV_TARGET {"
			"   return input.col;"
			"}";

		ID3DBlob* vs_blob = nullptr; // creating shaders and input layout
		ID3DBlob* ps_blob = nullptr;

		D3DCompile(shader_code, strlen(shader_code), nullptr, nullptr, nullptr, // compile vertex shader
			"vs_main", "vs_5_0", 0, 0, &vs_blob, nullptr);

		D3DCompile(shader_code, strlen(shader_code), nullptr, nullptr, nullptr, // compile pixel shader
			"ps_main", "ps_5_0", 0, 0, &ps_blob, nullptr);

		if (!vs_blob || !ps_blob) // if shaders still not compiled then cant render so return false
			return false;

		device->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vertex_shader); // create vertex and pixel shaders from blob data
		device->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &pixel_shader);

		D3D11_INPUT_ELEMENT_DESC layout[] = { // vertex layout
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		// create input layout
		device->CreateInputLayout(layout, 2, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout);

		D3D11_BUFFER_DESC buffer_desc = {}; // allows CPU writes and updated each frame
		buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		buffer_desc.ByteWidth = sizeof(vertex) * 6 * 1000;
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		device->CreateBuffer(&buffer_desc, nullptr, &vertex_buffer); // creates the vertex buffer

		vs_blob->Release();
		ps_blob->Release();

		if (!text.init(swap_chain)) // init D2D text renderer if fails return false
			return false;

		return true;
	}

	void renderer::begin() {
		float background_colour[4] = { 0.05f, 0.05f, 0.05f, 1.0f };

		context->OMSetRenderTargets(1, &render_target_view, nullptr); // setting render target to back buffer so we can draw
		context->ClearRenderTargetView(render_target_view, background_colour); // sets background for frame

		RECT rect;
		GetClientRect(window, &rect); // gather window dimensions for viewport

		D3D11_VIEWPORT viewport = {};
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(rect.right - rect.left);
		viewport.Height = static_cast<float>(rect.bottom - rect.top);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		context->RSSetViewports(1, &viewport); // viewports set to window dimensions

		text.begin(); // start text renderer
	}

	void renderer::end() {
		text.end();
		swap_chain->Present(1, 0); // show back buffer to screen, vsync toggled
	}

	void renderer::shutdown() { // cleanup resources objects, set pointers to nullptr for safety
		text.shutdown();

		if (input_layout) input_layout->Release();
		if (vertex_shader) vertex_shader->Release();
		if (pixel_shader) pixel_shader->Release();
		if (vertex_buffer) vertex_buffer->Release();

		input_layout = nullptr;
		vertex_shader = nullptr;
		pixel_shader = nullptr;
		vertex_buffer = nullptr;

		if (render_target_view) render_target_view->Release();
		if (swap_chain) swap_chain->Release();
		if (context) context->Release();
		if (device) device->Release();

		render_target_view = nullptr;
		swap_chain = nullptr;
		context = nullptr;
		device = nullptr;
	}

	void renderer::draw_rectangle(float x, float y, float w, float h, colour colour) { // our rectangle, most important
		RECT rect;
		GetClientRect(window, &rect);

		float screen_width = static_cast<float>(rect.right - rect.left); // needed data conversion from screen coords to normalised device coords for vertex shader
		float screen_height = static_cast<float>(rect.bottom - rect.top);

		float left = (x / screen_width) * 2.0f - 1.0f;
		float right = ((x + w) / screen_width) * 2.0f - 1.0f;
		float top = 1.0f - (y / screen_height) * 2.0f;
		float bottom = 1.0f - ((y + h) / screen_height) * 2.0f;

		vertex vertices[6] = {
			{ left,  top,    0.0f, colour.r, colour.g, colour.b, colour.a },
			{ right, top,    0.0f, colour.r, colour.g, colour.b, colour.a },
			{ left,  bottom, 0.0f, colour.r, colour.g, colour.b, colour.a },

			{ right, top,    0.0f, colour.r, colour.g, colour.b, colour.a },
			{ right, bottom, 0.0f, colour.r, colour.g, colour.b, colour.a },
			{ left,  bottom, 0.0f, colour.r, colour.g, colour.b, colour.a }
		}; // 2 overlapping traingles for our rectangle

		D3D11_MAPPED_SUBRESOURCE mapped = {};
		context->Map(vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
		memcpy(mapped.pData, vertices, sizeof(vertices));
		context->Unmap(vertex_buffer, 0); // update vertex buffer with our vertices for rectangle

		UINT stride = sizeof(vertex);
		UINT offset = 0;

		context->IASetInputLayout(input_layout);
		context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->VSSetShader(vertex_shader, nullptr, 0);
		context->PSSetShader(pixel_shader, nullptr, 0);

		context->Draw(6, 0); // draw the rectangle
	}

	void renderer::draw_text(const char* text, float x, float y, colour col) {
		this->text.draw_text(text, x, y, col);
	}
}
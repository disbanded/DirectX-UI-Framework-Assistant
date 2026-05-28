#include <windows.h>
#include "../renderer/renderer.h"
#include "draw/draw_list.h"
#include "../assistant/assistant.h"

namespace ui {
	class user_interface {
	public:
		int init(assistant::config_store config);
		ui::draw::draw_list* draw(); // draw list used for rendering the widgets

	private:
		bool create_window();
		void msg(assistant::config_store config); // the main window loop

		static LRESULT CALLBACK wnd_proc(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

		HWND window = nullptr;
		renderer::renderer renderer;

		ui::draw::draw_list* context = nullptr;
	};
}
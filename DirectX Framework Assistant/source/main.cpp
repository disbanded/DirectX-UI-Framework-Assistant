#include "ui/ui.h"

int main() {
	printf("[+] hello world\n");

	while (true) {

		if (GetAsyncKeyState(VK_DELETE) && 0x1) // kill switch
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return EXIT_SUCCESS;
}
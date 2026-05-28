#include "ui/ui.h"
#include "utility/tests.h"

int main() {
    printf("[+] debug | ui\n--------------\n");

	unit_test::run_tests(); // Runs unit tests, before real application launch

    auto config = assistant::generate_layout(); // Generate layout config thru UI Assistant

    ui::user_interface ui; // creates and init instance
    return ui.init(config);
}
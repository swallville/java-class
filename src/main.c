#include "menu.h"

int main(int argc, char *argv[]) {
    clearScreen();
    // Check if the first argument is the .class file's name exists
    if (argc > 1) {
        viewer(argv[1]);
    } else {
        viewer(NULL);
    }

    return 0;
}

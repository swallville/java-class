#include "menu.h"

int main(int argc, char *argv[]) {
    clearScreen();
    if (argc > 1) {
        menu(argv[1]);
    } else {
        menu(NULL);
    }
    return 0;
}

#include <genesis.h>
#include <resources.h>

int main() {

    // Main Loop.
    while(1) {
        // End of the frame.
        SYS_doVBlankProcess();
    }
    return 0;
}

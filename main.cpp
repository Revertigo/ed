#include <iostream>
#include "Editor.hpp"

#define FILE_PATH 1
using namespace std;

int main(int argc, char * argv[])
{
    switch (argc) {
        //No arguments
        case 1: {
            Editor().loop();
            break;
        }
        case 2: {
            Editor editor(argv[FILE_PATH]);
            editor.loop();
            break;
        }

        default: {
            cout << "Too many arguments, try again" << std::endl;
            break;
        }
    }

    return 0;
}

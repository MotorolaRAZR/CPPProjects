

#include <iostream>
#include <Windows.h>
#include <cctype>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

int startkey;
bool MacroEnabled = false;
string mode;

void lowerString(string& tolowerstring) {
    for (char& x : tolowerstring)
        x = tolower(x);
};

void dialogue() {
    cout << "If you want to use mouse buttons type below (mouse) next to 'KEYBINDS'. \nOr if you want to use a keyboard keybind type your keybind below.\n\nKEYBIND: ";
    string question;
    cin >> question;
    cout << question;
    lowerString(question);
    if (question == "mouse") {
        string mouseinput;
        cout << "Enter your preferred MouseButton: (Middle, M1, or M2): ";
        cin >> mouseinput;
		lowerString(mouseinput);
        if (mouseinput == "m1") {
            startkey = VK_XBUTTON1;
        }
        else if (mouseinput == "m2") {
            startkey = VK_XBUTTON2;
        }
        else if (mouseinput == "middlebutton") {
            startkey = VK_MBUTTON;
        };
    }
    else {
		
    }
    cout << "Do you want the macro to toggle or hold ? (toggle / hold) : ";
    cin >> mode;
}

bool isKeyPressed() {
    return GetAsyncKeyState(startkey) & 0x8000;
};

void onPress() {
    if (isKeyPressed()) {
        lowerString(mode);
        if (mode == "hold") {
            MacroEnabled = true;
        }
        else if (mode == "toggle") {
            MacroEnabled = !MacroEnabled;
        }
    };
};

void onRelease() {
    lowerString(mode);
        if (mode == "hold" && !isKeyPressed()) {
            MacroEnabled = false;
    }
}

void scrollup() {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = WHEEL_DELTA; // this will probably stay uncommented lol basically 1 notch up
    SendInput(1, &input, sizeof(INPUT));
};

void scrolldown() {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.mouseData = -WHEEL_DELTA;
    SendInput(1, &input, sizeof(INPUT));
};

void middlebutton() {
    INPUT input[2] = {0};
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
    SendInput(2, input, sizeof(INPUT));
};

void macroLogic() {
    middlebutton();
    Sleep(2);

    scrollup();
    Sleep(2);

    scrolldown();
    Sleep(2);

    middlebutton();
    Sleep(2);
}

/*
void stoptimer() {
    timeEndPeriod(1);
};*/

int main()
{
    dialogue();

    while (true) {
        if (isKeyPressed()) {
            timeBeginPeriod(1);
            macroLogic();
            timeEndPeriod(1);
        }
        Sleep(1);
    }
}
#include <Windows.h>

#pragma comment(lib, "user32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR args, int ncmdshow)
{
    MessageBox(NULL, "Hello, World", "Hello, World", MB_OK);

    return 0;
}
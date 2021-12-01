#include <Windows.h>

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc   = WindowProcedure;

    if(!RegisterClassW(&wc))
    {
        return -1;
    }

    CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }

}

/*** end of file ***/

/*
    References

    https://www.youtube.com/watch?v=8GCvZs55mEM&t=68s
*/
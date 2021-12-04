#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

#define OPEN_BUTTON 1

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Comdlg32.lib") // used for GetOpenFileName

/** Prototypes **/
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);

/** Gobal Variables **/
HWND    hMainWindow, hEdit;

/** Program Entry Point **/
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

    hMainWindow = CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

/** Private functions **/

void display_file(char * path)
{
    FILE * file = fopen(path, "rb");

    FILE * log = fopen("log.txt", "a");

    fseek(file, 0, SEEK_END);

    int size = ftell(file);

    fprintf(log, "\n%s size: %d\n", path, size);

    rewind(file);

    char * data = (char *) calloc(size, sizeof(char));

    fread(data, size, 1, file);

    SetWindowText(hEdit, data);

    free(data);
    fclose(file);
    fclose(log);
}

void open_file(HWND hWnd)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    char filename[100] = {0};

    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hWnd;
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = 100;
    ofn.lpstrFilter  = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
    ofn.nFilterIndex = 1;

    GetOpenFileName(&ofn);

    if (strcmp((char *) ofn.lpstrFile, "") != 0)
    {
        display_file((char *) ofn.lpstrFile);
    }

}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int val;

    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_CREATE:
            AddControls(hWnd);
        break;

        case WM_COMMAND:
            switch (wp)
            {
                case OPEN_BUTTON:
                    open_file(hWnd);
                break;
            }
        break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }

}

void AddControls(HWND hWnd)
{
    CreateWindowW(L"Button", L"Open File", WS_VISIBLE | WS_CHILD, 10, 10, 98, 38, hWnd, (HMENU) OPEN_BUTTON, NULL, NULL);
    hEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 10, 50, 460, 400, hWnd, NULL, NULL, NULL);
}

/*** end of file ***/

/*
    References

    01 - https://www.youtube.com/watch?v=8GCvZs55mEM&t=68s
    02 - https://www.youtube.com/watch?v=7K6HCeog09c
    03 - https://www.youtube.com/watch?v=9JMQkUOhW1s
    04 - https://www.youtube.com/watch?v=o2NkH5xxDQs
    05 - https://www.youtube.com/watch?v=PTjlGiCvYZU
    06 - https://www.youtube.com/watch?v=R7RvaQR-mm0
    07 - https://www.youtube.com/watch?v=6WJ_fljFmF0
    08 - https://www.youtube.com/watch?v=-iMGhSlvIR0
*/
#include <Windows.h>

#define FILE_MENU_NEW  1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE   4

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/* Prototypes */
void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND  hEdit;

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

        case WM_CREATE:
            AddMenus(hWnd);
            AddControls(hWnd);
        break;

        case WM_COMMAND:
            switch (wp)
            {
                case FILE_MENU_EXIT:
                    DestroyWindow(hWnd);
                break;

                case FILE_MENU_NEW:
                    MessageBeep(MB_NOFOCUS);
                break;

                case FILE_MENU_OPEN:
                    MessageBeep(MB_OK);
                break;

                case CHANGE_TITLE:
                    wchar_t text[100] = {0};
                    GetWindowTextW(hEdit, text, 100);
                    SetWindowTextW(hWnd, text);
                break;
            }
        break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }

}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu(); // file menu popup
    HMENU hSubMenu  = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, "Sub Menu Item"); // changed to dummy menu item

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Options");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    // AppendMenu(hMenu, MF_STRING, 1, "File");  // used when just having a string menu button. WM_COMMAND message generated
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd)
{
    CreateWindowW(L"Static", L"Enter text here:", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 100, 50, hWnd, NULL, NULL, NULL);

    hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 200, 152, 100, 50, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Change Title", WS_VISIBLE | WS_CHILD, 200, 204, 100, 50, hWnd, (HMENU) CHANGE_TITLE, NULL, NULL);
}

/*** end of file ***/

/*
    References

    https://www.youtube.com/watch?v=8GCvZs55mEM&t=68s
    https://www.youtube.com/watch?v=7K6HCeog09c
    https://www.youtube.com/watch?v=9JMQkUOhW1s
    https://www.youtube.com/watch?v=o2NkH5xxDQs
*/
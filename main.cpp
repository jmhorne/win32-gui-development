#include <Windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW   1
#define FILE_MENU_OPEN  2
#define FILE_MENU_EXIT  3
#define GENERATE_BUTTON 4

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/** Prototypes **/
void AddMenus(HWND);
void AddControls(HWND);
void loadImages();

/** Gobal Variables **/
HMENU   hMenu;
HWND    hName, hAge, hOut, hLogo;
HBITMAP hLogoImage, hGenerateImage;

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

    CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

/** Private functions **/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    int val;

    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_CREATE:
            loadImages();
            AddMenus(hWnd);
            AddControls(hWnd);
        break;

        case WM_COMMAND:
            switch (wp)
            {
                case FILE_MENU_EXIT:
                    val = MessageBoxW(hWnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);

                    if (val == IDYES)
                    {
                        DestroyWindow(hWnd);
                    }
                break;

                case FILE_MENU_NEW:
                    MessageBeep(MB_NOFOCUS);
                break;

                case FILE_MENU_OPEN:
                    MessageBeep(MB_OK);
                break;

                case GENERATE_BUTTON:
                    char name[30], age[10], out[50];

                    GetWindowText(hName, name, 30);
                    GetWindowText(hAge, age, 10);

                    if (strcmp(name, "") == 0 || strcmp(age, "") == 0)
                    {
                        val = MessageBoxW(hWnd, L"You did not enter anything!", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR); // NULL defaults to error

                        switch (val)
                        {
                            case IDABORT:
                                DestroyWindow(hWnd);
                            break;

                            case IDRETRY:
                            return 0;
                            
                            case IDIGNORE:
                            break;
                        }
                    }

                    strcpy(out, name);
                    strcat(out, " is ");
                    strcat(out, age);
                    strcat(out, " years old.");

                    SetWindowText(hOut, out);
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
    CreateWindowW(L"Static", L"Name: ", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Age: ", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hWnd, NULL, NULL, NULL);
    hAge = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hWnd, NULL, NULL, NULL);

    HWND hBut = CreateWindowW(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 150, 140, 98, 38, hWnd, (HMENU) GENERATE_BUTTON, NULL, NULL);
    SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hGenerateImage);

    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hWnd, NULL, NULL, NULL);
    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hWnd, NULL, NULL, NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hLogoImage);
}

void loadImages()
{
    hLogoImage = (HBITMAP) LoadImageW(NULL, L"logo.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
    hGenerateImage = (HBITMAP) LoadImageW(NULL, L"gen_btn.bmp", IMAGE_BITMAP, 98, 38, LR_LOADFROMFILE);
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
*/
#include "object.h"
#include <tchar.h>
#include <stdio.h>
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

static objects *objects[100];
char szClassName[ ] = "Lab#4";

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground =NULL;
COLORREF clr;
    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           "Animation",
           WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           700,
           500,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc,hdcMem;
    static PAINTSTRUCT ps;
    static RECT rect;
    static HBRUSH hBrush;
    static HBITMAP hbmMem;

    static HANDLE hOld;

    static int tspeed = 2,nrObj = 0;
    static RECT area = {0, 0, 700, 500};

    switch (message)
    {
        case WM_CREATE:
        {
          hdc = GetDC(hwnd);
          GetClientRect(hwnd,&rect);
          SetTimer(hwnd, ID_TIMER, tspeed, NULL);

        break;
        }

        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);

            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            hOld = SelectObject(hdcMem, hbmMem);

            for(int i = 0; i<nrObj-1; i++)
            {
                for(int j = i+1; j < nrObj; j++)
                {
                    Interaction(*objects[i],*objects[j]);
                }
            }

            FillRect(hdcMem, &rect,(HBRUSH)GetStockObject(WHITE_BRUSH));

            for(int i = 0; i < nrObj; i++)
            {
                objects[i] -> Move(hdcMem, rect, hBrush);
            }

            BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);

            EndPaint(hwnd,&ps);

        break;
        }

        case WM_SIZE:
        {
            hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);
        break;
        }


         case WM_KEYDOWN:
         {
            switch(wParam)
            {
                case VK_DOWN:
                {
                    tspeed+=10;
                break;
                }
                case VK_SPACE:
                    {
                      POINT coord;
            coord.x = rand() % 700;;
            coord.y = rand() % 500;;

            objects[nrObj] = new Circle(coord,10 + coord.x%2);

            nrObj++;
        break;
                }
                case VK_UP:
                {
                    tspeed-=10;

                        if (tspeed < 0)
                        {
                            tspeed = 1;
                        }
                 break;
                }

                default: return DefWindowProc (hwnd, message, wParam, lParam);
            break;
            }

            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,tspeed,NULL);
        break;
        }

          case WM_LBUTTONDOWN:
        {
            POINT coord;
            coord.x = LOWORD(lParam);
            coord.y = HIWORD(lParam);

            objects[nrObj] = new Circle(coord,2 + coord.x%5);
            objects[nrObj] -> Color(RGB(
(BYTE)(rand() % 255), // red component of color
(BYTE)(rand() % 255), // green component of color
(BYTE)(rand() % 255) // blue component of color
));

            nrObj++;
        break;
        }

        case WM_MOUSEWHEEL:
        {
            if((short)HIWORD(wParam)<0)
            {
                tspeed+=10;
            }
            else
            {
                tspeed-=10;
                if (tspeed<0)
                {
                    tspeed=1;
                }
            }
            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,tspeed,NULL);
        break;
        }



        case WM_ERASEBKGND:
            return 1;
        break;

        case WM_TIMER:
        {
            InvalidateRect(hwnd,NULL,FALSE);
        break;
        }

        case WM_DESTROY:
        {
            KillTimer(hwnd,ID_TIMER);

            PostQuitMessage (0);
        break;
        }

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include "resources.h"
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInstance;
/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
  HWND hwnd;               /* This is the handle for our window */
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */

  /* The Window structure */
  wincl.hInstance = hThisInstance;
  wincl.lpszClassName = szClassName;
  wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
  wincl.style = CS_HREDRAW | CS_VREDRAW;              /* Catch double-clicks */
  wincl.cbSize = sizeof (WNDCLASSEX);

  /* Use default icon and mouse-pointer */
   wincl.hIcon = LoadIcon (GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON));
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wincl.hCursor = LoadCursor (GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR));
  wincl.lpszMenuName = NULL;                 /* No menu */
  wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
  wincl.cbWndExtra = 0;                      /* structure or the window instance */
  /* Use Windows's default colour as the background of the window */
  wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

  /* Register the window class, and if it fails quit the program */
  if (!RegisterClassEx (&wincl))
    return 0;

  /* The class is registered, let's create the program*/
  hwnd = CreateWindowEx (
    0,                   /* Extended possibilites for variation */
    szClassName,         /* Classname */
    "WP Lab2 example",  /* Title Text */
    WS_OVERLAPPEDWINDOW, /* default window */
    CW_USEDEFAULT,       /* Windows decides the position */

    CW_USEDEFAULT,       /* where the window ends up on the screen */
    544,                 /* The programs width */
    375,                 /* and height in pixels */
    HWND_DESKTOP,        /* The window is a child-window to desktop */
    NULL,                /* No menu */
    hThisInstance,       /* Program Instance handler */
    NULL                 /* No Window Creation data */
  );

  /* Make the window visible on the screen */
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

  /* Run the message loop. It will run until GetMessage() returns 0 */
  while (GetMessage (&messages, NULL, 0, 0)){
    /* Translate virtual-key messages into character messages */
    TranslateMessage(&messages);
    /* Send message to WindowProcedure */
    DispatchMessage(&messages);
  }

  /* The program return-value is 0 - The value that PostQuitMessage() gave */
  return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HMENU hMenu, hSubMenu;
    HICON hIcon, hIconSm;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    HBRUSH hBrushStatic;
    LRESULT textSize;
    static HWND button1, button2, text1, text2, button3;
    static HWND hWndList;
    static HWND hwndScroll;
    static int cxCoord, cyCoord, posX,posY;
    static int scrollColor = 0;

    char box2[2000];
    char textStore[20];

    int screenW;
    int screenH;

    switch (message){
        case WM_CREATE:{


                button1 = CreateWindowEx((DWORD)NULL, TEXT("BUTTON"), TEXT("Clear"),
                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,
                                       0, 0,0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_1, GetModuleHandle(NULL), NULL);
                button2 =  CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Button2"),
                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON|BS_OWNERDRAW,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_2, GetModuleHandle(NULL), NULL);
                text1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_TEXTAREA1, GetModuleHandle(NULL), NULL);
                text2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_TEXTAREA2, GetModuleHandle(NULL), NULL);

            //List box
                hWndList = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("listbox"), "",
                                           WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
                                       0, 0, 0, 0,
                                        hwnd, (HMENU)222, GetModuleHandle(NULL), NULL);

            //Scroll Bar with color
           hwndScroll = CreateWindowEx((DWORD)NULL,
                    TEXT("scrollbar"),
                    NULL,
                    WS_CHILD | WS_VISIBLE | SBS_HORZ|ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                  0,0,0,0,
                    hwnd,
                    (HMENU) ID_SCROLL_BAR,
                   GetModuleHandle(NULL),
                    NULL);
                SetScrollRange(hwndScroll,SB_CTL, 0, 255, FALSE);
                SetScrollPos(hwndScroll, SB_CTL, 0, TRUE);

            // Menu
            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_MINIMIZE, "Minimize");
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_MAXIMIZE, "Maximize");
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");

            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_EDIT_GO, "&Go");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Edit");

            SetMenu(hwnd, hMenu);


        }
        break;



        case WM_SIZE:

            cxCoord = LOWORD(lParam); // 544
            cyCoord = HIWORD(lParam); // 375
            MoveWindow(button1, cxCoord-150, cyCoord/3-80, 110, 40, TRUE);
            MoveWindow(button2, cxCoord-150, cyCoord/3-25, 110, 40, TRUE);
            MoveWindow(text1, 15, 30, cxCoord-200, cyCoord/3, TRUE);
            MoveWindow(hWndList, 15, cyCoord/2+30, cxCoord-200, cyCoord/3, TRUE);
            MoveWindow(hwndScroll, cxCoord/2-150, cyCoord/2+10, 300, cyCoord/2-140, TRUE);

            break;

     case WM_PAINT:
        hdc = BeginPaint(hwnd,&ps);
        GetClientRect (hwnd, &rect);
        SetBkMode(hdc, OPAQUE);
         SetBkColor(hdc, RGB(scrollColor,scrollColor + 30, scrollColor+150));

        DrawText(hdc,TEXT("Done with Pride and Prejudice by Dragos Lupei "),-1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER|DT_NOCLIP);

        EndPaint(hwnd, &ps);
        return 0;
        break;

     case WM_HSCROLL: {
            switch (LOWORD(wParam)) {
            case SB_LINEDOWN: {
                    scrollColor = min (255, scrollColor + 1);
                }
                break;
            case SB_LINEUP: {
                    scrollColor = min (255, scrollColor - 1);
                }
                break;
            case SB_PAGEDOWN: {
                    scrollColor += 15;
                }
                break;
            case SB_PAGEUP: {
                    scrollColor -= 15;
                }
                break;
            case SB_BOTTOM: {
                    scrollColor = 255;
                }
                break;
            case SB_TOP: {
                    scrollColor = 0;
                }
                break;
            case SB_THUMBPOSITION:
            case SB_THUMBTRACK: {
                    scrollColor = HIWORD(wParam);
                }
                break;
            }

            SetScrollPos(hwndScroll, SB_CTL,scrollColor, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    case WM_SETFOCUS: {
            SetFocus(hwnd);
        }
        break;
    case WM_DRAWITEM:
            if ((UINT)wParam == IDC_BUTTON_2) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char button2[12];
                strcpy(button2, "Add to list");
                GetTextExtentPoint32(lpdis->hDC, button2, strlen(button2), &size);
                SetTextColor(lpdis->hDC, RGB(0,40,255));
                SetBkColor(lpdis->hDC, RGB(0,0,0));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    button2,
                    strlen(button2),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);
                return TRUE;
			}


			break;

      case WM_CONTEXTMENU:
        {
            if ((HWND)wParam == hWndList)
            {
                if(MessageBox(hwnd, "Do you want to delete this item?", "Notice", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
                {
                    int index = SendMessage(GetDlgItem(hwnd, 222), LB_GETCURSEL, 0, 0);
                    SendMessage(GetDlgItem(hwnd, 222), LB_DELETESTRING, index, 0);
                }
                break;

            }

            break;
            }
     case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_BUTTON_1:
                {
                    SendMessage(text1, WM_SETTEXT, NULL, NULL);
                    break;
                }

                 case IDC_BUTTON_2:
                {
                    textSize = SendMessage(text1, WM_GETTEXT, 100, (LPARAM)box2); // text size
                    box2[textSize] = _T('\0'); // initialization with null character
                    SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)box2); // add inputed text to window
                    SendMessage(hWndList, EM_REPLACESEL, 0, (LPARAM)" ");
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;
                }

            break;


            case ID_FILE_EXIT:
                {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
            }
            case ID_FILE_MINIMIZE:
                {
                 ShowWindow(hwnd, SW_MINIMIZE);
            break;
            }
            case ID_FILE_MAXIMIZE:{
                ShowWindow(hwnd, SW_MAXIMIZE);
            break;
            }
        }
        break;

       case WM_KEYDOWN:
            {
                switch(wParam)
                {
                    case VK_SPACE:
                        if(GetAsyncKeyState(VK_LCONTROL))
                        {
                            SendMessage(hwnd,WM_DESTROY,0,0);
                        }
                    break;

                }
            }
            break;
    case WM_SYSCOMMAND:
        {
            switch(wParam)
            {

                case SC_CLOSE:
                {
                    if(MessageBox(hwnd, "Do you really want to exit?", "Dragos's APP", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
                    {
                        exit(1);
                    }
                    break;
                }

                default:
                    return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;


    case WM_CTLCOLOREDIT: {
               if(IDC_TEXTAREA2 == GetDlgCtrlID((HWND)lParam))
               {
                    HDC hdcStatic = (HDC) wParam;
                    SetBkColor(hdcStatic, RGB(255,255,204));
                    return (INT_PTR)CreateSolidBrush(RGB(255,255,204));
                }
        break;
            }
case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
            winSize->ptMinTrackSize.x = 450;
            winSize->ptMinTrackSize.y = 375;
            winSize->ptMaxTrackSize.x = 1000;
            winSize->ptMaxTrackSize.y = 350;
            break;
        }

    case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }

    return 0;
}

}

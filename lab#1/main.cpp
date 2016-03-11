#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#define IDC_BUTTON_1 102
#define IDC_BUTTON_2 103
#define IDC_TEXTAREA1 104
#define IDC_TEXTAREA2 105
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

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
  wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
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
    "WP Lab#1 example",  /* Title Text */
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
  ShowWindow (hwnd, nCmdShow);

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
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    static HWND button1, button2, text1, text2;
    static int cxCoord, cyCoord;
    LRESULT textSize;
    char box2[2000];
    int screenW;
    int screenH;
    switch (message){
        case WM_CREATE:{


            button1 = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Clear"),
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


        break;}
         case WM_SIZE:
            cxCoord = LOWORD(lParam); // 544
            cyCoord = HIWORD(lParam); // 375
            MoveWindow(button1, cxCoord-150, cyCoord/3-80, 110, 40, TRUE);
            MoveWindow(button2, cxCoord-150, cyCoord/3-25, 110, 40, TRUE);
            MoveWindow(text1, 15, 30, cxCoord-200, cyCoord/3, TRUE);
            MoveWindow(text2, 15, cyCoord/2+30, cxCoord-200, cyCoord/3, TRUE);
            break;

     case WM_PAINT:
        hdc = BeginPaint(hwnd,&ps);
        GetClientRect (hwnd, &rect);
        DrawText(hdc,TEXT("Done with Pride and Prejudice by Dragos Lupei "),-1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
         DrawText(hdc,TEXT("How are you today? "),-1,&rect, DT_SINGLELINE | DT_CENTER | DT_TOP);
            SetBkColor(hdc, RGB(255,225,196));
             SetTextColor(hdc, RGB(0,0,128));
        DrawText(hdc,TEXT("Good, thank you "),-1,&rect, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);





        EndPaint(hwnd, &ps);
        return 0;
        break;
    case WM_DRAWITEM:
            if ((UINT)wParam == IDC_BUTTON_2) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char button2[10];
                strcpy(button2, "Copy text");
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
                    SendMessage(text2, EM_REPLACESEL, 0, (LPARAM)box2); // add inputed text to window
                    SendMessage(text2, EM_REPLACESEL, 0, (LPARAM)" ");
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;
                }


                }
        break;
     case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
            winSize->ptMinTrackSize.x = 510;
            winSize->ptMinTrackSize.y = 375;
            winSize->ptMaxTrackSize.x = 630;
            winSize->ptMaxTrackSize.y = 425;
            break;
        }
    case WM_CTLCOLOREDIT: {
               if(IDC_TEXTAREA2 == GetDlgCtrlID((HWND)lParam))
               {
                    HDC hdcStatic = (HDC) wParam;
                    SetBkColor(hdcStatic, RGB(255,255,204));
                    return (INT_PTR)CreateSolidBrush(RGB(255,255,204));
                }
                break;
            }



    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }

    return 0;
}


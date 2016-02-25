#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#define IDC_BUTTON_1 102
#define IDC_BUTTON_2 103

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
    static HWND button1, button2;
    static int cxCoord, cyCoord;
    switch (message){
        case WM_CREATE:{


            button1 = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Button1"),
                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,
                                       0, 0,0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_1, GetModuleHandle(NULL), NULL);
            button2 =  CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Button2"),
                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_2, GetModuleHandle(NULL), NULL);

        break;}
         case WM_SIZE:
            cxCoord = LOWORD(lParam); // 544
            cyCoord = HIWORD(lParam); // 375
            MoveWindow(button1, cxCoord-150, cyCoord/3-80, 110, 40, TRUE);
            MoveWindow(button2, cxCoord-150, cyCoord/3-25, 110, 40, TRUE);
            break;

     case WM_PAINT:
        hdc = BeginPaint(hwnd,&ps);
        GetClientRect (hwnd, &rect);
        DrawText(hdc,TEXT("Done with Pride and Prejudice by Dragos Lupei "),-1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        return 0;
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


#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "resources.h"

HINSTANCE hInstance;

char bmpfile[] = "hello.bmp";
int penColor[] = {0, 0, 0};
int brushColor[] = {255, 255, 255};
HBRUSH hBrush;
HPEN hPen;
POINT coords[4];
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

int eraseMode;

int radioMark;

int checkBoxMark;

int thicknessMark = 0;

int drawItemMark;

int eraserMark;

int bezierStage = 0;

int outOfBoud = 0;
char szClassName[ ] = "Lab#3";
int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               // This is the handle for our window
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    setupPen(1, penColor);
    setupBrush(brushColor);


  /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;     /* This function is called by windows */
    wincl.style = CS_HREDRAW|CS_VREDRAW;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                        /* No menu */
    wincl.cbClsExtra = 0;                             /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                             /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(240, 240, 240));

    wincl.lpszMenuName = NULL;
    if (!RegisterClassEx (&wincl))
        return 0;

   hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Lab#3",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           700,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT Ps;
    static HWND hBtnSetColor, hBtnDraw, hBtnThickness, hBtnEraser;      // Buttons
    static HWND hInptColorR, hInptColorG, hInptColorB;                  // Input Fields
    static HWND hCmbxDrawnObj, hCmbxThickness, hCmbxEraser;             // Combo boxes
    static HWND hChbxFilled;                                            // Check box
    static HWND hRadioPen, hRadioBrush;                                // Radio buttons

    RECT rcPenColor, rcBrushColor;
    RECT rcDrawingArea;
    RECT rcGradient;


    SetRect(&rcPenColor, 30, 315, 75, 360);
    SetRect(&rcBrushColor, 85, 315, 130, 360);
    SetRect(&rcDrawingArea, 180, 10, 770, 550);

    HDC hdc = GetDC(hwnd);

    HBRUSH hBrushStatic;

    switch(message) {
         case WM_GETMINMAXINFO:
         {
             LPMINMAXINFO mmi = (LPMINMAXINFO)lParam;
             mmi->ptMinTrackSize.x = 800;
             mmi->ptMinTrackSize.y = 550;
             mmi->ptMaxTrackSize.x = 850;
             mmi->ptMaxTrackSize.y = 600;
             break;}
    case WM_CREATE: {

            hBtnSetColor = CreateWindowEx(NULL,
                    TEXT("button"),
                    "Set",
                    WS_TABSTOP | WS_VISIBLE |
                    WS_CHILD | BS_DEFPUSHBUTTON | BS_TOP,
                    10, 25,
                    40, 25,
                    hwnd,
                    (HMENU)IDC_BUTTON_SET,
                    hInstance,
                    NULL);


            hInptColorR = CreateWindowEx((DWORD)NULL,
                    TEXT("edit"),
                    "",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    55, 25,
                    30, 25,
                    hwnd,
                    (HMENU)IDC_INPUT_COLOR_R,
                    hInstance,
                    NULL);

            hInptColorG = CreateWindowEx((DWORD)NULL,
                    TEXT("edit"),
                    "",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    90, 25,
                    30, 25,
                    hwnd,
                    (HMENU)IDC_INPUT_COLOR_G,
                    hInstance,
                    NULL);


            hInptColorB = CreateWindowEx((DWORD)NULL,
                    TEXT("edit"),
                    "",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    125, 25,
                    30, 25,
                    hwnd,
                    (HMENU)IDC_INPUT_COLOR_B,
                    hInstance,
                    NULL);


            hRadioPen = CreateWindowEx((DWORD)NULL,
                    TEXT("button"), "Pen",
                    WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                    10, 55,
                    50, 15,
                    hwnd, (HMENU)IDC_RADIO_PEN,
                    hInstance,
                    NULL);
            SendMessage(hRadioPen, BM_SETCHECK, BST_CHECKED, 1);


            hRadioBrush = CreateWindowEx((DWORD)NULL,
                    TEXT("button"), "Brush",
                    WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                    95, 55,
                    60, 15,
                    hwnd,
                    (HMENU)IDC_RADIO_BRUSH,
                    hInstance,
                    NULL);


            hBtnDraw = CreateWindowEx(NULL,
                    TEXT("button"),
                    "Draw",
                    WS_TABSTOP | WS_VISIBLE |
                    WS_CHILD | BS_DEFPUSHBUTTON | BS_TOP,
                    10, 100,
                    50, 25,
                    hwnd,
                    (HMENU)IDC_BUTTON_DRAW,
                    hInstance,
                    NULL);


            hCmbxDrawnObj = CreateWindowEx(NULL,
                    TEXT("combobox"),
                    NULL,
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST ,
                    65, 100,
                    90, 300,
                    hwnd,
                    (HMENU)IDC_COMBOBOX_DRAWN_OBJ,
                    hInstance,
                    NULL);

            SendMessage(hCmbxDrawnObj,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"Line"));
            SendMessage(hCmbxDrawnObj,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"Rectangle"));
            SendMessage(hCmbxDrawnObj,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"Circle"));
            SendMessage(hCmbxDrawnObj,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"Bezier Curves"));


            hChbxFilled = CreateWindowEx(0,
                        TEXT("button"),
                        "Filled Objects",
                        BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD,
                        10, 130,
                        145, 25,
                        hwnd,
                        (HMENU)IDC_CHECKBOX_FILLED,
                        hInstance,
                        NULL);


            hBtnThickness = CreateWindowEx(NULL,
                    TEXT("button"),
                    "Tickness",
                    WS_TABSTOP | WS_VISIBLE |
                    WS_CHILD | BS_DEFPUSHBUTTON | BS_TOP,
                    10, 185,
                    70, 25,
                    hwnd,
                    (HMENU)IDC_BUTTON_THICKNESS,
                    hInstance,
                    NULL);


            hCmbxThickness = CreateWindowEx(NULL,
                    TEXT("combobox"),
                    NULL,
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST ,
                    85, 185,
                    70, 300,
                    hwnd,
                    (HMENU)IDC_COMBOBOX_THICKNESS,
                    hInstance,
                    NULL);

            SendMessage(hCmbxThickness,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"1"));
            SendMessage(hCmbxThickness,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"2"));
            SendMessage(hCmbxThickness,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"3"));
            SendMessage(hCmbxThickness,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"4"));
            SendMessage(hCmbxThickness,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"5"));


            hBtnEraser = CreateWindowEx(NULL,
                    TEXT("button"),
                    "Eraser",
                    WS_TABSTOP | WS_VISIBLE |
                    WS_CHILD | BS_DEFPUSHBUTTON | BS_TOP,
                    10, 235,
                    60, 25,
                    hwnd,
                    (HMENU)IDC_COMBOBOC_ERASER,
                    hInstance,
                    NULL);


            hCmbxEraser = CreateWindowEx(NULL,
                    TEXT("combobox"),
                    NULL,
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST ,
                    75, 235,
                    80, 300,
                    hwnd,
                    (HMENU)IDC_COMBOBOC_ERASER,
                    hInstance,
                    NULL);

            SendMessage(hCmbxEraser,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"1"));
            SendMessage(hCmbxEraser,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"2"));
            SendMessage(hCmbxEraser,
                        CB_ADDSTRING,
                        0,
                        reinterpret_cast<LPARAM>((LPCTSTR)"3"));

            // Drawing the static text
            CreateWindowEx(0, TEXT("static"), "R",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                55, 5, 30, 17,
                hwnd, (HMENU)0, hInstance, NULL);

            CreateWindowEx(0, TEXT("static"), "G",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                90, 5, 30, 17,
                hwnd, (HMENU)0, hInstance, NULL);

            CreateWindowEx(0, TEXT("static"), "B",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                125, 5, 30, 17,
                hwnd, (HMENU)0, hInstance, NULL);

            CreateWindowEx(0, TEXT("static"), "Selected Color",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                30, 290, 100, 17,
                hwnd, (HMENU)0, hInstance, NULL);

    RegisterHotKey(hwnd, CONTROL_SPACE, MOD_CONTROL, VK_SPACE);
    RegisterHotKey(hwnd, ALT_LEFT, MOD_ALT,  0x42);
        }
        break;

    case WM_LBUTTONDOWN: {
            if (wParam & MK_LBUTTON) {

                if(!checkBoundries(LOWORD (lParam), HIWORD (lParam), rcDrawingArea)) {
                    outOfBoud = 1;
                    return 0;
                }
                outOfBoud = 0;

                if(eraseMode) {
                    int centerX = LOWORD (lParam);
                    int centerY = HIWORD (lParam);
                    int delta = 5 + (eraserMark * 3);
                    SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
                    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

                    coords[0].x = centerX - delta;
                    coords[0].y = centerY + delta;

                    coords[1].y = centerY - delta;
                    coords[1].x = centerX + delta;

                    drawRectangle(coords, hdc);
                    return 0;
                }

                if (drawItemMark == 3) {
                    SelectObject(hdc, CreatePen(PS_SOLID, thicknessMark + 1, RGB(255, 255, 255)));
                    switch (bezierStage) {
                    case 0:
                        for (int i = 0; i < 4; i++) {
                            coords[i].x = LOWORD (lParam);
                            coords[i].y = HIWORD (lParam);
                        }
                        break;
                    case 1:
                        drawBezier(coords, hdc);
                        coords[1].x = LOWORD (lParam);
                        coords[1].y = HIWORD (lParam);
                        SelectObject(hdc, hPen);
                        drawBezier(coords, hdc);
                        break;
                    case 2:
                        drawBezier(coords, hdc);
                        coords[2].x = LOWORD (lParam);
                        coords[2].y = HIWORD (lParam);
                        SelectObject(hdc, hPen);
                        drawBezier(coords, hdc);
                        break;
                    }
                } else {
                    coords[0].x = LOWORD (lParam);
                    coords[0].y = HIWORD (lParam);
                    coords[1].x = LOWORD (lParam);
                    coords[1].y = HIWORD (lParam);
                    bezierStage = 0;
                }
            }
        }
        break;

    case WM_LBUTTONUP:{
        if (drawItemMark == 3) {
            switch (bezierStage) {
            case 0:
                bezierStage = 1;
                break;
            case 1:
                bezierStage = 2;
                break;
            case 2:
                bezierStage = 0;
                break;
            }
        }
    }
    break;
    case WM_HOTKEY : {
            switch(wParam) {

                case CONTROL_SPACE: {
                   eraseMode=1;
                    break;
                }

                case ALT_LEFT: {
                     drawItemMark=2;
                    break;
                }
            }
        }
	case WM_MOUSEMOVE: {
            if (wParam & MK_LBUTTON) {
                if (outOfBoud) {
                    bezierStage --;
                    return 0;
                }

                if (!checkBoundries(LOWORD (lParam), HIWORD (lParam), rcDrawingArea))
                    return 0;
                SelectObject(hdc, CreatePen(PS_SOLID, thicknessMark + 1, RGB(255, 255, 255)));
                SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

                if (eraseMode) {
                    int centerX = LOWORD (lParam);
                    int centerY = HIWORD (lParam);
                    int delta = 5 + (eraserMark * 3);
                    SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
                    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

                    coords[0].x = centerX - delta;
                    coords[0].y = centerY + delta;

                    coords[1].y = centerY - delta;
                    coords[1].x = centerX + delta;

                    drawRectangle(coords, hdc);
                    return 0;
                }

                switch (drawItemMark) {
                case 0:{                                // Line
                        drawLine(coords, hdc);
                        coords[1].x = LOWORD (lParam);
                        coords[1].y = HIWORD (lParam);
                        SelectObject(hdc, hPen);
                        SelectObject(hdc, hBrush);
                        drawLine(coords, hdc);
                    }
                    break;
                case 1: {                                // Rectangle
                        drawRectangle(coords, hdc);
                        coords[1].x = LOWORD (lParam);
                        coords[1].y = HIWORD (lParam);
                        SelectObject(hdc, hPen);
                        if (checkBoxMark) {
                            SelectObject(hdc, hBrush);
                        }
                        drawRectangle(coords, hdc);
                    }
                    break;
                case 2:{                                // Circle
                        drawCircle(coords, hdc);
                        coords[1].x = LOWORD (lParam);
                        coords[1].y = HIWORD (lParam);
                        SelectObject(hdc, hPen);
                        if (checkBoxMark) {
                            SelectObject(hdc, hBrush);
                        }
                        drawCircle(coords, hdc);
                    }
                    break;
                case 3: {                               // Bezier Curve
                        switch (bezierStage) {
                        case 0:
                            drawBezier(coords, hdc);
                            coords[3].x = LOWORD (lParam);
                            coords[3].y = HIWORD (lParam);
                            SelectObject(hdc, hPen);
                            drawBezier(coords, hdc);
                            break;
                        case 1:
                            drawBezier(coords, hdc);
                            coords[1].x = LOWORD (lParam);
                            coords[1].y = HIWORD (lParam);
                            SelectObject(hdc, hPen);
                            drawBezier(coords, hdc);
                            break;
                        case 2:
                            drawBezier(coords, hdc);
                            coords[2].x = LOWORD (lParam);
                            coords[2].y = HIWORD (lParam);
                            SelectObject(hdc, hPen);
                            drawBezier(coords, hdc);
                            break;
                        }
                    }
                    break;
                }
            }
        }
	    break;

    case WM_PAINT: {
            HDC hdc = BeginPaint(hwnd, &Ps);
            RECT temp;

            SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, rcDrawingArea.left, rcDrawingArea.top, rcDrawingArea.right, rcDrawingArea.bottom);

            SelectObject(hdc, CreateSolidBrush(RGB(penColor[0], penColor[1], penColor[2])));
            Rectangle(hdc, rcPenColor.left, rcPenColor.top, rcPenColor.right, rcPenColor.bottom);

            SelectObject(hdc, CreateSolidBrush(RGB(brushColor[0], brushColor[1], brushColor[2])));
            Rectangle(hdc, rcBrushColor.left, rcBrushColor.top, rcBrushColor.right, rcBrushColor.bottom);

            // *** Gradient
            int r1 = 255, g1 = 0, b1 = 0;

            /* End Color; Change the R,G,B values
            to the color of your choice */
            int r2 = 255, g2 = 255, b2 = 0;

            /* loop to create the gradient */
            for(int i = rcGradient.left; i < rcGradient.right; i++)
            {
                int r,g,b;
                r = r1 + (i * (r2-r1) / rcGradient.right);
                g = g1 + (i * (g2-g1) / rcGradient.right);
                b = b1 + (i * (b2-b1) / rcGradient.right);
                temp.left = i;
                temp.top = rcGradient.top;
                temp.right = i + 1;
                temp.bottom = rcGradient.bottom;
                HBRUSH color = CreateSolidBrush(RGB(r, g, b));
                FillRect(hdc, &temp, color);
            }

            // Load a bitmap image
            // Static Bitmap Code:
            HWND hStatic = CreateWindowEx (WS_EX_STATICEDGE, "STATIC", NULL,
            WS_CHILD | WS_VISIBLE | SS_BITMAP, 0, 420, 0, 0, hwnd, 0, hInstance, NULL);

            HANDLE hImage = LoadImage(hInstance, bmpfile, IMAGE_BITMAP, 150, 130, LR_LOADFROMFILE);
            SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);


            EndPaint(hwnd, &Ps);
        }
        break;

    case WM_COMMAND: {

        switch (LOWORD(wParam)) {
        case IDC_BUTTON_SET: {
                char rBuffer[30], gBuffer[30], bBuffer[30];
                SendMessage(hInptColorR, WM_GETTEXT, 4, reinterpret_cast<LPARAM>(rBuffer));
                SendMessage(hInptColorG, WM_GETTEXT, 4, reinterpret_cast<LPARAM>(gBuffer));
                SendMessage(hInptColorB, WM_GETTEXT, 4, reinterpret_cast<LPARAM>(bBuffer));

                int red = atoi(rBuffer);
                int green = atoi(gBuffer);
                int blue = atoi(bBuffer);

                int radioPen = SendMessage(hRadioPen, BM_GETCHECK, 0, 0);
                if (radioPen) {
                    penColor[0] = red;
                    penColor[1] = green;
                    penColor[2] = blue;
                    setupPen(thicknessMark + 1, penColor);
                    InvalidateRect(hwnd, &rcPenColor, TRUE);
                } else {
                    brushColor[0] = red;
                    brushColor[1] = green;
                    brushColor[2] = blue;
                    setupBrush(brushColor);
                    InvalidateRect(hwnd, &rcBrushColor, TRUE);
                }
            }
            break;

        case IDC_BUTTON_DRAW: {
                drawItemMark = SendMessage((HWND) hCmbxDrawnObj, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
                if (drawItemMark < 0) {
                    drawItemMark = 0;
                }
                checkBoxMark = SendMessage(hChbxFilled, BM_GETCHECK, 0, 0);
                eraseMode = 0;
            }
            break;

        case IDC_COMBOBOX_THICKNESS: {
                thicknessMark = SendMessage((HWND) hCmbxThickness, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
                if (thicknessMark < 0) {
                    thicknessMark = 0;
                }
                setupPen(thicknessMark + 1, penColor);
            }
            break;

        case IDC_COMBOBOC_ERASER: {
                eraserMark = SendMessage((HWND) hCmbxEraser, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
                if (eraserMark < 0) {
                    eraserMark = 0;
                }
                eraseMode = 1;
            }
            break;
        }

        }
        break;

    case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }

    ReleaseDC(hwnd, hdc);
    return DefWindowProc(hwnd,message,wParam,lParam);
}

void setupPen(int stroke, int color[3]) {
    hPen = CreatePen(PS_SOLID, stroke, RGB(color[0], color[1], color[2]));
}


void setupBrush(int color[3]) {
    hBrush = CreateSolidBrush(RGB(color[0], color[1], color[2]));
}

int checkBoundries(int xPos, int yPos, RECT drawingArea){
    int delta;
    if (eraseMode) {
        delta = 5 + (eraserMark * 3);
    } else {
        delta = (thicknessMark+1)/2  + 1;
    }

    if (xPos < (drawingArea.left + delta))
        return 0;
    if (xPos > (drawingArea.right - delta))
        return 0;
    if (yPos < (drawingArea.top + delta))
        return 0;
    if (yPos > (drawingArea.bottom - delta))
        return 0;
    return 1;
}

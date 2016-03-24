#define IDC_BUTTON_SET          101
#define IDC_BUTTON_DRAW         102
#define IDC_BUTTON_THICKNESS    103
#define IDC_BUTTON_ERASER      104

#define IDC_INPUT_COLOR_R       105
#define IDC_INPUT_COLOR_G       106
#define IDC_INPUT_COLOR_B       107

#define IDC_COMBOBOX_DRAWN_OBJ  108
#define IDC_COMBOBOX_THICKNESS  109
#define IDC_COMBOBOC_ERASER     110

#define IDC_CHECKBOX_FILLED     111

#define IDC_RADIO_PEN           112
#define IDC_RADIO_BRUSH         113

#define CONTROL_SPACE 114
#define ALT_LEFT 115

void setupPen(int stroke, int color[3]);
void setupBrush(int color[3]);

void drawLine(POINT coord[4], HDC hdc) {
    MoveToEx(hdc, coord[0].x, coord[0].y, NULL);
    LineTo(hdc, coord[1].x, coord[1].y);
}

void drawCircle(POINT coord[4], HDC hdc) {
    Ellipse(hdc, coord[0].x, coord[0].y, coord[1].x, coord[1].y);
}

void drawRectangle(POINT coord[4], HDC hdc) {
    Rectangle(hdc, coord[0].x, coord[0].y, coord[1].x, coord[1].y);
}
void drawBezier(POINT coord[4], HDC hdc) {
    PolyBezier (hdc, coord, 4);
}

int checkBoundries(int xPos, int yPos, RECT drawingArea);

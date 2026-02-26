#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
#define ID_ADD   201
#define ID_SUB   202
#define ID_MUL   203
#define ID_DIV   204

HWND hEdit1, hEdit2;

bool isNumber(const char* str) {
    if (*str == '\0') return false;
    char* endPtr;
    strtod(str, &endPtr);
    return (*endPtr == '\0');
}

void Calculate(HWND hwnd, char op) {
    char buf1[100], buf2[100], resultStr[100];

    GetWindowText(hEdit1, buf1, 100);
    GetWindowText(hEdit2, buf2, 100);

    if (!isNumber(buf1) || !isNumber(buf2)) {
        MessageBox(hwnd, "Invalid input! Please enter numbers only.",
                   "Error", MB_ICONERROR);
        return;
    }

    double a = atof(buf1);
    double b = atof(buf2);
    double result = 0;

    if (op == '/' && b == 0) {
        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_ICONERROR);
        return;
    }

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
    }

    sprintf(resultStr, "%.6f", result);
    MessageBox(hwnd, resultStr, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

    case WM_CREATE: {
        CreateWindow("STATIC", "Please input two numbers",
            WS_VISIBLE | WS_CHILD,
            20, 10, 160, 20,
            hwnd, NULL, NULL, NULL);

        hEdit1 = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20, 40, 150, 20,
            hwnd, (HMENU)ID_EDIT1, NULL, NULL);

        hEdit2 = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20, 70, 150, 20,
            hwnd, (HMENU)ID_EDIT2, NULL, NULL);

        CreateWindow("BUTTON", "+",
            WS_VISIBLE | WS_CHILD,
            20, 110, 30, 30,
            hwnd, (HMENU)ID_ADD, NULL, NULL);

        CreateWindow("BUTTON", "-",
            WS_VISIBLE | WS_CHILD,
            60, 110, 30, 30,
            hwnd, (HMENU)ID_SUB, NULL, NULL);

        CreateWindow("BUTTON", "*",
            WS_VISIBLE | WS_CHILD,
            100, 110, 30, 30,
            hwnd, (HMENU)ID_MUL, NULL, NULL);

        CreateWindow("BUTTON", "/",
            WS_VISIBLE | WS_CHILD,
            140, 110, 30, 30,
            hwnd, (HMENU)ID_DIV, NULL, NULL);
        break;
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ID_ADD: Calculate(hwnd, '+'); break;
        case ID_SUB: Calculate(hwnd, '-'); break;
        case ID_MUL: Calculate(hwnd, '*'); break;
        case ID_DIV: Calculate(hwnd, '/'); break;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(50, 205, 50));
    wc.lpszClassName = "MyCalculatorClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0,
        "MyCalculatorClass",
        "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        250, 200,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
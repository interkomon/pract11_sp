﻿// pract11.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "pract11.h"
#include <windows.h>
#include <Commdlg.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRACT11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACT11));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACT11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRACT11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//

#define WC_HOTKEYCAL L"msctls_hotkey32"
#define IDS_HOTKEY 100

#define WC_LISTVIEW L"SysListView32"
#define IDS_LISTVIEW 150

#define WC_UPDOWNCAL L"msctls_updown32"
#define IDC_SPIN 100

#define WC_CHECKBOX L"Button"
#define IDS_CHECKB 100

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    HWND hWndHotKey = CreateWindowEx(0, WC_HOTKEYCAL, L"",
        WS_CHILD | WS_VISIBLE,
        20, 10, 150, 50,
        hWnd, (HMENU)IDS_HOTKEY,
        GetModuleHandle(NULL), NULL);

    if (!hWndHotKey)
    {
        return FALSE;
    }


    HWND hWndListView = CreateWindowEx(0, WC_LISTVIEW, L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 100, 200, 200,
        hWnd, (HMENU)IDS_LISTVIEW,
        GetModuleHandle(NULL), NULL);
    if (!hWndListView)
    {
        return FALSE;
    }


    HWND hWndSpin = CreateWindowEx(0, WC_UPDOWNCAL, L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        20, 320, 150, 50,
        hWnd, (HMENU)IDC_SPIN,
        GetModuleHandle(NULL), NULL);
    if (!hWndSpin)
    {
        return FALSE;
    }



    HWND hWndCheck = CreateWindowEx(0, WC_CHECKBOX, L"",
        WS_CHILD | WS_VISIBLE,
        20, 400, 10, 10,
        hWnd, (HMENU)IDS_CHECKB,
        GetModuleHandle(NULL), NULL);
    if (!hWndCheck)
    {
        return FALSE;
    }

//SendMessage(hWndCheck, , 0, (LPARAM)L"Название");

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
#define MAX_PATH 260
wchar_t szFileName[MAX_PATH];
wchar_t szFindWhat[MAX_PATH];
wchar_t szReplaceWith[MAX_PATH];

FINDREPLACE fr;
PRINTDLG pd;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_REPLACE:
                ZeroMemory(&fr, sizeof(fr));

                fr.lStructSize = sizeof(fr);
                fr.hwndOwner = hWnd;
                fr.wFindWhatLen = sizeof(szFindWhat);
                fr.wReplaceWithLen = sizeof(szReplaceWith);
                fr.Flags = FR_DOWN;
                fr.lpstrFindWhat = szFindWhat;
                fr.lpstrReplaceWith = szReplaceWith;

                if (ReplaceText(&fr) != FALSE) {
                  
                }
                break;
            case IDM_PRINTER:
                ZeroMemory(&pd, sizeof(PRINTDLG));
                pd.lStructSize = sizeof(pd);
                pd.hwndOwner = hWnd;
                pd.Flags = PD_RETURNDC;

                //диалог печати
                if (PrintDlg(&pd))
                {
                    // устройства для печвати
                    HDC hdcPrinter = pd.hDC;
                }

                   
                break;
            

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CHAR:
    {
        TCHAR ch = (TCHAR)wParam;
        char str[2] = { ch , '\0' };
        MessageBox(hWnd, L"WM_CHAR", L"WM_CHAR", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_KEYUP:
    {
        MessageBox(hWnd, L"WM_KEYUP", L"WM_KEYUP", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_LBUTTONDBLCLK:
    {
        MessageBox(hWnd, L"WM_LBUTTONDBLCLK", L"WM_LBUTTONDBLCLK", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        MessageBox(hWnd, L"WM_LBUTTONDOWN", L"WM_LBUTTONDOWN", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_LBUTTONUP:
    {
        MessageBox(hWnd, L"WM_LBUTTONUP", L"WM_LBUTTONUP", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        MessageBox(hWnd, L"WM_MOUSEWHEEL", L"WM_MOUSEWHEEL", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MOVING:
    {
        MessageBox(hWnd, L"WM_MOVING", L"WM_MOVING", MB_OK | MB_ICONINFORMATION);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

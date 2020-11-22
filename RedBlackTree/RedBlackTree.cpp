﻿// RedBlackTree.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "RedBlackTree.h"

#include "GlobalVariable.h"
#include <iostream>
#include "Tree.h"
#include "LogManager.h"
#include <process.h>
#include <time.h>


#define MAX_LOADSTRING 100
#define ARRAY_SIZE 40

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

unsigned int WINAPI InputThread(LPVOID lParam);

HWND g_hWnd;
int32_t g_ScreenX=0;
int32_t g_ScreenY = 0;
RedBlackTree g_Tree;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_REDBLACKTREE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REDBLACKTREE));

    MSG msg;

    bool bFirst = true;

    int arr[ARRAY_SIZE];
    int size = 20;
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = i;
    }

    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        int randIndex1 = rand() % ARRAY_SIZE;
        int temp = arr[randIndex1];

        int randIndex2= rand() % ARRAY_SIZE;
        arr[randIndex1] = arr[randIndex2];
        arr[randIndex2] = temp;
    }
    // 기본 메시지 루프입니다:


    //for (size_t i = 0; i < ARRAY_SIZE; i++)
    //{
    //    if (arr[i] == 11)
    //    {
    //        int a = 10;
    //    }
    //    g_Tree.InsertNode(arr[i]);
    //}
    //g_Tree.Print();

    //g_Tree.InsertNode(50);
    //g_Tree.InsertNode(30);
    //g_Tree.InsertNode(90);
    //g_Tree.InsertNode(15);
    //g_Tree.InsertNode(40);
    //g_Tree.InsertNode(60);
    //g_Tree.InsertNode(70);
    //g_Tree.InsertNode(80);
    //g_Tree.InsertNode(20);
    //g_Tree.InsertNode(77);
    //g_Tree.InsertNode(67);
    //g_Tree.InsertNode(42);
    //g_Tree.InsertNode(11);


    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, InputThread, NULL, 0, NULL);

    InvalidateRect(g_hWnd, NULL, TRUE);
    while (true)//(GetMessage(&msg, nullptr, 0, 0))
    {
        if (PeekMessage(&msg, g_hWnd, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }
        else
        {
           
        }
       
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REDBLACKTREE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REDBLACKTREE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_KEYDOWN:
        if (wParam == VK_LEFT)
        {
            g_ScreenX+=20;
        }
        if (wParam ==VK_RIGHT)
        {
            g_ScreenX-=20;
        }
        if (wParam == VK_SPACE)
        {
            g_Tree.InsertNode(rand() % 100);
        }
        if (wParam == 'D')
        {
            g_Tree.DeleteNode(rand() % 100);
        }
        InvalidateRect(hWnd, NULL, TRUE);
      
        break;
        
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
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
            WCHAR buf[128];
           
            g_Tree.PrintTree(g_ScreenX, g_ScreenY);
            wsprintf(buf, L"Max Black:%d", g_Tree.GetBlackNum());
            TextOut(hdc, 100, 50, buf, wcslen(buf));
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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

unsigned int __stdcall InputThread(LPVOID lParam)
{
    int result = 0;
    int insertOrDelete = 0;

    while (true)
    {
        CLogManager::GetInstance()->InputDeleteOrInsert(&insertOrDelete,&result);

        switch (insertOrDelete)
        {
        case 1:
            g_Tree.InsertNode(result);
            break;
        case 2:
            g_Tree.DeleteNode(result);
            break;
        }
        InvalidateRect(g_hWnd, NULL, TRUE);
    }
    return 0;
}

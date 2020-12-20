// Lab_4_1_Sort.cpp : Определяет точку входа для приложения.
//
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <io.h>
#include <stdio.h>
#include "framework.h"
#include "Lab_4_2_next.hpp"
#include"WindowHelper.hpp"
#include"HashTableExt.hpp"
constexpr auto MAX_LOADSTRING = 100;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

LPCWSTR SMALL_FILE = L"Small.txt";
LPCWSTR MEDIUM_FILE = L"Medium.txt";
LPCWSTR LARGE_FILE = L"Large.txt";

SizeSeq sizeSeq = SizeSeq::SMALL;
SizeCash sizeCash= SizeCash::SMALL;
Alg alg = Alg::Alg1;
HashTableExt<PersonForIndex> * hashTableExt = nullptr;
Sequence < std::wstring > * seqIndex = new ArraySequence<std::wstring>();

HWND hInputSeqButton = nullptr;
HWND hStartButton = nullptr;

HWND hGetSeqButton = nullptr;
HWND hSaveSeqButton = nullptr;
//ИД
HWND hGrpButtonsID = nullptr;
HWND hLoadButton = nullptr;
HWND hLoadPathButton = nullptr;
HWND hGeneratorButton = nullptr;
//Длина последовательности
HWND hGrpButtonsLength = nullptr;
HWND hSmallButton = nullptr;
HWND hMediumButton = nullptr;
HWND hLargeButton = nullptr;
//Размер Кэша
HWND hGrpButtonsLengthCash = nullptr;
HWND hSmallButtonCash = nullptr;
HWND hMediumButtonCash = nullptr;
HWND hLargeButtonCash = nullptr;

//Алгоритм 1
HWND hGrpButtonsAlg1 = nullptr;
HWND hAlg1Button = nullptr;
HWND hAlg2Button = nullptr;
HWND hAlg3Button = nullptr;

HWND hSearchButton = nullptr;
HWND hSearchButtonFirstName = nullptr;
HWND hSearchButtonMiddleName = nullptr;
HWND hSearchButtonLastName = nullptr;
HWND hSearchButtonAge = nullptr;
//Тип последовательности 1
HWND hGrpButtonsSeq1 = nullptr;
HWND hArrayList1Button = nullptr;
HWND hLinkedlists1Button = nullptr;
//Алгоритм 2
HWND hGrpButtonsAlg2 = nullptr;
HWND hSortQuick2Button = nullptr;
HWND hSortHeap2Button = nullptr;
HWND hSortShell2Button = nullptr;
//Тип последовательности 2
HWND hGrpButtonsSeq2 = nullptr;
HWND hArrayList2Button = nullptr;
HWND hLinkedlists2Button = nullptr;
HWND hInputButtonLabel = nullptr;
HWND hOutputButtonLabel1 = nullptr;
HWND hOutpuSeqtButton1 = nullptr;
HWND hOutputButtonLabel2 = nullptr;
HWND hOutpuSeqtButton2 = nullptr;



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
    LoadStringW(hInstance, IDC_LAB41SORT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB41SORT));

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
    return static_cast<int>(msg.wParam);
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB41SORT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
    wcex.lpszMenuName = nullptr;// (IDC_LAB41SORT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, L"Лабораторная работа 2", WS_OVERLAPPEDWINDOW,
        250, 250, 725, 650, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
//BOOL CreateConsole(void)
//{
//    FreeConsole(); //на всякий случай
//    if (AllocConsole())
//    {
//        int hCrt = _open_osfhandle((long)
//            GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
//        *stdout = *(::_fdopen(hCrt, "w"));
//        ::setvbuf(stdout, NULL, _IONBF, 0);
//        *stderr = *(::_fdopen(hCrt, "w"));
//        ::setvbuf(stderr, NULL, _IONBF, 0);
//        return TRUE;
//    }
//    return FALSE;
//}
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
    {



        hGetSeqButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Начать тест",      // Button text , 
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 530, 220, 50, hWnd, (HMENU)9999, NULL, NULL);

        hStartButton = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Поиск",      // Button text , 
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 245, 530, 220, 50, hWnd, (HMENU)10000, NULL, NULL);
        EnableWindow(hStartButton, false);
        
        
                //Длина последовательности
        hGrpButtonsLength = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Длина последовательности:",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping 
            10, 10,
            320, 90,
            hWnd,
            NULL,
            hInst, NULL);
        hSmallButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Small",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            20, 30,
            300, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10004,
            hInst, NULL);

        hMediumButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Medium",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            20, 50,
            300, 20,
            hWnd,
            (HMENU)10005,
            hInst, NULL);
        hLargeButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Large",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            20, 70,
            300, 20,
            hWnd,
            (HMENU)10006,
            hInst, NULL);
        SendMessage(hSmallButton, BM_SETCHECK, BST_CHECKED, 0);
        //Размер КЭШ
        hGrpButtonsLengthCash = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Размер Кеша:",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping 
            10, 110,
            320, 90,
            hWnd,
            NULL,
            hInst, NULL);
        hSmallButtonCash = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"SmallCash",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            20, 130,
            300, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10204,
            hInst, NULL);

        hMediumButtonCash = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"MediumCash",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            20, 150,
            300, 20,
            hWnd,
            (HMENU)10205,
            hInst, NULL);
        hLargeButtonCash = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"LargeCash",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            20, 170,
            300, 20,
            hWnd,
            (HMENU)10206,
            hInst, NULL);
        SendMessage(hSmallButtonCash, BM_SETCHECK, BST_CHECKED, 0);
   		

        //Алгоритм 1
        hGrpButtonsAlg1 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"Задание:",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,// <----BS_GROUPBOX does nothing on the grouping 
            340, 10,
            320, 190,
            hWnd,
            NULL,
            hInst, NULL);
        hAlg1Button = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"И-6.1. Кеширование данных",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            350, 30,
            300, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10007,
            hInst, NULL);

        hAlg2Button = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"BUTTON",
            L"И-5. Индексирование данных",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
            350, 50,
            305, 20,
            hWnd,
            (HMENU)10008,
            hInst, NULL);
        
        SendMessage(hAlg1Button, BM_SETCHECK, BST_CHECKED, 0);
        hSearchButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"FirstName_0 MiddleName_0 LastName_0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            350, 70,
            305, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10002,
            hInst, NULL);
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"FirstName",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            350, 95,
            80, 30,
            hWnd,
            NULL,
            hInst, NULL);

        hSearchButtonFirstName = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            440, 95,
            215, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10002,
            hInst, NULL);
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"MiddleName",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            350, 120,
            80, 30,
            hWnd,
            NULL,
            hInst, NULL);
        hSearchButtonMiddleName = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            440, 120,
            215, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10002,
            hInst, NULL);
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"LastName",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            350, 145,
            80, 30,
            hWnd,
            NULL,
            hInst, NULL);
        hSearchButtonLastName = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            440, 145,
            215, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10002,
            hInst, NULL);
        CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Age",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            350, 170,
            80, 20,
            hWnd,
            NULL,
            hInst, NULL);
        hSearchButtonAge = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,  // <---- WS_GROUP group the following radio buttons 1st,2nd button 
            440, 170,
            215, 20,
            hWnd, //<----- Use main window handle
            (HMENU)10002,
            hInst, NULL);

    	
        hInputButtonLabel = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Консоль 1",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            10, 205,
            220, 30,
            hWnd,
            (HMENU)10017,
            hInst, NULL);
        hInputSeqButton = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Нет данных",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            10, 225,
            220, 300,
            hWnd, //<----- Use main window handle
            (HMENU)10018,
            hInst, NULL);
        hOutputButtonLabel1 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Консоль 2",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            245, 205,
            220, 30,
            hWnd,
            (HMENU)10019,
            hInst, NULL);
        hOutpuSeqtButton1 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Нет данных",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            245, 225,
            220, 300,
            hWnd, //<----- Use main window handle
            (HMENU)10020,
            hInst, NULL);

        hOutputButtonLabel2 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"Static",
            L"Консоль 3",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_READONLY,
            480, 205,
            220, 30,
            hWnd,
            (HMENU)10021,
            hInst, NULL);
        hOutpuSeqtButton2 = CreateWindowEx(WS_EX_WINDOWEDGE,
            L"edit",
            L"Нет данных",
            WS_VSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | ES_MULTILINE,
            480, 225,
            220, 300,
            hWnd, //<----- Use main window handle
            (HMENU)10022,
            hInst, NULL);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int len = 0;
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case 10004:
            SetWindowText(hLoadPathButton, SMALL_FILE);
            sizeSeq = SizeSeq::SMALL;
            break;
        case 10005:
            SetWindowText(hLoadPathButton, MEDIUM_FILE);
            sizeSeq = SizeSeq::MEDIUM;
            break;
        case 10006:
            SetWindowText(hLoadPathButton, LARGE_FILE);
            sizeSeq = SizeSeq::LARGE;
            break;
        case 10007:
            SetWindowText(hLoadPathButton, LARGE_FILE);
            EnableWindow(hStartButton, false);
            alg = Alg::Alg1;
            break;
        case 10008:
            SetWindowText(hLoadPathButton, LARGE_FILE);
            EnableWindow(hStartButton, true);
            alg = Alg::Alg2;
            break;
        case 10204:
            sizeCash = SizeCash::SMALL;
            break;
        case 10205:
            sizeCash = SizeCash::MEDIUM;
            break;
        case 10206:
            sizeCash = SizeCash::LARGE;
            break;
        case 9999:
            switch (alg)
            {
            case Alg::Alg1:
                testCash(sizeSeq, sizeCash, hInputSeqButton, hOutpuSeqtButton1, hOutpuSeqtButton2);
            	break;
            case Alg::Alg2:
                hashTableExt =  testIndex(seqIndex, sizeSeq, hInputSeqButton, hOutpuSeqtButton1, hOutpuSeqtButton2);
                break;
            default: ;
            }
            
            break;
        case 10000:
            testSearch(seqIndex, hashTableExt, hInputSeqButton, hOutpuSeqtButton1, hOutpuSeqtButton2,
                hSearchButton, hSearchButtonFirstName, hSearchButtonMiddleName, hSearchButtonLastName, hSearchButtonAge);
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


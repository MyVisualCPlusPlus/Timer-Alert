// 整点报时.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "整点报时.h"
#pragma comment(lib, "winmm.lib")

#define MAX_LOADSTRING 100
#define TIMER_ID 1001
// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
// 定时器回调函数
void CALLBACK ClockTimeProc(HWND, UINT message, UINT idTimer, DWORD dwTime);
int AutoOpen(HINSTANCE hInstance); // 开机启动

int g_arrWav[24] = {IDR_WAVE1, IDR_WAVE2, IDR_WAVE3, IDR_WAVE4, IDR_WAVE5, IDR_WAVE6, IDR_WAVE7, IDR_WAVE8, IDR_WAVE9, IDR_WAVE10, IDR_WAVE11, IDR_WAVE12, IDR_WAVE13, IDR_WAVE14, IDR_WAVE15, IDR_WAVE16, IDR_WAVE17, IDR_WAVE18, IDR_WAVE19, IDR_WAVE20, IDR_WAVE21, IDR_WAVE22, IDR_WAVE23, IDR_WAVE24};

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	SetTimer(NULL, TIMER_ID, 1000, ClockTimeProc);
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	KillTimer(NULL, TIMER_ID);
	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   
   if (!hWnd)
   {
      return FALSE;
   }
   AutoOpen(hInstance);

   ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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

//  [3/9/2017 Administrator]
// 定时器回调函数
void CALLBACK ClockTimeProc(HWND hWnd, UINT message, UINT idTimer, DWORD dwTime)
{
	// 添加报时代码
	time_t t = time(NULL);
	tm* pt = NULL;
	pt = localtime(&t);
	if (pt->tm_min == 0 && pt->tm_sec == 0)
	{
		int nWholeClock = pt->tm_hour;
		CHAR szFile[32];
		sprintf(szFile, "c:\\报时语音\\%d.wav",nWholeClock);
		BOOL bPlay = PlaySoundA(MAKEINTRESOURCEA(g_arrWav[nWholeClock]), NULL, SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		if (bPlay == FALSE)
		{
			MessageBoxA(NULL, "报时语音播放错误", "提醒", MB_OK);
			return;
		}
	}
}

int AutoOpen(HINSTANCE hInstance)
{

	char curPath[256];
	GetModuleFileNameA(hInstance, curPath, sizeof(curPath));
	//判断环境是否为WOW64  
	BOOL isWOW64;  
	REGSAM p;  
	IsWow64Process(GetCurrentProcess(),&isWOW64);  
	if (isWOW64){  
		p = KEY_WRITE | KEY_WOW64_64KEY;  
	}  
	else{  
		p = KEY_WRITE;  
	}  
	HKEY hKey;  
	if (RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, p, NULL, &hKey, NULL) != ERROR_SUCCESS){  
		//失败  
		return 0;  
	}  
	if (RegSetValueExA(hKey, "报时程序注册表", 0, REG_SZ, (BYTE*)curPath, sizeof(curPath))!= ERROR_SUCCESS){  
		//失败  
		return 0;  
	}  
	RegCloseKey(hKey);  
	
	return 0;
}
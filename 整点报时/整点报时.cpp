// ���㱨ʱ.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "���㱨ʱ.h"
#pragma comment(lib, "winmm.lib")

#define MAX_LOADSTRING 100
#define TIMER_ID 1001
// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
// ��ʱ���ص�����
void CALLBACK ClockTimeProc(HWND, UINT message, UINT idTimer, DWORD dwTime);
int AutoOpen(HINSTANCE hInstance); // ��������

int g_arrWav[24] = {IDR_WAVE1, IDR_WAVE2, IDR_WAVE3, IDR_WAVE4, IDR_WAVE5, IDR_WAVE6, IDR_WAVE7, IDR_WAVE8, IDR_WAVE9, IDR_WAVE10, IDR_WAVE11, IDR_WAVE12, IDR_WAVE13, IDR_WAVE14, IDR_WAVE15, IDR_WAVE16, IDR_WAVE17, IDR_WAVE18, IDR_WAVE19, IDR_WAVE20, IDR_WAVE21, IDR_WAVE22, IDR_WAVE23, IDR_WAVE24};

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	SetTimer(NULL, TIMER_ID, 1000, ClockTimeProc);
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
// ��ʱ���ص�����
void CALLBACK ClockTimeProc(HWND hWnd, UINT message, UINT idTimer, DWORD dwTime)
{
	// ��ӱ�ʱ����
	time_t t = time(NULL);
	tm* pt = NULL;
	pt = localtime(&t);
	if (pt->tm_min == 0 && pt->tm_sec == 0)
	{
		int nWholeClock = pt->tm_hour;
		CHAR szFile[32];
		sprintf(szFile, "c:\\��ʱ����\\%d.wav",nWholeClock);
		BOOL bPlay = PlaySoundA(MAKEINTRESOURCEA(g_arrWav[nWholeClock]), NULL, SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		if (bPlay == FALSE)
		{
			MessageBoxA(NULL, "��ʱ�������Ŵ���", "����", MB_OK);
			return;
		}
	}
}

int AutoOpen(HINSTANCE hInstance)
{

	char curPath[256];
	GetModuleFileNameA(hInstance, curPath, sizeof(curPath));
	//�жϻ����Ƿ�ΪWOW64  
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
		//ʧ��  
		return 0;  
	}  
	if (RegSetValueExA(hKey, "��ʱ����ע���", 0, REG_SZ, (BYTE*)curPath, sizeof(curPath))!= ERROR_SUCCESS){  
		//ʧ��  
		return 0;  
	}  
	RegCloseKey(hKey);  
	
	return 0;
}
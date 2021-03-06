// WindowsProject1.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WindowsProject1.h"
#include <shellapi.h>
#include <tchar.h> 
#include <windows.h>
#include <ShlObj.h>
//#include "resource1.h"
#define _WIN32_WINNT 0x0501
#define MAX_LOADSTRING 100
#define ID_EDIT 100
// 전역 변수:
HINSTANCE hInst;  
int nTop = 10;
int count = 0;
BOOL bShow = TRUE;
HWND hEdit;                              // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];				     // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];
WIN32_FIND_DATA FindFileData;
HANDLE hFind;
HINSTANCE hInstanceset;
HANDLE hFile;
HANDLE hlog;
wchar_t szFileData[1024];
wchar_t wcsFullPath[256] = L"C:\\Users\\Cafemug\\AppData\\Roaming\\Microsoft\\Internet Explorer\\Quick Launch\\test.txt";

// 기본 창 클래스 이름입니다.
int a = 0;
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
wchar_t DirSpec[265] = L"C:\\Users\\Cafemug\\AppData\\Roaming\\Microsoft\\Internet Explorer\\Quick Launch\\*";
wchar_t exeDir[256]= L"C:\\Users\\Cafemug\\AppData\\Roaming\\Microsoft\\Internet Explorer\\Quick Launch\\";
wchar_t temp[256] = { 0, };
wchar_t* Searchfile(wchar_t* filename) {
	WIN32_FIND_DATA FindFileData; 
	HANDLE hFind = INVALID_HANDLE_VALUE; 
	wchar_t DirSpec[265] = L""; // directory specification 
	DWORD dwError;
	
	wcscpy_s(DirSpec,filename);
	//wcsncat_s(DirSpec, L"\\*", 3);
	/*
	hFind = FindFirstFile(DirSpec, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		wprintf(L"Invalid file handle. Error is %u\n", GetLastError());
		return DirSpec;
	}
	else {
		wprintf(L"First file name is %s\n", FindFileData.cFileName);
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			wprintf(L"Next file name is %s\n", FindFileData.cFileName);
		}
		dwError = GetLastError();
		FindClose(hFind);
		if (dwError != ERROR_NO_MORE_FILES) {
			wprintf(L"FindNextFile error. Error is %u\n", dwError); return DirSpec;
		}
	}*/
	return DirSpec;
}


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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW-2);//(HBRUSH)GetStockObject(BLACK_BRUSH);//
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"Inkprogram", WS_OVERLAPPEDWINDOW,
      500, 300,500,150, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static char str[256];
	wchar_t wstr[256] = { 0, };
	//int len;
	int nLen = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, str, strlen(str), NULL, NULL);
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, str, 80, wstr, 80);
	
	switch (message)
	{
	case WM_CREATE:
					hEdit = CreateWindowW(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
						ES_AUTOHSCROLL, 10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, hInst, NULL);
					CreateWindowW(L"button", L"실행", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 10, 100, 25, hWnd, (HMENU)0, hInst, NULL);
					CreateWindowW(L"button", L"관리자로 실행", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250, 50, 100, 25, hWnd, (HMENU)1, hInst, NULL);
					CreateWindowW(L"button", L"설정", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 370, 10, 100, 25, hWnd, (HMENU)2, hInst, NULL);
					return 0;
	
	
	case WM_COMMAND:

	{		wchar_t file[MAX_LOADSTRING];
            // 메뉴 선택을 구문 분석합니다.
			int wmId = LOWORD(wParam);
            switch (wmId)
            {
			
            /*case IDM_ABOUT:
                
                break;
				*/
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case 2:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
				
			case 0:	
				GetWindowText(hEdit, wstr, 256);

				wcsncat_s(wstr, L".lnk", 4);
				//FindFileData = L"..";
				//MessageBox(hWnd, wstr, L"Button", MB_OK);
				hFind = FindFirstFile(DirSpec, &FindFileData);
				while (FindNextFile(hFind, &FindFileData) != 0)
				{
					//MessageBox(hWnd, (LPCWSTR)(wchar_t)wcslen(FindFileData.cFileName) , L"Button", MB_OK);
					//MessageBox(hWnd, FindFileData.cFileName, L"Button", MB_OK);
					if (!lstrcmpi(FindFileData.cFileName, wstr)) {
						wcscpy_s(temp,exeDir);
						//MessageBox(hWnd, temp, L"Button", MB_OK);
						wcsncat_s(temp, wstr, wcslen(wstr));
						//MessageBox(hWnd, FindFileData.cFileName, L"Button", MB_OK);
						//MessageBox(hWnd, exeDir, L"Button", MB_OK);
						ShellExecute(NULL, L"open", temp, NULL, NULL, SW_SHOW);
						
						FindClose(hFind);
						break;
					}
				}
				return 0;
			case 1:
				GetWindowText(hEdit, wstr, 256);

				wcsncat_s(wstr, L".lnk", 4);
				//FindFileData = L"..";
				//MessageBox(hWnd, wstr, L"Button", MB_OK);
				hFind = FindFirstFile(DirSpec, &FindFileData);
				while (FindNextFile(hFind, &FindFileData) != 0)
				{
					//MessageBox(hWnd, (LPCWSTR)(wchar_t)wcslen(FindFileData.cFileName) , L"Button", MB_OK);
					//MessageBox(hWnd, FindFileData.cFileName, L"Button", MB_OK);
					if (!lstrcmpi(FindFileData.cFileName, wstr)) {
						wcscpy_s(temp, exeDir);
						//MessageBox(hWnd, temp, L"Button", MB_OK);
						wcsncat_s(temp, wstr, wcslen(wstr));
						//MessageBox(hWnd, FindFileData.cFileName, L"Button", MB_OK);
						//MessageBox(hWnd, exeDir, L"Button", MB_OK);
						ShellExecute(NULL, L"runas", temp, NULL, NULL, SW_SHOW);

						FindClose(hFind);
						break;
					}
				}
				return 0;;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	
	
    case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		
		
		

		TextOut(hdc, 30, 50, wstr, strlen(str));
			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
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
int createtext1(wchar_t* text){
	
	hFile = CreateFile(
		wcsFullPath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, NULL
	);
	if (hFile != INVALID_HANDLE_VALUE) {
		if (hlog != INVALID_HANDLE_VALUE) {
			CloseHandle(hlog);

		}
		hlog = hFile;
	}
	else {
		if (hlog == INVALID_HANDLE_VALUE) {
			hlog= CreateFile(
				wcsFullPath,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ, NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL
			);
			SetFilePointer(hlog, 0, NULL, FILE_END);
		}
		if (hlog != INVALID_HANDLE_VALUE) {
			DWORD dwWritten;
			lstrcat(text, L"\n");

			WriteFile(hFile, text, 2 * wcslen(text), &dwWritten, NULL);
		}

	}
	
	//CloseHandle(hFile);
	return 0;
}
wchar_t* readtext1(void) {
	DWORD dwRead=0;
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	ReadFile(hFile, szFileData, sizeof szFileData, &dwRead, NULL);
	szFileData[dwRead] = 0;
	



	return szFileData;
	

}
int writetext1()
{
	
	return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	OPENFILENAME OFN;

	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	TCHAR lpCurrDir[MAX_PATH] = TEXT("");
	TCHAR szmsg[] = TEXT("마우스 왼쪽 버튼으로 클릭하세요");
	TCHAR filter[] = TEXT("Every File(*.*) \0*.*\0Text File\0*.txt;*.doc\0");
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		int wmId = LOWORD(wParam);
		
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		switch (wmId){
		case IDC_BUTTON1:
			
			
			/*
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hDlg;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = MAX_PATH;
			OFN.lpstrInitialDir = TEXT(".");
			// 
			GetCurrentDirectory(sizeof(lpCurrDir), lpCurrDir);
			MessageBox(hDlg, lpCurrDir, TEXT("GetOpenFileName 실행전 현재디렉토리"), MB_OK);
			if (GetOpenFileName(&OFN) == 0)
			{
				break;
			}
			
			GetCurrentDirectory(sizeof(lpCurrDir), lpCurrDir);
			MessageBox(hDlg, lpCurrDir, TEXT("GetOpenFileName 실행후 현재디렉토리"), MB_OK);
			writetext1(lpCurrDir);
			MessageBox(hDlg, szFileData, TEXT("GetOpenFileName 실행후 현재디렉토리"), MB_OK);
			return 0;*/
			BROWSEINFO   bi;

			LPITEMIDLIST  idl;

			TCHAR szPathname[MAX_PATH] = { 0, };



			ZeroMemory(&bi, sizeof(BROWSEINFO));

			bi.hwndOwner = hDlg;

			bi.pszDisplayName = szPathname;  // 선택된 디렉토리명 저장 

			bi.lpszTitle = _T("폴더를 선택해 주세요");

			bi.ulFlags = BIF_EDITBOX    // 선택된 디렉토리명을 표시하고 편집할 수 있는 창

				| 0x0040;            // 새로운 디렉토리를 만들수 있는 버튼 추가 



			idl = SHBrowseForFolder(&bi);

			if (idl)

			{

				SHGetPathFromIDList(idl, szPathname);
				MessageBox(hDlg, szPathname, TEXT("GetOpenFileName 실행후 현재디렉토리"), MB_OK);
				createtext1(szPathname);
				//writetext1(szPathname);
				//MessageBox(hDlg, readtext1(), TEXT("GetOpenFileName 실행후 현재디렉토리"), MB_OK);
				//m_strDirPath.Format(_T("%s"), szPathname);

			}



		
			break;
		}
	
	}
	return (INT_PTR)FALSE;
}
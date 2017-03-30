#pragma once
#include<Windows.h>
#include"resource.h"
#include<CommCtrl.h>
//#include<Textserv.h>
#define BUFSIZE 1024
#include"alloperation.h"
#include"treeoperation.h"
#include"listoperation.h"
#pragma comment(lib,"listoperation.lib")
#pragma comment(lib,"treeoperation.lib")
#pragma comment(lib,"alloperation.lib")
//º¯ÊýÉùÃ÷
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateTreeView(HWND hwndParent, LPCWSTR szWindowName);
HWND CreateListView(HWND hwndParent, LPCWSTR szWindowName);
HWND CreateEdit(HWND hwndP, LPCWSTR szTitle);
DWORD SetWindows(LPRECT lpRect);

BOOL OnRclickList(NMHDR* pNMHDR);
BOOL OnclickList(NMHDR* pNMHDR);
BOOL OnRclickTree(NMHDR* pNMHDR);
BOOL OnclickTree(NMHDR* pNMHDR, LPNMHDR phdr);
BOOL OnChildWindowsNotify(PVOID pParam);
BOOL OnWindowResize();
VOID APIENTRY DisplayContextMenu(HWND hwnd, POINT pt,int ID);
LRESULT CALLBACK ABOUT(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

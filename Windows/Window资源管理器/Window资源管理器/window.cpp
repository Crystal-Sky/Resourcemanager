#pragma once
#include"window.h"
HWND hwndTreeView;
HWND hwndListView;
HWND hwndEdit;
HWND hwndMain;
HWND hwndPath;
HINSTANCE hinst;
/**************************************
*功能：显示一个窗口
**************************************/
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcx;//窗口类
	HWND hwnd;//窗口句柄
	MSG msg;//消息
	RECT rect;
	BOOL fGotMessage;//是否成功获取消息
	hinst = hinstance;//应用程序实例句柄，保存为全局变量
	//填充窗口类的数据结构
	wcx.cbSize = sizeof(wcx);//结构体的大小
	wcx.style = CS_HREDRAW | CS_VREDRAW;//样式：大小改变时重绘界面
	wcx.lpfnWndProc = MainWndProc;//窗口消息处理函数
	wcx.cbClsExtra = 0;//不使用类内存
	wcx.cbWndExtra = 0;//不使用窗口内存
	wcx.hInstance = hinstance;//所属的应用程序实例句柄
	wcx.hIcon = LoadIcon(NULL, L"folder.ico");//图标：默认IDI_APPLICATION
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//光标：默认
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景：白色WHITE_BRUSH
	wcx.lpszMenuName = NULL;//菜单：不使用
	wcx.lpszClassName = L"MainWClass";//窗口类名
	wcx.hIconSm = (HICON)LoadImage(hinstance,//小图标
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CXSMICON),
		LR_DEFAULTCOLOR);
	//注册窗口类
	if (!RegisterClassEx(&wcx))
	{
		return 1;
	}
	//创建窗口
	hwnd = CreateWindow(
		L"MainWClass",//窗口名
		L"Windows资源管理器",//窗口标题
		WS_OVERLAPPEDWINDOW,//窗口样式
		CW_USEDEFAULT,//水平位置X：默认
		CW_USEDEFAULT,//垂直位置Y：默认
		800,//宽度：默认
		600,//高度：默认
		(HWND)NULL,//父窗口：无
		(HMENU)::LoadMenu(hinst, MAKEINTRESOURCE(IDR_MAINWINDOW)),
		hinstance,//应用程序实例句柄
		(LPVOID)NULL);//窗口创建时数据：无
	if (!hwnd)
	{
		return FALSE;
	}
	// 获取本窗口客户区的RECT（矩形方框的四个边界点）
	GetClientRect(hwnd, &rect);
	// 设置子窗口的大小的位置
	hwndMain = hwnd;
	hwndTreeView = CreateTreeView(hwnd, L"文件夹");
	hwndListView = CreateListView(hwnd, L"文件");
	hwndEdit = CreateEdit(hwnd, L"搜索");
	hwndPath = CreateEdit(hwnd, NULL);
	// 获取本窗口客户区的RECT（矩形方框的四个边界点）
	GetClientRect(hwnd, &rect);
	// 设置子窗口的大小的位置
	SetWindows(&rect);

	InitTreeViewItems(hwndTreeView);
	InitListView(hwndListView);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//消息循环
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		if (msg.message == WM_KEYDOWN &&msg.wParam == VK_RETURN)
		{
			dwTotalFileNum = 0;
			ListView_DeleteAllItems(hwndListView);
			search(hwndEdit,hwndListView);
		}
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/********************************
*MainWndProc
*功能：窗口消息处理函数，
对所有的消息都使用默认处理函数
********************************/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:		// 窗口大小改变时
		OnWindowResize();
		break;
	case WM_NOTIFY:
		OnChildWindowsNotify((PVOID)lParam);
		break;
	case WM_COMMAND://处理应用程序菜单
		switch (LOWORD(wParam))
		{//在“帮助”菜单中选择“关于”
		case ID_40001://新建
		{
						  createfile(hinst, hwnd);
		return true;
		}
		break;
		case ID_40002://打开
		{
						  openfile(hinst, hwnd);
		return true;
		}
		break;
		case ID_40003://文件操作
		{
						  fileoperation(hinst, hwnd);
		return true;
		}
		break;
		case ID_40004://目录操作
		{
						  diroperation(hinst, hwnd);
		return true;
		}
		break;
		case ID_ABOUT:
		{
						 DialogBox(hinst, (LPCTSTR)IDD_DIALOG1, hwnd, (DLGPROC)ABOUT);
		}
		default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK ABOUT(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
					 EndDialog(hDlg, LOWORD(wParam));
					 return true;
		}
			break;
		case IDCANCEL:
		{
						 EndDialog(hDlg, LOWORD(wParam));
						 return true;
		}
			break;
		}

	}
	return false;
}
HWND CreateTreeView(HWND hwndParent, LPCWSTR szWindowName)
{
	HWND hwndTV;
	// 创建Tree View
	hwndTV = CreateWindowEx(0,
		WC_TREEVIEW,		//	Tree View控制窗口类
		szWindowName,	// 窗口的标题
		// 窗口样式 ：可见，子窗口，可改变大小，具体窗口标题
		WS_VISIBLE | WS_CHILD | WS_SIZEBOX | WS_TILED |
		// 附加Tree View样式
		TVS_HASBUTTONS | TVS_LINESATROOT,
		// 默认大小和位置，后面使用SetWindows函数设置
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hwndParent,		// 父窗口句柄
		(HMENU)NULL,	// 没有菜单
		hinst,		// 应用程序实例
		NULL);		// 没有图标
	return hwndTV;
}
HWND CreateListView(HWND hwndParent, LPCWSTR szWindowName)
{
	HWND hWndListView;
	// 创建List View
	hWndListView = CreateWindow(
		WC_LISTVIEW, // List View窗口类
		// 窗口标题，由于未指定 WS_TILED ，这是一个无标题的窗口
		szWindowName,
		// 窗口样式，可视，子窗口，以及List View样式
		WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS | WS_BORDER,
		// 位置和大小，创建完成后使用SetWindows设置
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hwndParent,		// 父窗口
		NULL, hinst, NULL);	// 无菜单，无图标
	if (hWndListView == NULL)
	{
		return NULL;
	}
	return hWndListView;
}
HWND CreateEdit(HWND hwndP, LPCWSTR szTitle)
{
	HWND hwnd;

	hwnd = CreateWindow(
		WC_EDIT, // 文本编译控件
		szTitle, // 没有标题
		// 窗口样式
		WS_CHILD | WS_VISIBLE | WS_BORDER |
		// 文本框样式
		ES_LEFT | ES_MULTILINE | ES_WANTRETURN,
		// 位置和大小
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hwndP, // 父窗口
		(HMENU)NULL, // 无菜单
		hinst, // 实例句柄
		(LPVOID)NULL); // 无图标

	if (!hwnd)
	{
		return NULL;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return hwnd;
}
DWORD SetWindows(LPRECT lpRect)
{
	SetWindowPos(hwndTreeView, HWND_TOP,
		lpRect->left, lpRect->top,
		lpRect->right *0.2, lpRect->bottom,
		SWP_SHOWWINDOW);
	SetWindowPos(hwndPath, HWND_TOP,
		lpRect->right * 0.2, lpRect->top,
		lpRect->right * 0.6, lpRect->bottom * 0.05,
		SWP_SHOWWINDOW);
	SetWindowPos(hwndEdit, HWND_TOP,
		lpRect->right * 0.8, lpRect->top,
		lpRect->right * 0.9, lpRect->bottom * 0.05,
		SWP_SHOWWINDOW);
	SetWindowPos(hwndListView, HWND_TOP,
		lpRect->right * 0.2, lpRect->bottom * 0.05,
		lpRect->right * 0.9, lpRect->bottom * 0.95,
		SWP_SHOWWINDOW);
	return 0;
}
BOOL OnChildWindowsNotify(PVOID pParam)
{
	LPNMHDR phdr = (LPNMHDR)pParam;
	// 只处理Tree View发送的Notify，其他不处理
	if (phdr->hwndFrom == hwndTreeView)
	{
		switch (((LPNMHDR)pParam)->code)
		{
			// 如果是右键单击，则调用OnRclickTree函数弹出右键菜单
		case NM_CLICK:
			OnclickTree((LPNMHDR)pParam, phdr);
			break;
		case NM_RCLICK:
			OnRclickTree((LPNMHDR)pParam);
			break;
		default:
			break;
		}
	}
	else if (phdr->hwndFrom == hwndListView)
	{
		switch (((LPNMHDR)pParam)->code)
		{
			// 如果是右键单击，则调用OnRclickTree函数弹出右键菜单
		case NM_DBLCLK:
			OnclickList((LPNMHDR)pParam);
			//MessageBox(NULL, TEXT("提示"), TEXT("提示"), 0);
			break;
		case NM_CLICK:
			//OnclickList((LPNMHDR)pParam);
			//MessageBox(NULL, TEXT("提示"), TEXT("提示"), 0);
			break;
		case NM_RCLICK:
			//MessageBox(NULL, TEXT("提示"), TEXT("提示"), 0);
			OnRclickList((LPNMHDR)pParam);
			break;
		default:
			break;
		}
	}
	else
		return FALSE;
	return TRUE;
}
BOOL OnclickList(NMHDR* pNMHDR)
{	
	LVITEM lvI;
	ZeroMemory(&lvI, sizeof(lvI));
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	// 填充LVITEM
	lvI.state = 0;
	lvI.stateMask = 0;
	lvI.iItem = dwTotalFileNum;
	lvI.iImage = 0;
	lvI.iSubItem = 0;
	// 项的文本和长度
	TCHAR text[MAX_PATH];
	lvI.pszText = text;
	lvI.cchTextMax =MAX_PATH;
	POINT point;
	LV_HITTESTINFO to;	
	GetCursorPos(&point);
	ScreenToClient(hwndListView, &point);
	to.pt = point;
	to.flags = TVHT_TOLEFT;
	int i=ListView_HitTest(hwndListView, &to);
	if (i != -1)
	{
		ClientToScreen(hwndTreeView, &point);
		ListView_GetItemText(hwndListView, i, 0, lvI.pszText, lvI.cchTextMax);
		TCHAR szTextToShow[MAX_PATH];
		SendMessage(hwndPath, WM_GETTEXT, MAX_PATH, (LPARAM)(void*)szTextToShow);
		wsprintf(szTextToShow, L"%s\\%s", szTextToShow, lvI.pszText);
		//MessageBox(NULL, szTextToShow, TEXT("提示"), MB_OK);
		WIN32_FILE_ATTRIBUTE_DATA data;
		GetFileAttributesEx(szTextToShow, GetFileExInfoStandard, &data);
		if (data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			SendMessage(hwndPath, WM_SETTEXT, 0, (LPARAM)szTextToShow);
			ListView_DeleteAllItems(hwndListView);
			AddListViewItems(hwndListView, szTextToShow);
		}
	}	
	//DisplayContextMenu(hwndMain, point);
	return TRUE;
}
BOOL OnRclickTree(NMHDR* pNMHDR)
{
	POINT point;
	TVHITTESTINFO thti;
	HTREEITEM htItem;
	GetCursorPos(&point);
	ScreenToClient(hwndTreeView, &point);
	thti.pt = point;
	thti.flags = TVHT_TORIGHT;
	htItem = TreeView_HitTest(hwndTreeView, &thti);
	if (htItem != NULL)
	{
		ClientToScreen(hwndTreeView, &point);
		TreeView_SelectItem(hwndTreeView, htItem);
		DisplayContextMenu(hwndMain, point,IDR_MENU_POP);
		return TRUE;
	}

	return FALSE;
}
BOOL OnRclickList(NMHDR* pNMHDR)
{
	LVITEM lvI;
	ZeroMemory(&lvI, sizeof(lvI));
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	// 填充LVITEM
	lvI.state = 0;
	lvI.stateMask = 0;
	lvI.iItem = dwTotalFileNum;
	lvI.iImage = 0;
	lvI.iSubItem = 0;
	// 项的文本和长度
	TCHAR text[MAX_PATH];
	lvI.pszText = text;
	lvI.cchTextMax = MAX_PATH;
	POINT point;
	LV_HITTESTINFO to;
	GetCursorPos(&point);
	ScreenToClient(hwndListView, &point);
	to.pt = point;
	to.flags = TVHT_TOLEFT;
	int i = ListView_HitTest(hwndListView, &to);
	if (i != -1)
	{
		ClientToScreen(hwndTreeView, &point);
		DisplayContextMenu(hwndMain, point,IDR_MENU_POPER);
		return TRUE;
		//ListView_GetItemText(hwndListView, i, 0, lvI.pszText, lvI.cchTextMax);
		//TCHAR szTextToShow[MAX_PATH];
		//SendMessage(hwndPath, WM_GETTEXT, MAX_PATH, (LPARAM)(void*)szTextToShow);
		//wsprintf(szTextToShow, L"%s\\%s", szTextToShow, lvI.pszText);
		//MessageBox(NULL, szTextToShow, TEXT("提示"), MB_OK);
		//WIN32_FILE_ATTRIBUTE_DATA data;
		//GetFileAttributesEx(szTextToShow, GetFileExInfoStandard, &data);
		//if (data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		//{
		//	SendMessage(hwndPath, WM_SETTEXT, 0, (LPARAM)szTextToShow);
		//	ListView_DeleteAllItems(hwndListView);
		//	AddListViewItems(hwndListView, szTextToShow);
		//}
	}
	else
	{
		ClientToScreen(hwndTreeView, &point);
		DisplayContextMenu(hwndMain, point, IDR_MENU_POP);
		return TRUE;
	}
	//DisplayContextMenu(hwndMain, point);
	return FALSE;
}
BOOL OnclickTree(NMHDR* pNMHDR, LPNMHDR phdr)
{
	POINT point;
	TVHITTESTINFO thti;
	HTREEITEM htItem;

	// 获取鼠标的位置
	GetCursorPos(&point);

	// 计算相对Client的鼠标位置，
	// TreeView_HitTest要求的鼠标位置是相对于Client
	ScreenToClient(hwndTreeView, &point);
	// 填充TVHITTESTINFO结构
	thti.pt = point;
	thti.flags = LVHT_TOLEFT;
	htItem = TreeView_HitTest(hwndTreeView, &thti);
	if (htItem != NULL)
	{
		ClientToScreen(hwndTreeView, &point);
		TreeView_SelectItem(hwndTreeView, htItem);
		TVITEM ti = { 0 };
		ti.mask = TVIF_HANDLE | TVIF_TEXT;
		TCHAR szPath[MAX_PATH] = { 0 };
		ti.cchTextMax = MAX_PATH;
		ti.pszText = szPath;
		ti.hItem = htItem;
		TreeView_GetItem(phdr->hwndFrom, &ti);
		TCHAR buf[5] = L"\\\0";

		TCHAR current[MAX_PATH];
		TVITEM to = { 0 };
		to.mask = TVIF_HANDLE | TVIF_TEXT;
		to.cchTextMax = MAX_PATH;
		to.pszText = current;
		
		HTREEITEM parent = TreeView_GetParent(hwndTreeView, htItem);
		while (parent != NULL)
		{
			to.hItem = parent;
			TreeView_GetItem(phdr->hwndFrom, &to);
			lstrcatW(to.pszText, buf);
			lstrcatW(to.pszText, ti.pszText);
			wcscpy_s(ti.pszText, MAX_PATH, to.pszText);
			parent = TreeView_GetParent(hwndTreeView, parent);
		}
		SendMessage(hwndPath, WM_SETTEXT, 0, (LPARAM)ti.pszText);
		TCHAR currentp[MAX_PATH];
		TVITEM tp = { 0 };
		tp.mask = TVIF_HANDLE | TVIF_TEXT;
		tp.cchTextMax = MAX_PATH;
		tp.pszText = currentp;
		TCHAR cp[MAX_PATH];
		LPWSTR CP = cp;
		HTREEITEM child = TreeView_GetChild(hwndTreeView, htItem);	
		//int i = 1;
		while (child!=NULL)
		{
			wcscpy_s(cp, MAX_PATH, ti.pszText);
			tp.hItem = child;
			TreeView_GetItem(hwndTreeView, &tp);
			lstrcatW(cp, buf);
			lstrcatW(cp, tp.pszText);
			if (!TreeView_GetChild(hwndTreeView,child))
				FindInAll(cp, child, hwndTreeView);
			child = TreeView_GetNextItem(hwndTreeView, child, 1);
		}
		ListView_DeleteAllItems(hwndListView);
		AddListViewItems(hwndListView, ti.pszText);
		return TRUE;
	}
	return FALSE;
}
BOOL OnWindowResize()
{
	RECT rcClient;
	GetClientRect(hwndMain, &rcClient);
	SetWindows(&rcClient);
	return TRUE;
}
VOID APIENTRY DisplayContextMenu(HWND hwnd, POINT pt,int ID)
{
	HMENU hmenu; // 顶级菜单
	HMENU hmenuTrackPopup; // 弹出菜单

	// 加载菜单资源，获得菜单句柄
	if ((hmenu = LoadMenu(hinst, MAKEINTRESOURCE(ID))) == NULL)
		return;

	// 获得菜单资源中的子菜单，所显示的是菜单资源中的子菜单
	hmenuTrackPopup = GetSubMenu(hmenu, 0);
	// 弹出
	TrackPopupMenuEx(hmenuTrackPopup,
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		pt.x, pt.y, hwnd, NULL);
	// 完成，释放相关资源
	DestroyMenu(hmenu);
}
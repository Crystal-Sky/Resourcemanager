#pragma once
#include"window.h"
HWND hwndTreeView;
HWND hwndListView;
HWND hwndEdit;
HWND hwndMain;
HWND hwndPath;
HINSTANCE hinst;
/**************************************
*���ܣ���ʾһ������
**************************************/
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcx;//������
	HWND hwnd;//���ھ��
	MSG msg;//��Ϣ
	RECT rect;
	BOOL fGotMessage;//�Ƿ�ɹ���ȡ��Ϣ
	hinst = hinstance;//Ӧ�ó���ʵ�����������Ϊȫ�ֱ���
	//��䴰��������ݽṹ
	wcx.cbSize = sizeof(wcx);//�ṹ��Ĵ�С
	wcx.style = CS_HREDRAW | CS_VREDRAW;//��ʽ����С�ı�ʱ�ػ����
	wcx.lpfnWndProc = MainWndProc;//������Ϣ������
	wcx.cbClsExtra = 0;//��ʹ�����ڴ�
	wcx.cbWndExtra = 0;//��ʹ�ô����ڴ�
	wcx.hInstance = hinstance;//������Ӧ�ó���ʵ�����
	wcx.hIcon = LoadIcon(NULL, L"folder.ico");//ͼ�꣺Ĭ��IDI_APPLICATION
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//��꣺Ĭ��
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//��������ɫWHITE_BRUSH
	wcx.lpszMenuName = NULL;//�˵�����ʹ��
	wcx.lpszClassName = L"MainWClass";//��������
	wcx.hIconSm = (HICON)LoadImage(hinstance,//Сͼ��
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CXSMICON),
		LR_DEFAULTCOLOR);
	//ע�ᴰ����
	if (!RegisterClassEx(&wcx))
	{
		return 1;
	}
	//��������
	hwnd = CreateWindow(
		L"MainWClass",//������
		L"Windows��Դ������",//���ڱ���
		WS_OVERLAPPEDWINDOW,//������ʽ
		CW_USEDEFAULT,//ˮƽλ��X��Ĭ��
		CW_USEDEFAULT,//��ֱλ��Y��Ĭ��
		800,//��ȣ�Ĭ��
		600,//�߶ȣ�Ĭ��
		(HWND)NULL,//�����ڣ���
		(HMENU)::LoadMenu(hinst, MAKEINTRESOURCE(IDR_MAINWINDOW)),
		hinstance,//Ӧ�ó���ʵ�����
		(LPVOID)NULL);//���ڴ���ʱ���ݣ���
	if (!hwnd)
	{
		return FALSE;
	}
	// ��ȡ�����ڿͻ�����RECT�����η�����ĸ��߽�㣩
	GetClientRect(hwnd, &rect);
	// �����Ӵ��ڵĴ�С��λ��
	hwndMain = hwnd;
	hwndTreeView = CreateTreeView(hwnd, L"�ļ���");
	hwndListView = CreateListView(hwnd, L"�ļ�");
	hwndEdit = CreateEdit(hwnd, L"����");
	hwndPath = CreateEdit(hwnd, NULL);
	// ��ȡ�����ڿͻ�����RECT�����η�����ĸ��߽�㣩
	GetClientRect(hwnd, &rect);
	// �����Ӵ��ڵĴ�С��λ��
	SetWindows(&rect);

	InitTreeViewItems(hwndTreeView);
	InitListView(hwndListView);
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//��Ϣѭ��
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
*���ܣ�������Ϣ��������
�����е���Ϣ��ʹ��Ĭ�ϴ�����
********************************/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:		// ���ڴ�С�ı�ʱ
		OnWindowResize();
		break;
	case WM_NOTIFY:
		OnChildWindowsNotify((PVOID)lParam);
		break;
	case WM_COMMAND://����Ӧ�ó���˵�
		switch (LOWORD(wParam))
		{//�ڡ��������˵���ѡ�񡰹��ڡ�
		case ID_40001://�½�
		{
						  createfile(hinst, hwnd);
		return true;
		}
		break;
		case ID_40002://��
		{
						  openfile(hinst, hwnd);
		return true;
		}
		break;
		case ID_40003://�ļ�����
		{
						  fileoperation(hinst, hwnd);
		return true;
		}
		break;
		case ID_40004://Ŀ¼����
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
	// ����Tree View
	hwndTV = CreateWindowEx(0,
		WC_TREEVIEW,		//	Tree View���ƴ�����
		szWindowName,	// ���ڵı���
		// ������ʽ ���ɼ����Ӵ��ڣ��ɸı��С�����崰�ڱ���
		WS_VISIBLE | WS_CHILD | WS_SIZEBOX | WS_TILED |
		// ����Tree View��ʽ
		TVS_HASBUTTONS | TVS_LINESATROOT,
		// Ĭ�ϴ�С��λ�ã�����ʹ��SetWindows��������
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hwndParent,		// �����ھ��
		(HMENU)NULL,	// û�в˵�
		hinst,		// Ӧ�ó���ʵ��
		NULL);		// û��ͼ��
	return hwndTV;
}
HWND CreateListView(HWND hwndParent, LPCWSTR szWindowName)
{
	HWND hWndListView;
	// ����List View
	hWndListView = CreateWindow(
		WC_LISTVIEW, // List View������
		// ���ڱ��⣬����δָ�� WS_TILED ������һ���ޱ���Ĵ���
		szWindowName,
		// ������ʽ�����ӣ��Ӵ��ڣ��Լ�List View��ʽ
		WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS | WS_BORDER,
		// λ�úʹ�С��������ɺ�ʹ��SetWindows����
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hwndParent,		// ������
		NULL, hinst, NULL);	// �޲˵�����ͼ��
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
		WC_EDIT, // �ı�����ؼ�
		szTitle, // û�б���
		// ������ʽ
		WS_CHILD | WS_VISIBLE | WS_BORDER |
		// �ı�����ʽ
		ES_LEFT | ES_MULTILINE | ES_WANTRETURN,
		// λ�úʹ�С
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		hwndP, // ������
		(HMENU)NULL, // �޲˵�
		hinst, // ʵ�����
		(LPVOID)NULL); // ��ͼ��

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
	// ֻ����Tree View���͵�Notify������������
	if (phdr->hwndFrom == hwndTreeView)
	{
		switch (((LPNMHDR)pParam)->code)
		{
			// ������Ҽ������������OnRclickTree���������Ҽ��˵�
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
			// ������Ҽ������������OnRclickTree���������Ҽ��˵�
		case NM_DBLCLK:
			OnclickList((LPNMHDR)pParam);
			//MessageBox(NULL, TEXT("��ʾ"), TEXT("��ʾ"), 0);
			break;
		case NM_CLICK:
			//OnclickList((LPNMHDR)pParam);
			//MessageBox(NULL, TEXT("��ʾ"), TEXT("��ʾ"), 0);
			break;
		case NM_RCLICK:
			//MessageBox(NULL, TEXT("��ʾ"), TEXT("��ʾ"), 0);
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
	// ���LVITEM
	lvI.state = 0;
	lvI.stateMask = 0;
	lvI.iItem = dwTotalFileNum;
	lvI.iImage = 0;
	lvI.iSubItem = 0;
	// ����ı��ͳ���
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
		//MessageBox(NULL, szTextToShow, TEXT("��ʾ"), MB_OK);
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
	// ���LVITEM
	lvI.state = 0;
	lvI.stateMask = 0;
	lvI.iItem = dwTotalFileNum;
	lvI.iImage = 0;
	lvI.iSubItem = 0;
	// ����ı��ͳ���
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
		//MessageBox(NULL, szTextToShow, TEXT("��ʾ"), MB_OK);
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

	// ��ȡ����λ��
	GetCursorPos(&point);

	// �������Client�����λ�ã�
	// TreeView_HitTestҪ������λ���������Client
	ScreenToClient(hwndTreeView, &point);
	// ���TVHITTESTINFO�ṹ
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
	HMENU hmenu; // �����˵�
	HMENU hmenuTrackPopup; // �����˵�

	// ���ز˵���Դ����ò˵����
	if ((hmenu = LoadMenu(hinst, MAKEINTRESOURCE(ID))) == NULL)
		return;

	// ��ò˵���Դ�е��Ӳ˵�������ʾ���ǲ˵���Դ�е��Ӳ˵�
	hmenuTrackPopup = GetSubMenu(hmenu, 0);
	// ����
	TrackPopupMenuEx(hmenuTrackPopup,
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		pt.x, pt.y, hwnd, NULL);
	// ��ɣ��ͷ������Դ
	DestroyMenu(hmenu);
}
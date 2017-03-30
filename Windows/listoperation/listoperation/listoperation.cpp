#include"listoperation.h"
BOOL itListViewImageLists(HWND hWndListView)
{
	HIMAGELIST himl;
	//HBITMAP hbmp;
	// 调用 GetImageList 获得ImageList
	itGetImageList(&himl);
	// 设置 List View的的 ImageList
	ListView_SetImageList(hWndListView, himl, LVSIL_SMALL);
	return TRUE;
}
BOOL itListViewColumns(HWND hWndListView)
{
	TCHAR szText[256];
	LVCOLUMN lvc;
	DWORD i;
	// 分栏标题
	LPWSTR ColNames[] = { L"名称", L"修改日期", L"类型", L"大小" };
	// LVCOLUMN中有效的成员
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	// 填充LVCOLUMN结构
	lvc.pszText = szText;
	lvc.cx = 250;						// 长度
	lvc.iImage = 1;
	lvc.fmt = LVCFMT_LEFT;	// 向左对齐
	// 前三个
	for (i = 0; i<3; i++)
	{
		//	设置栏的文本
		lvc.pszText = ColNames[i];
		lvc.iSubItem = i;
		// 调用ListView_InsertColumn插入分栏
		if (ListView_InsertColumn(hWndListView, i, &lvc) == -1)
		{
			return FALSE;
		}
	}
	// 最后一个分栏
	lvc.cx = 200; // 长度
	lvc.fmt = LVCFMT_RIGHT; // 右对齐
	lvc.iSubItem = 3;
	lvc.pszText = ColNames[3];
	// 插入分栏
	if (ListView_InsertColumn(hWndListView, 3, &lvc) == -1)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL itaddListViewItems(HWND hwndListView, LPCWSTR szPath)
{
	LVITEM lvI;

	ZeroMemory(&lvI, sizeof(lvI));
	// 有效的项
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	// 填充LVITEM
	lvI.state = 0;
	lvI.stateMask = 0;
	TCHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	TCHAR szFullPath[MAX_PATH];
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, L"\\*");
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, TEXT("无法写入文件"), L"提示", MB_OK);
		//printf("错误：%d", GetLastError());
		//return FALSE;
	}
	else
	{
		do
		{
			if ((lstrcmp(FindFileData.cFileName, TEXT(".")) == 0) ||
				(lstrcmp(FindFileData.cFileName, TEXT("..")) == 0))///
			{
				continue;
			}
			wsprintf(szFullPath, L"%s\\%s", szPath, FindFileData.cFileName);
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN)
			{
				continue;
			}
			dwTotalFileNum++;
			//printf("\n%d\t%s\t", dwTotalFileNum, szFullPath);
			lvI.iItem = dwTotalFileNum;
			lvI.iImage = 0;
			lvI.iSubItem = 0;
			// 项的文本和长度
			lvI.pszText = szFullPath;
			lvI.cchTextMax = lstrlen(lvI.pszText) + 1;
			// 插入项
			if (ListView_InsertItem(hwndListView, &lvI) == -1)
				return FALSE;
			// 设置子项的文本，0 based
			//ListView_SetItemText(hwndListView, dwTotalFileNum, 2, L"size a");
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				//printf("<DIR>");
				itaddListViewItems(hwndListView, szFullPath);

			}

		} while (FindNextFile(hListFile, &FindFileData));
	}
	return TRUE;
}
BOOL itGetImageList(HIMAGELIST *pHiml)
{
	return TRUE;
}
DWORD GetTextOnEdit(HWND hwndPath,HWND hwndEdit,TCHAR szTextToShow[100])
{
	SendMessage(hwndEdit, WM_GETTEXT, 100, (LPARAM)(void*)szTextToShow);
	return 0;
}
VOID search(HWND hwndPath,HWND hwndEdit,HWND hWndListView)
{
	TCHAR gettext[100];
	GetTextOnEdit(hwndPath,hwndEdit,gettext);
	itaddListViewItems(hWndListView, gettext);/////////addlist放在搜索这里。。。。。。。。。。。
}
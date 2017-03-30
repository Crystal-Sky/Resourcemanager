#include"treeoperation.h"
BOOL InitTreeViewItems(HWND hwndTV)
{
	HTREEITEM hRoot[20];
	TCHAR szLogicalDriveStrings[BUFSIZE];
	LPWSTR szDrive;
	ZeroMemory(szLogicalDriveStrings, BUFSIZE);
	GetLogicalDriveStrings(BUFSIZE - 1, szLogicalDriveStrings);
	szDrive = szLogicalDriveStrings;
	int i = 0;
	int l = lstrlen(szDrive) + 1;
	do
	{
		if (GetDriveType(szDrive) != DRIVE_CDROM)
		{
			szLogicalDriveStrings[(i + 1)*l - 2] = '\0';
			hRoot[i] = AddItemToTree(hwndTV, szDrive, NULL, TRUE);
			FindInAll(szDrive, hRoot[i],hwndTV);
			szLogicalDriveStrings[(i + 1)*l - 2] = '\\';
		}
		else
		{
			szLogicalDriveStrings[(i + 1)*l - 2] = '\0';
			hRoot[i] = AddItemToTree(hwndTV, szDrive, NULL, TRUE);
			szLogicalDriveStrings[(i + 1)*l - 2] = '\\';
		}
		i++;
		szDrive += (lstrlen(szDrive) + 1);
	} while (*szDrive != '\x00');
	return TRUE;
}
void FindInAll(LPCTSTR lpszPath, HTREEITEM Root, HWND hwndTV)
{
	TCHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	TCHAR szFullPath[MAX_PATH];
	HTREEITEM hP;
	lstrcpy(szFilePath, lpszPath);
	lstrcat(szFilePath, L"\\*");
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
		return;
	do
	{
		if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
			lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
		{
			continue;
		}
		wsprintf(szFullPath, L"%s\\%s",
			lpszPath, FindFileData.cFileName);
		if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN)
		{
			continue;
		}
		if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			hP = AddItemToTree(hwndTV, FindFileData.cFileName, Root, TRUE);
		}
	} while (FindNextFile(hListFile, &FindFileData));
	FindClose(hListFile);
}
HTREEITEM AddItemToTree(HWND hwndTV, LPWSTR lpszItem, HTREEITEM hParent, BOOL bFolder)
{
	TVITEM tvi;
	TVINSERTSTRUCT tvins;
	HTREEITEM hme;
	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvi.pszText = lpszItem;
	tvi.cchTextMax = sizeof(tvi.pszText) / sizeof(tvi.pszText[0]);
	if (bFolder)
	{
		tvi.iImage = 1;
		tvi.iSelectedImage = 2;
		tvi.cChildren = I_CHILDRENCALLBACK;
	}
	else
	{
		tvi.iImage = 3;
		tvi.iSelectedImage = 3;
		tvi.cChildren = 0;
	}
	tvins.item = tvi;
	tvins.hInsertAfter = TVI_SORT;
	if (hParent == NULL)
	{
		tvins.hParent = TVI_ROOT;
	}
	else
	{
		tvins.hParent = hParent;
	}
	hme = TreeView_InsertItem(hwndTV, &tvins);
	return hme;
}
BOOL InitListView(HWND hWndListView)
{
	if (InitListViewImageLists(hWndListView) &&
		InitListViewColumns(hWndListView))
	{
		return TRUE;
	}
	return FALSE;
}
BOOL InitListViewImageLists(HWND hWndListView)
{
	HIMAGELIST himl;
	GetImageList(&himl);
	ListView_SetImageList(hWndListView, himl, LVSIL_SMALL);
	return TRUE;
}
BOOL GetImageList(HIMAGELIST * pHiml)
{
	return TRUE;
}
BOOL InitListViewColumns(HWND hWndListView)
{
	TCHAR szText[256];
	LVCOLUMN lvc;
	RECT rect;
	GetClientRect(hWndListView, &rect);
	DWORD i;
	LPWSTR ColNames[] = { L"名称", L"修改日期", L"类型", L"大小" };
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.pszText = szText;
	lvc.cx = (rect.right - rect.left) / 4;						
	lvc.iImage = 1;
	lvc.fmt = LVCFMT_LEFT;	
	for (i = 0; i<4; i++)
	{
		lvc.pszText = ColNames[i];
		lvc.iSubItem = i;
		if (ListView_InsertColumn(hWndListView, i, &lvc) == -1)
		{
			return FALSE;
		}
	}
	return TRUE;
}
BOOL AddListViewItems(HWND hWndListView, LPCWSTR szPath)
{
	LVITEM lvI;
	DWORD index = 0;
	ZeroMemory(&lvI, sizeof(lvI));
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
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
		return FALSE;
	}
	else
	{
		do
		{
			if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
				lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
			{
				continue;
			}
			wsprintf(szFullPath, L"%s\\%s",
				szPath, FindFileData.cFileName);
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN)
			{
				continue;
			}
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			{
				WIN32_FILE_ATTRIBUTE_DATA data;
				GetFileAttributesEx(szFullPath, GetFileExInfoStandard, &data);
				lvI.iItem = index;
				lvI.iImage = 0;
				lvI.iSubItem = 0;
				lvI.pszText = FindFileData.cFileName;
				lvI.cchTextMax = lstrlen(lvI.pszText) + 1;
				if (ListView_InsertItem(hWndListView, &lvI) == -1)
					return FALSE;
				TCHAR TI[MAX_PATH];
				FILETIME ftLocal;
				SYSTEMTIME st;
				FileTimeToLocalFileTime(&(data.ftLastWriteTime), &ftLocal);
				FileTimeToSystemTime(&ftLocal, &st);
				int y = st.wYear;
				TCHAR year[MAX_PATH];
				_itow_s(y, year, 10);
				TCHAR month[MAX_PATH];
				y = st.wMonth;
				_itow_s(y, month, 10);
				TCHAR day[MAX_PATH];
				y = st.wDay;
				_itow_s(y, day, 10);
				TCHAR hour[MAX_PATH];
				y = st.wHour;
				_itow_s(y, hour, 10);
				TCHAR minute[MAX_PATH];
				y = st.wMinute;
				_itow_s(y, minute, 10);
				wsprintf(TI, L"%s/%s",year, month);
				wsprintf(TI, L"%s/%s", TI, day);
				wsprintf(TI, L"%s %s", TI, hour);
				wsprintf(TI, L"%s:%s", TI, minute);
				ListView_SetItemText(hWndListView, index, 1,TI);
				ListView_SetItemText(hWndListView, index, 2, L"文件夹");
				index++;
			}
			else
			{
				WIN32_FILE_ATTRIBUTE_DATA data;
				GetFileAttributesEx(szFullPath, GetFileExInfoStandard, &data);
				lvI.iItem = index;
				lvI.iImage = 0;
				lvI.iSubItem = 0;
				lvI.pszText = FindFileData.cFileName;
				TCHAR NAME[MAX_PATH];
				int i = 0, k = 0;
				while (FindFileData.cFileName[i] != '\0')
					i++;
				while (FindFileData.cFileName[i] != '.')
					i--;
				i++;
				while (FindFileData.cFileName[i] != '\0')
				{
					NAME[k] = FindFileData.cFileName[i];
					i++;
					k++;
				}
				NAME[k] = '\0';
				lstrcat(NAME, L"文件");
				lvI.cchTextMax = lstrlen(lvI.pszText) + 1;
				if (ListView_InsertItem(hWndListView, &lvI) == -1)
					return FALSE;
				TCHAR TI[MAX_PATH];
				FILETIME ftLocal;
				SYSTEMTIME st;
				FileTimeToLocalFileTime(&(data.ftLastWriteTime), &ftLocal);
				FileTimeToSystemTime(&ftLocal, &st);
				int y = st.wYear;
				TCHAR year[MAX_PATH];
				_itow_s(y, year, 10);
				TCHAR month[MAX_PATH];
				y = st.wMonth;
				_itow_s(y, month, 10);
				TCHAR day[MAX_PATH];
				y = st.wDay;
				_itow_s(y, day, 10);
				TCHAR hour[MAX_PATH];
				y = st.wHour;
				_itow_s(y, hour, 10);
				TCHAR minute[MAX_PATH];
				y = st.wMinute;
				_itow_s(y, minute, 10);
				wsprintf(TI, L"%s/%s", year, month);
				wsprintf(TI, L"%s/%s", TI, day);
				wsprintf(TI, L"%s %s", TI, hour);
				wsprintf(TI, L"%s:%s", TI, minute);
				ListView_SetItemText(hWndListView, index, 1, TI);
				ListView_SetItemText(hWndListView, index, 2, NAME);
				index++;
			}
		} while (FindNextFile(hListFile, &FindFileData));
	}
	return TRUE;
}

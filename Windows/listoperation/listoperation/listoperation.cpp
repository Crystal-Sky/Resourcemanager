#include"listoperation.h"
BOOL itListViewImageLists(HWND hWndListView)
{
	HIMAGELIST himl;
	//HBITMAP hbmp;
	// ���� GetImageList ���ImageList
	itGetImageList(&himl);
	// ���� List View�ĵ� ImageList
	ListView_SetImageList(hWndListView, himl, LVSIL_SMALL);
	return TRUE;
}
BOOL itListViewColumns(HWND hWndListView)
{
	TCHAR szText[256];
	LVCOLUMN lvc;
	DWORD i;
	// ��������
	LPWSTR ColNames[] = { L"����", L"�޸�����", L"����", L"��С" };
	// LVCOLUMN����Ч�ĳ�Ա
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	// ���LVCOLUMN�ṹ
	lvc.pszText = szText;
	lvc.cx = 250;						// ����
	lvc.iImage = 1;
	lvc.fmt = LVCFMT_LEFT;	// �������
	// ǰ����
	for (i = 0; i<3; i++)
	{
		//	���������ı�
		lvc.pszText = ColNames[i];
		lvc.iSubItem = i;
		// ����ListView_InsertColumn�������
		if (ListView_InsertColumn(hWndListView, i, &lvc) == -1)
		{
			return FALSE;
		}
	}
	// ���һ������
	lvc.cx = 200; // ����
	lvc.fmt = LVCFMT_RIGHT; // �Ҷ���
	lvc.iSubItem = 3;
	lvc.pszText = ColNames[3];
	// �������
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
	// ��Ч����
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	// ���LVITEM
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
		//MessageBox(NULL, TEXT("�޷�д���ļ�"), L"��ʾ", MB_OK);
		//printf("����%d", GetLastError());
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
			// ����ı��ͳ���
			lvI.pszText = szFullPath;
			lvI.cchTextMax = lstrlen(lvI.pszText) + 1;
			// ������
			if (ListView_InsertItem(hwndListView, &lvI) == -1)
				return FALSE;
			// ����������ı���0 based
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
	itaddListViewItems(hWndListView, gettext);/////////addlist�������������������������������
}
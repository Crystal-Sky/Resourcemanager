#pragma once
#include<Windows.h>
#include<CommCtrl.h>
DWORD dwTotalFileNum = 0;


BOOL itListViewImageLists(HWND hWndListView);
BOOL itListViewColumns(HWND hWndListView);
BOOL itaddListViewItems(HWND hwndListView, LPCWSTR szPath);
BOOL itGetImageList(HIMAGELIST *pHiml);
DWORD GetTextOnEdit(HWND hwndEdit, LPSTR szTextToShow);
VOID search(HWND hwndEdit, HWND hWndListView);
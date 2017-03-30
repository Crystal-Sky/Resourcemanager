#pragma once
#include<Windows.h>
#include<CommCtrl.h>
#define BUFSIZE 1024
BOOL InitTreeViewItems(HWND hwndTV);
void FindInAll(LPCTSTR lpszPath, HTREEITEM Root, HWND hwndTV);
HTREEITEM AddItemToTree(HWND hwndTV, LPWSTR lpszItem, HTREEITEM hParent, BOOL bFolder);
BOOL InitListView(HWND hWndListView);
BOOL InitListViewImageLists(HWND hWndListView);
BOOL GetImageList(HIMAGELIST * pHiml);
BOOL InitListViewColumns(HWND hWndListView);
BOOL AddListViewItems(HWND hwndListView, LPCWSTR szPath);
#pragma once
#include<Windows.h>
#include"resource.h"
#include<Shlobj.h>
#include<wchar.h>

void createfile(HINSTANCE hinst, HWND hwnd);
void openfile(HINSTANCE hinst, HWND hwnd);
void fileoperation(HINSTANCE hinst, HWND hwnd);
void diroperation(HINSTANCE hinst, HWND hwnd);

LRESULT CALLBACK CREATEFILE(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OPENFILE(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OPREATIONFILE(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK OPREATIONDIR(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);




void GETFILENAME(HWND hDlg, LPWSTR &filename, int nIDD);
void GETFILESAVE(HWND hDlg, LPWSTR &file);
void GETCREATEFILE(HWND hDlg, int nIDD);
void GETOPENFILE(HWND hDlg, int nIDD,int nIDD2);
void GETDIRECTORYROOT(HWND hDlg, LPWSTR &directory, int nIDD);
void GETDIRECTORYROOTEN(HWND hDlg, LPWSTR &directory);
void DeleteInAll(LPCTSTR lpszPath);
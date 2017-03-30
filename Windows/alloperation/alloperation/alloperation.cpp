#pragma once
#include"alloperation.h"
TCHAR COPYNAME[MAX_PATH];
LPWSTR copyname = COPYNAME;
TCHAR COPYENDNAME[MAX_PATH];
LPWSTR copyendname = COPYENDNAME;

TCHAR MOVENAME[MAX_PATH];
LPWSTR movename = MOVENAME;
TCHAR MOVEENDNAME[MAX_PATH];
LPWSTR moveendname = MOVEENDNAME;

TCHAR DELETENAME[MAX_PATH];
LPWSTR deletename = DELETENAME;

TCHAR RENAME[MAX_PATH];
LPWSTR rename = RENAME;

TCHAR CRDIRNAME[MAX_PATH] = { 0 };
LPWSTR crdirname = CRDIRNAME;

TCHAR MOVDIRNAME[MAX_PATH] = { 0 };
LPWSTR movdirname = MOVDIRNAME;

TCHAR REDIRNAME[MAX_PATH] = { 0 };
LPWSTR redirname = REDIRNAME;

TCHAR DEDIRNAME[MAX_PATH] = { 0 };
LPWSTR dedirname = DEDIRNAME;

TCHAR CODIRNAME[MAX_PATH]= { 0 };
LPWSTR codirname = CODIRNAME;

void createfile(HINSTANCE hinst, HWND hwnd)
{
	DialogBox(hinst, (LPCTSTR)IDD_CREATE_DIALOG, hwnd, (DLGPROC)CREATEFILE);
}
void openfile(HINSTANCE hinst, HWND hwnd)
{
	DialogBox(hinst, (LPCTSTR)IDD_OPEN_DIALOG, hwnd, (DLGPROC)OPENFILE);
	
}
void fileoperation(HINSTANCE hinst, HWND hwnd)
{
	DialogBox(hinst, (LPCTSTR)IDD_FILE_DIALOG, hwnd, (DLGPROC)OPREATIONFILE);
}
void diroperation(HINSTANCE hinst, HWND hwnd)
{
	DialogBox(hinst, (LPCTSTR)IDD_DIR_DIALOG, hwnd, (DLGPROC)OPREATIONDIR);
}

LRESULT CALLBACK CREATEFILE(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1://保存
		{
							 GETCREATEFILE(hDlg, IDC_FILECONTENT_EDIT);
							 return true;
		}
			break;
		case IDC_BUTTON2://取消
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
LRESULT CALLBACK OPENFILE(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
							GETOPENFILE(hDlg, IDC_FILECONTE_EDIT,IDC_EDIT1);
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
LRESULT CALLBACK OPREATIONFILE(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndCtl;
	int length;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
							GETFILENAME(hDlg,copyname,IDC_EDIT1);
							return true;
		}
			break;
		case IDC_BUTTON2:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT1);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择源文件"), TEXT("提示"), MB_OK);
								return true;
							}
							wcscpy_s(copyendname, MAX_PATH, copyname);
							GETFILESAVE(hDlg,copyendname);
							if (lstrcmpW(copyname, copyendname) == 0)
							{
								return true;
							}
							if (CopyFile(copyname, copyendname, FALSE))
							{
								MessageBox(hDlg, TEXT("复制成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT1, copyendname);
							}
							else
							{
								MessageBox(hDlg, TEXT("复制失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT1, L"");
							}
							return true;
		}
			break;
		case IDC_BUTTON3:
		{
							GETFILENAME(hDlg, movename, IDC_EDIT2);
							return true;
		}
		case IDC_BUTTON4:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT2);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择源文件"), TEXT("提示"), MB_OK);
								return true;
							}
							wcscpy_s(moveendname, MAX_PATH, movename);
							GETFILESAVE(hDlg, moveendname);
							if (lstrcmpW(movename, moveendname)==0)
							{
								return true;
							}
							if (MoveFile(movename, moveendname))
							{
								MessageBox(hDlg, TEXT("移动成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT2, moveendname);
							}
							else
							{
								MessageBox(hDlg, TEXT("移动失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT2, L"");
							}
							return true;
		}
			break;
		case IDC_BUTTON5:
		{
							GETFILENAME(hDlg, deletename, IDC_EDIT3);
							return true;
		}
		case IDC_BUTTON6:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT3);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择源文件"), TEXT("提示"), MB_OK);
								return true;
							}
							if (DeleteFile(deletename))
							{
								MessageBox(hDlg, TEXT("删除成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT3, L"");
							}
							else
							{
								MessageBox(hDlg, TEXT("删除失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT3, L"");
							}
							return true;
		}
			break;
		case IDC_BUTTON7:
		{
							GETFILENAME(hDlg, rename, IDC_EDIT4);
							return true;
		}
		case IDC_BUTTON8:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT4);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择源文件"), TEXT("提示"), MB_OK);
								return true;
							}
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT5);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("未写重命名"), TEXT("提示"), MB_OK);
								return true;
							}
							TCHAR FINALNAME[MAX_PATH];
							TCHAR CURRENTNAME[MAX_PATH];
							::GetDlgItemText(hDlg,IDC_EDIT4, (LPTSTR)(LPCTSTR)CURRENTNAME, sizeof(CURRENTNAME));
							::GetDlgItemText(hDlg, IDC_EDIT5, (LPTSTR)(LPCTSTR)FINALNAME, sizeof(FINALNAME));
							//::GetDlgItemText(hDlg, IDC_RENAMEFILE_NAME, (LPTSTR)(LPCTSTR)NAME, sizeof(NAME));
							int i = 0, j = 0, k = 0;
							while (CURRENTNAME[i] != '\0')
							{
								i++;
							}
							j = i;
							while (CURRENTNAME[j] != '.')
							{
								j--;
							}
							k = j;
							while (CURRENTNAME[k] != '\\')
							{
								k--;
							}
							int x = j, u = 0;
							while (FINALNAME[u] != '\0')
								u++;
							while (CURRENTNAME[x] != '\0')
							{
								FINALNAME[u] = CURRENTNAME[x];
								u++;
								x++;
							}
							FINALNAME[u] = '\0';
							CURRENTNAME[k + 1] = '\0';
							//LPWSTR szD = szSourcePathName;
							//LPWSTR sz = szDstPathFileName;
							//LPWSTR n = NAME;
							lstrcatW(CURRENTNAME, FINALNAME);
							if (MoveFile(rename, CURRENTNAME))
							{
								MessageBox(hDlg, TEXT("重命名成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT4, CURRENTNAME);
								::SetDlgItemText(hDlg, IDC_EDIT5, L"");
							}
							else
							{
								MessageBox(hDlg, TEXT("重命名失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT4, L"");
								::SetDlgItemText(hDlg, IDC_EDIT5, L"");
							}
							//MessageBox(hDlg, szD, TEXT("提示"), MB_OK);
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
LRESULT CALLBACK OPREATIONDIR(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndCtl;
	int length;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
							//MessageBox(hDlg, TEXT("提示"), TEXT("提示"), MB_OK);
							GETDIRECTORYROOT(hDlg,crdirname,IDC_EDIT2);
							return true;
		}
			break;
		case IDC_BUTTON2:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT2);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择目录"), TEXT("提示"), MB_OK);
								return true;
							}
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT3);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("未命名目录"), TEXT("提示"), MB_OK);
								return true;
							}
							//::GetDlgItemText(hDlg, IDC_CREATETABLE_ROOT, (LPTSTR)(LPCTSTR)szDstPathName, sizeof(szDstPathName));
							TCHAR TABLENAME[MAX_PATH];
							::GetDlgItemText(hDlg, IDC_EDIT3, (LPTSTR)(LPCTSTR)TABLENAME, sizeof(TABLENAME));
							int i = 0;
							while (crdirname[i] != '\0')
								i++;
							crdirname[i] = '\\';
							crdirname[i + 1] = '\0';
							lstrcatW(crdirname, TABLENAME);
							//MessageBox(hDlg, Dst, TEXT("提示"), MB_OK);
							if (CreateDirectory(crdirname, NULL))
							{
								MessageBox(hDlg, TEXT("创建成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT2, crdirname);
								::SetDlgItemText(hDlg, IDC_EDIT3, L"");
							}
							else
							{
								MessageBox(hDlg, TEXT("创建失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT2, L"");
								::SetDlgItemText(hDlg, IDC_EDIT3, L"");
							}
							return true;
		}
			break;
		case IDC_BUTTON3:
		{
							GETDIRECTORYROOT(hDlg, movdirname, IDC_EDIT4);
							return true;
		}
			break;
		case IDC_BUTTON4:
		{
							//TCHAR szDirectoryMoveSource[MAX_PATH];
							//::GetDlgItemText(hDlg, IDC_EDIT4, (LPTSTR)(LPCTSTR)szDirectoryMoveSource, sizeof(szDirectoryMoveSource));
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT4);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择目录"), TEXT("提示"), MB_OK);
								return true;
							}
							int i = 0, j = 0;
							while (movdirname[i] != '\0')
								i++;
							j = i;
							while (movdirname[j] != '\\')
								j--;
							TCHAR Name[MAX_PATH];
							int k = 0;
							while (movdirname[j] != '\0')
							{
								Name[k] = movdirname[j];
								j++;
								k++;
							}
							Name[k] = '\0';
							TCHAR szDirectoryMoveName[MAX_PATH];
							LPWSTR sz = szDirectoryMoveName;
							GETDIRECTORYROOTEN(hDlg, sz);
							lstrcatW(szDirectoryMoveName, Name);
							if (MoveFile(movdirname, szDirectoryMoveName))
							{
								MessageBox(hDlg, TEXT("移动成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT4, szDirectoryMoveName);
							}
							else
							{
								MessageBox(hDlg, TEXT("移动失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT4, L"");
							}
							return true;
		}
			break;
		case IDC_BUTTON5:
		{
							GETDIRECTORYROOT(hDlg, redirname, IDC_EDIT5);
							//::GetDlgItemText(hDlg, IDC_RENAME_DIR_EDIT, (LPTSTR)(LPCTSTR)szDirectoryRenameSource, sizeof(szDirectoryRenameSource));
							//MessageBox(hDlg, szDirectoryDeleteName, L"提示", MB_OK);
							return true;
		}
			break;
		case IDC_BUTTON6:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT5);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择目录"), TEXT("提示"), MB_OK);
								return true;
							}
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT6);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("未重命名目录"), TEXT("提示"), MB_OK);
								return true;
							}
							TCHAR szDirectoryRenameName[MAX_PATH];
							//::GetDlgItemText(hDlg, IDC_RENAME_DIR_EDIT, (LPTSTR)(LPCTSTR)szDirectoryRenameSource, sizeof(szDirectoryRenameSource));
							::GetDlgItemText(hDlg, IDC_EDIT6, (LPTSTR)(LPCTSTR)szDirectoryRenameName, sizeof(szDirectoryRenameName));
							int i = 0, j = 0;
							while (redirname[i] != '\0')
								i++;
							j = i;
							while (redirname[j] != '\\')
								j--;
							redirname[j + 1] = '\0';
							lstrcatW(redirname, szDirectoryRenameName);
							::GetDlgItemText(hDlg, IDC_EDIT5, (LPTSTR)(LPCTSTR)szDirectoryRenameName, sizeof(szDirectoryRenameName));
							LPCTSTR Sou = szDirectoryRenameName;
							//LPCTSTR Dst = szDirectoryRenameSource;
							if (MoveFile(Sou, redirname))
							{
								MessageBox(hDlg, TEXT("重命名成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT5, redirname);
								::SetDlgItemText(hDlg, IDC_EDIT6, L"");
							}
							else
							{
								MessageBox(hDlg, TEXT("重命名失败"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT5, L"");
								::SetDlgItemText(hDlg, IDC_EDIT6, L"");
							}
							return true;
		}
			break;
		case IDC_BUTTON7:
		{
							GETDIRECTORYROOT(hDlg, dedirname, IDC_EDIT7);
							//::GetDlgItemText(hDlg, IDC_DIRECTORY_DELETE_EDIT, (LPTSTR)(LPCTSTR)szDirectoryDeleteName, sizeof(szDirectoryDeleteName));
							//MessageBox(hDlg, szDirectoryDeleteName, L"提示", MB_OK);
							return true;
		}
			break;
		case IDC_BUTTON8:
		{
							hwndCtl = GetDlgItem(hDlg, IDC_EDIT7);
							length = GetWindowTextLength(hwndCtl);
							if (length <= 0)
							{
								MessageBox(hDlg, TEXT("请选择目录"), TEXT("提示"), MB_OK);
								return true;
							}
							//::GetDlgItemText(hDlg, IDC_DIRECTORY_DELETE_EDIT, (LPTSTR)(LPCTSTR)szDirectoryDeleteName, sizeof(szDirectoryDeleteName));
							//MessageBox(hDlg, szDirectoryDeleteName, L"提示", MB_OK);
							if (RemoveDirectory(dedirname))
							{
								MessageBox(hDlg, TEXT("删除成功"), TEXT("提示"), MB_OK);
								::SetDlgItemText(hDlg, IDC_EDIT7, L"");
							}
							else
							{
								DeleteInAll(dedirname);
								if (RemoveDirectory(dedirname))
								{
									MessageBox(hDlg, TEXT("删除成功"), TEXT("提示"), MB_OK);
									::SetDlgItemText(hDlg, IDC_EDIT7, L"");
								}
								else
								{
									MessageBox(hDlg, TEXT("删除失败"), TEXT("提示"), MB_OK);
									::SetDlgItemText(hDlg, IDC_EDIT7, L"");
								}								
							}
							return true;
		}
			break;
		case IDC_BUTTON9:
		{
							GETDIRECTORYROOT(hDlg, codirname, IDC_EDIT8);
							//::GetDlgItemText(hDlg, IDC_DIRECTORY_DELETE_EDIT, (LPTSTR)(LPCTSTR)szDirectoryDeleteName, sizeof(szDirectoryDeleteName));
							//MessageBox(hDlg, szDirectoryDeleteName, L"提示", MB_OK);
							return true;
		}
			break;
		case IDC_BUTTON10:
		{
							 hwndCtl = GetDlgItem(hDlg, IDC_EDIT8);
							 length = GetWindowTextLength(hwndCtl);
							 if (length <= 0)
							 {
								 MessageBox(hDlg, TEXT("请选择目录"), TEXT("提示"), MB_OK);
								 return true;
							 }
							 ::GetDlgItemText(hDlg, IDC_EDIT8, (LPTSTR)(LPCTSTR)CODIRNAME, sizeof(CODIRNAME));
							 TCHAR CODIRENDNAME[MAX_PATH];
							 LPWSTR codirendname = CODIRENDNAME;
							 GETDIRECTORYROOTEN(hDlg, codirendname);
							 TCHAR DN[MAX_PATH];
							 int i = 0, j = 0;
							 while (codirname[i] != '\0')
								 i++;
							 j = i;
							 while (codirname[j] != '\\')
								 j--;
							 int k = 0;
							 while (codirname[j] != '\0')
							 {
								 DN[k] = codirname[j];
								 j++;
								 k++;
							 }
							 DN[k] = '\0';
							 lstrcatW(codirendname,DN);
							 CreateDirectory(codirendname, NULL);
							 CopyInAll(codirname, codirendname);
							 MessageBox(hDlg, TEXT("复制成功"), TEXT("提示"), MB_OK);
							 ::SetDlgItemText(hDlg, IDC_EDIT8, L"");
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

void GETFILENAME(HWND hDlg, LPWSTR &filename, int nIDD)
{
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hDlg;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrTitle = TEXT("选择文件");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		//显示选择的文件
		OutputDebugString(szFile);
		::SetDlgItemText(hDlg, nIDD, ofn.lpstrFile);
		OutputDebugString(L"\r\n");
		int i = 0;
		while (szFile[i] != '\0')
		{
			filename[i] = szFile[i];
			i++;
		}
		filename[i] = '\0';
	}
}
void GETFILESAVE(HWND hDlg, LPWSTR &file)
{
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	TCHAR szFil[MAX_PATH];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hDlg;
	ofn.lpstrFile = szFile;
	ofn.lpstrFilter = L"所有文件\0\0*.txt\0";
	ofn.lpstrDefExt = L"txt";
	ofn.lpstrFile = file;
	//ofn.lpstrFile[0] = '\0'; 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = TEXT("保存");
	ofn.lpstrFileTitle = szFil;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;
	if (GetSaveFileName(&ofn) == TRUE)
	{
		//::SetDlgItemText(hDlg, nIDD, ofn.lpstrFile);
	}
}
void GETCREATEFILE(HWND hDlg, int nIDD)
{
	TCHAR content[100000];
	DWORD dwBytesWrite;
	DWORD WF;
	int length2;
	HANDLE hFileWrite;
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	TCHAR szFil[MAX_PATH] = L"新建文本文档.txt";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hDlg;
	ofn.lpstrFile = szFile;
	ofn.lpstrFilter = L"文本文档(*.txt)\0*.txt\0";
	ofn.lpstrDefExt = L"txt";
	ofn.lpstrFile = szFil;
	//ofn.lpstrFile[0] = '\0'; 
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = TEXT("保存到");
	//wcscpy_s(ofn.lpstrFileTitle, MAX_PATH, file);
	ofn.lpstrFileTitle = szFil;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;
	if (GetSaveFileName(&ofn) == TRUE)
	{
		hFileWrite = CreateFile(ofn.lpstrFile,//szFilePath,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		HWND hwndCtl2 = GetDlgItem(hDlg, nIDD);
		length2 = GetWindowTextLength(hwndCtl2);
		if (length2 > 0)
		{
			::GetDlgItemText(hDlg, nIDD, (LPTSTR)(LPCTSTR)content, sizeof(content));
			::SetFilePointer(hFileWrite, 0, NULL, FILE_END);
			char szTextAnsi[100000];
			int a = WideCharToMultiByte(CP_ACP, NULL, content, -1, LPSTR(szTextAnsi), MAX_PATH, NULL, FALSE);//Unicode转换为ANSI，a的值包括了字符串最后的0
			WF = WriteFile(hFileWrite, szTextAnsi, a - 1, &dwBytesWrite, NULL);//写入的时候最后的0不用写入所以要用a-1
			if (WF == 0)
			{
				MessageBox(hDlg, TEXT("无法写入文件"), L"提示", MB_OK);
			}
			::CloseHandle(hFileWrite);//关闭文件
		}
	}
}
void GETOPENFILE(HWND hDlg, int nIDD,int nIDD2)
{
	char *ansiPtr;
	HANDLE hFileRead;
	int iFileLength;
	//PBYTE pBuffer;
	DWORD dwByteRead;
	//DWORD dwRF;

	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hDlg;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = L"文本文档(*.txt)\0*.txt\0";
	ofn.nFilterIndex = 1;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFileTitle = TEXT("选择文件");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		//显示选择的文件
		OutputDebugString(szFile);
		::SetDlgItemText(hDlg, nIDD2, ofn.lpstrFile);
		OutputDebugString(L"\r\n");
		hFileRead = CreateFile(ofn.lpstrFile,//szFilePath,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFileRead == INVALID_HANDLE_VALUE)
		{
			MessageBox(hDlg, L"打开文件失败！", L"提示", MB_OK);
		}
		else
		{

			iFileLength = ::GetFileSize(hFileRead, NULL);
			if (iFileLength != INVALID_FILE_SIZE)
			{
				ansiPtr = new char[iFileLength + 1];
				ReadFile(hFileRead, (LPVOID)ansiPtr, iFileLength, &dwByteRead, NULL);
				//该句是必须的，否则将会有多余的怪码
				ansiPtr[iFileLength] = '\0';
				//首先获取将char字串转换为wchar_t后wchar_t的长度
				int wcs_len = MultiByteToWideChar(CP_ACP, 0, ansiPtr, -1, NULL, NULL);
				LPWSTR wcsPtr = new WCHAR[wcs_len + 1];  //分配内存空间
				if (wcsPtr != NULL)
				{
					//将char字串转换为wchar_t字串
					MultiByteToWideChar(CP_ACP, 0, ansiPtr, strlen(ansiPtr) + 1, wcsPtr, wcs_len + 1);
				}
				::SetDlgItemText(hDlg, nIDD, (PTSTR)wcsPtr);
				delete[] ansiPtr;

			}
		}

	}
}
void GETDIRECTORYROOT(HWND hDlg, LPWSTR &directory, int nIDD)
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = hDlg;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
	bi.pszDisplayName = directory;//接收文件夹的缓冲区
	//bi.lpszTitle = TEXT("保存到");//标题
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (SHGetPathFromIDList(idl, directory))
	{
		OutputDebugString(szBuffer);
		::SetDlgItemText(hDlg, nIDD, bi.pszDisplayName);
		OutputDebugString(L"\r\n");
		//wcscpy_s(file, MAX_PATH, bi.pszDisplayName);
	}
}
void GETDIRECTORYROOTEN(HWND hDlg, LPWSTR &directory)
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = hDlg;//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄
	bi.pszDisplayName = directory;//接收文件夹的缓冲区
	//bi.lpszTitle = TEXT("保存到");//标题
	bi.ulFlags = BIF_NEWDIALOGSTYLE;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (SHGetPathFromIDList(idl, directory))
	{
		//OutputDebugString(szBuffer);
		//::SetDlgItemText(hDlg, nIDD, bi.pszDisplayName);
		//OutputDebugString(L"\r\n");
		//wcscpy_s(file, MAX_PATH, bi.pszDisplayName);
	}
}

void DeleteInAll(LPCTSTR lpszPath)
{
	TCHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	TCHAR szFullPath[MAX_PATH];
	
	//构造代表子目录和文件夹路径的字符串，使用通配符“*”
	lstrcpy(szFilePath, lpszPath);
	lstrcat(szFilePath, L"\\*");
	//查找第一个文件/目录，获得查找句柄
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
		return;
	do
	{
		//	过滤“.”和“..”，不需要遍历
		if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
			lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
		{
			continue;
		}
		//构造成全路径
		wsprintf(szFullPath, L"%s\\%s",
			lpszPath, FindFileData.cFileName);
		if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			
			//MessageBox(NULL, szFullPath, TEXT("提示"), MB_OK);
			DeleteInAll(szFullPath);
			RemoveDirectory(szFullPath);
		}
		else
		{
			//MessageBox(NULL, szFullPath, TEXT("提示"), MB_OK);
			DeleteFile(szFullPath);
		}
	} while (FindNextFile(hListFile, &FindFileData));
	FindClose(hListFile);
}
void CopyInAll(LPCTSTR lpszSourcePath, LPCTSTR lpszDstPath)
{
	TCHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	TCHAR szFullPath[MAX_PATH];
	//TCHAR szFileDstPath[MAX_PATH];
	TCHAR szFullendPath[MAX_PATH];
	//lstrcpy(szFileDstPath, lpszDstPath);
	//构造代表子目录和文件夹路径的字符串，使用通配符“*”
	lstrcpy(szFilePath, lpszSourcePath);
	lstrcat(szFilePath, L"\\*");
	//查找第一个文件/目录，获得查找句柄
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
		return;
	do
	{
		//	过滤“.”和“..”，不需要遍历
		if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
			lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
		{
			continue;
		}
		//构造成全路径
		wsprintf(szFullPath, L"%s\\%s",lpszSourcePath, FindFileData.cFileName);
		wsprintf(szFullendPath, L"%s\\%s", lpszDstPath, FindFileData.cFileName);
		if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(szFullendPath, NULL);
			CopyInAll(szFullPath,szFullendPath);
			
		}
		else
		{
			CopyFile(szFullPath, szFullendPath, FALSE);
		}
	} while (FindNextFile(hListFile, &FindFileData));
	FindClose(hListFile);
}
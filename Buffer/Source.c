#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();
TCHAR* ClipboardOutptText2();
LPSTR Data;
LPWSTR result;
DWORD str;
LPWSTR res;
TCHAR* arr;

int ClipboardInputText(LPWSTR buffer)
{
	DWORD mess;
	HANDLE hMen; // ���������� ���������� ������� ������ 
	mess = wcslen(buffer) + 1;
	hMen = GlobalAlloc(GMEM_MOVEABLE, mess * sizeof(LPWSTR));// Global - �������� ������ � ���������� ������� ���������, ����� ������ ���� ����� �� ��������� ���������
	//memcpy - ������� ����������� � ������
	// GlobalLock - ��������� ���������� ������
	memcpy(GlobalLock(hMen), buffer, mess * sizeof(LPWSTR));
	GlobalUnlock(hMen); // ������ ���������� ��������� 
	OpenClipboard(0); // ��������� ����� ������ 
	EmptyClipboard(); // ������ ������ ������
	//CF_UNICODETEXT - ��� ������ (������ ����� - ���), hMen - ��� ���������� (���������� ����� ���������� ������� ������ �������)
	SetClipboardData(CF_UNICODETEXT, hMen);
	CloseClipboard(); // ������� �����, ������ ��� ��������� ��� ������ ����������
	return 0;
}

int ClipboardOutptText() // �� ������ ���� ���������� � ����� ���������� ���������� ������� ������
{
	LPWSTR Mess = NULL; // ���������, ������� ��� ������ � MessageBox
	OpenClipboard(NULL); // ������� ����� ������ - ��� NULL � ������ �� ���������
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (LPWSTR)GlobalLock(hClipboardData); // ������� �� ����������� ������� ������, �������� ��� � � ������ (LPWSTR) � ��������� � ������ Messege
	GlobalUnlock(hClipboardData);
	CloseClipboard();// ������ ����� ��������� ��� ������ ����������
	MessageBox(NULL, Mess, L"���������� ������", MB_OK);
	return 0;
}

TCHAR* ClipboardOutptText2()
{
	TCHAR* Mess = NULL;
	OpenClipboard(NULL);
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (TCHAR*)GlobalLock(hClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	//EmptyClipboard();
	return Mess;
}

int main()
{
	////����� ������� ����� ����������� word � ���������� WinAPI
	//LPWSTR Message = L"����� ��� ������ � ����� � ����������� ����������� � Word"; 
	//ClipboardInputText(Message);
	//ClipboardOutptText();

	////������ ����������� �� ���������� ������ ������
	//while (TRUE) 
	//{
	//	LPSTR Data = ClipboardOutptText2(); // ��������� ���� - ����� �������
	//	TCHAR Alert[] = L"��������� ��������� ���� ��� ����������� ������: "; // ������ ������ ��� MessageBox
	//	TCHAR third[512]; // ����������� �� ����� �������� - 1 ��
	//	swprintf(third, sizeof third, L"%s%s", Alert, Data);
	//	if (*Data != 0) // ���� �� ������ ������
	//	{
	//		MessageBox(NULL, &third, L"�������� ���������", MB_OK | MB_ICONASTERISK);
	//		ClipboardInputText(""); // ������� ����� 
	//	}
	//	Sleep(1000); 
	//}
	Data = ClipboardOutptText2();
	str = wcslen(Data) + 1;	
	arr = calloc(str, sizeof(TCHAR));
	DWORD k;
	res = calloc(512, sizeof(TCHAR));
	//��� ����������� ����� � ��������� ����� ������ �������� � ����� �� ��������� ��������
	while (TRUE)
	{
		// 0 1 2 3 4 5 6 7 8 9 	0123	
		if (*Data != 0) // ���� �� ������ ������
		{
			
			for (size_t i = 0; i < str; i++)
			{
				switch (Data[i])
				{
				case '0':
					result= L"����";					
					k = wcslen(result) + 1;
					arr = realloc(arr, k*sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"����");
					break;
				case '1':
					result = L"����";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"����");
					break;
				case '2':
					result = L"���";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"���");
					break;
				case '3':
					result = L"���";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"���");
					break;
				case '4':
					result = L"������";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"������");
					break;
				case '5':
					result = L"����";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"����");
					break;
				case '6':
					result = L"�����";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"�����");
					break;
				case '7':
					result = L"����";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"����");
					break;
				case '8':
					result = L"������";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"������");
					break;
				case '9':
					result = L"������";
					k = wcslen(result) + 1;
					arr = realloc(arr, k * sizeof(TCHAR));
					swprintf(res, sizeof arr, L"%s ", result);
					//ClipboardInputText(L"������");
					break;
				default:
					ClipboardInputText(Data);
					break;
				}
				
			}
			MessageBox(NULL, &res, L"������������", MB_OK | MB_ICONASTERISK);
			/*LPWSTR res = Data;
			ClipboardInputText(res);*/
		}
		Sleep(1000); // ����� 1 ��� 
	}


	return 0;
}





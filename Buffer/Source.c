#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();
TCHAR* ClipboardOutptText2();

int ClipboardInputText(LPWSTR buffer)
{
	DWORD len; // ���������� ��� ����� ���������
	HANDLE hMen; // ���������� ���������� ������� ������ 
	len = wcslen(buffer) + 1; //(���������� ��������) ���������� ����� � ������� (+1  ������ ������ ����������� ������� ��������)
	// ������ ����������
	// Global - �������� ������ � ���������� ������� ���������, ����� ������ ���� ����� �� ��������� ���������
	hMen = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
	//memcpy - ������� ����������� � ������ (�������� �� ��� � ������ � ����������� ������� ������)
	// GlobalLock - ��������� ��� ������ (���������������)
	// buffer - ���������� ������, ����� ������� ���� �������� ����
	memcpy(GlobalLock(hMen), buffer, len * sizeof(LPWSTR)); // �������� ������� ������ �� buffer � hMen 
	GlobalUnlock(hMen); // �������������� ���������� ���� ������(������� ��������� ��� ������ �������� - ��� ���������� ������)
	OpenClipboard(0); // ���� ����� ������ - ��� 0 ������ � ������ �� �����
	EmptyClipboard(); // �������� ����� ������ - ���� �� ���� �������, ������ ����
	//CF_UNICODETEXT - ��� ������ (������ ����� - ���), hMen - ��� ���������� (���������� ����� ���������� ������� ������ �������)
	SetClipboardData(CF_UNICODETEXT, hMen); // �������� � ����� ������ ��������������� ����
	CloseClipboard(); // ������� �����, ������ ��� ��������� ��� ������ ����������
	return 0;
}

int ClipboardOutptText() // �� ������ ���� ���������� � ����� ���������� ���������� ������� ������
{
	LPWSTR Mess = NULL; // ���������, ������� ��������� � ������� ���� (�� ��������� ���� )
	OpenClipboard(NULL); // ������� ����� ������ - ��� NULL ������ � ������ �� �����
	// ����������� ��������, � �������� ��������� ���
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT); // �������� � ����� ������ ������ ���������������� ����
	Mess = (LPWSTR)GlobalLock(hClipboardData); // ������� �� ����������� ������� ������, �������� ��� � � ������ (LPWSTR) � ��������� � ������ Messege
	// ����������� , ������ ��� �� ����� ����� �� ��������������
	GlobalUnlock(hClipboardData); // ����������� ���������� ������� ������
	CloseClipboard(); // ������� ����� ������, ������� ��� ������������ ������ ����
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
	//����� ������� ����� ����������� word � ���������� WinAPI
	//LPWSTR Message = L"�����"; //������ ���������
	//ClipboardInputText(Message); // �������� ����� � ����� ������
	//ClipboardOutptText();// �������� ����� �� ������

	//������ ����������� �� ���������� ������ ������
	//while (TRUE) 
	//{
	//	LPSTR Data = ClipboardOutptText2(); // ��������� ���� - ����� �������
	//	TCHAR Alert[] = L"��������� ��������� ���� ��� ����������� ������: "; // ������ ������ ��� �����
	//	TCHAR third[512]; // ����������� �� ����� �������� - 1 ��
	//	// ������� ������ (���������) Alert + Data 0
	//	//������ ������, ������ �� �� �������, � � ���������� ����������, �������� � ��������
	//	// sizeof - ����� ������, L - ������, ��������� �� ������
	//	swprintf(third, sizeof third, L"%s%s", Alert, Data);
	//	if (*Data != 0) // ���� �� ������ ������
	//	{
	//		MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
	//		ClipboardInputText(""); // ������� ����� 
	//	}
	//	Sleep(1000); // ����� 1 ���
	//}



	//��� ����������� ����� � ��������� ����� ������ �������� � ����� �� ��������� ��������
	while (TRUE) // �� ��������� ���� 
	{
		// 1 2 3 4 5 6 7 8 9 ������ ����� ������ ������ ��������� ����  ������ ������ ���� ����� ���� ������ ��� 2 ��� ���� ���

		LPSTR Data = ClipboardOutptText2();
		if (*Data != 0) // ���� �� ������ ������
		{
			switch (*Data)
			{
			case '0':
				ClipboardInputText(L"����");
				break;
			case '1':
				ClipboardInputText(L"����");
				break;
			case '2':
				ClipboardInputText(L"���");
				break;
			case '3':
				ClipboardInputText(L"���");
				break;
			case '4':
				ClipboardInputText(L"������");
				break;
			case '5':
				ClipboardInputText(L"����");
				break;
			case '6':
				ClipboardInputText(L"�����");
				break;
			case '7':
				ClipboardInputText(L"����");
				break;
			case '8':
				ClipboardInputText(L"������");
				break;
			case '9':
				ClipboardInputText(L"������");
				break;
			default:
				ClipboardInputText(Data);
				break;
			}
			//
			//if (*Data == '0') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"����");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"����"); 
			//}
			//else if (*Data == '1') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"����");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"����"); 
			//}
			//else if (*Data == '2') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"���");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"���"); 
			//}
			//else if (*Data == '3') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"���");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"���"); 
			//}
			//else if (*Data == '4') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"������");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"������"); 
			//}
			//else if (*Data == '5') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"����");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"����"); 
			//}
			//else if (*Data == '6') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"�����");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"�����"); 
			//}
			//else if (*Data == '7') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"����");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"����"); 
			//}
			//else if (*Data == '8') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"������");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"������"); 
			//}
			//else if (*Data == '9') // ���� �� ������ ������
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"������");
			//	MessageBox(NULL, &third, L"���������!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"������"); 
			//} 
		}
		Sleep(1000); // ����� 1 ��� 
	}


	return 0;
}





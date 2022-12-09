#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();
TCHAR* ClipboardOutptText2();

int ClipboardInputText(LPWSTR buffer)
{
	DWORD mess; 
	HANDLE hMen; // дескриптор глобальной области памяти 
	mess = wcslen(buffer) + 1; //(количество символов) вычисление длины в юникоде (+1  строка должна заканчивать нулевым символом)	
	hMen = GlobalAlloc(GMEM_MOVEABLE, mess * sizeof(LPWSTR));// Global - выделяем память в глобальной области видимости, чтобы память была видна за пределами программы
	//memcpy - функция копирования в памяти
	// GlobalLock - фиксирует выделенную память
	memcpy(GlobalLock(hMen), buffer, mess * sizeof(LPWSTR)); 
	GlobalUnlock(hMen); // делаем содержимое доступным 
	OpenClipboard(0); // открываем буфер обмена 
	EmptyClipboard(); // очиска буфера обмена
	//CF_UNICODETEXT - что кладем (юникод текст - тип), hMen - что записываем (дискриптор нашей глобальной области памяти передем)
	SetClipboardData(CF_UNICODETEXT, hMen);
	CloseClipboard(); // закрыть буфер, сделав его доступным для других проложений
	return 0;
}

int ClipboardOutptText() // из буфера тест помещается в некий дискриптор глобальной области памяти
{
	LPWSTR Mess = NULL; // переменна, которая для вывода в MessageBox
	OpenClipboard(NULL); // открыть буфер обмена - код NULL в режиме по умолчанию
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	Mess = (LPWSTR)GlobalLock(hClipboardData); // считать из глобального участка памяти, привести это в к строке (LPWSTR) и поместить в строку Messege
	GlobalUnlock(hClipboardData); 
	CloseClipboard();// делаем буфер доступным для других приложений
	MessageBox(NULL, Mess, L"Содержимое буфера", MB_OK);
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
	////Обмен данными между приложением word и программой WinAPI
	//LPWSTR Message = L"Текст для записи в буфер и дальнейшего копирования в Word"; 
	//ClipboardInputText(Message);
	//ClipboardOutptText();

	////запрет копирования из системного буфера обмена
	//while (TRUE) 
	//{
	//	LPSTR Data = ClipboardOutptText2(); // указатель дата - вызов функции
	//	TCHAR Alert[] = L"Нарушение авторских прав при копировнаие текста: "; // первая строка для MessageBox
	//	TCHAR third[512]; // ограничение на длину символов - 1 мб
	//	swprintf(third, sizeof third, L"%s%s", Alert, Data);
	//	if (*Data != 0) // если не пустая строка
	//	{
	//		MessageBox(NULL, &third, L"Выявлено нарушение", MB_OK | MB_ICONASTERISK);
	//		ClipboardInputText(""); // очищаем буфер 
	//	}
	//	Sleep(1000); 
	//}



	//при копировании цифры в системный буфер обмена выводить в буфер ее словесное описание
	while (TRUE) 
	{
		// 0 1 2 3 4 5 6 7 8 9 

		LPSTR Data = ClipboardOutptText2();
		if (*Data != 0) // если не пустая строка
		{
			switch (*Data)
			{
			case '0':
				ClipboardInputText(L"ноль");
				break;
			case '1':
				ClipboardInputText(L"один");
				break;
			case '2':
				ClipboardInputText(L"два");
				break;
			case '3':
				ClipboardInputText(L"три");
				break;
			case '4':
				ClipboardInputText(L"четыре");
				break;
			case '5':
				ClipboardInputText(L"пять");
				break;
			case '6':
				ClipboardInputText(L"шесть");
				break;
			case '7':
				ClipboardInputText(L"семь");
				break;
			case '8':
				ClipboardInputText(L"восемь");
				break;
			case '9':
				ClipboardInputText(L"девять");
				break;
			default:
				ClipboardInputText(Data);
				break;
			}
			
			//if (*Data == '0') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"ноль");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"ноль"); 
			//}
			//else if (*Data == '1') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"один");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"один"); 
			//}
			//else if (*Data == '2') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"два");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"два"); 
			//}
			//else if (*Data == '3') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"три");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"три"); 
			//}
			//else if (*Data == '4') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"четыре");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"четыре"); 
			//}
			//else if (*Data == '5') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"пять");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"пять"); 
			//}
			//else if (*Data == '6') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"шесть");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"шесть"); 
			//}
			//else if (*Data == '7') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"семь");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"семь"); 
			//}
			//else if (*Data == '8') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"восемь");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"восемь"); 
			//}
			//else if (*Data == '9') // если не пустая строка
			//{
			//	swprintf(third, sizeof third, L"%s%s", Alert, L"девять");
			//	MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
			//	ClipboardInputText(L"девять"); 
			//} 
		}
		Sleep(1000); // ждать 1 сек 
	}


	return 0;
}





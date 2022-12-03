#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int ClipboardInputText(LPWSTR buffer);
int ClipboardOutptText();
TCHAR* ClipboardOutptText2();

int ClipboardInputText(LPWSTR buffer)
{
	DWORD len; // переменная под длину сообщения
	HANDLE hMen; // дескриптор глобальной области памяти 
	len = wcslen(buffer) + 1; //(количество символов) вычисление длины в юникоде (+1  строка должна заканчивать нулевым символом)
	// задаем дескриптор
	// Global - выделяем память в глобальной области видимости, чтобы память была видна за пределами программы
	hMen = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR));
	//memcpy - функция копирования в памяти (копируем то что в буфере в глобадьрную область памяти)
	// GlobalLock - фиксирует эту память (зарезервировать)
	// buffer - содержимое строки, затем сколько байт копируем туда
	memcpy(GlobalLock(hMen), buffer, len * sizeof(LPWSTR)); // копируем область памяти из buffer в hMen 
	GlobalUnlock(hMen); // разблокировать содержимое этой памяти(сделать доступным для дргуих программ - для системного буфера)
	OpenClipboard(0); // откр буфер обмена - код 0 значит в режиме по умолч
	EmptyClipboard(); // очистить буфер обмена - чтоб не было лишнего, толбко свое
	//CF_UNICODETEXT - что кладем (юникод текст - тип), hMen - что записываем (дискриптор нашей глобальной области памяти передем)
	SetClipboardData(CF_UNICODETEXT, hMen); // записать в буфер данные соответсвующего типа
	CloseClipboard(); // закрыть буфер, сделав его доступным для других проложений
	return 0;
}

int ClipboardOutptText() // из буфера тест помещается в некий дискриптор глобальной области памяти
{
	LPWSTR Mess = NULL; // переменна, которая выводится в мессэдж бокс (по умолчанию нуль )
	OpenClipboard(NULL); // открыть буфер обмена - код NULL значит в режиме по умолч
	// присваиваем значение, в кафестве аргумента тип
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT); // записать в буфер обмена данные соответствующего типа
	Mess = (LPWSTR)GlobalLock(hClipboardData); // считать из глобального участка памяти, привести это в к строке (LPWSTR) и поместить в строку Messege
	// скопировали , память нам не нужна можно ее разблокировать
	GlobalUnlock(hClipboardData); // освободдить глобальный участок памяти
	CloseClipboard(); // закрыть буфер обмена, сделать его доступнымдля других прил
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
	//Обмен данными между приложением word и программой WinAPI
	//LPWSTR Message = L"Текст"; //строка сообщения
	//ClipboardInputText(Message); // положить текст в буфер обмена
	//ClipboardOutptText();// получить текст из буфера

	//запрет копирования из системного буфера обмена
	//while (TRUE) 
	//{
	//	LPSTR Data = ClipboardOutptText2(); // указатель дата - вызов функции
	//	TCHAR Alert[] = L"Нарушение авторских прав при копировнаие текста: "; // первая строка для бокса
	//	TCHAR third[512]; // ограничение на длину символов - 1 мб
	//	// склеить строки (указатели) Alert + Data 0
	//	//аналог принта, только не на консоль, а в переменную записывает, рабоатет в юникодом
	//	// sizeof - выдел памяти, L - формат, указатель на юникод
	//	swprintf(third, sizeof third, L"%s%s", Alert, Data);
	//	if (*Data != 0) // если не пустая строка
	//	{
	//		MessageBox(NULL, &third, L"Нарушение!!", MB_OK | MB_ICONASTERISK);
	//		ClipboardInputText(""); // очищаем буфер 
	//	}
	//	Sleep(1000); // ждать 1 сек
	//}



	//при копировании цифры в системный буфер обмена выводить в буфер ее словесное описание
	while (TRUE) // не напряжный цикл 
	{
		// 1 2 3 4 5 6 7 8 9 четыре шесть четыре четыре напряжный цикл  девять восемь семь шесть пять четыре три 2 два один два

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
			//
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





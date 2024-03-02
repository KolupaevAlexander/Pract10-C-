#include <windows.h>
#include <iostream>
#include <conio.h>
#include <format>
#include <string>
#include <format>
#pragma warning(disable : 4996)

//int main()
//{
//    setlocale(LC_ALL,"rus");
//    char path[] = "C:\\Users\\st310-05\\Desktop\\kolupaev\\CA.exe";
//
//    wchar_t wtext[50];
//    mbstowcs(wtext, path, strlen(path) + 1);//Plus null
//    LPWSTR lpszAppName = wtext;
//
//    STARTUPINFO si;
//    PROCESS_INFORMATION piApp;
//    ZeroMemory(&si, sizeof(STARTUPINFO));
//    si.cb = sizeof(STARTUPINFO);
//
//    // создаем новый консольный процесс
//    if (!CreateProcess(lpszAppName, NULL, NULL, NULL, true,
//        CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
//    {
//        _cputs("The new process is not created.\n");
//        _cputs("Check a name of the process.\n");
//        _cputs("Press any key to finish.\n");
//        _getch();
//        return 0;
//    }
//    _cputs("The new process is created.\n");
//    //WaitForSingleObject(piApp.hProcess, INFINITE);
//
//    std::cout << piApp.dwProcessId << " - " << piApp.dwThreadId << std::endl;
//    std::cout << piApp.hProcess << " - " << piApp.hThread << std::endl;
//    while (true)
//    {
//        char c;
//        _cputs("Input 't' to terminate the new console process: ");
//        c = _getch();
//        if (c == 't')
//        {
//            _cputs("t\n");
//            TerminateProcess(piApp.hProcess, 1);
//            break;
//        }
//    }
//
//    // закрываем дескрипторы этого процесса в текущем процессе
//    CloseHandle(piApp.hThread);
//    CloseHandle(piApp.hProcess);
//
//    
//
//    return 0;
//}

volatile int count;
void thread()
{
	for (;;)
	{
		count++;
		Sleep(500);
		_cprintf("count = %d\n", count);
	}
}
int main()
{
	int data = 10;

	char lpszComLine[80] = "C:\\Users\\st310-05\\Desktop\\kolupaev\\Inherit.exe 10 ";
	// для символьного представления дескриптора
	char lpszHandle[20];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hThread;
	DWORD IDThread;

	_cputs("Press any key to start the count-thread.\n");
		_cputs("After terminating the thread press any key to exit.\n");
	_getch();
	// запускаем поток-счетчик
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL,
		0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	// делаем дескриптор потока наследуемым
	if (!SetHandleInformation(
		hThread, // дескриптор потока
		HANDLE_FLAG_INHERIT, // изменяем наследование дескриптора
		HANDLE_FLAG_INHERIT)) // делаем дескриптор наследуемым
	{
		_cputs("The inheritance is not changed.\n");
		_cputs("Press any char to finish.\n");
		_getch();
		return GetLastError();
	}
	// устанавливаем атрибуты нового процесса
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	// преобразуем дескриптор в символьную строку
	_itoa((int)hThread, lpszHandle, 10);
	// создаем командную строку
	strcat(lpszComLine, lpszHandle);
	// запускаем новый консольный процесс

	wchar_t wtext[50];
    mbstowcs(wtext, lpszComLine, strlen(lpszComLine) + 1);//Plus null
    LPWSTR lpszAppName = wtext;

	if (!CreateProcess(
		NULL, // имя процесса
		lpszAppName, // адрес командной строки
		NULL, // атрибуты защиты процесса по умолчанию
		NULL, // атрибуты защиты первичного потока по умолчанию
		TRUE, // наследуемые дескрипторы текущего процесса
		// наследуются новым процессом
		CREATE_NEW_CONSOLE, // новая консоль
		NULL, // используем среду окружения процесса-предка
		NULL, // текущий диск и каталог, как и в процессе-предке
		&si, // вид главного окна - по умолчанию
		&pi // здесь будут дескрипторы и идентификаторы
		// нового процесса и его первичного потока
	)
		)
	{
		_cputs("The new process is not created.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	// закрываем дескрипторы нового процесса


	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	_getch();
	// закрываем дескриптор потока
	
	CloseHandle(hThread);
	return 0;
}
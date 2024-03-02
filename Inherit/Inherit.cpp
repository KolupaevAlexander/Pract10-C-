#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hThread;
	char c;

	auto a = argv[1];

	cout << std::stoi(a) * std::stoi(a) << endl;
	
	// преобразуем символьное представление дескриптора в число
	hThread = (HANDLE)atoi(argv[2]);
	// ждем команды о завершении потока

	while (true)
	{
		_cputs("Input 't' to terminate the thread: ");
		c = _getch();
		if (c == 't')
		{
			_cputs("t\n");
			break;
		}
	}
	// завершаем поток
	TerminateThread(hThread, 10);
	// закрываем дескриптор потока
	CloseHandle(hThread);
	_cputs("Press any key to exit.\n");
	_getch();
	return 0;
}
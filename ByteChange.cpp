#include "MyFunction.h"

bool ByteChange()
{
	bool w = true;
	char *path, *name = (char*)calloc(1,1);
	__int64 position;

	while(w)
	{	
		system("cls");
		cout << "Введите название диска(Заглавную букву): " << endl;
		
		cin >> name;

		if(name[0] >= 65 && name[0] <= 90)
		{
			path = new char[10];
			strcpy(path, Wstr);
			strcat(path, name);
			strcat(path, endStr);
			w = false;
		}
		else 
		{
			system("cls");
			cout << "Попробуйте ввести еще раз..." << endl;
			Sleep(2000);
		}
	}
	
	w = true;
	while(w)
	{
		system("cls");
		cout << "Введите позицию для изменения: " << endl;
		cin >> position;
		Disc qd;
		if(position > (qd.GetSize(path) / 512))
		{
			system("cls");
			cout << "Не входит в данный раздел. Попробуйте еще раз!" << endl;
			Sleep(2000);
		}
		else
		{
			w = false;
		}
	}

	_LARGE_INTEGER step, _step;
	step.QuadPart = 512;
	_step.QuadPart = -512;
	BYTE bufW[512], bufR[512];
	DWORD byteWrite, byteRead;
	int sizeSector = 512;

	HANDLE hDisk = CreateFile(path,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL, OPEN_EXISTING,
		FILE_FLAG_RANDOM_ACCESS,
		NULL);

   if (hDisk == INVALID_HANDLE_VALUE)
   {
	   cout << "Error: " << GetLastError() << endl;
	   getch();
	   return false;
   }
   else
   {
	   for (__int64 i = 0; i < position; i++)
		   SetFilePointerEx(hDisk, step, NULL, FILE_CURRENT);

	   if (!ReadFile(hDisk, bufR, sizeof(bufR), &byteRead, NULL) || byteRead != sizeof(bufR))
	   {
		   cout << "Error" << endl;
		   return false;
	   }
	   else
	   {
		   system("cls");
		   cout << "THIS SECTOR:" << endl << endl;
		   for(int i = 0; i< sizeSector ;i++)
		   {
			   cout << i << "\t" << bufR[i] << "\t";
			   if(i % 7 == 0)
				   cout << endl;
		   }
		   cout << endl << endl;
		   SetFilePointerEx(hDisk, _step, NULL, FILE_CURRENT);
	   }

	   cout << "Для продолжения нажмите любую клавишу..." << endl;
	   getch();
	   system("cls");
	   int value;
	   cout << "Введите значения для замены в кодировке Ascii(номер): ";
	   cin >> value;
	   system("cls");
	   for(int i = 0; i< sizeSector ;i++)
		   bufW[i] = value;

	   if (!WriteFile(hDisk, bufW, sizeof(bufW), &byteWrite, NULL))
	   {
		   cout << "Error3 " << GetLastError() << endl;
		   return false;
	   }
	   else
		   SetFilePointerEx(hDisk, _step, NULL, FILE_CURRENT);

   
	   if (!ReadFile(hDisk, bufR, sizeof(bufR), &byteRead, NULL) || byteRead != sizeof(bufR))
	   {
		   cout << "Error4" << endl;
		   return false;
	   }
	   else
	   {
		   cout << "NEW SECTOR:" << endl << endl;
		   for(int i = 0; i< sizeSector ;i++)
		   {
			   cout << i << "\t" << bufR[i] << "\t";
			   if(i % 7 == 0)
				   cout << endl;
		   }
		   SetFilePointerEx(hDisk, _step, NULL, FILE_CURRENT);
	   }
   }
   CloseHandle(hDisk);
   return true;
}
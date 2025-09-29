#include <iostream>
#include <Windows.h>
#include <conio.h>


using namespace std;

enum ERenderScreenBuffer
{
	FrontBuffer = 0,
	BackBuffer = 1
};

int CurrentBufferIndex = FrontBuffer;

struct FCharacter
{
	int X;
	int Y;
	string Shape;
};

FCharacter Characters[3];

int KeyCode;

HANDLE FrontBufferHandle;
HANDLE BackBufferHandle;

void Input()
{
	KeyCode = _getch();
}


//C++
void RenderCharacter(const FCharacter* InData)
{
	COORD Position;
	Position.X = (SHORT)InData->X;
	//Position.Y = (SHORT)(*InData).Y;
	Position.Y = (SHORT)InData->Y;


	if (CurrentBufferIndex == FrontBuffer)
	{
		SetConsoleCursorPosition(FrontBufferHandle, Position);
		WriteConsole(FrontBufferHandle, InData->Shape.c_str(), 1, NULL, NULL);
	}
	else
	{
		SetConsoleCursorPosition(BackBufferHandle, Position);
		WriteConsole(BackBufferHandle, InData->Shape.c_str(), 1, NULL, NULL);
	}


}

void Clear()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (CurrentBufferIndex == FrontBuffer)
	{
		//스크린 버퍼 정보 가져오기
		GetConsoleScreenBufferInfo(FrontBufferHandle, &csbi);
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(FrontBufferHandle,
			(TCHAR)' ',
			dwConSize,
			coordScreen,
			&cCharsWritten);
	}
	else
	{
		GetConsoleScreenBufferInfo(BackBufferHandle, &csbi);
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(BackBufferHandle,
			(TCHAR)' ',
			dwConSize,
			coordScreen,
			&cCharsWritten);
	}
}

void Present()
{
	if (CurrentBufferIndex == FrontBuffer)
	{
		SetConsoleActiveScreenBuffer(FrontBufferHandle);
	}
	else
	{
		SetConsoleActiveScreenBuffer(BackBufferHandle);
	}

	CurrentBufferIndex++;
	CurrentBufferIndex = CurrentBufferIndex % 2;
}


//렌더
//렌더 모든 캐릭터를 
void Render()
{
	//그래픽 카드 그리는 방식
	Clear();

	for (int i = 0; i < 2; ++i)
	{
		RenderCharacter(&Characters[i]);
	}

	Present();
}

void Init()
{
	//0
	FrontBufferHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);

	//1
	BackBufferHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);

	//형변환, Casting
	srand((unsigned int)time(nullptr));

	Characters[0].X = 1;
	Characters[0].Y = 1;
	Characters[0].Shape = "P";

	Characters[1].X = 10;
	Characters[1].Y = 10;
	Characters[1].Shape = "M";
}

void MovePlayer()
{
	if (KeyCode == 'w')
	{
		Characters[0].Y--;
	}
	else if (KeyCode == 's')
	{
		Characters[0].Y++;
	}
	else if (KeyCode == 'a')
	{
		Characters[0].X--;
	}
	else if (KeyCode == 'd')
	{
		Characters[0].X++;
	}
}

void MoveMonster()
{
	int Direction = rand() % 4;

	switch (Direction)
	{
	case 0:	//Up
		Characters[1].Y--;
		break;
	case 1:	//Down
		Characters[1].Y++;
		break;
	case 2: //Left
		Characters[1].X--;
		break;
	case 3: //Right
		Characters[1].X++;
		break;
	default:
		//Error
		break;
	}

}

void Tick()
{
	MovePlayer();
	MoveMonster();
}




int main()
{
	//FCharacter* Data = new FCharacter();

	//(*Data).X = 1;
	//Data->X = 1;

	//delete Data;

	Init();

	while (true)
	{
		Input();
		Tick();
		Render();
	}

	return 0;
}
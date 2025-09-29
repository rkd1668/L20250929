#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// C++ -> class
// UE F추가
struct FCharacter
{
	int X;
	int Y;
	char Shape;
};

FCharacter Characters[3];
int MaxX = 20;
int MaxY = 20;
int KeyCode;

bool bIsRunning = true;

void Input()
{
	KeyCode = _getch();
}

bool Predict(int NewX, int NewY)
{
	if (NewX < 0 || NewY < 0 || NewX >= MaxX || NewY >=MaxY)
	{
		return false;
	}
	return true;
}

void RenderCharacter(FCharacter InData)
{
	COORD Position;
	Position.X = InData.X;
	Position.Y = InData.Y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
	cout << InData.Shape;
}

void Render()
{
	for (int i = 0; i < 3; i++)
	{
		RenderCharacter(Characters[i]);
	}
}

void Init()
{
	srand((unsigned int)time(nullptr));

	Characters[0].X = 1;
	Characters[0].Y = 1;
	Characters[0].Shape = 'P';

	Characters[1].X = 10;
	Characters[1].Y = 10;
	Characters[1].Shape = 'M';
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
	case 0: //Up
		Characters[1].Y--;
		break;
	case 1: //Down
		Characters[1].Y++;
		break;
	case 2: //Left
		Characters[1].X--;
		break;
	case 3: //Right
		Characters[1].X++;
		break;
	default://Error
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
	Init(); 

	while (true)
	{
		Input();
		Tick();
		Render();
	}
	return 0;
}
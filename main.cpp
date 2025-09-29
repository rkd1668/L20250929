#include <iostream>
#include <conio.h>

using namespace std;

int MaxX = 20;
int MaxY = 20;
int KeyCode;
int PlayerX = 0;
int PlayerY = 0;
int MonsterX = 1;
int MonsterY = 3;
char PlayerShape = 'P';
char MonsterShape = 'M';
bool bIsRunning = true;

void Input()
{
	KeyCode = _getch();
}

bool Predict(int NewX, int NewY)
{
	if (NewX < 0 || NewY < 0 || NewX >= MaxX || NewY >= MaxY)
	{
		return false;
	}
	return true;
}

void Process()
{
	if (KeyCode == 'w')
	{
		if (Predict(PlayerX, PlayerY - 1))
		{
			PlayerY--;
		}
	}
	else if (KeyCode == 's')
	{
		if (Predict(PlayerX, PlayerY + 1))
		{
			PlayerY++;
		}
	}
	else if (KeyCode == 'a')
	{
		if (Predict(PlayerX - 1, PlayerY))
		{
			PlayerX--;
		}
	}
	else if (KeyCode == 'd')
	{
		if (Predict(PlayerX + 1, PlayerY))
		{
			PlayerX++;
		}
	}
	else if (KeyCode == 'q')
	{
		bIsRunning = false;
	}
}

void Render()
{
	system("cls");
	for (int y = 0; y < MaxY; y++)
	{
		for (int x = 0; x < MaxX; x++)
		{
			if (PlayerX == x && PlayerY == y)
			{
				cout << PlayerShape;
			}
			else if (MonsterX == x && MonsterY == y)
			{
				cout << MonsterShape;
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

int main()
{
	while (bIsRunning)
	{
		Render();
		Input();
		Process();
	}

	return 0;
}
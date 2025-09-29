#include <iostream>
#include <conio.h>

using namespace std;

int KeyCode;
int PlayerX = 0;
int PlayerY = 0;
char PlayerShape = 'P';
bool bIsRunning = true;

void Input()
{
	KeyCode = _getch();
}

bool Predict(int NewX, int NewY)
{
	if (NewX < 0 || NewY < 0)
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
}

void Render()
{
	system("cls");
	for (int i = 0; i <= PlayerY; i++)
	{
		for (int j = 0; j <= PlayerX; j++)
		{
			if (PlayerX == j && PlayerY == i)
			{
				cout << PlayerShape;
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
		Input();
		Process();
		Render();
	}

	return 0;
}
// øàëîì
#include <iostream>
#include <string>
#include <set>
#include <random>
#include <chrono>
using namespace std;
int field[9][9];
set <int > squares[9], rows[9], columns[9];
int randint(int a, int b) 
{
	mt19937 m(chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> uid(a, b);
	return uid(m);
}
void OutputOfThePlayingField()
{
	system("cls");
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		
		if (i % 3 == 0 && i != 8)
		{
			cout << "=======================================" << endl;
		}
		else
		{
			cout << "+---+---+---++---+---+---++---+---+---+" << endl;
		}
		for (int j = 0; j < 9; j++)
		{
			cout << "|";
			if (j % 3 == 0 && j != 8 && j != 0)
			{
				cout << "|";
			}
			if (field[i][j])
			{
				cout << ' ' << field[i][j] << ' ';// << ' ';
			}
			else
			{
				cout << " . ";
			}
			
		}
		cout << "|";
		cout << endl;
	}
	cout << "=======================================" << endl;
}
bool PlaceInField(int x, int y, int n)
{
	x--, y--;
	if (!(x >= 0 && x < 9 && y >= 0 && y <= 9)) return 0;
	if (rows[x].lower_bound(n) != rows[x].end() && *rows[x].lower_bound(n) == n && \
		columns[y].lower_bound(n) != columns[y].end() && *columns[y].lower_bound(n) == n)
	{
		int id = x / 3 * 3 + y / 3;
		if (*squares[id].lower_bound(n) == n)
		{
			field[x][y] = n;
			rows[x].erase(n);
			columns[y].erase(n);
			squares[id].erase(n);
			return 1;
		}
		return 0;
	}
	return 0;
}
void transposing()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = i; j < 9; j++)
		{
			swap(field[i][j], field[j][i]);
		}
	}
}
void swap_rows()
{
	int i = randint(0, 8);
	int j = randint(i / 3 * 3, i / 3 * 3 + 2);
	swap(field[i], field[j]);
}
void swap_columns()
{
	transposing();
	swap_rows();
	transposing();
}
void swap_rows_area()
{
	int i = randint(0, 8), j = randint(0, 8);
	i = i / 3 * 3;
	j = j / 3 * 3;
	int o = 3;
	while (o--)
	{
		swap(field[i], field[j]);
		i++;
		j++;
	}
}
void swap_columns_area()
{
	transposing();
	swap_rows_area();
	transposing();
}
void StartFilling(int dif)
{
	/*
	set <int > st;
	for (int i = 1; i <= 9; i++)
	{
		st.insert(i);
	}
	for (int i = 0; i < 9; i++)
	{
		squares[i] = st;
		rows[i] = st;
		columns[i] = st;
	}
	*/
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			field[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
		}
	}
	for (int i = 0; i < 1000; i++)
	{
		int perm = randint(0, 4);
		switch (perm)
		{
			case 0:
				transposing();
			case 1:
				swap_rows();
			case 2:
				swap_columns();
			case 3:
				swap_rows_area();
			case 4:
				swap_columns_area();
		}
	}
	dif *= 16;
	for (int o = 0; o < dif; o++)
	{
		int i = randint(0, 8);
		int j = randint(0, 8);
		while (field[i][j] == 0)
		{
			i = randint(0, 8);
			j = randint(0, 8);
		}
		int k = field[i][j];
		
		rows[i].insert(k);
		columns[j].insert(k);
		squares[i / 3 * 3 + j / 3].insert(k);
		field[i][j] = 0;
	}
	
}
void Game()
{
	cout << "google translate" << endl;
	int dif;
	cout << "Select difficulty (1 - simplest, 4 - hardest)." << endl;
	cin >> dif;
	
	StartFilling(dif);
	bool game = 1;
	dif *= 16;
	
	while (game)
	{
		OutputOfThePlayingField();
		cout << "Enter the coordinates of the cell, and the number you want to insert there." << endl;
		int x, y, n;
		cin >> x >> y >> n;
		
		while (!PlaceInField(x, y, n))
		{
			cout << "You cannot select this cell, try again." << endl;
			cin >> x >> y >> n;
		}
		if (dif > 0)
			dif--;
		if (!dif)
		{
			cout << "You won" << endl;
			return;
		}
		
	}
	

}
int main()
{
	system("color F0");
	Game();
	return 0;
}

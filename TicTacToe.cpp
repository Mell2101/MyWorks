#include<iostream>
#include<clocale>
#include<Windows.h>
#include<time.h>
using namespace std;
//=======================================================
//создаем массив
char el[] = { '-','-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' ,'-' };
//	add colors
void SetColor(int text, int background)
{
	//change color
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, ((WORD)(background << 4) | text));
}
//=======================================================
void space(int s)
{
	for (int i = 0;i < s;i++)
	{
		cout << ' ';
	}
}
//=======================================================
void sell()
{
	SetColor(14, 0);
	space(34); cout << '-' << el[0] << "-|-" << el[1] << "-|-" << el[2] << "-\n";
	space(34); cout << '-' << el[3] << "-|-" << el[4] << "-|-" << el[5] << "-\n";
	space(34); cout << '-' << el[6] << "-|-" << el[7] << "-|-" << el[8] << "-\n";
	
}
//=======================================================
void clearEl()
//clear sell
{
	for (int i = 0;i < 9;i++)
	{
		el[i] = char(i + 49);
	}

}
//=======================================================
void clearscreen(int s)
{
	for (int i = 0;i < s;i++)
	{
		cout << endl;
	}

}
//=======================================================
void print()
{
	//print logo 
	SetColor(7, 0);
    space(16); cout << " ##     ##    ##     ##  ######      #######  \n";
	space(16); cout << "  ##   ##     ##     ## ##    ##    ##     ## \n";
	space(16); cout << "   ## ##      ##     ## ##          ##     ## \n";
	SetColor(8, 0);
	space(16); cout << "    ###       ##     ##  ######     ##     ## \n";
	space(16); cout << "   ## ##       ##   ##        ##    ##     ## \n";
	space(16); cout << "  ##   ##       ## ##   ##    ##    ##     ## \n";
	space(16); cout << " ##     ##       ###    ######      #######  \n";
}
//=======================================================
bool isWinner(char who)
{
	if (el[0] == who && el[1] == who && el[2] == who) return true;
	if (el[3] == who && el[4] == who && el[5] == who) return true;
	if (el[6] == who && el[7] == who && el[8] == who) return true;
	if (el[0] == who && el[3] == who && el[6] == who) return true;
	if (el[1] == who && el[4] == who && el[7] == who) return true;
	if (el[2] == who && el[5] == who && el[8] == who) return true;
	if (el[0] == who && el[4] == who && el[8] == who) return true;
	if (el[2] == who && el[4] == who && el[6] == who) return true;
	return false;
}
//=======================================================
int Bot()
{
	if (el[4] == '5') return 5;
	for (int i = 0; i < 9; i++)
		if (el[i] == char(i + 49)) {
			el[i] = 'O';
			if (isWinner('O'))
				return i + 1;
			else
				el[i] = char(i + 49);

			el[i] = 'X';
			if (isWinner('X'))
				return i + 1;
			else
				el[i] = char(i + 49);
		}
	for (int i = 0; i < 9; i++)
		if (el[i] == char(i + 49))
			return i + 1;
}


void print2()
{
	system("cls");
	clearscreen(2);
	print();
	clearscreen(2);
	sell();
	clearscreen(1);
}
//=========================================================
char game(int a)
{
	int turn = 1;
	int move;
	char c = 'X', b = 'O';
	if (a == 0)
	{
		swap(c, b);
	}
	while (1)
	{
		if (turn % 2 == a)
		{
			print2();
			SetColor(12, 0);
			if (turn > 1)
			{
				space(30);
				cout << "Bot set " << b << " on " << move << endl;
			}


			space(34);
			cout << "You turn:"<<" ";
			cin >> move;
			while (move > 9 || el[move - 1] == 'X' || el[move - 1] == 'O')
			{
				SetColor(12, 0);
				space(15);
				cout << "Please enter correct values" << endl;
				space(34);
				cout << "You turn:"<<" ";
				cin >> move;

			}
			el[move - 1] = c;
			if (isWinner(c))
			{
				print2();
				space(35);
				for (int i = 0;i < 4000'000'00;i++)
				{
					if (i % 100'00'00'00 == 0)
					{
						cout << '.';
					}
				}
				SetColor(2, 0);
				cout << "X win" << endl;
				return c;

			}
		}
		else
		{
			print2();
			SetColor(12, 0);
			if (turn > 1)
			{
				space(30);
				cout << " You bet " << c << " on " << move << endl;
			}
			space(35);
			cout << "Bot thinks ";
			for (int i = 0; i < 600'000'000;i++)
			{
				if (i % 100000000 == 0) 
				{
					cout << '.';
				}
			}
			cout << endl;
			move = Bot();
			el[move - 1] = b;
			if (isWinner(b))
			{
				print2();
				space(33);
				for (int i = 0;i < 400'000'000;i++)
				{
					if (i % 100'000'000)
					{
						cout << '.';
					}
					SetColor(2, 0);
					cout << "O win!" << endl;
					return b;
				}
			}
		}
		turn++;
		if (turn == 10)
		{
			print2;
			space(33);
			for (int i = 0;i < 400'000'000;i++)
			{
				if (i % 100000000 == 0)
				{
					cout << '.';
				}
			}	
			SetColor(2, 0);
			cout << "Draw!"<<endl;
			return'D';
		}

	}
}
int main()
{
	srand(time(0));
	int p_wins, b_wins, draws;
	p_wins = b_wins = draws = 0; // статистика
	char choice = 'y';
	int h = 0;
	while (choice == 'y') {
		clearEl();
		char winner;
		h = abs(h - 1);
		winner = game(h);
		if (winner == 'D') draws++;
		if (winner == 'X') {
			if (h == 1) p_wins++;
			else b_wins++;
		}
		if (winner == 'O') {
			if (h == 0) p_wins++;
			else b_wins++;
		}
		SetColor(3, 0);
		space(32);
		
		cout << "You win " << p_wins <<" "<< "once\n";
		space(32);
		cout << "Computer win " << b_wins << " once\n";
		space(32);
		cout << "Drow " << draws << " again\n";
		SetColor(7, 0);
		space(32);
		cout << "again? y/n :";
		cin >> choice;
	}
	return 0;
}
#include<iostream>
#include<conio.h> 
#include <windows.h>
#include <time.h>

int screen_length = 115;     // left verticle line;
int  screen_height = 28;
int win_w = 80;              // middle line space;

using namespace std;
COORD CursorPosition;

int y[3];
int x[3];
int flag[3];

char ship[3][5] = { ' ',' ','^',' ',' ',
					' ','=','|','=',' ',
					'=','=','^','=','=' };

int ship_position = win_w / 2;
int score = 0;
int level = 0;
int lives;
int fire[20][4];
int firelife[20];
int c_Index = 0;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
void setcursor(bool visible, double size)
{
	if (size == 0)
	{
		size = 20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
}
void draw_border()
{
	system("cls");
	for (int i = 2; i < screen_height; i++) {
		gotoxy(2, i);
		cout << "@@";//ą
		gotoxy(screen_length, i);
		cout << "@@";
	}
	for (int i = 2; i < screen_height; i++) {
		gotoxy(win_w, i); cout << "@@";
	}

	for (int i = 2; i < screen_length; i++) {
		gotoxy(i, 1); cout << "@@@";
		gotoxy(i, screen_height); cout << "@@@";

	}
	for (int i = win_w; i <= screen_length; i++)
	{
		int j = 9; j++;
		gotoxy(i, j);
		cout << "@@";
	}
	for (int i = win_w; i <= screen_length; i++)
	{
		gotoxy(i, 18);
		cout << "@@";
	}
}
void drawEnemy(int ind)
{
	if (flag[ind] == true)
	{
		gotoxy(x[ind], y[ind]);   cout << "___";
		gotoxy(x[ind], y[ind] + 1); cout << ":::";
	}
}
void produce_enemy(int ind)
{
	x[ind] = 6 + rand() % (win_w - 10);
}


void eraseEnemy(int ind) {
	if (flag[ind] == true)
	{
		gotoxy(x[ind], y[ind]); cout << "    ";
		gotoxy(x[ind], y[ind] + 1); cout << "    ";

	}
}
void renew_enemy(int ind)
{
	eraseEnemy(ind);
	y[ind] = 4;
	produce_enemy(ind);
}
void genfire()
{
	fire[c_Index][0] = 22;
	fire[c_Index][1] = ship_position + 2;
	//	bullets[bIndex][2] = 22; 
	//	bullets[bIndex][3] = birdPos+4; 
	c_Index++;
	if (c_Index == 20)
	{
		c_Index = 0;
	}
}
void move_fire()
{
	int i = 0;
	while (i < 20)
	{
		if (fire[i][0] > 2)
		{
			fire[i][0]--;
		}
		else
		{
			fire[i][0] = 0;
		}
		if (fire[i][2] > 2)
		{
			fire[i][2]--;
		}
		else
		{
			fire[i][2] = 0;
		}
		i++;
	}
}
void drawfire()
{
	int j = 0;
	while (j <= 20)
	{
		if (fire[j][0] > 1)
		{
			gotoxy(fire[j][1], fire[j][0]); cout << "*";

		}
		j++;
	}
}
void erasefire(int i)
{
	gotoxy(fire[i][1], fire[i][0]); cout << " ";

}
void remove_fire()
{
	int i = 0;
	while (i < 20)
	{
		if (fire[i][0] >= 1)
		{
			gotoxy(fire[i][1], fire[i][0]); cout << " ";
		}
		i++;
	}

}
void design_character()
{
	int i = 0;
	while (i < 3)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoxy(j + ship_position, i + 25); cout << ship[i][j];
		}
		i++;
	}
}
void eraseship()
{
	int i = 0;
	while (i < 3)
	{
		for (int j = 0; j < 5; j++) {
			gotoxy(j + ship_position, i + 25); cout << " ";
		}
		i++;
	}
}

int collision()
{
	if (y[0] + 4 >= 26)
	{
		if (x[0] + 4 - ship_position >= 0 && x[0] + 4 - ship_position < 8)
		{
			return 1;
		}
	}
	return 0;
}
int fire_hitting() {
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 4; j += 2)
		{
			if (fire[i][j] != 0)
			{
				if (fire[i][j] >= y[0] && fire[i][j] <= y[0] + 4) {
					if (fire[i][j + 1] >= x[0] && fire[i][j + 1] <= x[0] + 4)
					{
						erasefire(i);
						fire[i][j] = 0;
						renew_enemy(0);
						return 1;
					}
				}
				if (fire[i][j] >= y[1] && fire[i][j] <= y[1] + 4) {
					if (fire[i][j + 1] >= x[1] && fire[i][j + 1] <= x[1] + 4)
					{
						erasefire(i);
						renew_enemy(1);
						fire[i][j] = 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void game_over()
{
	system("cls");
	//cout<<endl;
	gotoxy(30, 6); cout << "--------------------------";
	gotoxy(30, 7); cout << "-------- Game Over -------";
	gotoxy(30, 8); cout << "--------------------------";
	gotoxy(30, 9); cout << "Press any key to go back to menu.";
	_getch();
}
void updateScore()
{
	//	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
	gotoxy(win_w + 13, 22); cout << "S C O R E = " << score;
}

void instructions()
{
	int ch;
	system("cls");
	gotoxy(30, 6); cout << "|---------------------|";
	gotoxy(30, 7); cout << "|-----Instruction-----|";
	gotoxy(30, 8); cout << "|---------------------|";
	gotoxy(30, 12); cout << "use arrow keys (F To H) to move";
	gotoxy(30, 16); cout << "use space bar to fire the bullets";
	gotoxy(30, 20); cout << "Enter any integer number to go back to menu";
	cin >> ch;
}
void control_level()
{
	int x = 0;
	gotoxy(win_w + 10, 4); cout << " *--------------* ";
	gotoxy(win_w + 13, 5); cout << " S P A C E ";
	gotoxy(win_w + 11, 6); cout << " S H O O T E R ";
	gotoxy(win_w + 10, 7); cout << " *--------------* ";
	gotoxy(win_w + 13, 22); cout << "S C O R E = " << x;
	gotoxy(win_w + 13, 24); cout << "L I V E S = " << lives;
}
void update_level()
{
	gotoxy(win_w + 12, 13); cout << " L E V E L # " << level;
}
void update_lives()
{
	gotoxy(win_w + 13, 24); cout << "L I V E S = " << lives;
	lives++;

}
void main1()
{

	ship_position = -1 + win_w / 2;
	score = 0;
	level = 0;
	lives = 0;
	flag[0] = 1;
	flag[1] = 1;
	y[0] = y[1] = 5;

	for (int i = 0; i < 20; i++)
	{
		fire[i][0] = fire[i][1] = 0;
	}

	system("cls");
	draw_border();
	produce_enemy(0);
	produce_enemy(1);
	updateScore();
	update_level();
	update_lives();

	control_level();

	_getch();

	while (1)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'F' || ch == 'f')
			{
				if (ship_position > 6)
				{

					ship_position -= 3;
				}
			}
			if (ch == 'H' || ch == 'h')
			{
				if (ship_position < win_w - 7)
				{

					ship_position += 3;
				}
			}
			if (ch == 32) {
				genfire();
			}
			if (ch == 27)
			{
				break;
			}
		}

		design_character();
		drawEnemy(0);
		drawEnemy(1);
		drawfire();

		//collision();
		if (collision() == 1)
		{
			if (lives == 3)
			{
				game_over();
				return;
			}

			update_lives();
		}

		if (fire_hitting() == 1) {
			score++;
			updateScore();
			if (score % 10 == 0)
			{
				level++;
				update_level();
			}

		}
		if (level >= 0 && level <= 2)
		{
			Sleep(200);
		}
		else if (level >= 3 && level <= 5)
		{

			Sleep(100);
		}
		else
		{
			Sleep(50);
		}
		eraseship();
		eraseEnemy(0);
		eraseEnemy(1);
		remove_fire();
		move_fire();
		if (flag[0] == 1)
			y[0] += 1;

		if (flag[1] == 1)
			y[1] += 1;

		if (y[0] > screen_height - 4)
		{
			renew_enemy(0);
		}
		if (y[1] > screen_height - 4)
		{
			renew_enemy(1);
		}
	}
}

int main()
{
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	do {
		system("cls");
		gotoxy(30, 3);  cout << "*---------------------------*";
		gotoxy(30, 4);  cout << "|                           |";
		gotoxy(30, 5); cout << "*_______SPACE SHOOTER_______*";
		gotoxy(30, 6); cout << "|                           |";
		gotoxy(30, 7); cout << "*---------------------------*";
		gotoxy(30, 10); cout << "1. Start Game";
		gotoxy(30, 13); cout << "2. Instructions";
		gotoxy(30, 16); cout << "3. Quit";
		gotoxy(30, 19); cout << "Select option: ";
		char op;
		cin >> op;
		if (op == '1')
		{
			main1();

		}
		else if (op == '2')
		{

			instructions();
		}
		else if (op == '3')
		{
			exit(0);
		}


	} while (1);

	return 0;
}

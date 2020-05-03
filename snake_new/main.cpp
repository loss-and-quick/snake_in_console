#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <random>
using namespace std;
void cls(){//аналог system cls ,но быстрей
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}
int main();
vector<vector<char>> starting() {//включает создание и генерирование поля
	 unsigned int size;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		3);
	
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	
	SetConsoleTitle("THE BEST SNAKE IN THE WORLD beta 0.8 by minicx");
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	
	COORD pos;
	pos.X = ((csbiInfo.srWindow.Left + csbiInfo.srWindow.Right) / 2) - 27;
	pos.Y = (csbiInfo.srWindow.Top + csbiInfo.srWindow.Bottom) / 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	
	cout << "please write size of field lines:"; GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	
	pos.Y = csbiInfo.dwCursorPosition.Y+1; pos.X = csbiInfo.dwCursorPosition.X-35;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout <<"A size greater than 25 can have bad consequences";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { csbiInfo.dwCursorPosition.X ,csbiInfo.dwCursorPosition.Y });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	vector<vector<char>> a;
	cin >> size;
	if ( size<100&&size > 8 ) {
		a.resize(size); for (int i = 0; i != size; i++) { a[i].resize(size * 2); }
	}
	else
	{
		system("cls");
		main();
	}
		
	//генерация поля
	for (int i = 0; i != size; i++) {
		for (int j = 0; j != a[i].size(); j++) {
			if (i == 0 || i == a.size() - 1) {
				if (j == 0 || j == a[i].size() - 1)
					a[i][j] = '|';
				else
				{
					a[i][j] = '-';
				}
			}
			else
			{
				if (j == 0 || j == a[i].size() - 1)
					a[i][j] = '|';
				else
				{
					a[i][j] = char(177);
				}
			}
			
		}
	}
	return a;
}


class snakehead {
public:
	int length = 0;
	int points = 0;
	int x;
	int y;
	char print = '>';
};
void show_field(vector<vector<char>> &field, snakehead snake) {
	cls();
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	COORD center;
	center.X = ((csbiInfo.srWindow.Left + csbiInfo.srWindow.Right) / 2)-field.size();
	center.Y = ((csbiInfo.srWindow.Top + csbiInfo.srWindow.Bottom) / 2)-field.size()/2;
	
	for (int i = 0; i < field.size(); i++) {
		center.Y++;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), center);
		for (int j = 0; j < field[i].size(); j++) {
			if (field[i][j] == '*') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_RED);
				cout << field[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (field[i][j] == '=')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_GREEN);
				cout << field[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (field[i][j] == snake.print)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_GREEN);
				cout << field[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
			{
				cout << field[i][j];
			}

		}
		if (i == 2) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED);
			cout << "	Your length is " << snake.length;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		if (i == 3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED);
			cout << "	Your points are " << snake.points;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		cout << endl;
		
	}
}
class class_apple {
public:
	int x = -1;
	int y = -1;
	char print = '*';
};
class snakebody {
public:
	int x=1;
	int y=-1;
	char print = '=';
	int prev_x = 0;
	int prev_y = 0;
	void move(int prev2_x, int prev2_y,vector<vector<char>> &field) {
		prev_x = x;
		prev_y = y;
		field[prev2_y][prev2_x] = print;
		x = prev2_x; y = prev2_y;
		field[prev_y][prev_x] = char(177);
	}
};
void mover(vector<snakebody> &bodies ,vector<vector<char>> &field,snakehead snake,COORD prev_posofhead) {
	for (int i = 0; i != bodies.size(); i++) {
		
		
		
		
		if (i != 0) {
			bodies[i].move(bodies[i - 1].prev_x, bodies[i - 1].prev_y, field);
		}
		else
		{
			bodies[i].move(prev_posofhead.X, prev_posofhead.Y, field);
		}
		
		
	}
}
char handler_key(snakehead &snake) {
	
	const long U = 72, L = 75, D = 80, R = 77, E = 224,exit=27;
		switch (_getch()) {
		case exit:
			return 'e';
			break;
		
		case D:
			
			snake.print = 'v';
			return 'd';
			break;
		case U:
			
			snake.print = '^';
			return  'u';
			break;

		case L:
			snake.print = '<';
			return  'l';
			break;
		case R:
			snake.print = '>';
			return 'r';

			break;
		default:
			break;
		}
	return NULL;
}
long random(long from, long to) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(from, to);
	return dist(rd);
}

void gameover(snakehead snake) {
	system("cls");
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	COORD pos;
	pos.X = ((csbiInfo.srWindow.Left + csbiInfo.srWindow.Right) / 2) -(sizeof(string)-sizeof("YOU DIED"));
	pos.Y = (csbiInfo.srWindow.Top + csbiInfo.srWindow.Bottom) / 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "YOU DIED";
	pos.Y++; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "Your length is "<< snake.length;
	pos.Y++; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << "Your points are " << snake.points;
	
	Sleep(1500);
	system("cls");
	cout << "rebooted";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	main();
}

int main() {
	vector<vector<char>> field = starting();
	class_apple apple;
	snakehead snake;
	cls;
	char current_step = '-';
	apple.y =random(2, field.size()-2 ); apple.x =random(2, field[0].size()-2);
	field[apple.y][apple.x] = apple.print;
	COORD prev_posofhead;
	vector<snakebody> bodies;
	snake.x = field[0].size() / 2;
	snake.y = field.size() / 2;
	field[snake.y][snake.x] = snake.print;
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { short(GetSystemMetrics(SM_CXSCREEN)) , short(GetSystemMetrics(SM_CYSCREEN)) });
	system("cls");
	show_field(field, snake);
	while (true) {
		
		MoveWindow(GetConsoleWindow(),0, 0, GetSystemMetrics(SM_CXSCREEN) , GetSystemMetrics(SM_CYSCREEN) , true);
		
		//Sleep(40);
		
		if (_kbhit()) {
			current_step = handler_key(snake);
		}
		prev_posofhead.X = snake.x; prev_posofhead.Y = snake.y;
		
		
		if (current_step == 'e') {
			Sleep(400);
			return 0;
		}
		if (current_step == 'd') {


			
			if (field[snake.y + 1][snake.x] != '|' &&field[snake.y + 1][snake.x] != '-' && field[snake.y + 1][snake.x] != '=') {
				snake.y++;
				Sleep(50);
				field[snake.y - 1][snake.x] = char(177);
				mover(bodies, field, snake, prev_posofhead);
				
			}
			else
			{
				gameover(snake);
				return 0;
			}

		}
		if (current_step == 'u') {
			
			if (field[snake.y - 1][snake.x] != '|' && field[snake.y - 1][snake.x] != '-'&& field[snake.y - 1][snake.x] != '=') {
				snake.y--;
				Sleep(50);
				field[snake.y + 1][snake.x] = char(177);
				mover(bodies, field, snake, prev_posofhead);
			}
			else {
				gameover(snake);
				return 0;
			}
		}

		if (current_step == 'l') {
			

			if (field[snake.y][snake.x - 1] != '|' &&field[snake.y][snake.x - 1] != '-'&& field[snake.y][snake.x - 1] != '=') {
				snake.x--;

				field[snake.y][snake.x + 1] = char(177);
				mover(bodies, field, snake, prev_posofhead);
			}
			else
			{
				gameover(snake);
				return 0;
			}
		}
		
		if (current_step == 'r') {
			
			if (field[snake.y][snake.x + 1] != '|' &&field[snake.y][snake.x + 1] != '-'&& field[snake.y][snake.x + 1] != '=') {
				snake.x++;
				field[snake.y][snake.x - 1] = char(177);
				mover(bodies, field, snake, prev_posofhead);
			}
			else {
				gameover(snake);
				return 0;
			}
		}
		
		if (snake.x == apple.x && snake.y == apple.y) {
			snake.points+=random(1,30); snake.length++;
			bodies.resize(bodies.size() + 1);
			if (bodies.size() == 1) {
				bodies.at(0).x = prev_posofhead.X; bodies.at(0).y = prev_posofhead.Y;
			}
			else 
			{
				bodies.at(bodies.size()-1).x = bodies.at(bodies.size() - 2).prev_x; bodies.at(bodies.size() - 1).y = bodies.at(bodies.size() - 2).prev_y;
			}
			field[apple.y][apple.x] = char(177);
			apple.y = random(2, field.size() - 2); apple.x = random(2, field[0].size() - 2);
			field[apple.y][apple.x] = apple.print;
			}
		field[snake.y][snake.x] = snake.print;
		field[apple.y][apple.x] = apple.print;
		show_field(field,snake);
	}
	system("pause");
	return 0;
}
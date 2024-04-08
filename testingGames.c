#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")

#define MAX_SNAKE_SIZE 500
#define WIDTH 280
#define HEIGHT 510

enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Position {
	int x;
	int y;
};
struct Snake {
	Position coord[MAX_SNAKE_SIZE];
	int size;
	int len;  // Snake's len
	DIR dir;  //The direction the snake moves
	int score;
};
struct Snake snake;
struct Position food;

void createFood() {
	srand((unsigned)time(NULL) + clock());

	//Since we initialized the layout of width to be 960 and height of 640
	// we need to make sure the position of food
	// is a multiple of 10, in order for snake to successfully eating the food
	food.x = (rand() % (WIDTH/10)) * 10;
	food.y = (rand() % (HEIGHT/10)) * 10;
}
void gameInit() {
	snake.size = 10;
	snake.len = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.coord[0] = { 50, 10 };
	snake.coord[1] = { 40, 10 };
	snake.coord[2] = { 30, 10 };

	//init food
	createFood();
}

void draw() {

	//To make sure when the snake move, the layers will not show
	cleardevice();
	for (int i = 0; i < snake.len; i++) {
		setlinecolor(YELLOW);
		setfillcolor(WHITE);
		fillrectangle(snake.coord[i].x, snake.coord[i].y, 
			snake.coord[i].x + snake.size, snake.coord[i].y + snake.size);
	}

	//draw food
	setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	solidrectangle(food.x, food.y, food.x + 10, food.y + 10);

	//display score
	char stringg[20] = "score";
	sprintf_s(stringg, "score: %d", snake.score);
	//Need to set up project -> testingGames properties -> 
	// Advancaed -> Character Set -> Use Multi-Byte
	outtextxy(20, 20, stringg);
}

void snakeMove() {
	//moves to right

	//To make the whole snake moves
	/*
	for (int i = 0; i < snake.len; i++) {
		snake.coord[i].x += 10;
	}
	*/

	
	for (int i = snake.len - 1; i >= 1; i--) {
		snake.coord[i] = snake.coord[i - 1];//snake is moving 5 index per time
	}
	switch(snake.dir){
	case UP:
		snake.coord[0].y -= 5;
		break;
	case DOWN:
		snake.coord[0].y += 5;
		break;
	case LEFT:
		snake.coord[0].x -= 5;
		break;
	case RIGHT:
		snake.coord[0].x += 5;
		break;
	}
	
	
}

void modifyDir() {
	//need to acquire keyboard char
	//72 H for up, 80 P for down, 75 K for left, 77 M for right
	//_kbhit() detect if keyboard is pressed, return 1 if yes, else 0

	//_kbhit(): Will make sure the snakes move no matter the keyboard
	// pressed or not
	if (_kbhit()) {
		char key = _getch();
		printf("%d\n", key);
		switch (key) {
		case 'W':
		case 'w':
		case 'H':
			//if (snake.dir != DOWN) {
				snake.dir = UP;
			//}
			break;
		case 'P':
			//if (snake.dir != UP) {
				snake.dir = DOWN;
			//}
			break;
		case 'K':
			//if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			//}
			break;
		case 'M':
			//if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			//}
			break;
		}
	}
}

void eatFood() {
	if (snake.coord[0].x == food.x && snake.coord[0].y == food.y) {
		snake.len++;
		snake.score += 10;
		createFood();
	}
}

int main() {
	
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	//solidcircle(50, 50, 30);
	gameInit();
	BeginBatchDraw();
	while (1) {
		eatFood();
		draw();
		FlushBatchDraw();
		snakeMove();
		modifyDir();
		Sleep(100);
	}
	EndBatchDraw();
	while (1);
	closegraph();

	return 0;
}
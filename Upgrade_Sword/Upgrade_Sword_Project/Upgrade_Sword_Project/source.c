#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void gotoxy(int x, int y);
int movecursorYAxis(int x, int y, int min, int max, char shape, int IDcre);
int movecursorXAxis(int x, int y, int min, int max, char shape, int IDcre);
void ShowInterface(int swordDataNum);
void ShowSwordsData(int check);
void GameScreen(int swordSelect);

int main()
{
	srand((unsigned int)GetTickCount64());
	system("mode con: cols=99 lines=30");
	int select, swordSelect = 0, checkQuit;
	while (1) {
		ShowInterface(swordSelect);
		select = movecursorYAxis(41, 11, 11, 13, '>', 1);
		if (select == 0) { //start
			GameScreen(swordSelect);
		}
		else if (select == 1) { //load
			while (1) {
				ShowSwordsData(swordSelect);
				checkQuit = movecursorYAxis(1, 1 + swordSelect * 3, 1, 10, '>', 3);
				if (checkQuit != 3) swordSelect = checkQuit;
				else break;
			}
		}
		else if (select == 2) { //quit
			system("cls");
			break;
		}
	}
	
	
	return 0;
}

//Interface
void ShowInterface(int swordDataNum) {
	system("cls");
	char Itfc[7][95] = {
		"    ****                                  *    *       *                                      ",
		"   *                                      *    **     **                                      ",
		"   *                                      *    * *   * *                    *                 ",
		"    ****   *       *   ****   *  **   *****    *  * *  *   ****     ***   *****   ****   *  **",
		"        *  *   *   *  *    *  **     *    *    *   *   *  *    *   *___     *    *____*  **   ",
		"        *   * * * *   *    *  *      *    *    *       *  *    *       *    *    *       *    ",
		"    ****     *   *     ****   *       *****    *       *   **** *   ***     *     ****   *    ",
	};
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 94; j++) {
			printf("%c", Itfc[i][j]);
		}
		printf("\n");
	}
	gotoxy(39, 9);
	printf("Sword Number : %d", swordDataNum + 1);
	gotoxy(43, 11);
	printf("start");
	gotoxy(43, 12);
	printf("load");
	gotoxy(43, 13);
	printf("quit");
	gotoxy(38, 15);
	printf("[Enter to Select]");
	
	
}

//load
void ShowSwordsData(int check) {
	system("cls");
	FILE* goldData = NULL, * levelData = NULL, * swordNameData = NULL;
	long long int gold = 0;
	int level = 0;
	char swordName[51];
	fopen_s(&swordNameData, "SwordNameData.txt", "r");

	for (int i = 1; i <= 3; i++) {
		//switch (i) {
		//case 0:
		//	fopen_s(&goldData, "GoldData//Sword1GoldData.txt", "r+");
		//	fopen_s(&levelData, "LevelData//Sword1LevelData.txt", "r+");
		//	break;
		//case 1:
		//	fopen_s(&goldData, "GoldData//Sword2GoldData.txt", "r+");
		//	fopen_s(&levelData, "LevelData//Sword2LevelData.txt", "r+");
		//	break;
		//case 2:
		//	fopen_s(&goldData, "GoldData//Sword3GoldData.txt", "r+");
		//	fopen_s(&levelData, "LevelData//Sword3LevelData.txt", "r+");
		//	break;
		//}
		//if (swordNameData == NULL) {
		//	printf("파일 열기에 실패했습니다. : SwordNameData");
		//	exit(0);
		//}
		//if (goldData == NULL) {
		//	printf("파일 열기에 실패했습니다. : GoldData");
		//	exit(0);
		//}
		//if (levelData == NULL) {
		//	printf("파일 열기에 실패했습니다. : LevelData");
		//	exit(0);
		//}

		////showInfomation
		//fscanf_s(goldData, "%lld", &gold);
		//fscanf_s(levelData, "%d", &level);

		//fseek(swordNameData, 0, SEEK_SET);

		//for (int i = 0; i < level; i++) {
		//	fgets(swordName, 51, swordNameData);
		//}

		printf("   ========================================\n   %d%40c\n\n", i, check == i - 1 ? 'V' : 0);
	}
	printf("   ========================================\n");
	printf("   Quit");
}

//start
//GameScreen
void GameScreen(int swordSelect)
{
	system("cls");

	FILE* goldData = NULL, * levelData = NULL, * newLevelData, * newGoldData;
	FILE *costData = NULL, *priceData = NULL, * swordNameData = NULL;
	long long int gold = 0, cost = 0, price = 0;
	int level = 0, POU = 0, select, RandomOfPOU = 0;
	char swordName[51];

	fopen_s(&costData, "CostData.txt", "r");
	fopen_s(&priceData, "PriceData.txt", "r");
	fopen_s(&swordNameData, "SwordNameData.txt", "r");
	
	switch (swordSelect) {
	case 0:
		fopen_s(&goldData, "GoldData//Sword1GoldData.txt", "r+");
		fopen_s(&levelData, "LevelData//Sword1LevelData.txt", "r+");
		break;
	case 1:
		fopen_s(&goldData, "GoldData//Sword2GoldData.txt", "r+");
		fopen_s(&levelData, "LevelData//Sword2LevelData.txt", "r+");
		break;
	case 2:
		fopen_s(&goldData, "GoldData//Sword3GoldData.txt", "r+");
		fopen_s(&levelData, "LevelData//Sword3LevelData.txt", "r+");
		break;
	}
	
	//check file existence
	if (costData == NULL) {
		printf("파일 열기에 실패했습니다. : costData");
		exit(0);
	}
	if (priceData == NULL) {
		printf("파일 열기에 실패했습니다. : priceData");
		exit(0);
	}
	if (swordNameData == NULL) {
		printf("파일 열기에 실패했습니다. : SwordNameData");
		exit(0);
	}
	if (goldData == NULL) {
		printf("파일 열기에 실패했습니다. : GoldData");
		exit(0);
	}
	if (levelData == NULL) {
		printf("파일 열기에 실패했습니다. : LevelData");
		exit(0);
	}

	//-------------Play-----------------
	while (1)
	{
		fseek(goldData, 0, SEEK_SET);
		fseek(levelData, 0, SEEK_SET);

		fscanf_s(goldData, "%lld", &gold);
		fscanf_s(levelData, "%d", &level);

		fseek(goldData, 0, SEEK_SET);
		fseek(levelData, 0, SEEK_SET);
		fseek(costData, 0, SEEK_SET);
		fseek(priceData, 0, SEEK_SET);
		fseek(swordNameData, 0, SEEK_SET);

		for(int i = 0; i < level; i++)
			fscanf_s(costData, "%lld", &cost);
		for (int i = 0; i < level; i++)
			fscanf_s(priceData, "%lld", &price);
		for (int i = 0; i < level; i++) {
			fgets(swordName, 51, swordNameData);
		}
		POU = 100 - ((level) / 2) * 5;

		gotoxy(2, 1);
		printf("Price : %lldG", price);
		gotoxy(2, 2);
		printf("Cost  : %lldG", cost);
		gotoxy(2, 3);
		printf("Level : Lv.%d", level);
		gotoxy(2, 4);
		printf("Name  : %s", swordName);
		gotoxy(2, 5);
		printf("POU   : %d%%", POU);
		gotoxy(10, 11);
		printf("Gold  : %lldG", gold);

		gotoxy(2, 8);
		printf("Upgrade");
		gotoxy(15, 8);
		printf("Quit");
		gotoxy(25, 8);
		printf("Sell");
		if (level > 19) {
			gotoxy(33, 8);
			printf("Make Piece");
		}

		select = movecursorXAxis(16, 10, 5, 27 + (level > 19 ? 11 : 0), '^', 11);

		for (int gcnt = gold; gcnt; gcnt /= 10) {
			fputc(' ', goldData);
		}
		for (int lcnt = level; lcnt; lcnt /= 10) {
			fputc(' ', levelData);
		}
		fseek(goldData, 0, SEEK_SET);
		fseek(levelData, 0, SEEK_SET);

		if (select == 1) { //Quit
			fprintf(goldData, "%lld", gold);;
			fprintf(levelData, "%d", level);
			break;
		}
		else if (select == 0) { //Upgrade
			if (cost > gold) {
				system("cls");
				gotoxy(10, 7);
				printf("It's too expensive");
				continue;
			}
			gold -= cost;
			RandomOfPOU = rand() % 100;
			if (RandomOfPOU < POU) {
				level++;
			}
			else {
				level--;
			}
		}
		else if (select == 2) { //Sell
			gold += price;
			level = 1;
		}
		system("cls");

		fprintf(goldData, "%lld", gold);
		fprintf(levelData, "%d", level);
	}
	
	

	fclose(goldData);
	fclose(levelData);
	fclose(costData);
	fclose(priceData);
	fclose(swordNameData);
}

//MoveSelectCursor(XAxis)
int movecursorXAxis(int x, int y, int min, int max, char shape, int IDcre) {
	char c;
	gotoxy(x, y);
	printf("%c", shape);
	gotoxy(x, y);
	while (1) {
		int cnt = 0;
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				if (c == LEFT) {
					x > min ? x -= IDcre : 0;
				}
				else if (c == RIGHT) {
					x < max ? x += IDcre : 0;
				}
			}
			else if (c == 13) {
				for (int i = min; i <= max; i += IDcre) {
					if (x == i)
						return cnt;
					cnt++;
				}
			}
			printf(" ");
			gotoxy(x, y);
			printf("%c", shape);
			gotoxy(x, y);
		}
	}
}

//MoveSelectCursor(YAxis)
int movecursorYAxis(int x, int y, int min, int max, char shape, int IDcre) {
	char c;
	gotoxy(x, y);
	printf("%c", shape);
	gotoxy(x, y);
	while (1) {
		int cnt = 0;
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				if (c == UP) {
					y > min ? y -= IDcre : 0;
				}
				else if (c == DOWN) {
					y < max ? y += IDcre : 0;
				}
			}
			else if (c == 13) {
				for (int i = min; i <= max; i += IDcre) {
					if (y == i)
						return cnt;
					cnt++;
				}
			}
			printf(" ");
			gotoxy(x, y);
			printf("%c", shape);
			gotoxy(x, y);
		}
	}
}

//SelectCursorPosition
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
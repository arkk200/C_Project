#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define NOW 13346 //Numver Of Words
#define TIME 8

void ToUpper(char *str);
int CheckStrLen(char* str, int num);
void CheckAlphabetPosition(char letter, int* checkAlphabet, int level);
void VirtualKeyboardPrint(int checkAlphabet[27]);

int main()
{
	//Setting
	system("mode con:cols=20 lines=20");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	srand((unsigned int)time(NULL));

	FILE* words;

	if ((fopen_s(&words, "Words.txt", "r"))) {
		printf("Error!");
		return 0;
	}

	int checkans[5] = { 0 }, checkinp[TIME][5] = { {0} }, checkAlphabet[27] = { 0 }, rd, checkcor = 0, na;
	char inp[TIME][100] = {{0}}, ans[6] = "", checkerr[10] = "0";
	//First Line Keyboard Alphabet to Third Line Keyboard Alphabet
	char alphabet[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

	for (int i = 0; i < NOW; i++) { //Find wrong word in file
		fgets(checkerr, 7, words);
		if (checkerr[5] != '\n') {
			printf("Error on the line %d", i + 1);
			return 0;
		}
	}
	rd = (rand() % (NOW)) * 7;

	fseek(words, rd, SEEK_SET);
	fgets(ans, 6, words);
	ToUpper(ans);

	//Play
	for(int cnt = TIME; cnt >= 0; cnt--)
	{
		printf("Time : %0d\n", cnt);

		VirtualKeyboardPrint(checkAlphabet);
		for (int cnt2 = 0; cnt2 < TIME - cnt; cnt2++) { //Show history	
			for (int i = 0; i < 5; i++) {
				if (checkinp[cnt2][i] == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (10 << 4) + 7);
				}
				else if (checkinp[cnt2][i] == 1) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (13 << 4) + 7);
				}
				printf("%c", inp[cnt2][i]);
				checkcor < 10 ? checkcor += checkans[i] : 0;
				checkinp[TIME - cnt][i] = 0;
				checkans[i] = 0;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			printf("\n");
		}
		if (checkcor == 10) { // Collect
			fclose(words);
			printf("\nGreat!");
			Sleep(1500);
			printf("\nClick to quit");
			printf("\n");
			_getch();
			return 0;
		}
		checkcor = 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		if (!cnt) break;

		na = scanf_s("%s", inp[TIME - cnt], 6);

		ToUpper(inp[TIME - cnt]);

		if (!strcmp(inp[TIME - cnt], "!QUIT")) break;


		if (!(64 < inp[TIME - cnt][0] && inp[TIME - cnt][0] < 91 && 64 < inp[TIME - cnt][1] && inp[TIME - cnt][1] < 91 && 64 < inp[TIME - cnt][2] && inp[TIME - cnt][2] < 91 && 64 < inp[TIME - cnt][3] && inp[TIME - cnt][3] < 91 && 64 < inp[TIME - cnt][4] && inp[TIME - cnt][4] < 91)) {
			cnt++;
			system("cls");
			continue;
		}
		
		
		if (!CheckStrLen(inp[TIME - cnt], 5)) {
			cnt++;
			system("cls");
			continue;
		}

		

		for (int i = 0; i < 5; i++) //Green is more important than pink ex) JAZZY AAZZY = 02222
			if (ans[i] == inp[TIME - cnt][i]) {
				checkans[i] = 2;
				checkinp[TIME - cnt][i] = 2;
			}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (checkinp[TIME-cnt][i] == 2)
					break;
				if (ans[j] == inp[TIME - cnt][i] && !checkans[j]) { //pzazz  plzaz
					checkans[j] = 1;					//1. 20002 20002, 2. 11020 11020, 3. 11020 11020, 4. 11022 11022
					checkinp[TIME - cnt][i] = 1;					//earth three
					break;								//1. 00010 10000, 2. 00011 11000, 3. 00111 11100, 4. 10211 11210
				}
			}
		}

		for (int i = 0; i < 5; i++) { //Setting virtual keyboard letters color.
			CheckAlphabetPosition(inp[TIME - cnt][i], checkAlphabet, checkinp[TIME - cnt][i]);
			/*CheckAlphabetPosition(inp[TIME - cnt][i], checkAlphabet, checkans[i]);*/
		}
		system("cls");
	}

	fclose(words);
	printf("Answer : %s", ans); // Failed
	printf("\n");
	Sleep(1500);
	printf("Click to quit\n");
	_getch();
	return 0;
}



void ToUpper(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
		str[i] = (int)str[i] > 96 ? str[i] - 32 : str[i];
}



int CheckStrLen(char* str, int num)
{
	int cnt = 0;
	while (str[cnt] != '\0') cnt++;
	return cnt == num;
}



void CheckAlphabetPosition(char letter, int *checkAlphabet, int level)
{
	char alphabet[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";
	int i = 0;
	while (alphabet[i] != letter) i++;

	checkAlphabet[i] = checkAlphabet[i] < level ? level : checkAlphabet[i];
	!checkAlphabet[i] ? checkAlphabet[i] = -1 : 0;
}



void VirtualKeyboardPrint(int checkAlphabet[27])
{
	char alphabet[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

	for (int i = 0; i < 26; i++) {
		checkAlphabet[i] == 2 ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10) : 0;
		checkAlphabet[i] == 1 ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13) : 0;
		checkAlphabet[i] == -1 ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8) : 0;
		printf("%c ", alphabet[i]);
		i == 9 ? printf("\n ") : 0;
		i == 18 ? printf("\n   ") : 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	printf("\n");
	return;
}
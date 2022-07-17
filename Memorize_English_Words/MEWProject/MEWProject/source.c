#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

void Quiz(int n, char char1[][30], char char2[][30]);

int main() {
	srand((unsigned int)time(NULL));

	char eng[101][30] = {""}, kor[101][30] = {""};
	int n, chs, rdm = 0;

	while (1) {
		printf("Input the number of words : ");
		scanf("%d", &n);
		if (n > 0) break;
		printf("Error: This number is out of range\n");
	}

	printf("Input the words, ex)Apple 사과[Enter]\n");
	printf("But do not enter spaces within words\n");

	for (int i = 0; i < n; i++) {
		scanf("%s", eng[i]);
		scanf("%s", kor[i]);
	}

	while (1) {
		printf("Choose among the two ways, (1: kor->eng), (2: eng->kor) : ");
		scanf("%d", &chs);
		if (0 < chs && chs < 3) break;
		printf("Error: This number is out of range\n");
	}

	printf("!QUIT : quit, !CLEAR : clear\n");

	if (chs == 1) {
		Quiz(n, kor, eng);
	}
	else if (chs == 2) {
		Quiz(n, eng, kor);
	}
	return 0;
}

void Quiz(int n, char char1[][30], char char2[][30]) {
	int rdm;
	char word[30] = "";
	while (1) {
		rdm = rand() % n;
		printf("%s : ", char1[rdm]);
		scanf("%s", word);
		if (!(strcmp(word, "!QUIT"))) break;
		else if (!strcmp(word, "!CLEAR")) {
			system("cls");
			continue;
		}
		else if (word[0] == '!') {
			printf("Error: This command does not exist\n");
			continue;
		}
		if (!(strcmp(char2[rdm], word)))
			printf("correct!\n");
		else printf("wrong : %s\n", char2[rdm]);
	}
}
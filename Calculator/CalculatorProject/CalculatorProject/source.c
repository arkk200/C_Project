#include <stdio.h>

int main() {
	long long num, sum = 0, pow = 1;
	int chooseQorR;
	char oprtr;
	printf(">>> ");
	scanf("%lld ", &sum);
	while (1) {
		scanf("%c %lld", &oprtr, &num);
		getchar();
		if (oprtr == '+') {
			sum += num;
		}
		else if (oprtr == 45) {
			sum -= num;
		}
		else if (oprtr == 42) {
			sum *= num;
		}
		else if (oprtr == 47) {
			if (sum < 0) {
				printf("ERROR: sign error\nCannot divide negative numbers\n");
			}
			else {
				while (1) {
					printf("What number do you want to use?\n");
					printf("(1. number: %d (Quotient), 2. number: %d (Remainder) : ", sum / num, sum % num);
					scanf("%d", &chooseQorR);
					getchar();
					if (chooseQorR / 3 > 0 || chooseQorR < 1) {
						printf("ERROR: value error\nThis value is a non-existent value\n");
						continue;
					}
					else
						break;
				}
				(chooseQorR - 2) ? (sum /= num) : (sum %= num);
			}
		}
		else if (oprtr == 94) {
			for (int i = 0; i < num; i++) {
				pow *= sum;
			}
			sum = pow;
		}
		else {
			printf("ERROR: operator error\nThis operator is a non-existent operator\n");
		}
		printf(">>> ");
		printf("%lld ", sum);
	}
	return 0;
}

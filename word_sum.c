// Some stupid words game..
// Reversed and coded by blasty
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i;
	unsigned char *b;
	unsigned short fsum=0,sum=0;
	FILE *f = fopen(argv[1], "rb+");

	b = malloc(0x2000);
	fread(b, 0x2000, 1, f);

	fsum = b[4] | (b[5] << 8);

	b[4] = 0;
	b[5] = 0;

	printf("FILE SUM: %04X -- ", fsum);

	for (i = 0; i < 0x2000; i++) {
		sum -= b[i];
	}

	free(b);

	sum -= 0x6d0c;

	if (sum != fsum) {
		printf("SUM FAIL! Fixing..\n");
		fseek(f, 0x04, SEEK_SET);
		fwrite(&sum, 2, 1, f);
	} else {
		printf("SUM OK!\n");
	}

	fclose(f);

	return 0;
}

//
// zelda_ph.c -- Checksum fixer for "The Legend of Zelda: Phantom Hourglass"
//
// Bit of a mess, sorry for that. If my memory serves me right, CaitSith2 
// originally reversed most of the checksum, props to him.
//

#include <stdio.h>

int blockSizes[70]={
	0x1400, 0x1400, 

	0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
	0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
	0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
	0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
	0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
	0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 
	
	0x500, 0x500,
	0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80
};

int main(int argc, char *argv[]) {
	FILE *in;
	int i, j, z;
	unsigned short b, c;
	unsigned int sum=0, fsum=0, ppos, tsum=0;

	in = fopen(argv[1], "rb+");

	// 2 slots, 70 blocks each
	for (z = 0; z < 2; z++) {
		ppos = (z * 0x3F500);

		for (j = 0; j < 70; j++) {
			fseek(in, ppos, SEEK_SET);

			fsum = 0;
			sum  = 0;
			c    = 0;

			for (i = 0; i < (blockSizes[j]-2)/2; i++) {
				fread(&b, 2, 1, in);
				sum += b;
			}

			// read sum from file
			fread(&b, 2, 1, in);

			fsum = 0xFFFF-(((sum >> 16) + (sum & 0xFFFF))&0xFFFF); // sum in 16bit form
			printf("SLOT %d BLOCK %02d [%08X] SUM: %04X FILE: %04X SUM: %08X ", z, j, ppos, fsum, b, sum);

			tsum += sum;
			ppos += blockSizes[j];

			if (fsum == b) {
				printf("[OK!]\n");
				continue;
			}

			fseek(in, ftell(in)-2, SEEK_SET);
			c = fsum & 0xFFFF;
			fwrite(&c, 2, 1, in);
			printf("[FIXED]\n");
		}
	
		tsum = 0;
	}

	fclose(in);

	return 0;
}


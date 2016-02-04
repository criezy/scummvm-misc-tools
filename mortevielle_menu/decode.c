#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* infile, *outfile;
	unsigned char c, mask, bit;
	int bytes_cpt;

	if (argc < 2 || argc > 3) {
		printf("Usage: %s menu_file [output_file]\n", argv[0]);
		return -1;
	}

	infile = fopen(argv[1], "rb");
	if (infile == 0) {
		printf("Cannot open file %s\n", argv[1]);
		return -2;
	}
	outfile = stdout;
	if (argc == 3) {
		outfile = fopen(argv[2], "w");
		if (outfile == 0) {
			fclose(infile);
			printf("Cannot create file %s\n", argv[2]);
			return -3;
		}
	}

	/* Each bit of the file is a pixel.
	 * Each menu entry is 24x8 pixels (i.e. 3x8 bytes)
	 * 1 for forground and 0 for background.
	 *
	 * For readibility we split the lines after 24 characters
	 * and we replace 0 by . so that the 1 is more visible. */
	bytes_cpt = 0;
	while (!feof(infile) && fread(&c, 1, 1, infile) > 0) {
		mask = 0x80;
		for (bit = 0 ; bit < 8 ; ++bit) {
			fputc((c & mask) != 0 ? '1' : '.', outfile);
			mask = (mask >> 1);
		}
		++bytes_cpt;
		if (bytes_cpt == 3) {
			fputc('\n', outfile);
			bytes_cpt = 0;
		}
	}

	fclose(infile);
	if (argc == 3)
		fclose(outfile);
	return 0;
}


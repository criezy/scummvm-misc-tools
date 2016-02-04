#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* infile, *outfile;
	unsigned char c[8], byte;
	int bit_cpt, i, n;

	if (argc != 3) {
		printf("Usage: %s menu_txt_file output_file\n", argv[0]);
		return -1;
	}

	infile = fopen(argv[1], "r");
	if (infile == 0) {
		printf("Cannot open file %s\n", argv[1]);
		return -2;
	}
	outfile = fopen(argv[2], "wb");
	if (outfile == 0) {
		fclose(infile);
		printf("Cannot create file %s\n", argv[2]);
		return -3;
	}

	/* Each bit of the file is a pixel.
	 * Each menu entry is 24x8 pixels (i.e. 3x8 bytes)
	 * 1 for forground and 0 for background.
	 *
	 * Since decode transforms bit 0 into '.', here we recognize
	 * both '.' and '0'. Also we skip the end of lines addded by
	 * decode. */
	bit_cpt = 0;
	byte = 0;
	while (!feof(infile) && (n = fread(&c, 1, 8, infile)) > 0) {
		for (i = 0 ; i < n ; ++i) {
			if (c[i] == '1')
				byte |= (1 << (7 - bit_cpt++));
			else if (c[i] == '0' || c[i] == '.')
				++bit_cpt;
			else
				continue;
			if (bit_cpt == 8) {
				fwrite(&byte, 1, 1, outfile);
				bit_cpt = 0;
				byte = 0;
			}
		}
	}

	fclose(infile);
	fclose(outfile);
	return 0;
}


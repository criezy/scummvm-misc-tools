#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	char buffer[256];
	int i, c;

	if (argc == 1) {
		printf("Usage: %s file1 [file2 ...]\n", argv[0]);
		return 0;
	}

	for (i = 1 ; i < argc ; ++i) {
		FILE* inFile = fopen(argv[i], "rb");
		if (inFile == NULL)
			continue;
		sprintf(buffer, "%s.xored", argv[i]);
		FILE* outFile = fopen(buffer, "wb");
		if (outFile == NULL) {
			fclose(inFile);
			continue;
		}

		while ((c = fgetc(inFile)) != EOF) {
			fputc(c ^ 0xFF, outFile);
		}

		fclose(inFile);
		fclose(outFile);
		printf("...wrote file %s\n", buffer);
	}

	return 0;
}

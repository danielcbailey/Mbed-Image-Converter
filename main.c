#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "stb_image.h"
#include <stdint.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./imgconv [image file] [name of output]. Example: ./imgconv mysprite.png my_sprite\n");
		printf("    NOTE: The name of the output must not contain spaces and must be a valid C variable name.\n");
		return 1;
	}

	int x, y, z;
	uint8_t* data = (uint8_t*)stbi_load(argv[1], &x, &y, &z, 3);

	char* fileName = (char*)malloc(strlen(argv[2]) + 3); //The + 3 to account for ".c\0"
	if (!fileName) {
		printf("System out of memory.\n");
		return 2;
	}

	strcpy(fileName, argv[2]);
	strcat(fileName, ".c");

	//Preparing the output file
	FILE* file = fopen(fileName, "w");

	// writing obligatory stuff at beginning of file
	fprintf(file, "// Autogenerated c file from image.\n// Learn more at https://github.com/danielcbailey/Mbed-Image-Converter\n");
	fprintf(file, "#include <stdint.h>\n\n");
	fprintf(file, "#define IMAGE_%s_WIDTH %d\n", argv[2], x);
	fprintf(file, "#define IMAGE_%s_HEIGHT %d\n\n", argv[2], y);
	fprintf(file, "const uint32_t %s[%d] = [\n\t", argv[2], x * y);

	int lineLength = 0;
	for (int i = 0; x * y * 3 > i; i += 3) {
		if (i) {
			fprintf(file, ", ");
			lineLength += 2;
		}
		if (lineLength > 80) {
			fprintf(file, "\n\t");
			lineLength = 0;
		}
		uint32_t pixel = ((uint32_t)data[i] << 16) | ((uint32_t)data[i + 1] << 8) | (uint32_t)data[i + 2];
		lineLength += fprintf(file, "%d", pixel);
	}

	fprintf(file, "];\n");

	STBI_FREE(data);
	fclose(file);
	printf("Saved the image as \"%s\"\n", fileName);
	free(fileName);
}
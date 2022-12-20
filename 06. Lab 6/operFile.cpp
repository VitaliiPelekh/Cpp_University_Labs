// operFile.cpp - additional file for function operating from additional header file
#include"headOperFile.h"

bool checkFile(FILE*& file, const char* filename, const char* filemode) {
	file = fopen(filename, filemode); // open file to read/write
	if (!file) { // if file didn't open
		printf("\n File %s not found \n", filename);
		fclose(file); // close file
		return false;
	}

	return true;
}
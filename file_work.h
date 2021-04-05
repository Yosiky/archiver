#ifndef FILE_WORK_H
#define FILE_WORK_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"

extern const size_t MAX_SIZE_STR;

FILE* file_open();
size_t* file_read(FILE* file);

#endif
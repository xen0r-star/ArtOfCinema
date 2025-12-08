#ifndef UTILS_RESOURCE_H
#define UTILS_RESOURCE_H


#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

char* loadResource(UINT id, DWORD* outSize);

#endif
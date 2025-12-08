#include "resource.h"


char* loadResource(UINT id, DWORD* outSize) {
    if (!outSize) return NULL;
    *outSize = 0;

    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(id), RT_RCDATA);
    if (!hRes) return NULL;

    HGLOBAL hData = LoadResource(NULL, hRes);
    if (!hData) return NULL;

    DWORD size = SizeofResource(NULL, hRes);
    const char* data = (const char*)LockResource(hData);
    if (!data || size == 0) return NULL;

    char* buffer = malloc(size + 1);  // +1 pour \0 si texte
    if (!buffer) return NULL;

    memcpy(buffer, data, size);
    buffer[size] = '\0';  // pratique pour texte/CSV

    *outSize = size;
    return buffer;
}
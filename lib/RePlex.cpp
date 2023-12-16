#include "pub/RePlex.h"

#include <cstdio>
#include <windows.h>

// from: https://gist.github.com/jsxinvivo/11f383ac61a56c1c0c25
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

void* Load(const char* filepath) {
    return LoadLibrary(convertCharArrayToLPCWSTR(filepath));
}

void* LoadSymbol(void* library, const char* symbol) {
    return GetProcAddress((HMODULE)library, symbol);
}

void Reload(void* &library, const char* filepath) {
    FreeLibrary((HMODULE)library);
    library = Load(filepath);
}

void PrintError() {
    printf("Error: %d\n", GetLastError());
}
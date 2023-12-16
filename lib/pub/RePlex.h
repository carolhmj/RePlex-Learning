#pragma once

__declspec(dllexport) void* Load(const char* filepath);
__declspec(dllexport) void* LoadSymbol(void* library, const char* symbol);
__declspec(dllexport) void Reload(void* &library, const char* filepath);
__declspec(dllexport) void PrintError();
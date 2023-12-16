#include <RePlex.h>
#include <iostream>

#ifdef RELEASE
const char* g_libpath = "bin/Release/RePlexTest.dll";
#else
const char* g_libpath = "bin/Debug/RePlexTest.dll";
#endif

void(*foo)();

int main() {
    void* handle = Load(g_libpath);
    if (handle) {
        foo = reinterpret_cast<void(*)()>(LoadSymbol(handle, "foo"));
        if (!foo) {
            PrintError();
            return 1;
        }
        foo();

        int bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
        std::cout << "bar == " << bar << std::endl;

        std::cout << "Make some changes, recompile and press enter." << std::flush;
        while(std::cin.get() != '\n') { }

        Reload(handle, g_libpath);

        foo = reinterpret_cast<void(*)()>(LoadSymbol(handle, "foo"));
        if (!foo) {
            PrintError();
            return 1;
        }
        foo();

        bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
        std::cout << "bar == " << bar << std::endl;
    } else {
        PrintError();
    }
    return 0;
}
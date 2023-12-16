#pragma once

#include <RePlex.h>

extern "C" {
    void foo();
    int bar;
}

std::array<const char*, 2> g_symbols = {
    "foo",
    "bar"
};

class TestModule: public RePlexModule<TestModule, g_symbols.size()> {
    public:
        static int Foo(int arg) {
            return GetInstance().Execute<int, int>("foo", arg);
        }

        static int GetBar() {
            return *GetInstance().GetVar<decltype(bar)>("bar");
        }
        
    protected:
        const char* GetPath() const override {
            return "bin/Release/RePlexTest.dll";
        }

        std::array<const char*, g_symbols.size()>& GetSymbolNames() const override {
            return g_symbols;
        }
};
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
        static void Foo() {
            GetInstance().Execute<void>("foo");
        }

        static int GetBar() {
            return *GetInstance().GetVar<decltype(bar)>("bar");
        }
        
    protected:
        const char* GetPath() const override {
            return "bin/Debug/RePlexTest.dll";
        }

        std::array<const char*, g_symbols.size()>& GetSymbolNames() const override {
            return g_symbols;
        }
};
#pragma once

extern "C" {
    __declspec(dllexport) void foo();

    __declspec(dllexport) extern int bar;
}
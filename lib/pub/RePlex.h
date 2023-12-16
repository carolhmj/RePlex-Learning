#pragma once

class Foo {
    public:
         __declspec(dllexport) int GetTheAnswer() const;
    private:
        int m_theAnswer = 42;
};
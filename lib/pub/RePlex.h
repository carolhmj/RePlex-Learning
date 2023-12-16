#pragma once

#include <array>
#include <unordered_map>
#include <string>
#include <windows.h>

// from: https://gist.github.com/jsxinvivo/11f383ac61a56c1c0c25
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

template <typename E, size_t NumSymbols>
class RePlexModule {
    public:
        static void LoadMyLibrary() { GetInstance().Load(); }
        static void ReloadLibrary() { GetInstance().Reload(); }
    protected:
        static E& GetInstance() {
            static E instance;
            return instance;
        }

        virtual const char* GetPath() const = 0;

        virtual std::array<const char*, NumSymbols>& GetSymbolNames() const = 0;

        template <typename Ret, typename ...Args>
        Ret Execute(const char* name, Args... args) {
            auto symbol = m_symbols.find(name);
            if (symbol != m_symbols.end()) {
                return reinterpret_cast<Ret(*)(Args...)>(symbol->second)(args...);
            } else {
                throw std::runtime_error(std::string("Function not found: ") + name);
            }
        }

        template<typename T>
        T* GetVar(const char* name) {
            auto symbol = m_symbols.find(name);
            if (symbol != m_symbols.end()) {
                return static_cast<T*>(symbol->second);
            } else {
                return nullptr;
            }
        }

    private:
        void Load() {
            m_libhandle = LoadLibrary(convertCharArrayToLPCWSTR(GetPath()));
            LoadSymbols();
        }

        void Reload() {
            FreeLibrary((HMODULE)m_libhandle);
            m_symbols.clear();
            Load();
        }

        void LoadSymbols() {
            for (auto name : GetSymbolNames()) {
                auto symbol = GetProcAddress((HMODULE)m_libhandle, name);
                if (symbol) {
                    m_symbols[name] = symbol;
                } else {
                    throw std::runtime_error(std::string("Symbol not found: ") + name);
                }
            }
        }

        void* m_libhandle;
        std::unordered_map<std::string, void*> m_symbols;
        //using SymbolArray = std::array<std::pair<const char*, void*>>;
        //SymbolArray& m_symbols;
};
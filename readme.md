# C++ Learning

Following RePlex loader library tutorial at: https://howistart.org/posts/cpp/1/index.html

Some takeaways I've learned:
1. To get Visual Studio to generate a `.lib` file (and thus build properly), `__declspec(dllexport)` has to be added before public exported objects.
2. A different error that may occurr due to lack of declspec is: `LNK2019	unresolved external symbol "void * __cdecl Load(char const *)" (?Load@@YAPAXPBD@Z) referenced in function _main	RePlexRuntime` 
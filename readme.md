# C++ Learning

Following RePlex loader library tutorial at: https://howistart.org/posts/cpp/1/index.html

Some takeaways I've learned:
1. To get Visual Studio to generate a `.lib` file (and thus build properly), `__declspec(dllexport)` has to be added before public exported objects.
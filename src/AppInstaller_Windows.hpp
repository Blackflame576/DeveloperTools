#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "Progressbar.hpp"
#include <cctype>
#include <fstream>
#include <json/json.h>
#include <conio.h>
#include <Windows.h>
#include <functional>

using namespace std;
// using funct_t = void (*)(void);
using namespace Json;

// Переменные
progressbar bar(100);
int TempPercentage = 0;
const string TrueVarious[3] = { "yes", "y", "1"};
string new_sentence;
Value translate;
string LangReadySet;
map<int, string> Languages{
    {1,"Python"},{2,"JavaScript"},{3,"C++"},{4,"Java"},
    {5,"Go"},{6,"Rust"},{7,"Ruby"},{8,"C"},
    {9,"C#"},{10,"PHP"},{11,"Kotlin"}
};
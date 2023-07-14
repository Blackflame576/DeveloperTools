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
#include <functional>
#include "Logger.cpp"


// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    #include <jsoncpp/json/json.h>
// cout << "Linux" << endl;
#elif __FreeBSD__
    #include <jsoncpp/json/json.h>
// cout << "FreeBSD" << endl;
#elif __APPLE__
    #include <jsoncpp/json/json.h>
// cout << "macOS" << endl;
#elif _WIN32
    // #include <format>
    #include <json/json.h>
    #include <conio.h>
    #include <Windows.h>
#endif

using namespace std;
using namespace Json;
using namespace Logger;

// Переменные
MainLogger logger(true,"logs/DeepForgeToolset.log");
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
const string KotlinUrl = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
const string PHPUrl = "https://windows.php.net/downloads/releases/php-8.2.7-nts-Win32-vs16-x64.zip";
const string WgetUrl = "https://eternallybored.org/misc/wget/1.21.4/64/wget.exe";
string ProjectDir = std::filesystem::current_path().generic_string();
string KotlinDir = ProjectDir + "/Programms/Kotlin";
string PHPDir = ProjectDir + "/Programms/PHP";
string WgetDir = ProjectDir + "/Programms/Wget";
string NewKotlinDir = "C:\\Kotlin";
string NewPHPDir = "C:\\PHP";
string NewWgetDir = "C:\\Wget";
string AddKotlinPathScript = ProjectDir + "/Scripts/AddKotlinPath.ps1";
string AddPHPPathScript = ProjectDir + "/Scripts/AddPHPPathScript.ps1";
string AddWgetPathScript = ProjectDir + "/Scripts/AddWgetPath.ps1";
string WinGetScriptPath = ProjectDir + "/Scripts/InstallWinGet.ps1";
int result;
int output_func;
string haveString = "";
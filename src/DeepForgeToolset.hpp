#include <iostream>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "Progressbar.hpp"
#include <cctype>
#include <exception>

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
    #include <json/json.h>
    #include <conio.h>
    #include <Windows.h>
#endif

// using funct_t = void(*)(void);
// using namespace Json;

string OS_NAME;
// Value translate;
string Language;
string SelectPackages;
string Answer;
string InstallTools;
bool Install;
#include <iostream>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "Progressbar.hpp"
#include <cctype>
#include <exception>
#include <regex>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
// cout << "Linux" << endl;
#elif __FreeBSD__
// cout << "FreeBSD" << endl;
#elif __APPLE__
// cout << "macOS" << endl;
#elif _WIN32
    #include <conio.h>
    #include <Windows.h>
#endif

string OS_NAME;
string Language;
string SelectPackages;
string Answer;
string InstallTools;
bool Install;
string __version__ = "0.2";
string MODE = "DEV";
string NameDistribution;
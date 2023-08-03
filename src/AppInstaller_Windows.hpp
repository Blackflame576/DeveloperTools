/*  The MIT License (MIT)
    ============================================================================

    ██████╗ ███████╗███████╗██████╗ ███████╗ ██████╗ ██████╗  ██████╗ ███████╗    
    ██╔══██╗██╔════╝██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔══██╗██╔════╝ ██╔════╝    
    ██║  ██║█████╗  █████╗  ██████╔╝█████╗  ██║   ██║██████╔╝██║  ███╗█████╗      
    ██║  ██║██╔══╝  ██╔══╝  ██╔═══╝ ██╔══╝  ██║   ██║██╔══██╗██║   ██║██╔══╝      
    ██████╔╝███████╗███████╗██║     ██║     ╚██████╔╝██║  ██║╚██████╔╝███████╗    
    ╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝      ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚══════╝    
                                                                                
    ████████╗ ██████╗  ██████╗ ██╗     ███████╗███████╗████████╗                  
    ╚══██╔══╝██╔═══██╗██╔═══██╗██║     ██╔════╝██╔════╝╚══██╔══╝                  
       ██║   ██║   ██║██║   ██║██║     ███████╗█████╗     ██║                     
       ██║   ██║   ██║██║   ██║██║     ╚════██║██╔══╝     ██║                     
       ██║   ╚██████╔╝╚██████╔╝███████╗███████║███████╗   ██║                     
       ╚═╝    ╚═════╝  ╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝   

    ============================================================================
    Copyright (c) 2023 DeepForge Technology
    ============================================================================
    Company: DeepForge Technology
    ============================================================================
    Author: Blackflame576
    ============================================================================
    Created: 4 Juny 2023
    ============================================================================
*/
// Импортирование библиотек
// Importing Libraries
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
#include "json/json.h"
#include <time.h>
#include <stdint.h>

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
// Checking the name of the operating system and importing the necessary libraries for this system
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

using namespace std;
using namespace Json;
using namespace Logger;

// Переменные
// Variables
string ProjectDir = std::filesystem::current_path().generic_string();
MainLogger logger(true,"logs/DeepForgeToolset.log");
ProgressBar bar;
int Percentage;
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
const string EclipseUrl = "https://mirrors.jevincanders.net/eclipse/technology/epp/downloads/release/2023-06/R/eclipse-java-2023-06-R-win32-x86_64.zip";
// const string EclipseUrl = "https://fileinfo.com/img/ss/xl/url_181.png";
string KotlinDir = ProjectDir + "/Programms/Kotlin";
string PHPDir = ProjectDir + "/Programms/PHP";
string WgetDir = ProjectDir + "/Programms/Wget";
string NewKotlinDir = "C:\\Kotlin";
string NewPHPDir = "C:\\PHP";
string NewWgetDir = "C:\\Wget";
string NewEclipseDir = "C:\\";
string AddKotlinPathScript = ProjectDir + "/Scripts/AddKotlinPath.ps1";
string AddPHPPathScript = ProjectDir + "/Scripts/AddPHPPathScript.ps1";
string AddWgetPathScript = ProjectDir + "/Scripts/AddWgetPath.ps1";
string AddEclipsePathScript = ProjectDir + "/Scripts/AddEclipsePath.ps1";
string WinGetScriptPath = ProjectDir + "/Scripts/InstallWinGet.ps1";
int result;
int output_func;
string haveString = "";
double DownloadSpeed = 0.0;
CURL* curl = curl_easy_init();
CURLcode res;
double EndTime;
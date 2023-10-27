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
    Organization: DeepForge Technology
    ============================================================================
    Author: Blackflame576
    ============================================================================
    Created: 4 Juny 2023
    ============================================================================
*/
// Importing Libraries
#ifndef APPINSTALLER_LINUX_HPP_
#define APPINSTALLER_LINUX_HPP_

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
#include <chrono>
#include <regex>
#include "DatabaseConnect.cpp"
#include "fmt/format.h"


/* The `#define OS_NAME "Linux"` statement is a preprocessor directive that defines a macro named `OS_NAME` with the value "Linux". This macro can be used throughout the code to represent the name of the operating system. */
#define OS_NAME "Linux"

using namespace std;
using namespace DB;
using namespace Bar;

// Variables
// int type
int Percentage;
int TempPercentage;
int result;
int output_func;
// float type
double LastSize;
double LastTotalSize;
// double type
double DownloadSpeed = 0.0;
// string type
const string TrueVarious[3] = {"yes", "y", "1"};
string new_sentence;
string LangReadySet;
string NameDistribution;
string PackageManager;
string haveString = "";
string ProjectDir = std::filesystem::current_path().generic_string();
string DatabasePath = ProjectDir + "/DB/AppInstaller.db";
string LogPath = ProjectDir + "/logs/DeepForgeToolset.log"; 
string Architecture;
string InstallDelimiter = "========================================================";
string Language;
string SelectPackages;
string Answer;
string InstallTools;
string MODE = "DEV";
// Boolean type
bool Install;
// init classes
Json::Value translate;
ProgressBar_v1 progressbar;
Logger logger(LogPath.c_str(), "10mb");
Database database;
// map type
map<string, string> Packages;
map<string, string> DevelopmentPacks;
map<int, string> Languages = {
    {1, "Python"}, {2, "JavaScript"}, {3, "C++"}, {4, "Java"}, {5, "Go"}, {6, "Rust"}, {7, "Ruby"}, {8, "C"}, {9, "C#"}, {10, "PHP"}, {11, "Kotlin"}
};
#endif
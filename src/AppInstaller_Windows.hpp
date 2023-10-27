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
#ifndef APPINSTALLER_WINDOWS_HPP_
#define APPINSTALLER_WINDOWS_HPP_

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
#include "DatabaseConnect.cpp"
#include "fmt/format.h"

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
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "shlobj.h"
#endif

#define OS_NAME "Windows"

using namespace std;
using namespace DB;
using namespace Bar;

// Variables
// int type
int Percentage;
int TempPercentage;
int result;
int output_func;
// double type
double LastSize;
double LastTotalSize;
// map type
map<string, string> Packages;
map<string, string> DevelopmentPacks;
map<int, string> Languages{
    {1, "Python"}, {2, "JavaScript"}, 
    {3, "C++"}, {4, "Java"}, 
    {5, "Go"}, {6, "Rust"}, 
    {7, "Ruby"}, {8, "C"}, 
    {9, "C#"}, {10, "PHP"}, 
    {11, "Kotlin"}
};

/* The `replaceAll` function is a utility function that replaces all occurrences of a substring `from` with another substring `to` in a given string `str`. */
string replaceAll(string str, const string &from, const string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
// string type
const string TrueVarious[3] = {"yes", "y", "1"};
string Architecture;
string ProjectDir = std::filesystem::current_path().generic_string();
string haveString = "";
string new_sentence;
string LangReadySet;
string InstallDelimiter = "========================================================";
string Language;
string SelectPackages;
string Answer;
string InstallTools;
string MODE = "DEV";
// Boolean type
bool Install;
// Get user folder(example - C:\Users\NameUser)
char *UserFolder = getenv("USERPROFILE");
string DesktopPath = string(UserFolder) + "\\Desktop";
const string ApplicationDir = "C:\\ProgramData\\DeepForge\\DeepForge-Toolset";
string DatabasePath = replaceAll(ProjectDir, "/", "\\") == DesktopPath ? ApplicationDir + "\\DB\\AppInstaller.db" : ProjectDir + "\\DB\\AppInstaller.db";
string LogPath = ProjectDir + "\\logs\\DeepForgeToolset.log"; 
// init classes
Logger logger(LogPath.c_str(), "10kb");
ProgressBar_v1 progressbar;
Json::Value translate;
Database database;

#endif
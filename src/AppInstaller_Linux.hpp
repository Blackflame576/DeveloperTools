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

/* The `#define` statements are defining error messages as string constants. These error messages are related to different error codes that can be returned by the libcurl library when making HTTP requests. Each error message describes a specific error condition that can occur during the request process. These error messages can be used later in the code to provide more descriptive error messages to the user when a specific error occurs. */
#define ERROR_CURLE_COULDNT_CONNECT "❌ Failed to connect to host or proxy."
#define ERROR_CURLE_COULDNT_RESOLVE_HOST "❌ Failed to resolve host. The given remote host was not allowed."
#define ERROR_CURLE_COULDNT_RESOLVE_PROXY "❌ Failed to resolve proxy. The given proxy host could not be resolved."
#define ERROR_CURLE_UNSUPPORTED_PROTOCOL "❌ Failed to connect to the site using this protocol."
#define ERROR_CURLE_SSL_CONNECT_ERROR "❌ The problem occurred during SSL/TLS handshake."

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
    {1, "Python"}, {2, "JavaScript"}, {3, "C++"}, {4, "Java"}, {5, "Go"}, {6, "Rust"}, {7, "Ruby"}, {8, "C"}, {9, "C#"}, {10, "PHP"}, {11, "Kotlin"}};

/* The `GetNameDistribution()` function is used to retrieve the name of the Linux distribution that the code is running on. */
string GetNameDistribution()
{
    ifstream stream("/etc/os-release");
    string line;
    regex nameRegex("^NAME=\"(.*?)\"$");
    smatch match;
    string name;
    while (getline(stream, line))
    {
        if (regex_search(line, match, nameRegex))
        {
            name = match[1].str();
            break;
        }
    }
    return name;
}

void UpdateData()
{
    try
    {
        /* This code block checks if the database file specified by `DatabasePath` exists.
        If the file does not exist, it proceeds to download the file from a specified URL using the libcurl library. */
        if (filesystem::exists(DatabasePath) == false)
        {
            string url = "https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/InstallerUtils/AppInstaller.db";
            string name = (url.substr(url.find_last_of("/")));
            string filename = ProjectDir + "/" + name.replace(name.find("/"), 1, "");
            FILE *file = fopen(filename.c_str(), "wb");
            CURL *curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
            curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            CURLcode response = curl_easy_perform(curl);
            /* This code block is checking the response from the libcurl library after performing an HTTP request. If the response is not `CURLE_OK`, which indicates a successful request, it means that an error occurred during the request. */
            if (response != CURLE_OK)
            {
                switch (response)
                {
                    case CURLE_COULDNT_CONNECT:
                        logger.WRITE_AND_LOG_ERROR(ERROR_CURLE_COULDNT_CONNECT);
                        break;
                    case CURLE_COULDNT_RESOLVE_HOST:
                        logger.WRITE_AND_LOG_ERROR(ERROR_CURLE_COULDNT_RESOLVE_HOST);
                        break;
                    case CURLE_COULDNT_RESOLVE_PROXY:
                        logger.WRITE_AND_LOG_ERROR(ERROR_CURLE_COULDNT_RESOLVE_PROXY);
                        break;
                    case CURLE_UNSUPPORTED_PROTOCOL:
                        logger.WRITE_AND_LOG_ERROR(ERROR_CURLE_UNSUPPORTED_PROTOCOL);
                        break;
                    case CURLE_SSL_CONNECT_ERROR:
                        logger.WRITE_AND_LOG_ERROR(ERROR_CURLE_SSL_CONNECT_ERROR);
                        break;
                }
            }
            curl_easy_cleanup(curl);
            fclose(file);
        }
        database.open();
        NameDistribution = GetNameDistribution();
        Packages = database.GetAllValuesFromDB("Applications", "Linux");
        DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
        PackageManager = database.GetValueFromDB("SupportedOS", NameDistribution, "PackageManager");
    }
    catch (exception &error)
    {
        logger.WRITE_AND_LOG_ERROR("❌ An error occurred when trying to download the database and open it");
        logger.WRITE_AND_LOG_ERROR(error.what());
    }
}
#endif
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
#ifndef DEEPFORGE_TOOLSET_LINUX_HPP_
#define DEEPFORGE_TOOLSET_LINUX_HPP_

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
#include "DatabaseConnect.hpp"
#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include <vector>
#include "zip/zip.h"
#include <cstring>
#include <fstream>

/* The `#define OS_NAME "Linux"` statement is a preprocessor directive that defines a macro named `OS_NAME` with the value "Linux". This macro can be used throughout the code to represent the name of the operating system. */
#define OS_NAME "Linux"

using namespace std;
using namespace DB;
using namespace Bar;

namespace Linux
{

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
    const string OrganizationFolder = "/usr/bin/DeepForge";
    const string ApplicationFolder = OrganizationFolder + "/DeepForge-Toolset";
    const string UpdateManagerFolder = OrganizationFolder + "/UpdateManager";
    const string TempFolder = ApplicationFolder + "/Temp";
    const string LocaleDir = TempFolder + "/locale";
#if defined(__x86_64__)
    string Architecture = "amd64";
#elif __arm__ || __aarch64__ || _M_ARM64
    string Architecture = "arm64";
#endif
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

    int CallbackProgress(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (TotalToDownload <= 0.0)
        {
            return 0;
        }

        Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        // cout << Percentage << endl;
        if (TempPercentage != Percentage && TempPercentage <= 100)
        {
            progressbar.Update(NowDownloaded, TotalToDownload);
            LastSize = NowDownloaded;
            LastTotalSize = TotalToDownload;
            TempPercentage = Percentage;
        }
        return 0;
    }
    // Function for write data from curl
    size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }

    class AppInstaller
    {
    public:
        /**
         * The function `InstallVCpkg` installs vcpkg and adds it to the system path.
         *
         * @return an integer value. The possible return values are:
         * - 0: indicating successful installation of vcpkg
         * - 403: indicating that vcpkg is already installed in the specified directory
         */
        int InstallVCpkg()
        {
#if defined(__x86_64__)
            string NewVCpkgDir = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", "Directory");
            string VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", "Url");
#elif __arm__ || __aarch64__ || _M_ARM64
            string NewVCpkgDir = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", "Directory");
            string VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", "Url");
#endif

            string PathRepository = NewVCpkgDir + "vcpkg";
            if (std::filesystem::exists(PathRepository) && std::filesystem::is_empty(PathRepository) == false)
            {
                cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " в " << PathRepository << endl;
                return 403;
            }
#if defined(__x86_64__)
            string InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
            string InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", PackageManager);
#endif
            string Command = "cd " + NewVCpkgDir + " && sudo git clone " + VCpkgRepository;
            string Command_Install = "sudo " + NewVCpkgDir + "vcpkg/bootstrap-vcpkg.sh -disableMetrics";
            string Command_AddPath = "sudo ./utils/pathman-linux-amd64 add /usr/bin/vcpkg";
            system(InstallDependenciesCommand.c_str());
            MainInstaller("Git");
            result = system(Command.c_str());
            if (result == 0)
            {
                system(Command_Install.c_str());
                system(Command_AddPath.c_str());
                cout << "vcpkg " << translate["Located"].asString() << " " << PathRepository << endl;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        int InstallGoogleChrome()
        {
#if defined(__x86_64__)
            string NewGoogleChromeDir = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "GoogleChrome", "Directory");
            string GoogleChromeRepository = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "GoogleChrome", "Url");
#elif __arm__ || __aarch64__ || _M_ARM64
            string NewGoogleChromeDir = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "GoogleChrome", "Directory");
            string GoogleChromeRepository = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "GoogleChrome", "Url");
#endif

            string PathRepository = NewGoogleChromeDir + "vcpkg";
            if (std::filesystem::exists(PathRepository) && std::filesystem::is_empty(PathRepository) == false)
            {
                cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " в " << PathRepository << endl;
                return 403;
            }
#if defined(__x86_64__)
            string InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
            string InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", PackageManager);
#endif
            string Command = "cd " + NewVCpkgDir + " && sudo git clone " + VCpkgRepository;
            string Command_Install = "sudo " + NewVCpkgDir + "vcpkg/bootstrap-vcpkg.sh -disableMetrics";
            string Command_AddPath = "sudo ./utils/pathman-linux-amd64 add /usr/bin/vcpkg";
            system(InstallDependenciesCommand.c_str());
            MainInstaller("Git");
            result = system(Command.c_str());
            if (result == 0)
            {
                system(Command_Install.c_str());
                system(Command_AddPath.c_str());
                cout << "vcpkg " << translate["Located"].asString() << " " << PathRepository << endl;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        /* The above code is defining two function pointer types: `AppInstaller_funct_t` and
        `map_funct_t`. `AppInstaller_funct_t` is a function pointer type that points to a member
        function of the `AppInstaller` class that takes no arguments and returns an `int`.
        `map_funct_t` is a function pointer type that points to a function that takes no arguments
        and returns `void`. */
        using AppInstaller_funct_t = int (AppInstaller::*)(void);
        using map_funct_t = void (*)(void);

        map<string, AppInstaller_funct_t> PackagesFromSource{
            {"vcpkg", &AppInstaller::InstallVCpkg},
            {"Google Chrome",&AppInstaller::InstallGoogleChrome}
        };
        void UpdateData()
        {
            try
            {
                database.open(&DatabasePath);
#if defined(__x86_64__)
                Packages = database.GetAllValuesFromDB("Applications", "Linux_amd64");
#elif __arm__ || __aarch64__ || _M_ARM64
                Packages = database.GetAllValuesFromDB("Applications", "Linux_arm64");
#endif
                NameDistribution = GetNameDistribution();
                DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
                PackageManager = database.GetValueFromDB("SupportedOS", NameDistribution, "PackageManager");
            }
            catch (exception &error)
            {
                logger.WriteError(translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString());
                logger.WriteError(error.what());
            }
        }
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
        /**
         * The MainInstaller function installs an application on a Linux system based on the provided
         * name and architecture.
         *
         * @param Name The "Name" parameter is a string that represents the name of the application or
         * package that needs to be installed.
         *
         * @return the value of the variable "result".
         */
        int MainInstaller(string Name)
        {
            #if defined(__x86_64__)
                string Value = database.GetValueFromDB("Applications", Name, "Linux_amd64");
            #elif __arm__ || __aarch64__ || _M_ARM64
                string Value = database.GetValueFromDB("Applications", Name, "Linux_arm64");
            #endif
            if (Value != "ManualInstallation")
            {
                result = system(Value.c_str());
            }
            else if (PackagesFromSource.find(Name) != PackagesFromSource.end())
            {
                result = (this->*(PackagesFromSource[Name]))();
            }
            else
            {
                #if defined(__x86_64__)
                    string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", Name, PackageManager);
                #elif __arm__ || __aarch64__ || _M_ARM64
                    string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", Name, PackageManager);
                #endif
                    if (InstallCommand != "Empty")
                        result = system(InstallCommand.c_str());
            }
            return result;
        }
        AppInstaller()
        {
            try
            {
                UpdateData();
                InstallSnap();
                cout << InstallDelimiter << endl;
            }
            catch (exception &error)
            {
                cout << error.what() << endl;
            }
        }

        ~AppInstaller()
        {
        }

    private:
        void InstallSnap()
        {
            try
            {
                UpdateData();
                cout << NameDistribution << endl;
                /* The above code is written in C++ and it is performing the following tasks: */
                system("bash ./Scripts/CheckWSL.sh");
                result = system("snap --version");
                if (result == 0)
                {
                    system("sudo ln -s /var/lib/snapd/snap /snap");
                    system("sudo systemctl restart snapd.service");
                }
                else
                {
#if defined(__x86_64__)
                    string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "snap", PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
                    string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "snap", PackageManager);
#endif
                    if (InstallCommand != "Empty")
                        result = system(InstallCommand.c_str());
                }
            }
            catch (exception &error)
            {
                string ErrorText = "❌ " + translate["LOG_ERROR_INSTALL_SNAP"].asString();
                logger.WriteError(translate["LOG_ERROR_INSTALL_SNAP"].asString());
                logger.WriteError(error.what());
                cerr << ErrorText << endl;
                ;
            }
            // if (PackageManager == "apt")
            // {
            //     result = system("snap --version");
            //     if (result != 0)
            //     {
            //         cout << translate["Installing"].asString() << " " << "snap" << " ..." << endl;
            //         system("sudo apt-get update && sudo apt-get install -yqq daemonize dbus-user-session fontconfig");
            //         // system("sudo daemonize /usr/bin/unshare --fork --pid --mount-proc /lib/systemd/systemd --system-unit=basic.target");
            //         system("sudo apt install snap snapd");
            //         system("sudo ln -s /var/lib/snapd/snap /snap");
            //         system("sudo systemctl enable snapd.service");
            //         system("sudo systemctl start snapd.service");
            //         cout << "✅ " << "snap"<< " " << translate["Installed"].asString() << endl;
            //     }
            //     system("sudo ln -s /var/lib/snapd/snap /snap");
            //     system("sudo systemctl restart snapd.service");
            // }
        }
        /*The `MakeDirectory` function is responsible for creating a directory (folder) in the file system.*/
        void MakeDirectory(string dir)
        {
            string currentDir;
            string fullPath = "";
            string delimiter = "/";
            size_t pos = 0;
            while ((pos = dir.find(delimiter)) != string::npos)
            {
                currentDir = dir.substr(0, pos);
                if (fullPath != "")
                {
                    fullPath = fullPath + "/" + currentDir;
                    if (filesystem::exists(fullPath) == false)
                    {
                        filesystem::create_directory(fullPath);
                    }
                }
                else
                {
                    fullPath = "/" + currentDir;
                }
                dir.erase(0, pos + delimiter.length());
            }
            fullPath = fullPath + "/" + dir;
            if (filesystem::exists(fullPath) == false)
            {
                filesystem::create_directory(fullPath);
            }
        }
        /*  The `UnpackArchive` function takes two parameters: `path_from` and `path_to`.
            It uses the `Unzipper` class to extract the contents of an archive file located at `path_from` and saves them to the directory specified by `path_to`.
            After extracting the contents, the function closes the `Unzipper` object.
        */
        void UnpackArchive(string path_from, string path_to)
        {
            try
            {
                MakeDirectory(path_to);
                int err;
                struct zip *zip = zip_open(path_from.c_str(), ZIP_RDONLY, &err);
                if (zip == nullptr)
                {
                    string ErrorText = "==> ❌" + translate["CannotOpenArchive"].asString() + path_from;
                    throw runtime_error(ErrorText);
                }

                int num_entries = zip_get_num_entries(zip, 0);
                for (int i = 0; i < num_entries; ++i)
                {
                    zip_stat_t zip_stat;
                    zip_stat_init(&zip_stat);
                    int err = zip_stat_index(zip, i, 0, &zip_stat);
                    if (err != 0)
                    {
                        zip_close(zip);
                    }

                    string file_name = zip_stat.name;
                    string full_path = path_to + "/" + file_name;
                    filesystem::path file_dir(full_path);
                    MakeDirectory(file_dir.remove_filename().string());

                    struct zip_file *zip_file = zip_fopen_index(zip, i, 0);
                    if (zip_file == nullptr)
                    {
                        string ErrorText = "==> ❌" + translate["CannotOpenFile"].asString() + file_name;
                        zip_close(zip);
                        throw runtime_error(ErrorText);
                    }

                    if(filesystem::is_directory(full_path) == false)
                    {
                        ofstream out_file(full_path,ios::binary);
                        if (!out_file.is_open())
                        {
                            string ErrorText = "==> ❌" + translate["CannotWriteFile"].asString() + full_path;
                            zip_fclose(zip_file);
                            zip_close(zip);
                            throw runtime_error(ErrorText);
                        }
                        vector<char> buffer(zip_stat.size);
                        zip_fread(zip_file, buffer.data(), buffer.size());
                        out_file.write(buffer.data(), buffer.size());
                        out_file.close();
                    }
                    

                    zip_fclose(zip_file);
                }

                zip_close(zip);
            }
            catch (exception& error)
            {
                logger.SendError(Architecture, "Empty", OS_NAME, "UnpackArchive()", error.what());
                cerr << error.what() << endl;
            }
        }
        void DownloadDatabase()
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
                    /* `curl_easy_cleanup(curl);` is a function call to clean up and release resources associated with a CURL handle. It is used to free the resources allocated by `curl_easy_init()` function, which initializes a CURL handle for making HTTP requests. This function should be called after the request is completed or when the handle is no longer needed to avoid memory leaks. */
                    curl_easy_cleanup(curl);
                    fclose(file);
                    /* This code block is checking the response from the libcurl library after performing an HTTP request. If the response is not CURLE_OK (indicating a successful request), it enters the switch statement to handle different error cases. Depending on the specific error code, it logs an appropriate error message using the logger object. */
                    if (response != CURLE_OK)
                    {
                        switch (response)
                        {
                        case CURLE_COULDNT_CONNECT:
                            logger.WriteError(translate["LOG_ERROR_CURLE_COULDNT_CONNECT"].asString());
                        case CURLE_COULDNT_RESOLVE_HOST:
                            logger.WriteError(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                        case CURLE_COULDNT_RESOLVE_PROXY:
                            logger.WriteError(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                        case CURLE_UNSUPPORTED_PROTOCOL:
                            logger.WriteError(translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                        case CURLE_SSL_CONNECT_ERROR:
                            logger.WriteError(translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                        }
                    }
                }
            }
            catch (exception &error)
            {
                logger.WriteError(translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString());
                logger.WriteError(error.what());
            }
        }
        /**
         * The function `Download` downloads a file from a given URL and saves it to a specified
         * directory, while also displaying a progress bar.
         *
         * @param url The URL of the file you want to download.
         * @param dir The `dir` parameter is a string that represents the directory where the
         * downloaded file will be saved.
         *
         * @return an integer value. If the download is successful, it returns 200. If there is an
         * error, it returns 502.
         */
        int Download(string url, string dir)
        {
            string name = (url.substr(url.find_last_of("/")));
            string filename = dir + "/" + name.replace(name.find("/"), 1, "");
            FILE *file = fopen(filename.c_str(), "wb");
            CURL *curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &CallbackProgress);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
            curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteData);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            CURLcode response = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(file);
            /* The bellow code is checking the value of the variable "response" and performing
            different actions based on its value. If the value of "response" is not equal to
            CURLE_OK, it enters a switch statement. Inside the switch statement, it checks the
            value of "response" against different cases and performs specific actions for each
            case. The actions involve writing and logging different error messages based on the
            value of "response". */
            if (response != CURLE_OK)
            {
                switch (response)
                {
                case CURLE_COULDNT_CONNECT:
                    throw domain_error(translate["LOG_ERROR_CURLE_COULDNT_CONNECT"].asString());
                case CURLE_COULDNT_RESOLVE_HOST:
                    throw domain_error(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                case CURLE_COULDNT_RESOLVE_PROXY:
                    throw domain_error(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                case CURLE_UNSUPPORTED_PROTOCOL:
                    throw domain_error(translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                case CURLE_SSL_CONNECT_ERROR:
                    throw domain_error(translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                }
            }
            // If the progress bar is not completely filled in, then paint over manually
            if (Process < 100 && Process != Percentage)
            {
                for (int i = (Process - 1); i < 99; i++)
                {
                    progressbar.Update(LastSize, LastTotalSize);
                }
            }
            // Reset all variables and preferences
            progressbar.ResetAll();
            Percentage = 0;
            TempPercentage = 0;
            return 200;
        }
    };
    // Function to create a string with two application names
    string NewString(string sentence)
    {
        string new_sentence = "";
        // If the string is empty, then the first application name is added.
        if (haveString == "")
        {
            haveString = sentence;
            return new_sentence;
        }
        else
        {
            // Formatting string with two columns
            /* If the string already contains the name of the application,
            then the second name of the application is added and the formatted string is returned */
            new_sentence = fmt::format("{:<40} {:<15}\n", haveString, sentence);
            haveString = "";
            return new_sentence;
        }
    }
    // Function of make string to lower
    string to_lower(string sentence)
    {
        string new_sentence = "";
        for (int i = 0; i < sentence.length(); i++)
        {
            char ch = sentence[i];
            // cout << ch << endl;
            ch = tolower(ch);
            new_sentence += ch;
        }
        return new_sentence;
    }
    // Function for check of answer
    bool CheckAnswer(string answer)
    {
        bool status;
        // string Answer = to_lower(answer);

        /* The above code is checking if the string variable "Answer" matches any of the elements in
        the "TrueVarious" vector. It also checks if "Answer" is empty or if it matches certain
        predefined strings ("да", "ДА", "Да"). If any of these conditions are true, the boolean
        variable "status" is set to true. */
        string Answer = answer;
        for (int i = 0; i < TrueVarious->size(); i++)
        {
            if (Answer == TrueVarious[i] || Answer.empty() || Answer == "\n" || Answer == "да" || Answer == "ДА" || Answer == "Да")
            {
                status = true;
                break;
            }
        }
        return status;
    }
    // Initialization class
    AppInstaller Installer;
    // Function for install of DevelopmentPack(ready pack for certain programming language
    void InstallDevelopmentPack(string n)
    {
        try
        {
            Installer.UpdateData();
/* The above code is retrieving values from a database for a specific development pack on the
Linux platform. It then iterates over the retrieved values and creates a map of enumerated
packages. It also creates a string representation of each package with its corresponding
index. The code then checks if the number of packages is even or odd and prints the string
representation accordingly. */
#if defined(__x86_64__)
            auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Linux_amd64");
#elif __arm__ || __aarch64__ || _M_ARM64
            auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Linux_arm64");
#endif
            map<int, string> EnumeratePackages;
            string NamePackage;
            string delimiter = ",";
            size_t pos = 0;
            string token;
            /* The bellow code is retrieving values from a database for a specific development pack on the
            Windows platform. It then iterates over the retrieved values and creates a map of enumerated
            packages. It also creates a string representation of each package with its corresponding
            index. The code then checks if the number of packages is even or odd and prints the string
            representation accordingly. */
            for (int i = 1; const auto &element : DevelopmentPack)
            {
                /* The bellow code is inserting packages into a map called EnumeratePackages, where the
                key is an integer and the value is a string. It then creates a string called
                NamePackage by concatenating the key and the package name. It then calls a function
                called NewString with NamePackage as an argument and assigns the result to
                getNewString. */
                EnumeratePackages.insert(pair<int, string>(i, element.first));
                NamePackage = to_string(i) + ". " + element.first;
                // Formatting output text
                string getNewString = NewString(NamePackage);
                if (DevelopmentPack.size() % 2 == 0)
                {
                    if (getNewString != "")
                    {
                        cout << getNewString << endl;
                    }
                }
                else
                {
                    if (getNewString != "")
                    {
                        cout << getNewString << endl;
                    }
                    if (i == DevelopmentPack.size())
                    {
                        cout << NamePackage << endl;
                        haveString = "";
                    }
                }
                i++;
            }
            cout << "" << endl;
            cout << translate["SelectingPackages"].asString();
            getline(cin, SelectPackages);
            if (SelectPackages.empty() == false)
            {
                /* The bellow code is splitting a string called `SelectPackages` into multiple tokens using a
                delimiter (","). It then checks if each token is present in a map called
                `EnumeratePackages`. If a token is found in the map, it retrieves the corresponding value
                (package name) and performs some installation-related operations. These operations include
                printing messages, calling a `MainInstaller` function with the package name, and logging
                success or error messages based on the output of the `MainInstaller` function. Finally, it
                removes the processed token from the `SelectPackages` string and continues the loop until
                all tokens */
                while ((pos = SelectPackages.find(delimiter)) != string::npos)
                {
                    token = SelectPackages.substr(0, pos);
                    if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
                    {
                        NamePackage = EnumeratePackages[stoi(token)];
                        // =============================
                        cout << InstallDelimiter << endl;
                        cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                        // Install application
                        output_func = Installer.MainInstaller(NamePackage);
                        // Loggin and print messages
                        if (output_func == 0)
                        {
                            string SuccessText = "==> ✅ " + NamePackage + " " + translate["Installed"].asString();
                            cout << SuccessText << endl;
                        }
                        else if (output_func != 403)
                        {
                            string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                            cerr << ErrorText << endl;
                        }
                        SelectPackages.erase(0, pos + delimiter.length());
                    }
                }

                /* The bellow code is checking if a package with a specific ID exists in a map called
                EnumeratePackages. If the package exists, it retrieves the name of the package and proceeds
                to install it using the MainInstaller function from the Installer object. After
                installation, it logs and prints success or error messages based on the output of the
                installation process. */
                if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
                {
                    NamePackage = EnumeratePackages[stoi(SelectPackages)];
                    if (NamePackage != "AllPackages")
                    {
                        cout << InstallDelimiter << endl;
                        cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                        // Install application
                        output_func = Installer.MainInstaller(NamePackage);
                        // Logging and print messages
                        if (output_func == 0)
                        {
                            string SuccessText = "==> ✅ " + NamePackage + " " + translate["Installed"].asString();
                            cout << SuccessText << endl;
                        }
                        else if (output_func != 403)
                        {
                            string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                            cerr << ErrorText << endl;
                        }
                    }
                    else
                    {
                        DevelopmentPack.erase("AllPackages");
                        for (const auto &element : DevelopmentPack)
                        {
                            cout << InstallDelimiter << endl;
                            cout << translate["Installing"].asString() << " " << element.first << " ..." << endl;
                            output_func = Installer.MainInstaller(element.first);
                            if (output_func == 0)
                            {
                                string SuccessText = "==> ✅ " + element.first + " " + translate["Installed"].asString();
                                cout << SuccessText << endl;
                            }
                            else if (output_func != 403)
                            {
                                string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + element.first;
                                cerr << ErrorText << endl;
                            }
                        }
                    }
                }
            }
        }
        catch (exception &error)
        {
            string ErrorText = "==> ❌ " + string(error.what());
            logger.WriteError(error.what());
            cerr << ErrorText << endl;
        }
        cout << InstallDelimiter << endl;
    }
}
#endif
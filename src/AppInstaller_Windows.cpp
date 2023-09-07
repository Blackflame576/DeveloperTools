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
#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "AppInstaller_Windows.hpp"
#include <iostream>

using namespace std;

namespace Windows
{

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
            curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &DownloadSpeed);
            // printf("Average download speed: %lu kbyte/sec.\n",
            //         (unsigned long)(DownloadSpeed / 1024));
            progressbar.Update((float)(DownloadSpeed),(float)(NowDownloaded),(float)(TotalToDownload));
            LastDownloadSpeed = (float)(DownloadSpeed);
            LastSize = (float)(NowDownloaded);
            LastTotalSize = (float)(TotalToDownload);
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
        int InstallMake()
        {
            string NewMakeDir = database.GetValueFromDB("PackagesFromSource", "Make", "WindowsDir");
            string ArchivePath = ProjectDir + "/utils/Make_3.81.zip ";
            string Command = "tar -xf" + ArchivePath + "--directory " + NewMakeDir;
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewMakeDir;
            if (std::filesystem::exists(NewMakeDir))
            {
                cout << "✅ Make " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewMakeDir << endl;
                return 403;
            }
            if (std::filesystem::exists(ArchivePath))
            {
                if (std::filesystem::exists(NewMakeDir) == false)
                {
                    std::filesystem::create_directory(NewMakeDir);
                }
                result = system(Command.c_str());
                switch (result)
                {
                    case 0:
                        system(Command_AddPath.c_str());
                        cout << "Make " << translate["Located"].asString() << " " << NewMakeDir << endl;
                        return 0;
                }
            }
            else
            {
                throw logic_error("Zip archive not found");
            }
        }

        int InstallVCpkg()
        {
            string NewVCpkgDir = database.GetValueFromDB("PackagesFromSource", "vcpkg", "WindowsDir");
            string VCpkgRepository = database.GetValueFromDB("PackagesFromSource", "vcpkg", "Url");
            string PathRepository = NewVCpkgDir + "vcpkg";
            if (std::filesystem::exists(PathRepository))
            {
                cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << PathRepository << endl;
                return 403;
            }
            string Command = "cd " + NewVCpkgDir + " && git clone " + VCpkgRepository;
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewVCpkgDir + "vcpkg";
            string Command_Install = NewVCpkgDir + "vcpkg\\bootstrap-vcpkg.bat -disableMetrics";
            result = system(Command.c_str());
            switch (result)
            {
                case 0:
                    system(Command_Install.c_str());
                    system(Command_AddPath.c_str());
                    cout << "vcpkg " << translate["Located"].asString() << " " << PathRepository << endl;
                    return 0;
            }
        }

        int InstallPHP()
        {
            string NewPHPDir = database.GetValueFromDB("PackagesFromSource", "PHP", "WindowsDir");
            string ArchivePath = ProjectDir + "/utils/php-8.2.9.zip ";
            string Command = "tar -xf" + ArchivePath + "--directory " + NewPHPDir;
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewPHPDir;
            if (std::filesystem::exists(NewPHPDir))
            {
                cout << "✅ PHP " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewPHPDir << endl;
                return 403;
            }

            if (std::filesystem::exists(ArchivePath))
            {
                std::filesystem::create_directory(NewPHPDir);
                result = system(Command.c_str());
                switch (result)
                {
                    case 0:
                        cout << "" << endl;
                        system(Command_AddPath.c_str());
                        cout << "PHP " << translate["Located"].asString() << " " << NewPHPDir << endl;
                        return 0;
                }
            }
            else
            {
                throw logic_error("Zip archive not found");
            }
        }
        int InstallEclipse()
        {
            string EclipseUrl = database.GetValueFromDB("PackagesFromSource", "Eclipse IDE", "Url");
            string NewEclipseDir = database.GetValueFromDB("PackagesFromSource", "Eclipse IDE", "WindowsDir");
            string ArchiveDir = ProjectDir + "/Downloads";
            string ArchivePath = ArchiveDir + "/eclipse-java-2023-06-R-win32-x86_64.zip ";
            if (std::filesystem::exists("C:\\eclipse"))
            {
                cout << "✅ Eclipse IDE " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewEclipseDir << "eclipse" << endl;
                return 403;
            }
            if (std::filesystem::exists(ArchiveDir) == false)
            {
                std::filesystem::create_directory(ArchiveDir);
            }
            if (std::filesystem::exists(ArchivePath))
                std::filesystem::remove(ArchivePath);
            result = Download(EclipseUrl, ArchiveDir);
            string Command = "tar -xf" + ArchivePath + "--directory " + NewEclipseDir;
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewEclipseDir + "eclipse";
            switch (result)
            {
                case 200:
                    system(Command.c_str());
                    system(Command_AddPath.c_str());
                    std::filesystem::remove(ArchivePath);
                    cout << "Eclipse " << translate["Located"].asString() << " " << NewEclipseDir << "eclipse" << endl;
                    return 0;
                case 500:
                    throw domain_error("Unable to connect");
            }
        }

        int InstallKotlin()
        {
            string NewKotlinDir = database.GetValueFromDB("PackagesFromSource", "Kotlin", "WindowsDir");
            string KotlinUrl = database.GetValueFromDB("PackagesFromSource", "Kotlin", "Url");
            string ArchiveDir = ProjectDir + "/Downloads";
            string ArchivePath = ArchiveDir + "/kotlin-compiler-1.8.22.zip ";
            if (std::filesystem::exists("C:\\kotlinc"))
            {
                cout << "✅ Kotlin " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewKotlinDir << "kotlinc" << endl;
                return 403;
            }
            if (std::filesystem::exists(ArchiveDir) == false)
            {
                std::filesystem::create_directory(ArchiveDir);
            }
            if (std::filesystem::exists(ArchivePath))
                std::filesystem::remove(ArchivePath);
            result = Download(KotlinUrl, ArchiveDir);
            string Command = "tar -xf" + ArchivePath + "--directory " + NewKotlinDir;
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewKotlinDir;
            switch (result)
            {
                case 200:
                    system(Command.c_str());
                    system(Command_AddPath.c_str());
                    std::filesystem::remove(ArchivePath);
                    cout << "Kotlin " << translate["Located"].asString() << " " << NewKotlinDir << endl;
                    return 0;
                case 500:
                    throw domain_error("Unable to connect");
            }
        }

        int InstallWget()
        {
            string NewWgetDir = database.GetValueFromDB("PackagesFromSource", "Wget", "WindowsDir");
            string WgetUrl = database.GetValueFromDB("PackagesFromSource", "Wget", "Url");
            string ApplicationPath = NewWgetDir + "/wget.exe ";
            if (std::filesystem::exists(NewWgetDir))
            {
                cout << "✅ Wget " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewWgetDir << endl;
                return 403;
            }
            if (std::filesystem::exists(NewWgetDir) == false)
            {
                std::filesystem::create_directory(NewWgetDir);
            }
            result = Download(WgetUrl, NewWgetDir);
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewWgetDir;
            switch (result)
            {
                case 200:
                    system(Command_AddPath.c_str());
                    cout << "Wget " << translate["Located"].asString() << " " << NewWgetDir << endl;
                    return 0;
                case 500:
                    throw domain_error("Unable to connect");
            }
        }

        int InstallNginx()
        {
            string NewNginxDir = database.GetValueFromDB("PackagesFromSource", "Nginx", "WindowsDir");
            string ArchivePath = ProjectDir + "/utils/Nginx-1.25.1.zip ";
            string Command = "tar -xf" + ArchivePath + "--directory " + NewNginxDir;
            string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewNginxDir + "Nginx-1.25.1";
            if (std::filesystem::exists("C:\\Nginx-1.25.1"))
            {
                cout << "✅ Nginx " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewNginxDir << "Nginx-1.25.1" << endl;
                return 403;
            }
            if (std::filesystem::exists(ArchivePath))
            {
                result = system(Command.c_str());
                switch (result)
                {
                case 0:
                    system(Command_AddPath.c_str());
                    cout << "Nginx " << translate["Located"].asString() << " " << NewNginxDir << "Nginx-1.25.1" << endl;
                    return 0;
                }
            }
            else
            {
                throw logic_error("Zip archive not found");
            }
        }

        using AppInstaller_funct_t = int (AppInstaller::*)(void);
        using map_funct_t = void (*)(void);

        map<string, AppInstaller_funct_t> PackagesFromSource{
            {"Eclipse IDE", &AppInstaller::InstallEclipse},
            {"Kotlin", &AppInstaller::InstallKotlin},
            {"vcpkg", &AppInstaller::InstallVCpkg},
            {"PHP", &AppInstaller::InstallPHP},
            {"Make", &AppInstaller::InstallMake},
            {"Wget", &AppInstaller::InstallWget},
            {"Nginx", &AppInstaller::InstallNginx}};

        int MainInstaller(string Name)
        {
            string Value = database.GetValueFromDB("Applications", Name, "Windows");
            if (Value != "ManualInstallation")
            {
                result = system(Value.c_str());
            }
            else if (PackagesFromSource.find(Name) != PackagesFromSource.end())
            {
                result = (this->*(PackagesFromSource[Name]))();
            }
            return result;
        }
        AppInstaller()
        {
            UpdateData();
            InstallWinGet();
            cout << InstallDelimiter << endl;
        }

        ~AppInstaller()
        {
        }

    private:
        void InstallWinGet()
        {
            cout << "WinGet ";
            result = system("winget -v");
            if (result != 0)
            {
                cout << translate["Installing"].asString() << " " << "winget"
                     << " ..." << endl;
                string Command = "powershell.exe " + ProjectDir + "/Scripts/InstallWinGet.ps1";
                system(Command.c_str());
                cout << "✅ " << "winget" << " " << translate["Installed"].asString() << endl;
            }
        }

        int Download(string url, string dir)
        {
            try
            {
                string name = (url.substr(url.find_last_of("/")));
                string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                FILE *file = fopen(filename.c_str(), "wb");
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
                if (Process < 100)
                {
                    for (int i = (Process - 1);i < 99;i++)
                    {
                        progressbar.Update(0.0,LastSize,LastTotalSize);
                    }
                }
                cout << "" << endl;
                return 200;
            }
            catch (exception &error)
            {
                string ErrorText_1 = "DownloadError.Function - Download(). Code: 502.";
                string ErrorText_2 = error.what();
                logger.Error(ErrorText_1.c_str());
                logger.Error(ErrorText_2.c_str());
                return 502;
            }
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
    // Method of make string to lower
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

    // AppInstaller Installer;
    // typedef void (AppInstaller::*funct_t)(void);
    // typedef std::map<std::string, funct_t> AppInstaller_func_map_t;
    // AppInstaller_func_map_t Packages = {
    //     {"Git",&AppInstaller::InstallGit}
    // };
    // map<string, function<void()>> Packages = {
    //     {"Git",[&installer](){installer.InstallGit();}}
    // };
    // Initialization class
    AppInstaller Installer;
    // Function for install of DevelopmentPack(ready pack for certain programming language
    void InstallDevelopmentPack(string n)
    {
        UpdateData();
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Windows");
        map<int, string> EnumeratePackages;
        string NamePackage;
        for (int i = 1; const auto &element : DevelopmentPack)
        {
            EnumeratePackages.insert(pair<int, string>(i, element.first));
            NamePackage = to_string(i) + ". " + element.first;
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
        string delimiter = ",";
        size_t pos = 0;
        string token;
        while ((pos = SelectPackages.find(delimiter)) != string::npos)
        {
            token = SelectPackages.substr(0, pos);
            if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end()) {
                NamePackage = EnumeratePackages[stoi(token)];
                // =============================
                cout << InstallDelimiter << endl;
                cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                // Install application
                output_func = Installer.MainInstaller(NamePackage);
                // Loggin and print messages
                if (output_func == 0)
                {
                    cout << "✅ " << NamePackage << " " << translate["Installed"].asString() << endl;
                    string SuccessText = NamePackage + " " + translate["Installed"].asString();
                    logger.Success(SuccessText.c_str());
                }
                else if (output_func != 403)
                {
                    cout << "❌ " << translate["ErrorInstall"].asString() << " " << NamePackage << endl;
                    string ErrorText = translate["ErrorInstall"].asString() + " " + NamePackage;
                    logger.Error(ErrorText.c_str());
                }
                SelectPackages.erase(0, pos + delimiter.length());
            }
        }
        if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end()) {
            NamePackage = EnumeratePackages[stoi(SelectPackages)];
            // =============================
            cout << InstallDelimiter << endl;
            cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
            // Install application
            output_func = Installer.MainInstaller(NamePackage);
            // Logging and print messages
            if (output_func == 0)
            {
                cout << "✅ " << NamePackage << " " << translate["Installed"].asString() << endl;
                string SuccessText = NamePackage + " " + translate["Installed"].asString();
                logger.Success(SuccessText.c_str());
            }
            else if (output_func != 403)
            {
                cout << "❌ " << translate["ErrorInstall"].asString() << " " << NamePackage << endl;
                string ErrorText = translate["ErrorInstall"].asString() + " " + NamePackage;
                logger.Error(ErrorText.c_str());
            }
        }
        cout << InstallDelimiter << endl;
    }
}
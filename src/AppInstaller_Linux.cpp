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
#include "AppInstaller_Linux.hpp"
#include <iostream>

using namespace std;

namespace Linux
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
        int InstallVCpkg()
        {
            string NewVCpkgDir = database.GetValueFromDB("PackagesFromSource", "vcpkg", "LinuxDir");
            string VCpkgRepository = database.GetValueFromDB("PackagesFromSource", "vcpkg", "Url");
            string PathRepository = NewVCpkgDir + "vcpkg";
            if (std::filesystem::exists(PathRepository))
            {
                cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " в " << PathRepository << endl;
                return 403;
            }
            string Command = "cd " + NewVCpkgDir + " && sudo git clone " + VCpkgRepository;
            string Command_Install = "sudo " + NewVCpkgDir + "vcpkg/bootstrap-vcpkg.sh -disableMetrics";
            // string Command_AddPath = "bash -c 'source ./Scripts/AddPath.sh'";
            string Command_AddPath = "sudo ./utils/pathman-linux-amd64 add /usr/bin/vcpkg";
            result = system(Command.c_str());
            // result = system("ls");
            switch (result)
            {
            case 0:
                // result = system(Command_Install.c_str());
                if (result == 0)
                {
                    system(Command_AddPath.c_str());
                    cout << "vcpkg " << translate["Located"].asString() << " " << NewVCpkgDir << "vcpkg" << endl;
                }
                return 0;
            }
        }

        // int InstallPython_3_9() {
        //     if (Architecture == "x86") {
        //         string Python_3_9_Url = database.GetValueFromDB("PackagesFromSource","Python3.9","Url");
        //     }
        //     else if (Architecture == "arm64"){
        //         string Python_3_9_Url = database.GetValueFromDB("PackagesFromSource","Python3.9","Url_arm64");
        //     }
        //     string NewPython_3_9_Dir = database.GetValueFromDB("PackagesFromSource","Python 3.9","LinuxDir");
        //     string ArchiveDir = ProjectDir + "/Downloads";
        //     string ArchivePath;
        //     if (Architecture == "x86") {
        //         ArchivePath = ArchiveDir + "/Python3.9.6_linux_amd64.zip ";
        //     }
        //     else if (Architecture == "arm64") {
        //         ArchivePath = ArchiveDir + "/Python3.9.6_linux_arm64.zip ";
        //     }
        //     string Command = "tar -xf " + ArchivePath + "--directory " + NewPython_3_9_Dir;
        //     string Command_AddPath;
        //     if (Architecture == "x86") {
        //         Command_AddPath = "sudo " + ProjectDir + "/utils/pathman-linux-amd64" + NewPython_3_9_Dir;
        //     }
        //     else if (Architecture == "arm64") {
        //         Command_AddPath = "sudo " + ProjectDir + "/utils/pathman-linux-armv8" + NewPython_3_9_Dir;
        //     }
        //     if (std::filesystem::exists(ArchiveDir) == false) {
        //         std::filesystem::create_directory(ArchiveDir);
        //     }
        //     if (std::filesystem::exists(ArchivePath)) std::filesystem::remove(ArchivePath);
        //     result = Download(NewPython_3_9_Dir,ArchiveDir);
        //     switch (result) {
        //         case 200:
        //             system(Command.c_str());
        //             system(Command_AddPath.c_str());
        //             std::filesystem::remove(ArchivePath);
        //             cout << "Python 3.9 " << translate["Located"].asString() << " " << NewPython_3_9_Dir << endl;
        //             return 0;
        //         case 500:
        //             throw domain_error("Unable to connect");
        //     }
        // }

        // int InstallPython_3_10() {
        //     if (Architecture == "x86") {
        //         string Python_3_10_Url = database.GetValueFromDB("PackagesFromSource","Python3.10","Url");
        //     }
        //     else if (Architecture == "arm64"){
        //         string Python_3_10_Url = database.GetValueFromDB("PackagesFromSource","Python3.10","Url_arm64");
        //     }
        //     string NewPython_3_10_Dir = database.GetValueFromDB("PackagesFromSource","Python 3.10","LinuxDir");
        //     string ArchiveDir = ProjectDir + "/Downloads";
        //     string ArchivePath;
        //     if (Architecture == "x86") {
        //         ArchivePath = ArchiveDir + "/Python3.10.12_linux_amd64.zip ";
        //     }
        //     else if (Architecture == "arm64") {
        //         ArchivePath = ArchiveDir + "/Python3.10.12_linux_arm64.zip ";
        //     }
        //     string Command = "tar -xf " + ArchivePath + "--directory " + NewPython_3_10_Dir;
        //     string Command_AddPath;
        //     if (Architecture == "x86") {
        //         Command_AddPath = "sudo " + ProjectDir + "/utils/pathman-linux-amd64" + NewPython_3_10_Dir;
        //     }
        //     else if (Architecture == "arm64") {
        //         Command_AddPath = "sudo " + ProjectDir + "/utils/pathman-linux-armv8" + NewPython_3_10_Dir;
        //     }
        //     if (std::filesystem::exists(ArchiveDir) == false) {
        //         std::filesystem::create_directory(ArchiveDir);
        //     }
        //     if (std::filesystem::exists(ArchivePath)) std::filesystem::remove(ArchivePath);
        //     result = Download(NewPython_3_10_Dir,ArchiveDir);
        //     switch (result) {
        //         case 200:
        //             system(Command.c_str());
        //             system(Command_AddPath.c_str());
        //             std::filesystem::remove(ArchivePath);
        //             cout << "Python 3.10 " << translate["Located"].asString() << " " << NewPython_3_10_Dir << endl;
        //             return 0;
        //         case 500:
        //             throw domain_error("Unable to connect");
        //     }
        // }

        // int InstallPython_3_11() {
        //     if (Architecture == "x86") {
        //         string Python_3_11_Url = database.GetValueFromDB("PackagesFromSource","Python3.11","Url");
        //     }
        //     else if (Architecture == "arm64"){
        //         string Python_3_11_Url = database.GetValueFromDB("PackagesFromSource","Python3.11","Url_arm64");
        //     }
        //     string NewPython_3_11_Dir = database.GetValueFromDB("PackagesFromSource","Python 3.11","LinuxDir");
        //     string ArchiveDir = ProjectDir + "/Downloads";
        //     string ArchivePath;
        //     if (Architecture == "x86") {
        //         ArchivePath = ArchiveDir + "/Python3.11.4_linux_amd64.zip ";
        //     }
        //     else if (Architecture == "arm64") {
        //         ArchivePath = ArchiveDir + "/Python3.11.4_linux_arm64.zip ";
        //     }
        //     string Command = "tar -xf " + ArchivePath + "--directory " + NewPython_3_11_Dir;
        //     string Command_AddPath;
        //     if (Architecture == "x86") {
        //         Command_AddPath = "sudo " + ProjectDir + "/utils/pathman-linux-amd64" + NewPython_3_11_Dir;
        //     }
        //     else if (Architecture == "arm64") {
        //         Command_AddPath = "sudo " + ProjectDir + "/utils/pathman-linux-armv8" + NewPython_3_11_Dir;
        //     }
        //     if (std::filesystem::exists(ArchiveDir) == false) {
        //         std::filesystem::create_directory(ArchiveDir);
        //     }
        //     if (std::filesystem::exists(ArchivePath)) std::filesystem::remove(ArchivePath);
        //     result = Download(NewPython_3_11_Dir,ArchiveDir);
        //     switch (result) {
        //         case 200:
        //             system(Command.c_str());
        //             system(Command_AddPath.c_str());
        //             std::filesystem::remove(ArchivePath);
        //             cout << "Python 3.11 " << translate["Located"].asString() << " " << NewPython_3_11_Dir << endl;
        //             return 0;
        //         case 500:
        //             throw domain_error("Unable to connect");
        //     }
        // }
        int InstallPython_3_9()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "Python 3.9", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
            // else {
            //     if (PackageManager == "zypper") {

            //     }
            // }
        }

        int InstallPython_3_10()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "Python 3.10", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }

        int InstallPython_3_11()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "Python 3.11", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }

        int InstallPHP()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "PHP", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }

        int InstallMake()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "Make", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }

        int InstallWget()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "Wget", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }

        int InstallNginx()
        {
            string InstallCommand = database.GetValueFromDB("PackagesFromSource", "Nginx", PackageManager);
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }

        using AppInstaller_funct_t = int (AppInstaller::*)(void);
        using map_funct_t = void (*)(void);

        map<string, AppInstaller_funct_t> PackagesFromSource{
            {"vcpkg", &AppInstaller::InstallVCpkg},
            {"Python 3.9", &AppInstaller::InstallPython_3_9},
            {"Python 3.10", &AppInstaller::InstallPython_3_10},
            {"Python 3.11", &AppInstaller::InstallPython_3_11},
            {"Wget", &AppInstaller::InstallWget},
            {"Make", &AppInstaller::InstallMake},
            {"PHP", &AppInstaller::InstallPHP},
            {"Nginx", &AppInstaller::InstallNginx}};

        int MainInstaller(string Name)
        {
            string Value = database.GetValueFromDB("Applications", Name, "Linux");
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
            InstallSnap();
            cout << InstallDelimiter << endl;
        }

        ~AppInstaller()
        {
        }

    private:
        void InstallSnap()
        {
            UpdateData();
            cout << NameDistribution << endl;
            result = system("snap --version");
            if (result != 0) {
                string InstallCommand = database.GetValueFromDB("PackagesFromSource", "snap", PackageManager);
                if (InstallCommand != "Empty")
                    result = system(InstallCommand.c_str());
                    cout << "✅ " << "snap"<< " " << translate["Installed"].asString() << endl;
            }
            else {
                system("sudo ln -s /var/lib/snapd/snap /snap");
                system("sudo systemctl restart snapd.service");
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
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Linux");
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
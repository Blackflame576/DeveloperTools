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
#include "AppInstaller_macOS.hpp"
#include <iostream>

using namespace std;

namespace macOS {

    int CallbackProgress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (TotalToDownload <= 0.0) {
            return 0;
        }

        Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        if (TempPercentage != Percentage && TempPercentage <= 100) {
            curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &DownloadSpeed);
            if ((CURLE_OK == res) && (DownloadSpeed > 0.0)) {
                // printf("Average download speed: %lu kbyte/sec.\n",
                //         (unsigned long)(DownloadSpeed / 1024));
                float Speed = (float) (DownloadSpeed / 1024);
                progressbar.Update(Speed);
                TempPercentage = Percentage;
            }
        }
        return 0;
    }
    // Function for write data from curl
    size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }

    class AppInstaller
    {
    public:
        using AppInstaller_funct_t = int(AppInstaller::*)(void);
        using map_funct_t = void(*)(void);

        map<string,AppInstaller_funct_t> PackagesFromSource {
        };

        int MainInstaller(string Name) {
            string Value = database.GetValueFromDB("Applications",Name,"macOS");
            if (Value != "ManualInstallation") {
                result = system(Value.c_str());
            }
            else if (PackagesFromSource.find(Name) != PackagesFromSource.end()) {
                result = (this->*(PackagesFromSource[Name]))();
            }
            return result;
        }
        AppInstaller() {
            UpdateData();
            InstallBrew();
            cout << InstallDelimiter << endl;
        }

        ~AppInstaller() {

        }
    private:
        void InstallBrew() {
            cout << translate["Installing"].asString() << " " << "brew" << " ..." << endl;
            system("bash ./Scripts/InstallBrew.sh");
            cout << "✅ " << "brew" << " " << translate["Installed"].asString() << endl;
        }
        
        int Download(string url, string dir)
        {
            try {
                string name = (url.substr(url.find_last_of("/")));
                string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                FILE* file = fopen(filename.c_str(), "wb");
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
            catch (exception& error) {
                string ErrorText_1 = "DownloadError.Function - Download(). Code: 502.";
                string ErrorText_2 = error.what();
                logger.Error(ErrorText_1.c_str());
                logger.Error(ErrorText_2.c_str());
                return 502;
            }
        }
    };
    // Function to create a string with two application names
    string NewString(string sentence) {
        string new_sentence = "";
        // If the string is empty, then the first application name is added.
        if (haveString == "") {
            haveString = sentence;
            return new_sentence;
        }
        else {
            // Formatting string with two columns
            /* If the string already contains the name of the application,
            then the second name of the application is added and the formatted string is returned */
            new_sentence = fmt::format("{:<40} {:<15}\n",haveString,sentence);
            haveString = "";
            return new_sentence;
        }
    }
    // Function of make string to lower
    string to_lower(string sentence)
    {
        string new_sentence = "";
        for(int i = 0;i < sentence.length();i++) {
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
        for (int i = 0; i < TrueVarious->size(); i++) {
            if (Answer == TrueVarious[i] || Answer.empty() || Answer == "\n" || Answer == "да" || Answer == "ДА" || Answer == "Да") {
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
    void InstallDevelopmentPack(string n) {
        UpdateData();
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n],"macOS");
        map<int,string> EnumeratePackages;
        string NamePackage;
        for (int i = 1;const auto &element:DevelopmentPack) {
            EnumeratePackages.insert(pair<int,string>(i,element.first));
            NamePackage = to_string(i) + ". " + element.first;
            string getNewString = NewString(NamePackage);
            if (DevelopmentPack.size() % 2 == 0) {
                if (getNewString != "") {
                    cout << getNewString << endl;
                }
            }
            else {
                if (getNewString != "") {
                    cout << getNewString << endl;
                }
                if (i == DevelopmentPack.size()) {
                    cout << NamePackage << endl;
                    haveString = "";
                }
            }
            i++;
        }
        cout << "" << endl;
        cout << translate["SelectingPackages"].asString();
        getline(cin,SelectPackages);
        string delimiter = ",";
        size_t pos = 0;
        string token;
        while ((pos = SelectPackages.find(delimiter)) != string::npos) {
            token = SelectPackages.substr(0, pos);
            NamePackage = EnumeratePackages[stoi(token)];
            // =============================
            cout << InstallDelimiter << endl;
            cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
            // Install application
            output_func = Installer.MainInstaller(NamePackage);
            // Loggin and print messages
            if (output_func == 0) {
                cout << "✅ " << NamePackage << " " << translate["Installed"].asString() << endl;
                string SuccessText = NamePackage + " " + translate["Installed"].asString();
                logger.Success(SuccessText.c_str());
            }
            else {
                string ErrorText = translate["ErrorInstall"].asString() + " " + NamePackage;
                logger.Error(ErrorText.c_str());
            }
            SelectPackages.erase(0, pos + delimiter.length());
        }
        NamePackage = EnumeratePackages[stoi(SelectPackages)];
        // =============================
        cout << InstallDelimiter << endl;
        cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
        // Install application
        output_func = Installer.MainInstaller(NamePackage);
        // Logging and print messages
        if (output_func == 0) {
            cout << "✅ " << NamePackage << " " << translate["Installed"].asString() << endl;
            string SuccessText = NamePackage + " " + translate["Installed"].asString();
            logger.Success(SuccessText.c_str());
        }
        else {
            string ErrorText = translate["ErrorInstall"].asString() + " " + NamePackage;
            logger.Error(ErrorText.c_str());
        }
        cout << InstallDelimiter << endl;
    }
}
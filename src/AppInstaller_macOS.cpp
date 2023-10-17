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
#include "AppInstaller_macOS.hpp"

namespace macOS
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
        using AppInstaller_funct_t = int (AppInstaller::*)(void);
        using map_funct_t = void (*)(void);

        map<string, AppInstaller_funct_t> PackagesFromSource{};

        int MainInstaller(string Name)
        {
            string Value = database.GetValueFromDB("Applications", Name, "macOS");
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
            GetArchitectureOS();
            UpdateData();
            InstallBrew();
            cout << InstallDelimiter << endl;
        }

        ~AppInstaller()
        {
        }

    private:
        // Method for getting architecture of OS
        void GetArchitectureOS()
        {
            #if defined(__x86_64__)
                Architecture = "amd64";
            #elif __arm__
                Architecture = "arm64";
            #endif
        }
        void InstallBrew()
        {   result = system("brew --version");
            if (result != 0) 
            {
                cout << translate["Installing"].asString() << " " << "brew" << " ..." << endl;
                system("bash ./Scripts/InstallBrew.sh");
                cout << "✅ " << "brew" << " " << translate["Installed"].asString() << endl;
            }
        }

        int Download(string url, string dir)
        {
            try
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
                if (response != CURLE_OK)
                {
                    switch (response)
                    {
                    case CURLE_COULDNT_CONNECT:
                        cerr << "❌ Failed to connect to host or proxy." << endl;
                        break;
                    case CURLE_COULDNT_RESOLVE_HOST:
                        cerr << "❌ Failed to resolve host. The given remote host was not allowed." << endl;
                        break;
                    case CURLE_COULDNT_RESOLVE_PROXY:
                        cerr << "❌ Failed to resolve proxy. The given proxy host could not be resolved." << endl;
                        break;
                    case CURLE_UNSUPPORTED_PROTOCOL:
                        cerr << "❌ Failed to connect to the site using this protocol." << endl;
                        break;
                    case CURLE_SSL_CONNECT_ERROR:
                        cerr << "❌ The problem occurred during SSL/TLS handshake." << endl;
                        break;
                    }
                }
                curl_easy_cleanup(curl);
                fclose(file);
                // If the progress bar is not completely filled in, then paint over manually
                if (Process < 100 && Process != Percentage)
                {
                    for (int i = (Process - 1); i < 99; i++)
                    {
                        progressbar.Update(0.0, LastSize, LastTotalSize);
                    }
                }
                // Reset all variables and preferences
                progressbar.ResetAll();
                Percentage = 0;
                TempPercentage = 0;
                cout << InstallDelimiter << endl;
                return 200;
            }
            catch (exception& error)
            {
                cerr << error.what() << endl;
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
    // Initialization class
    AppInstaller Installer;
    // Function for install of DevelopmentPack(ready pack for certain programming language
    void InstallDevelopmentPack(string n)
    {
        UpdateData();
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "macOS");
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
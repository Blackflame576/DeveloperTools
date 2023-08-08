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
#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "AppInstaller_Windows.hpp"
#include <iostream>

using namespace std;

namespace Windows {
    
    int CallbackProgress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (TotalToDownload <= 0.0) {
            return 0;
        }

        int Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        if (TempPercentage != Percentage && TempPercentage <= 100) {
            curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &DownloadSpeed);
            if ((CURLE_OK == res) && (DownloadSpeed > 0.0)) {
                // printf("Average download speed: %lu kbyte/sec.\n",
                //         (unsigned long)(DownloadSpeed / 1024));
                float Speed = (float) (DownloadSpeed / 1024);
                bar.Update(Speed);
                TempPercentage = Percentage;
            }
        }
        return 0;
    }

    size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }
    
    class AppInstaller {
        public:
            int InstallGit() {
                result = system("winget install --id Git.Git -e --source winget");
                return result;
            }

            int InstallVSCode() {
                result = system("winget install -e --id Microsoft.VisualStudioCode");
                return result;
            }

            int InstallWebStorm() {
                result = system("winget install -e --id JetBrains.WebStorm");
                return result;
            }

            int InstallDocker() {
                result = system("winget install -e --id Docker.DockerDesktop");
                return result;
            }

            int InstallPostman() {
                result = system("winget install -e --id Postman.Postman");
                return result;
            }

            int InstallRubyMine() {
                result = system("winget install -e --id JetBrains.RubyMine");
                return result;
            }

            int InstallCLion() {
                result = system("winget install -e --id JetBrains.CLion");
                return result;
            }

            int InstallDataGrip() {
                result = system("winget install -e --id JetBrains.DataGrip");
                return result;
            }

            int InstallDataSpell() {
                result = system("winget install -e --id JetBrains.DataSpell");
                return result;
            }

            int InstallGoLand() {
                result = system("winget install -e --id JetBrains.GoLand");
                return result;
                
            }

            int InstallIntelliJIDEACommunity() {
                result = system("winget install -e --id JetBrains.IntelliJIDEA.Community");
                return result;
            }

            int InstallIntelliJIDEAUltimate() {
                result = system("winget install -e --id JetBrains.IntelliJIDEA.Ultimate");
                return result;
            }

            int InstallRider() {
                result = system("winget install -e --id JetBrains.Rider");
                return result;
            }

            int InstallPhpStorm() {
                result = system("winget install -e --id JetBrains.PHPStorm");
                return result;
            }

            int InstallSpace() {
                result = system("winget install -e --id JetBrains.Space");
                return result;
            }

            int InstallPostgresql() {
                result = system("winget install -e --id PostgreSQL.PostgreSQL");
                return result;
            }
            int InstallPgAdmin() {
                result = system("winget install -e --id PostgreSQL.pgAdmin");
                return result;
            }

            int InstallNgrok() {
                result = system("winget install -e --id Ngrok.Ngrok");
                return result;
            }

            int InstallSublimeText() {
                result = system("winget install -e --id SublimeHQ.SublimeText.4");
                return result;
            }

            int InstallPyCharmCommunity() {
                result = system("winget install -e --id JetBrains.PyCharm.Community");
                return result;
            }

            int InstallPyCharmProffessional() {
                result = system("winget install -e --id JetBrains.PyCharm.Professional");
                return result;
            }

            int InstallDiscord() {
                result = system("winget install -e --id Discord.Discord");
                return result;
            }

            int InstallTelegram() {
                result = system("winget install -e --id Telegram.TelegramDesktop");
                return result;
            }

            int InstallNodeJS() {
                result = system("winget install -e --id OpenJS.NodeJS");
                return result;
            }

            int InstallGo() {
                result = system("winget install -e --id GoLang.Go.1.18");
                return result;
            }

            int InstallJDK_19() {
                result = system("winget install -e --id Oracle.JDK.19");
                return result;
            }

            int InstallJDK_18() {
                result = system("winget install -e --id Oracle.JDK.18");
                return result;
            }

            int InstallVisualStudioCE() {
                result = system("winget install -e --id Microsoft.VisualStudio.2022.Community.Preview");
                return result;
            }

            int InstallVisualStudioPE() {
                result = system("winget install -e --id Microsoft.VisualStudio.2022.Professional.Preview");
                return result;
            }

            int InstallRust() {
                result = system("winget install -e --id Rustlang.Rust.MSVC");
                return result;
            }

            int InstallRuby() {
                result = system("winget install -e --id RubyInstallerTeam.Ruby.3.1");
                return result;
            }

            int InstallNetFramework() {
                result = system("winget install -e --id Microsoft.DotNet.Framework.DeveloperPack_4");
                return result;
            }

            int InstallPython3_9() {
                result = system("winget install -e --id Python.Python.3.9");
                return result;
            }
            
            int InstallPython3_10() {
                result = system("winget install -e --id Python.Python.3.10");
                return result;
            }

            int InstallPython3_11() {
                result = system("winget install -e --id Python.Python.3.11");
                return result;
            }

            int InstallVim() {
                result = system("winget install -e --id vim.vim");
                return result;
            }

            int InstallNeoVim() {
                result = system("winget install -e --id Neovim.Neovim");
                return result;
            }

            int InstallEclipse() {
                string ArchiveDir = ProjectDir + "/Downloads";
                string ArchivePath = ArchiveDir + "/eclipse-java-2023-06-R-win32-x86_64.zip ";
                if (std::filesystem::exists(ArchiveDir) == false) {
                    std::filesystem::create_directory(ArchiveDir);
                }
                if (std::filesystem::exists(ArchivePath)) std::filesystem::remove(ArchivePath);
                result = Download(EclipseUrl,ArchiveDir);
                string Command = "tar -xf" + ArchivePath + "--directory " + NewEclipseDir;
                string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewEclipseDir + "eclipse";
                switch (result) {
                    case 200:
                        system(Command.c_str());
                        system(Command_AddPath.c_str());
                        std::filesystem::remove(ArchivePath);
                        cout << "Eclipse " << translate["Located"].asString() << " " << NewEclipseDir << "eclipse" << endl;
                        break;
                    case 500:
                        throw domain_error("Unable to connect");
                }
                return 0;
            }

            int InstallKotlin() {
                string ArchiveDir = ProjectDir + "/Downloads";
                string ArchivePath = ArchiveDir + "/kotlin-compiler-1.8.22.zip ";
                if (std::filesystem::exists(ArchiveDir) == false) {
                    std::filesystem::create_directory(ArchiveDir);
                }
                if (std::filesystem::exists(ArchivePath)) std::filesystem::remove(ArchivePath);
                result = Download(KotlinUrl,ArchiveDir);
                string Command = "tar -xf" + ArchivePath + "--directory " + NewKotlinDir;
                string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewKotlinDir;
                switch (result) {
                    case 200:
                        system(Command.c_str());
                        system(Command_AddPath.c_str());
                        std::filesystem::remove(ArchivePath);
                        cout << "Kotlin " << translate["Located"].asString() << " " << NewKotlinDir << endl;
                        break;
                    case 500:
                        throw domain_error("Unable to connect");
                }
                return 0;
            }

            using AppInstaller_funct_t = int(AppInstaller::*)(void);
            using map_funct_t = void(*)(void);

            map<string,AppInstaller_funct_t> PackagesFromSource {
                {"Eclipse IDE",&AppInstaller::InstallEclipse}
            };

            int MainInstaller(string Name) {
                string* Value = database.GetValueFromDB(Name,OS_NAME);
                if (Value[0] != "Not Found") {
                    result = system(Value[0].c_str());
                }
                else if (PackagesFromSource.find(Name) != PackagesFromSource.end()) {
                    result = (this->*(PackagesFromSource[Name]))();
                }
                return result;
            }
            AppInstaller() {
                UpdateData();
            }

            ~AppInstaller() {
                
            }
        private:
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

    string NewString(string sentence) {
        string new_sentence = "";
        if (haveString == "") {
            haveString = sentence;
            return new_sentence;
        }
        else {
            // Formatting string with two columns
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

    // Импортирование класса с функциями для установки приложений
    // AppInstaller Installer;
    // typedef void (AppInstaller::*funct_t)(void);
    // typedef std::map<std::string, funct_t> AppInstaller_func_map_t;
    // AppInstaller_func_map_t Packages = {
    //     {"Git",&AppInstaller::InstallGit}
    // };
    // map<string, function<void()>> Packages = {
    //     {"Git",[&installer](){installer.InstallGit();}}
    // };
    AppInstaller Installer;

    void InstallDevelopmentPack(string n) {
        UpdateData();
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n],"Windows");
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
            cout << InstallDelimiter << endl;
            cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
            output_func = Installer.MainInstaller(NamePackage);
            // output_func = (Installer.*(DevelopmentPack[NamePackage]))();
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
        cout << InstallDelimiter << endl;
        cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
        output_func = Installer.MainInstaller(NamePackage);
        // output_func = (Installer.*(DevelopmentPack[NamePackage]))(); 
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
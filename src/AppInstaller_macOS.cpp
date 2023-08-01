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
#include "AppInstaller_macOS.hpp"
#include <iostream>

using namespace std;

namespace macOS {

    size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }

    int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {

        if (TotalToDownload <= 0.0) {
            return 0;
        }

        int percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        if (TempPercentage != percentage && TempPercentage <= 100) {
            bar.update();
            TempPercentage = percentage;
        }
        return 0;
    }
    
    class AppInstaller {
        public:
            int InstallGit() {
                result = system("brew install --cask git");
                return result;
            }

            int InstallVSCode() {
                result = system("brew install --cask visual-studio-code");
                return result;
            }

            int InstallWebStorm() {
                result = system("brew install --cask webstorm");
                return result;
            }

            int InstallDocker() {
                result = system("brew install --cask docker");
                return result;
            }

            int InstallPostman() {
                result = system("brew install --cask postman");
                return result;
            }

            int InstallRubyMine() {
                result = system("brew install --cask rubymine");
                return result;
            }

            int InstallCLion() {
                result = system("brew install --cask clion");
                return result;
            }

            int InstallDataGrip() {
                result = system("brew install --cask datagrip");
                return result;
            }

            int InstallDataSpell() {
                result = system("brew install --cask dataspell");
                return result;
            }

            int InstallGoLand() {
                result = system("brew install --cask goland");
                return result;
                
            }

            int InstallIntelliJIDEACommunity() {
                result = system("brew install --cask intellij-idea-ce");
                return result;
            }

            int InstallIntelliJIDEAUltimate() {
                result = system("brew install --cask intellij-idea");
                return result;
            }

            int InstallRider() {
                result = system("brew install --cask rider");
                return result;
            }

            int InstallPhpStorm() {
                result = system("brew install --cask phpstorm");
                return result;
            }

            int InstallSpace() {
                result = system("brew install --cask jetbrains-space");
                return result;
            }

            int InstallPostgresql() {
                result = system("brew install postgresql@14");
                return result;
            }
            int InstallPgAdmin() {
                result = system("brew install --cask pgadmin4");
                return result;
            }

            int InstallNgrok() {
                result = system("brew install --cask ngrok");
                return result;
            }

            int InstallSublimeText() {
                result = system("brew install --cask sublime-text");
                return result;
            }

            int InstallPyCharmCommunity() {
                result = system("brew install --cask pycharm-ce");
                return result;
            }

            int InstallPyCharmProffessional() {
                result = system("brew install --cask pycharm");
                return result;
            }

            int InstallDiscord() {
                result = system("brew install --cask discord");
                return result;
            }

            int InstallTelegram() {
                result = system("brew install --cask telegram");
                return result;
            }

            int InstallNodeJS() {
                result = system("brew install node");
                return result;
            }

            int InstallGo() {
                result = system("brew install go");
                return result;
            }

            int InstallJDK_19() {
                result = system("brew install openjdk@19");
                return result;
            }

            int InstallJDK_18() {
                result = system("brew install openjdk@18");
                return result;
            }

            int InstallVisualStudio() {
                result = system("brew install --cask visual-studio");
                return result;
            }

            int InstallRust() {
                result = system("brew install rust");
                return result;
            }

            int InstallRuby() {
                result = system("brew install ruby");
                return result;
            }

            int InstallNetFramework() {
                result = system("brew install dotnet");
                return result;
            }

            int InstallPython3_9() {
                result = system("brew install python@3.9");
                return result;
            }
            
            int InstallPython3_10() {
                result = system("brew install python@3.10");
                return result;
            }

            int InstallPython3_11() {
                result = system("brew install python@3.11");
                return result;
            }

            int InstallVim() {
                result = system("winget install -e --id vim.vim");
                return result;
            }

            int InstallNeoVim() {
                result = system("brew install neovim");
                return result;
            }

            int InstallEclipse() {
                result = system("brew install --cask eclipse-ide");
                return result;
            }

            // int InstallPHP_

            AppInstaller() {
                
            }

            ~AppInstaller() {
                
            }
        private:
            int Download(string url, string dir)
            {
                try {
                    string name = (url.substr(url.find_last_of("/")));
                    string filename = dir + "/" + name.replace(name.find("/"), 1, "");
                    CURL* curl = curl_easy_init();
                    FILE* file = fopen(filename.c_str(), "wb");
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
                    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
                    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
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
            new_sentence = fmt::format("{:<40} {:<15}\n",haveString,sentence);
            haveString = "";
            return new_sentence;
        }
    }

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
    AppInstaller Installer;
    // typedef void (AppInstaller::*funct_t)(void);
    // typedef std::map<std::string, funct_t> AppInstaller_func_map_t;
    // AppInstaller_func_map_t Packages = {
    //     {"Git",&AppInstaller::InstallGit}
    // };
    // map<string, function<void()>> Packages = {
    //     {"Git",[&installer](){installer.InstallGit();}}
    // };
    using AppInstaller_funct_t = int(AppInstaller::*)(void);
    using map_funct_t = void(*)(void);

    map<string,AppInstaller_funct_t> Packages = {
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"JetBrains WebStorm",&AppInstaller::InstallWebStorm},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"JetBrains RubyMine",&AppInstaller::InstallRubyMine},
        {"JetBrains CLion",&AppInstaller::InstallCLion},
        {"JetBrains DataGrip",&AppInstaller::InstallDataGrip},
        {"JetBrains DataSpell",&AppInstaller::InstallDataSpell},
        {"JetBrains GoLand",&AppInstaller::InstallGoLand},
        {"JetBrains IntelliJ IDEA Community",&AppInstaller::InstallIntelliJIDEACommunity},
        {"JetBrains IntelliJ IDEA Ultimate",&AppInstaller::InstallIntelliJIDEAUltimate},
        {"JetBrains Rider",&AppInstaller::InstallRider},
        {"JetBrains PHPStorm",&AppInstaller::InstallPhpStorm},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"Ngrok",&AppInstaller::InstallNgrok},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"JetBrains PyCharm Community",&AppInstaller::InstallPyCharmCommunity},
        {"JetBrains PyCharm Community",&AppInstaller::InstallPyCharmProffessional},
        {"Discord",&AppInstaller::InstallDiscord},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Rust",&AppInstaller::InstallRust},
        {"Ruby",&AppInstaller::InstallRuby},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Go",&AppInstaller::InstallGo},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"🐍 Python 3.9",&AppInstaller::InstallPython3_9},
        {"🐍 Python 3.10",&AppInstaller::InstallPython3_10},
        {"🐍 Python 3.11",&AppInstaller::InstallPython3_11},
        {"NodeJS",&AppInstaller::InstallNodeJS},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> PythonDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"JetBrains PyCharm Community",&AppInstaller::InstallPyCharmCommunity},
        {"JetBrains PyCharm Proffessional",&AppInstaller::InstallPyCharmProffessional},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Docker",&AppInstaller::InstallDocker},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"Postman",&AppInstaller::InstallPostman},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"🐍 Python 3.9",&AppInstaller::InstallPython3_9},
        {"🐍 Python 3.10",&AppInstaller::InstallPython3_10},
        {"🐍 Python 3.11",&AppInstaller::InstallPython3_11},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> JavaScriptDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Docker",&AppInstaller::InstallDocker},
        {"JetBrains WebStorm",&AppInstaller::InstallWebStorm},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"NodeJS",&AppInstaller::InstallNodeJS},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> RustDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Rust",&AppInstaller::InstallRust},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> RubyDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"JetBrains RubyMine",&AppInstaller::InstallRubyMine},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Ruby",&AppInstaller::InstallRuby},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> CppDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> CSDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> CDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> GoDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"Go",&AppInstaller::InstallGo},
        {"GoLand",&AppInstaller::InstallGoLand},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> JavaDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"JDK 18",&AppInstaller::InstallJDK_18},
        {"JDK 19",&AppInstaller::InstallJDK_19},
        {"JetBrains IntelliJIDEA Community",&AppInstaller::InstallIntelliJIDEACommunity},
        {"JetBrains IntelliJIDEA Ultimate",&AppInstaller::InstallIntelliJIDEAUltimate},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> PhpDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"JetBrains PHP Storm",&AppInstaller::InstallPhpStorm},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> KotlinDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"JDK 18",&AppInstaller::InstallJDK_18},
        {"JDK 19",&AppInstaller::InstallJDK_19},
        {"JetBrains IntelliJIDEA Community",&AppInstaller::InstallIntelliJIDEACommunity},
        {"JetBrains IntelliJIDEA Ultimate",&AppInstaller::InstallIntelliJIDEAUltimate},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},
        {"Telegram",&AppInstaller::InstallTelegram},
        {"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},
        {"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Visual Studio for Mac",&AppInstaller::InstallVisualStudio},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<int,map<string,AppInstaller_funct_t>> DevelopmentPacks{
        {1,macOS::PythonDevelopmentTools},{2,macOS::JavaScriptDevelopmentTools},
        {3,macOS::CppDevelopmentTools},{4,macOS::JavaDevelopmentTools},
        {5,macOS::GoDevelopmentTools},{6,macOS::RustDevelopmentTools},
        {7,macOS::RubyDevelopmentTools},{8,macOS::CDevelopmentTools},
        {9,macOS::CSDevelopmentTools},{10,macOS::PhpDevelopmentTools},
        {11,macOS::KotlinDevelopmentTools}
    };

    void InstallDevelopmentPack(int n) {
        auto DevelopmentPack = DevelopmentPacks[n];
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
            output_func = (Installer.*(DevelopmentPack[NamePackage]))();
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
        output_func = (Installer.*(DevelopmentPack[NamePackage]))(); 
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
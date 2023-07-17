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

namespace Linux {
    class AppInstaller {
        public:
            int InstallGit() {
                result = system("winget install --id Git.Git -e --source winget");
                return result;
            }

            int InstallVSCode() {
                result = system("sudo snap install code --classic");
                return result;
            }

            int InstallWebStorm() {
                result = system("sudo snap install webstorm --classic");
                return result;
            }

            int InstallDocker() {
                result = system("sudo snap install docker");
                return result;
            }

            int InstallPostman() {
                result = system("sudo snap install postman");
                return result;
            }

            int InstallRubyMine() {
                result = system("sudo snap install rubymine --classic");
                return result;
            }

            int InstallCLion() {
                result = system("sudo snap install clion --classic");
                return result;
            }

            int InstallDataGrip() {
                cout << translate["InstallDataGrip"].asString() << endl;
                result = system("sudo snap install datagrip --classic");
                return result;
            }

            int InstallDataSpell() {
                result = system("sudo snap install dataspell --classic");
                return result;
            }

            int InstallGoLand() {
                result = system("sudo snap install goland --classic");
                return result;
                
            }

            int InstallIntelliJIDEACommunity() {
                result = system("sudo snap install intellij-idea-community --classic");
                return result;
            }

            int InstallIntelliJIDEAUltimate() {
                result = system("sudo snap install intellij-idea-ultimate --classic");
                return result;
            }

            int InstallRider() {
                result = system("sudo snap install rider --classic");
                return result;
            }

            int InstallPhpStorm() {
                result = system("sudo snap install phpstorm --classic");
                return result;
            }

            int InstallSpace() {
                result = system("sudo snap install space");
                return result;
            }

            int InstallPostgresql() {
                result = system("sudo snap install postgresql");
                return result;
            }
            int InstallPgAdmin() {
                result = system("winget install -e --id PostgreSQL.pgAdmin");
                return result;
            }

            int InstallNgrok() {
                result = system("sudo snap install ngrok");
                return result;
            }

            int InstallSublimeText() {
                result = system("sudo snap install sublime-text --classic");
                return result;
            }

            int InstallPyCharmCommunity() {
                result = system("sudo snap install pycharm-community --classic");
                return result;
            }

            int InstallPyCharmProffessional() {
                result = system("sudo snap install pycharm-professional --classic");
                return result;
            }

            int InstallDiscord() {
                result = system("sudo snap install discord");
                return result;
            }

            int InstallTelegram() {
                result = system("sudo snap install telegram-desktop");
                return result;
            }

            int InstallNodeJS() {
                result = system("sudo snap install node --classic");
                return result;
            }

            int InstallGo() {
                result = system("sudo snap install go --classic");
                return result;
            }

            int InstallJDK_19() {
                result = system("sudo snap install openjdk@19");
                return result;
            }

            int InstallJDK_18() {
                result = system("sudo snap install openjdk@18");
                return result;
            }

            int InstallRust() {
                result = system("sudo snap install rustup --classic");
                return result;
            }

            int InstallRuby() {
                result = system("sudo snap install ruby --classic");
                return result;
            }

            int InstallNetFramework() {
                result = system("sudo snap install dotnet-sdk --classic");
                return result;
            }

            int InstallVim() {
                result = system("sudo snap install vim-editor --beta");
                return result;
            }

            int InstallNeoVim() {
                result = system("sudo snap install nvim --classic");
                return result;
            }

            AppInstaller() {
                
            }

            ~AppInstaller() {
                
            }
        private:
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
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> CppDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> CSDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<string, AppInstaller_funct_t> CDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},
        {"VSCode",&AppInstaller::InstallVSCode},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin},
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
        {"Vim",&AppInstaller::InstallVim},
        {"NeoVim",&AppInstaller::InstallNeoVim}
    };

    map<int,map<string,AppInstaller_funct_t>> DevelopmentPacks{
        {1,Linux::PythonDevelopmentTools},{2,Linux::JavaScriptDevelopmentTools},
        {3,Linux::CppDevelopmentTools},{4,Linux::JavaDevelopmentTools},
        {5,Linux::GoDevelopmentTools},{6,Linux::RustDevelopmentTools},
        {7,Linux::RubyDevelopmentTools},{8,Linux::CDevelopmentTools},
        {9,Linux::CSDevelopmentTools},{10,Linux::PhpDevelopmentTools},
        {11,Linux::KotlinDevelopmentTools}
    };

    void InstallDevelopmentPack(auto DevelopmentPack) {
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
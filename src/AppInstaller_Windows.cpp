// #include "Logger.hpp"
#include "AppInstaller_Windows.hpp"
#include <iostream>

using namespace std;
// using namespace Json;
// using namespace Logger;

namespace Windows {
    class AppInstaller {
        public:
            void InstallGit() {
                cout << translate["InstallGit"].asString() << endl;
                system("winget install --id Git.Git -e --source winget");
                cout << translate["InstalledGit"].asString() << endl;
            }

            void InstallVSCode() {
                cout << translate["InstallVSCode"].asString() << endl;
                system("winget install -e --id Microsoft.VisualStudioCode");
                cout << translate["InstalledVSCode"] << endl;
            }

            void InstallWebStorm() {
                cout << translate["InstallWebStorm"].asString() << endl;
                system("winget install -e --id JetBrains.WebStorm");
                cout << translate["InstalledWebStorm"].asString() << endl;
            }

            void InstallDocker() {
                cout << translate["InstallDocker"].asString() << endl;
                system("winget install -e --id Docker.DockerDesktop");
                cout << translate["InstalledDocker"].asString() << endl;
            }

            void InstallPostman() {
                cout << translate["InstallPostman"].asString() << endl;
                system("winget install -e --id Postman.Postman");
                cout << translate["InstalledPostman"].asString() << endl;
            }

            void InstallRubyMine() {
                cout << translate["InstallRubyMine"].asString() << endl;
                system("winget install -e --id JetBrains.RubyMine");
                cout << translate["InstalledRubyMine"].asString() << endl;
            }

            void InstallCLion() {
                cout << translate["InstallCLion"].asString() << endl;
                system("winget install -e --id JetBrains.CLion");
                cout << translate["InstalledCLion"].asString() << endl;
            }

            void InstallDataGrip() {
                cout << translate["InstallDataGrip"].asString() << endl;
                system("winget install -e --id JetBrains.DataGrip");
                cout << translate["InstalledDataGrip"].asString() << endl;
            }

            void InstallDataSpell() {
                cout << translate["InstallDataSpell"].asString() << endl;
                system("winget install -e --id JetBrains.DataSpell");
                cout << translate["InstalledDataSpell"].asString() << endl;
            }

            void InstallGoLand() {
                cout << translate["InstallGoLand"].asString() << endl;
                system("winget install -e --id JetBrains.GoLand");
                cout << translate["InstalledGoLand"].asString() << endl;
            }

            void InstallIntelliJIDEACommunity() {
                cout << translate["InstallIntelliJIDEA Community"].asString() << endl;
                system("winget install -e --id JetBrains.IntelliJIDEA.Community");
                cout << translate["InstalledIntelliJIDEA Community"].asString() << endl;
            }

            void InstallIntelliJIDEAUltimate() {
                cout << translate["InstallIntelliJIDEA Ultimate"].asString() << endl;
                system("winget install -e --id JetBrains.IntelliJIDEA.Ultimate");
                cout << translate["InstalledIntelliJIDEA Ultimate"].asString() << endl;
            }

            void InstallRider() {
                cout << translate["InstallRider"].asString() << endl;
                    system("winget install -e --id JetBrains.Rider");
                    cout << translate["InstalledRider"].asString() << endl;
            }

            void InstallPhpStorm() {
                cout << translate["InstallPHPStorm"].asString() << endl;
                system("winget install -e --id JetBrains.PHPStorm");
                cout << translate["InstalledPHPStorm"].asString() << endl;
            }

            void InstallSpace() {
                cout << translate["InstallSpace"].asString() << endl;
                system("winget install -e --id JetBrains.Space");
                cout << translate["InstalledSpace"].asString() << endl;
            }

            void InstallPostgresql() {
                cout << translate["InstallPostgreSQL"].asString() << endl;
                system("winget install -e --id PostgreSQL.PostgreSQL");
                system("winget install -e --id PostgreSQL.pgAdmin");
                cout << translate["InstalledPostgreSQL"].asString() << endl;
            }

            void InstallNgrok() {
                cout << translate["InstallNgrok"].asString() << endl;
                system("winget install -e --id Ngrok.Ngrok");
                cout << translate["InstalledNgrok"].asString() << endl;
            }

            void InstallSublimeText() {
                cout << translate["InstalledSublimeText"].asString() << endl;
                system("winget install -e --id SublimeHQ.SublimeText.4");
                cout << translate["InstalledSublimeText"].asString() << endl;
            }

            void InstallPyCharmCommunity() {
                cout << translate["InstallPyCharm_CE"].asString() << endl;
                system("winget install -e --id JetBrains.PyCharm.Community");
                cout << translate["InstalledPyCharm_CE"].asString() << endl;
            }

            void InstallPyCharmProffessional() {
                cout << translate["InstallPyCharm_PE"].asString() << endl;
                system("winget install -e --id JetBrains.PyCharm.Professional");
                cout << translate["InstalledPyCharm_PE"].asString() << endl;
            }

            void InstallDiscord() {
                cout << translate["InstallDiscord"].asString() << endl;
                system("winget install -e --id Discord.Discord");
                cout << translate["InstalledDiscord"].asString() << endl;
            }

            void InstallTelegram() {
                cout << translate["InstallDiscord"].asString() << endl;
                system("winget install -e --id Telegram.TelegramDesktop");
                cout << translate["InstalledDiscord"].asString() << endl;
            }

        private:
    };

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
        // ensure that the file to be downloaded is not empty
        // because that would cause a division by zero error later on
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
        catch (string error) {
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
    using AppInstaller_funct_t = void(AppInstaller::*)(void);
    using map_funct_t = void(*)(void);
    map<string,AppInstaller_funct_t> Packages = {
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode},{"JetBrains WebStorm",AppInstaller::InstallWebStorm},{"Docker",AppInstaller::InstallDocker},
        {"Postman",AppInstaller::InstallPostman},{"JetBrains RubyMine",AppInstaller::InstallRubyMine},{"JetBrains CLion",AppInstaller::InstallCLion},
        {"JetBrains DataGrip",AppInstaller::InstallDataGrip},{"JetBrains DataSpell",AppInstaller::InstallDataSpell},{"JetBrains GoLand",AppInstaller::InstallGoLand},
        {"JetBrains IntelliJ IDEA Community",AppInstaller::InstallIntelliJIDEACommunity},{"JetBrains IntelliJ IDEA Ultimate",AppInstaller::InstallIntelliJIDEAUltimate},
        {"JetBrains Rider",AppInstaller::InstallRider},{"JetBrains PHPStorm",AppInstaller::InstallPhpStorm},{"JetBrains Space",AppInstaller::InstallSpace},
        {"Postgresql",AppInstaller::InstallPostgresql},{"Ngrok",AppInstaller::InstallNgrok},{"Sublime Text",AppInstaller::InstallSublimeText},{"JetBrains PyCharm Community",AppInstaller::InstallPyCharmCommunity},
        {"JetBrains PyCharm Community",AppInstaller::InstallPyCharmProffessional},{"Discord",AppInstaller::InstallDiscord},{"Telegram",AppInstaller::InstallTelegram}
    };

    map<string, AppInstaller_funct_t> PythonDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Python 3.9", InstallPython3_9 }, { "Python 3.10", InstallPython3_10 }, { "Python 3.11", InstallPython3_11 },
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "PyCharm Community", InstallPyCharmCommunity },
        // { "PyCharm Proffessional", InstallPyCharmProffessional }, { "Sublime Text", InstallSublimeText }, { "Docker", InstallDocker },
        // { "Postman", InstallPostman }, { "Postgresql", InstallPostgresql }, { "MongoDB", InstallMongoDB },
        // { "MongoDB Atlas", InstallMongoDBAtlas }, { "MongoDB Compass", InstallMongoDBCompass },
        // { "Wget", InstallWget }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        // { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "GitHub Desktop", InstallGitHubDesktop },
        // { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes }, { "JetBrains Fleet", InstallFleet }, { "Visual Studio Proffessional", InstallVisualStudioProffessional },
        // { "Visual Studio Community", InstallVisualStudioCommunity }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Slack", InstallSlack },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> JavaScriptDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "JetBrains WebStorm", InstallWebStorm },
        // { "Docker", InstallDocker }, { "Postman", InstallPostman }, { "JetBrains Fleet", InstallFleet },
        // { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        // { "Discord", InstallDiscord }, { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer },
        // { "MongoDB Compass", InstallMongoDBCompass }, { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        // { "NodeJS", InstallNodeJS }, { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi },
        // { "Kubernetes", InstallKubernetes }, { "Visual Studio Proffessional", InstallVisualStudioProffessional },
        // { "Visual Studio Community", InstallVisualStudioCommunity }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        // { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> RustDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker },
        // { "Postman", InstallPostman }, { "JetBrains Fleet", InstallFleet }, { "Wget", InstallWget },
        // { "Sublime Text", InstallSublimeText }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        // { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi },
        // { "Kubernetes", InstallKubernetes }, { "Rust", InstallRust }, { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        // { "NodeJS", InstallNodeJS }, { "MongoDB Compass", InstallMongoDBCompass }, { "Ngrok", InstallNgrok }, { "Kubernetes", InstallKubernetes },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        // { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> RubyDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Ruby", InstallRuby }, { "RubyMine", InstallRubyMine }, { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker },
        // { "Postman", InstallPostman }, { "JetBrains Fleet", InstallFleet }, { "Wget", InstallWget },
        // { "Sublime Text", InstallSublimeText }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        // { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi },
        // { "Kubernetes", InstallKubernetes }, { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        // { "NodeJS", InstallNodeJS }, { "MongoDB Compass", InstallMongoDBCompass }, { "Ngrok", InstallNgrok }, { "Kubernetes", InstallKubernetes },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        // { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> CppDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "CLion", InstallCLion }, { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        // { "JetBrains Fleet", InstallFleet }, { "Sublime Text", InstallSublimeText }, { "Ngrok", InstallNgrok },
        // { "Wget", InstallWget }, { "Docker", InstallDocker }, { "Discord", InstallDiscord },
        // { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer },
        // { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "JetBrains Space", InstallSpace },
        // { "JetBrains ToolBox", InstallToolBox }, { "MSYS2", InstallMSYS2 }, { "Postman", InstallPostman }, { "MongoDB Compass", InstallMongoDBCompass },
        // { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "Postgresql", InstallPostgresql },
        // { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> CSDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "JetBrains Rider", InstallRider }, { ".Net Framework", InstallNetFramework }, { "Git", InstallGit }, { "VSCode", InstallVSCode },
        // { "Postman", InstallPostman }, { "Nuget", InstallNuget }, { "GitHub Desktop", InstallGitHubDesktop },
        // { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes }, { "Visual Studio Proffessional", InstallVisualStudioProffessional },
        // { "Visual Studio Community", InstallVisualStudioCommunity }, { "JetBrains Fleet", InstallFleet }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        // { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        // { "JetBrains dotUltimate", InstalldotUltimate }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        // { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "Postgresql", InstallPostgresql },
        // { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome },
        // {".NET SDK 7.0",InstallNetSDK_7},{".NET SDK 6.0",InstallNetSDK_6},{".NET Runtime 7.0",InstallNetRuntime_7}
    };
    map<string, AppInstaller_funct_t> CDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "MSYS2", InstallMSYS2 }, { "Nuget", InstallNuget },
        // { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        // { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        // { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText }, { "JetBrains Fleet", InstallFleet },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Slack", InstallSlack },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> GoDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "GoLang", InstallGoLang }, { "JetBrains Fleet", InstallFleet }, { "GoLand", InstallGoLand },
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        // { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        // { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        // { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        // { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "GitHub Desktop", InstallGitHubDesktop },
        // { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes }, { "Slack", InstallSlack },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> JavaDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "JDK 18", InstallJDK_18 }, { "JDK 19", InstallJDK_19 },
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        // { "JetBrains Fleet", InstallFleet }, { "JetBrains IntelliJ Community", InstallIntelliJCommunity }, { "JetBrains IntelliJ Ultimate", InstallIntelliJUltimate },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        // { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        // { "Discord", InstallDiscord }, { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        // { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        // { "Nuget", InstallNuget }, { "Slack", InstallSlack },
        // { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }, { "Android Studio", InstallAndroidStudio },
        // { "Eclipse", InstallEclipse }, { "Kotlin", InstallKotlin }
    };
    map<string, AppInstaller_funct_t> PhpDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        // { "JetBrains Fleet", InstallFleet }, { "JetBrains PhpStorm", InstallPhpStorm }, { "Postgresql", InstallPostgresql },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        // { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        // { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        // { "MongoDB Compass", InstallMongoDBCompass }, { "Slack", InstallSlack },
        // { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        // { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        // { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, AppInstaller_funct_t> KotlinDevelopmentTools{
        {"Git",AppInstaller::InstallGit},{"VSCode",AppInstaller::InstallVSCode}
        // { "Kotlin", InstallKotlin }, { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        // { "JDK 18", InstallJDK_18 }, { "JDK 19", InstallJDK_19 }, { "JetBrains Fleet", InstallFleet }, { "JetBrains IntelliJ Community", InstallIntelliJCommunity }, { "JetBrains IntelliJ Ultimate", InstallIntelliJUltimate },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        // { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        // { "Discord", InstallDiscord }, { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        // { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        // { "Nuget", InstallNuget }, { "Slack", InstallSlack },
        // { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }, { "Android Studio", InstallAndroidStudio },
        // { "Eclipse", InstallEclipse }
    };

    void PythonDevelopment()
    {
        for (const auto& element : PythonDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void JavaScriptDevelopment()
    {
        for (const auto& element : JavaScriptDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void RustDevelopment()
    {
        for (const auto& element : RustDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void RubyDevelopment()
    {
        for (const auto& element : RubyDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void CppDevelopment()
    {
        for (const auto& element : CppDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void CSDevelopment()
    {
        for (const auto& element : CSDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void CDevelopment()
    {
        for (const auto& element : CDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void GoDevelopment()
    {
        for (const auto& element : GoDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void JavaDevelopment()
    {
        for (const auto& element : JavaDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void PHPDevelopment()
    {
        for (const auto& element : PhpDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    void KotlinDevelopment()
    {
        for (const auto& element : KotlinDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            // (Installer.*(element.second))();
        }
    }
    map<int, map_funct_t> DevelopmentPacks{
        {1,Windows::PythonDevelopment},{2,Windows::JavaDevelopment},
        {3,Windows::CppDevelopment},{4,Windows::JavaDevelopment},
        {5,Windows::GoDevelopment},{6,Windows::RustDevelopment},
        {7,Windows::RubyDevelopment},{8,Windows::CDevelopment},
        {9,Windows::CSDevelopment},{10,Windows::PHPDevelopment},
        {11,Windows::KotlinDevelopment}
    };
}
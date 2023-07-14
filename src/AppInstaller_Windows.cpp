// #include "Logger.hpp"
#include "AppInstaller_Windows.hpp"
#include <iostream>

using namespace std;

namespace Windows {
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
                cout << translate["InstallDataGrip"].asString() << endl;
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
            new_sentence = format("{:<40} {:<15}\n",haveString,sentence);
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"JetBrains WebStorm",&AppInstaller::InstallWebStorm},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"JetBrains RubyMine",&AppInstaller::InstallRubyMine},{"JetBrains CLion",&AppInstaller::InstallCLion},
        {"JetBrains DataGrip",&AppInstaller::InstallDataGrip},{"JetBrains DataSpell",&AppInstaller::InstallDataSpell},{"JetBrains GoLand",&AppInstaller::InstallGoLand},
        {"JetBrains IntelliJ IDEA Community",&AppInstaller::InstallIntelliJIDEACommunity},{"JetBrains IntelliJ IDEA Ultimate",&AppInstaller::InstallIntelliJIDEAUltimate},
        {"JetBrains Rider",&AppInstaller::InstallRider},{"JetBrains PHPStorm",&AppInstaller::InstallPhpStorm},{"JetBrains Space",&AppInstaller::InstallSpace},
        {"Postgresql",&AppInstaller::InstallPostgresql},{"Ngrok",&AppInstaller::InstallNgrok},{"Sublime Text",&AppInstaller::InstallSublimeText},{"JetBrains PyCharm Community",&AppInstaller::InstallPyCharmCommunity},
        {"JetBrains PyCharm Community",&AppInstaller::InstallPyCharmProffessional},{"Discord",&AppInstaller::InstallDiscord},{"Telegram",&AppInstaller::InstallTelegram},{"Rust",&AppInstaller::InstallRust},
        {"Ruby",&AppInstaller::InstallRuby},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
    };

    map<string, AppInstaller_funct_t> PythonDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"JetBrains PyCharm Community",&AppInstaller::InstallPyCharmCommunity},
        {"JetBrains PyCharm Proffessional",&AppInstaller::InstallPyCharmProffessional},{"Sublime Text",&AppInstaller::InstallSublimeText},{"Docker",&AppInstaller::InstallDocker},
        {"Discord",&AppInstaller::InstallDiscord},{"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},
        {"Postgresql",&AppInstaller::InstallPostgresql},{"Postman",&AppInstaller::InstallPostman},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Sublime Text",&AppInstaller::InstallSublimeText},{"Docker",&AppInstaller::InstallDocker},
        {"JetBrains WebStorm",&AppInstaller::InstallWebStorm},{"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},
        {"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"Discord",&AppInstaller::InstallDiscord},
        {"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Sublime Text",&AppInstaller::InstallSublimeText},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"JetBrains RubyMine",&AppInstaller::InstallRubyMine},
        {"Discord",&AppInstaller::InstallDiscord},{"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Sublime Text",&AppInstaller::InstallSublimeText},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
        // { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "MSYS2", InstallMSYS2 }, { "Nuget", InstallNuget },
        // { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        // { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        // { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText }, { "JetBrains Fleet", InstallFleet },
        // { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Slack", InstallSlack },
        // { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };

    map<string, AppInstaller_funct_t> GoDevelopmentTools{
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"Go",&AppInstaller::InstallGo},
        {"GoLand",&AppInstaller::InstallGoLand},{"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},{"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"JDK 18",&AppInstaller::InstallJDK_18},
        {"JDK 19",&AppInstaller::InstallJDK_19},{"JetBrains IntelliJIDEA Community",&AppInstaller::InstallIntelliJIDEACommunity},
        {"JetBrains IntelliJIDEA Ultimate",&AppInstaller::InstallIntelliJIDEAUltimate},{"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},{"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"JetBrains PHP Storm",&AppInstaller::InstallPhpStorm},
        {"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},{"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Sublime Text",&AppInstaller::InstallSublimeText},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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
        {"Git",&AppInstaller::InstallGit},{"VSCode",&AppInstaller::InstallVSCode},{"JDK 18",&AppInstaller::InstallJDK_18},
        {"JDK 19",&AppInstaller::InstallJDK_19},{"JetBrains IntelliJIDEA Community",&AppInstaller::InstallIntelliJIDEACommunity},
        {"JetBrains IntelliJIDEA Ultimate",&AppInstaller::InstallIntelliJIDEAUltimate},{"Sublime Text",&AppInstaller::InstallSublimeText},
        {"Discord",&AppInstaller::InstallDiscord},{"JetBrains Space",&AppInstaller::InstallSpace},{"Telegram",&AppInstaller::InstallTelegram},{"Docker",&AppInstaller::InstallDocker},
        {"Postman",&AppInstaller::InstallPostman},{"Postgresql",&AppInstaller::InstallPostgresql},{"PgAdmin 4",&AppInstaller::InstallPgAdmin}
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

     map<int,map<string,AppInstaller_funct_t>> DevelopmentPacks{
        {1,Windows::PythonDevelopmentTools},{2,Windows::JavaScriptDevelopmentTools},
        {3,Windows::CppDevelopmentTools},{4,Windows::JavaDevelopmentTools},
        {5,Windows::GoDevelopmentTools},{6,Windows::RustDevelopmentTools},
        {7,Windows::RubyDevelopmentTools},{8,Windows::CDevelopmentTools},
        {9,Windows::CSDevelopmentTools},{10,Windows::PhpDevelopmentTools},
        {11,Windows::KotlinDevelopmentTools}
    };

    void InstallDevelopmentPack(auto DevelopmentPack) {
        map<int,string> EnumeratePackages;
        for (int i = 1;const auto &element:DevelopmentPack) {
            EnumeratePackages.insert(pair<int,string>(i,element.first));
            string NamePackage = to_string(i) + ". " + element.first;
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
            string name = EnumeratePackages[stoi(token)];
            cout << translate["Installing"].asString() << " " << name << " ..." << endl;
            output_func = (Installer.*(DevelopmentPack[name]))();
            if (output_func == 0) {
                cout << "✅ " << name << " " << translate["Installed"].asString() << endl;
                string SuccessText = name + " " + translate["Installed"].asString();
                logger.Success(SuccessText.c_str());
            }
            else {
                string ErrorText = translate["ErrorInstall"].asString() + " " + name;
                logger.Error(ErrorText.c_str());
            }
            SelectPackages.erase(0, pos + delimiter.length());
        }
        string NamePackage = EnumeratePackages[stoi(SelectPackages)];
        (Installer.*(DevelopmentPack[NamePackage]))();
    }
}
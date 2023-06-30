#pragma warning( push )
#pragma warning( pop )
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <filesystem>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "Progressbar.hpp"

using namespace std;
// using namespace std::filesystem;

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
// cout << "Linux" << endl;
#elif __FreeBSD__
// cout << "FreeBSD" << endl;
#elif __APPLE__
// cout << "macOS" << endl;
#elif _WIN32
    #include <Windows.h>
#endif

namespace AppInstaller {
    using funct_t = void (*)(void);
    // Переменные
    bool Install;
    string OS_NAME;
    string NameDistribution;
    string Answer;
    string new_sentence;
    map<string, funct_t> Tools;
    const string TrueVarious[3] = { "yes", "y", "1"};
    const string KotlinUrl = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
    const string PHPUrl = "https://windows.php.net/downloads/releases/php-8.2.7-nts-Win32-vs16-x64.zip";
    const string WgetUrl = "https://eternallybored.org/misc/wget/1.21.4/64/wget.exe";
    string ProjectDir = std::filesystem::current_path().generic_string();
    string KotlinDir = ProjectDir + "/Programms/Kotlin";
    string PHPDir = ProjectDir + "/Programms/PHP";
    string WgetDir = ProjectDir + "/Programms/Wget";
    string NewKotlinDir = "C:\\Kotlin";
    string NewPHPDir = "C:\\PHP";
    string NewWgetDir = "C:\\Wget";
    string AddKotlinPathScript = ProjectDir + "/Scripts/AddKotlinPath.ps1";
    string AddPHPPathScript = ProjectDir + "/Scripts/AddPHPPathScript.ps1";
    string AddWgetPathScript = ProjectDir + "/Scripts/AddWgetPath.ps1";
    string TypeInstall = "open";
    map<int, string> Languages{
        {1,"Python"},{2,"JavaScript"},{3,"C++"},{4,"Java"},
        {5,"Go"},{6,"Rust"},{7,"Ruby"},{8,"C"},
        {9,"C#"},{10,"PHP"},{11,"Kotlin"}
    };
    progressbar bar(100);
    int TempPercentage = 0;

    // Функции
    string to_lower(string sentence)
    {
        new_sentence = "";
        for (int i = 0; i < sizeof(sentence); i++) {
            new_sentence += tolower(sentence[i]);
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
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
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
    void InstallGit()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Git (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Git ..." << endl;
                    system("winget install --id Git.Git -e --source winget");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Git ..." << endl;
                    system("brew install --cask git");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Git ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Git ..." << endl;
                system("winget install --id Git.Git -e --source winget");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Git ..." << endl;
                system("brew install --cask git");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Git ..." << endl;
            }
        }
    }
    void InstallVSCode()
    {   if (TypeInstall == "open") {
            cout << "Вы хотите установить VSCode (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка VSCode ..." << endl;
                    system("winget install -e --id Microsoft.VisualStudioCode");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка VSCode ..." << endl;
                    system("brew install --cask visual-studio-code");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка VSCode ..." << endl;
                }
            }
        
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка VSCode ..." << endl;
                system("winget install -e --id Microsoft.VisualStudioCode");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка VSCode ..." << endl;
                system("brew install --cask visual-studio-code");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка VSCode ..." << endl;
            }
        }
    }
    void InstallWebStorm()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains WebStorm (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains WebStorm ..." << endl;
                    system("winget install -e --id JetBrains.WebStorm");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains WebStorm ..." << endl;
                    system("brew install --cask webstorm");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains WebStorm ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains WebStorm ..." << endl;
                system("winget install -e --id JetBrains.WebStorm");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains WebStorm ..." << endl;
                system("brew install --cask webstorm");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains WebStorm ..." << endl;
            }
        }
    }
    void InstallDocker()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Docker (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Docker ..." << endl;
                    system("winget install -e --id Docker.DockerDesktop");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Docker ..." << endl;
                    system("brew install --cask docker");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Docker ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Docker ..." << endl;
                system("winget install -e --id Docker.DockerDesktop");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Docker ..." << endl;
                system("brew install --cask docker");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Docker ..." << endl;
            }
        }
    }
    void InstallPostman()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Postman (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Postman ..." << endl;
                    system("winget install -e --id Postman.Postman");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Postman ..." << endl;
                    system("brew install --cask postman");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Postman ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Postman ..." << endl;
                system("winget install -e --id Postman.Postman");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Postman ..." << endl;
                system("brew install --cask postman");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Postman ..." << endl;
            }
        }
    }
    void InstallRubyMine()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains RubyMine (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains RubyMine ..." << endl;
                    system("winget install -e --id JetBrains.RubyMine");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains RubyMine ..." << endl;
                    system("brew install --cask rubymine");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains RubyMine ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains RubyMine ..." << endl;
                system("winget install -e --id JetBrains.RubyMine");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains RubyMine ..." << endl;
                system("brew install --cask rubymine");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains RubyMine ..." << endl;
            }
        }
    }
    void InstallAqua()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains Aqua (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains Aqua ..." << endl;
                    system("winget install -e --id JetBrains.Aqua.EAP");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains Aqua ..." << endl;
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains Aqua ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains Aqua ..." << endl;
                system("winget install -e --id JetBrains.Aqua.EAP");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains Aqua ..." << endl;
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains Aqua ..." << endl;
            }
        }
    }
    void InstallCLion()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains CLion (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains CLion ..." << endl;
                    system("winget install -e --id JetBrains.CLion");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains CLion ..." << endl;
                    system("brew install --cask clion");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains CLion ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains CLion ..." << endl;
                system("winget install -e --id JetBrains.CLion");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains CLion ..." << endl;
                system("brew install --cask clion");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains CLion ..." << endl;
            }
        }
    }
    void InstallDataGrip()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains DataGrip (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains DataGrip ..." << endl;
                    system("winget install -e --id JetBrains.DataGrip");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains DataGrip ..." << endl;
                    system("brew install --cask datagrip");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains DataGrip ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains DataGrip ..." << endl;
                system("winget install -e --id JetBrains.DataGrip");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains DataGrip ..." << endl;
                system("brew install --cask datagrip");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains DataGrip ..." << endl;
            }
        }
    }
    void InstallDataSpell()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains DataSpell (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains DataSpell ..." << endl;
                    system("winget install -e --id JetBrains.DataSpell");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains DataSpell ..." << endl;
                    system("brew install --cask dataspell");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains DataSpell ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains DataSpell ..." << endl;
                system("winget install -e --id JetBrains.DataSpell");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains DataSpell ..." << endl;
                system("brew install --cask dataspell");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains DataSpell ..." << endl;
            }
        }
    }
    void InstallFleet()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains Fleet (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains Fleet ..." << endl;
                    system("winget install -e --id JetBrains.FleetLauncher.Preview");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains Fleet ..." << endl;
                    system("brew install --cask fleet");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains Fleet ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains Fleet ..." << endl;
                system("winget install -e --id JetBrains.FleetLauncher.Preview");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains Fleet ..." << endl;
                system("brew install --cask fleet");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains Fleet ..." << endl;
            }
        }
    }
    void InstallGoLand()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains GoLand (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains GoLand ..." << endl;
                    system("winget install -e --id JetBrains.GoLand");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains GoLand ..." << endl;
                    system("brew install --cask goland");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains GoLand ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains GoLand ..." << endl;
                system("winget install -e --id JetBrains.GoLand");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains GoLand ..." << endl;
                system("brew install --cask goland");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains GoLand ..." << endl;
            }
        }
    }
    void InstallIntelliJCommunity()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains IntelliJIDEA Community (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains IntelliJIDEA Community ..." << endl;
                    system("winget install -e --id JetBrains.IntelliJIDEA.Community");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains IntelliJIDEA Community ..." << endl;
                    system("brew install --cask intellij-idea-ce");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains IntelliJIDEA Community ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains IntelliJIDEA Community ..." << endl;
                system("winget install -e --id JetBrains.IntelliJIDEA.Community");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains IntelliJIDEA Community ..." << endl;
                system("brew install --cask intellij-idea-ce");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains IntelliJIDEA Community ..." << endl;
            }
        }
    }
    void InstallIntelliJUltimate()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains IntelliJIDEA Ultimate (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains IntelliJIDEA Ultimate ..." << endl;
                    system("winget install -e --id JetBrains.IntelliJIDEA.Ultimate");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains IntelliJIDEA Ultimate ..." << endl;
                    system("brew install --cask intellij-idea");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains IntelliJIDEA Ultimate ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains IntelliJIDEA Ultimate ..." << endl;
                system("winget install -e --id JetBrains.IntelliJIDEA.Ultimate");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains IntelliJIDEA Ultimate ..." << endl;
                system("brew install --cask intellij-idea");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains IntelliJIDEA Ultimate ..." << endl;
            }
        }
    }
    void InstallReSharper()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains ReSharper (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains ReSharper ..." << endl;
                    system("winget install -e --id JetBrains.ReSharper");
                }
                else if (OS_NAME == "macOS") {
                    
                }
                else if (OS_NAME == "Linux") {
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                system("winget install -e --id JetBrains.ReSharper");
            }
            else if (OS_NAME == "macOS") {
            }
            else if (OS_NAME == "Linux") {
            }
        }
    }
    void InstallRider()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains Rider (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains Rider ..." << endl;
                    system("winget install -e --id JetBrains.Rider");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains Rider ..." << endl;
                    system("brew install --cask rider");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains Rider ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains Rider ..." << endl;
                system("winget install -e --id JetBrains.Rider");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains Rider ..." << endl;
                system("brew install --cask rider");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains Rider ..." << endl;
            }
        }
    }
    void InstallPhpStorm()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains PHPStorm (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains PHPStorm ..." << endl;
                    system("winget install -e --id JetBrains.PHPStorm");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains PHPStorm ..." << endl;
                    system("brew install --cask phpstorm");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains PHPStorm ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains PHPStorm ..." << endl;
                system("winget install -e --id JetBrains.PHPStorm");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains PHPStorm ..." << endl;
                system("brew install --cask phpstorm");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains PHPStorm ..." << endl;
            }
        }
    }
    void InstalldotUltimate()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains dotUltimate (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains dotUltimate ..." << endl;
                    system("winget install -e --id JetBrains.dotUltimate");
                }
                else if (OS_NAME == "macOS") {
                }
                else if (OS_NAME == "Linux") {
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                system("winget install -e --id JetBrains.dotUltimate");
            }
            else if (OS_NAME == "macOS") {
            }
            else if (OS_NAME == "Linux") {
            }
        }
    }
    void InstallSpace()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains Space (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains Space ..." << endl;
                    system("winget install -e --id JetBrains.Space");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains Space ..." << endl;
                    system("brew install --cask jetbrains-space");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains Space ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains Space ..." << endl;
                system("winget install -e --id JetBrains.Space");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains Space ..." << endl;
                system("brew install --cask jetbrains-space");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains Space ..." << endl;
            }
        }
    }
    void InstallToolBox()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains Toolbox (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains Toolbox ..." << endl;
                    system("winget install -e --id JetBrains.Toolbox");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains Toolbox ..." << endl;
                    system("brew install --cask jetbrains-toolbox");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains Toolbox ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains Toolbox ..." << endl;
                system("winget install -e --id JetBrains.Toolbox");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains Toolbox ..." << endl;
                system("brew install --cask jetbrains-toolbox");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains Toolbox ..." << endl;
            }
        }
    }
    void InstallPostgresql()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить PostgreSQL (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка PostgreSQL ..." << endl;
                    system("winget install -e --id PostgreSQL.PostgreSQL");
                    system("winget install -e --id PostgreSQL.pgAdmin");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка PostgreSQL ..." << endl;
                    system("brew install postgresql@14");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка PostgreSQL ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка PostgreSQL ..." << endl;
                system("winget install -e --id PostgreSQL.PostgreSQL");
                system("winget install -e --id PostgreSQL.pgAdmin");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка PostgreSQL ..." << endl;
                system("brew install postgresql@14");
                system("brew install --cask pgadmin4");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка PostgreSQL ..." << endl;
            }
        }
    }
    void InstallCLink()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Clink (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Clink ..." << endl;
                    system("winget install -e --id chrisant996.Clink");
                }
                else if (OS_NAME == "macOS") {
                }
                else if (OS_NAME == "Linux") {
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Clink ..." << endl;
                system("winget install -e --id chrisant996.Clink");
            }
            else if (OS_NAME == "macOS") {
            }
            else if (OS_NAME == "Linux") {
            }
        }
    }
    void InstallNgrok()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Ngrok (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Ngrok ..." << endl;
                    system("winget install -e --id Ngrok.Ngrok");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Ngrok ..." << endl;
                    system("brew install --cask ngrok");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Ngrok ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Ngrok ..." << endl;
                system("winget install -e --id Ngrok.Ngrok");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Ngrok ..." << endl;
                system("brew install --cask ngrok");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Ngrok ..." << endl;
            }
        }
    }
    void InstallWget()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Wget? (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Wget ..." << endl;
                    system("winget install -e --id JernejSimoncic.Wget");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Wget ..." << endl;
                    system("brew install wget");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Wget ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Wget ..." << endl;
                system("winget install -e --id JernejSimoncic.Wget");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Wget ..." << endl;
                system("brew install wget");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Wget ..." << endl;
            }
        }
    }
    void InstallSublimeText()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить SublimeText (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка SublimeText ..." << endl;
                    system("winget install -e --id SublimeHQ.SublimeText.4");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка SublimeText ..." << endl;
                    system("brew install --cask sublime-text");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка SublimeText ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка SublimeText ..." << endl;
                system("winget install -e --id SublimeHQ.SublimeText.4");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка SublimeText ..." << endl;
                system("brew install --cask sublime-text");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка SublimeText ..." << endl;
            }
        }
    }
    void InstallPyCharmCommunity()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains PyCharm Community (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains PyCharm Community ..." << endl;
                    system("winget install -e --id JetBrains.PyCharm.Community");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains PyCharm Community ..." << endl;
                    system("brew install --cask pycharm-ce");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains PyCharm Community ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JetBrains PyCharm Community ..." << endl;
                system("winget install -e --id JetBrains.PyCharm.Community");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains PyCharm Community ..." << endl;
                system("brew install --cask pycharm-ce");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains PyCharm Community ..." << endl;
            }
        }
    }
    void InstallPyCharmProffessional()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JetBrains PyCharm Professional (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JetBrains PyCharm Professional ..." << endl;
                    system("winget install -e --id JetBrains.PyCharm.Professional");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JetBrains PyCharm ..." << endl;
                    system("brew install --cask pycharm");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JetBrains PyCharm Professional ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                system("winget install -e --id JetBrains.PyCharm.Professional");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JetBrains PyCharm ..." << endl;
                system("brew install --cask pycharm");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JetBrains PyCharm Professional ..." << endl;
            }
        }
    }
    void InstallPowerToys()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Microsoft PowerToys (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Microsoft PowerToys ..." << endl;
                    system("winget install -e --id Microsoft.PowerToys");
                }
                else if (OS_NAME == "macOS") {
                }
                else if (OS_NAME == "Linux") {
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Microsoft PowerToys ..." << endl;
                system("winget install -e --id Microsoft.PowerToys");
            }
            else if (OS_NAME == "macOS") {
                cout << "Microsoft PowerToys не предназначена для macOS и устанавливается только на Windows" << endl;
            }
            else if (OS_NAME == "Linux") {
                cout << "Microsoft PowerToys не предназначена для macOS и устанавливается только на Windows" << endl;
            }
        }
    }
    void InstallDiscord()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Discord (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Discord ..." << endl;
                    system("winget install -e --id Discord.Discord");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Discord ..." << endl;
                    system("brew install --cask discord");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Discord ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Discord ..." << endl;
                system("winget install -e --id Discord.Discord");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Discord ..." << endl;
                system("brew install --cask discord");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Discord ..." << endl;
            }
        }
    }
    void InstallTelegram()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Telegram (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Telegram ..." << endl;
                    system("winget install -e --id Telegram.TelegramDesktop");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Telegram ..." << endl;
                    system("brew install --cask telegram");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Telegram ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Telegram ..." << endl;
                system("winget install -e --id Telegram.TelegramDesktop");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Telegram ..." << endl;
                system("brew install --cask telegram");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Telegram ..." << endl;
            }
        }
    }
    void InstallVNCServer()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить RealVNC Server (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка RealVNC Server ..." << endl;
                    system("winget install -e --id RealVNC.VNCServer");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка RealVNC Server ..." << endl;
                    system("brew install --cask vn-server");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка RealVNC Server ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка RealVNC Server ..." << endl;
                system("winget install -e --id RealVNC.VNCServer");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка RealVNC Server ..." << endl;
                system("brew install --cask vn-server");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка RealVNC Server ..." << endl;
            }
        }
    }
    void InstallVNCViewer()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить RealVNC Viewer (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка RealVNC Viewer ..." << endl;
                    system("winget install -e --id RealVNC.VNCViewer");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка RealVNC Viewer ..." << endl;
                    system("brew install --cask vn-viewer");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка RealVNC Viewer ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка RealVNC Viewer ..." << endl;
                system("winget install -e --id RealVNC.VNCViewer");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка RealVNC Viewer ..." << endl;
                system("brew install --cask vn-viewer");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка RealVNC Viewer ..." << endl;
            }
        }
    }
    void InstallMongoDBCompass()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить MongoDB Compass (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка MongoDB Compass ..." << endl;
                    system("winget install -e --id MongoDB.Compass.Full");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка MongoDB Compass ..." << endl;
                    system("brew install --cask mongodb-compass");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка MongoDB Compass ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка MongoDB Compass ..." << endl;
                system("winget install -e --id MongoDB.Compass.Full");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка MongoDB Compass ..." << endl;
                system("brew install --cask mongodb-compass");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка MongoDB Compass ..." << endl;
            }
        }
    }
    void InstallMongoDB()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить MongoDB Server (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка MongoDB Server ..." << endl;
                    system("winget install -e --id MongoDB.Server");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка MongoDB Server ..." << endl;
                    system("brew install mongodb-community");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка MongoDB Server ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка MongoDB Server ..." << endl;
                system("winget install -e --id MongoDB.Server");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка MongoDB Server ..." << endl;
                system("brew install mongodb-community");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка MongoDB Server ..." << endl;
            }
        }
    }
    void InstallMongoDBAtlas()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить MongoDB MongoDBAtlasCLI (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка MongoDB Atlas ..." << endl;
                    system("winget install -e --id MongoDB.MongoDBAtlasCLI");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка MongoDB Atlas ..." << endl;
                    system("brew install mongodb-atlas-cli");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка MongoDB Atlas ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка MongoDB Atlas ..." << endl;
                system("winget install -e --id MongoDB.MongoDBAtlasCLI");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка MongoDB Atlas ..." << endl;
                system("brew install mongodb-atlas-cli");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка MongoDB Atlas ..." << endl;
            }
        }
    }
    void InstallNodeJS()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить NodeJS (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка NodeJS ..." << endl;
                    system("winget install -e --id OpenJS.NodeJS");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка NodeJS ..." << endl;
                    system("brew install node");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка NodeJS ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка NodeJS ..." << endl;
                system("winget install -e --id OpenJS.NodeJS");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка NodeJS ..." << endl;
                system("brew install node");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка NodeJS ..." << endl;
            }
        }
    }
    void InstallGoLang()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить GoLang 1.18 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка GoLang ..." << endl;
                    system("winget install -e --id GoLang.Go.1.18");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка GoLang ..." << endl;
                    system("brew install go");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка GoLang ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка GoLang ..." << endl;
                system("winget install -e --id GoLang.Go.1.18");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка GoLang ..." << endl;
                system("brew install go");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка GoLang ..." << endl;
            }
        }
    }
    void InstallPython3_9()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Python 3.9 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка 🐍 python 3.9..." << endl;
                    system("winget install -e --id Python.Python.3.9");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка 🐍 python 3.9..." << endl;
                    system("brew install python@3.9");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка 🐍 python 3.9..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка 🐍 python 3.9..." << endl;
                system("winget install -e --id Python.Python.3.9");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка 🐍 python 3.9..." << endl;
                system("brew install python@3.9");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка 🐍 python 3.9..." << endl;
            }
        }
    }
    void InstallPython3_10()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Python 3.10 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка 🐍 python 3.10..." << endl;
                    system("winget install -e --id Python.Python.3.10");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка 🐍 python 3.10..." << endl;
                    system("brew install python@3.10");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка 🐍 python 3.10..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                    cout << "Установка 🐍 python 3.10..." << endl;
                    system("winget install -e --id Python.Python.3.10");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка 🐍 python 3.10..." << endl;
                    system("brew install python@3.10");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка 🐍 python 3.10..." << endl;
                }
        }
    }
    void InstallPython3_11()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Python 3.11 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка 🐍 python 3.11..." << endl;
                    system("winget install -e --id Python.Python.3.11");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка 🐍 python 3.11..." << endl;
                    system("brew install python@3.11");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка 🐍 python 3.11..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка 🐍 python 3.11..." << endl;
                system("winget install -e --id Python.Python.3.11");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка 🐍 python 3.11..." << endl;
                system("brew install python@3.11");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка 🐍 python 3.11..." << endl;
            }
        }
    }
    void InstallJDK_19()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JDK 19 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JDK 19 ..." << endl;
                    system("winget install -e --id Oracle.JDK.19");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JDK 19 ..." << endl;
                    system("brew install openjdk@19");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JDK 19 ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JDK 19 ..." << endl;
                system("winget install -e --id Oracle.JDK.19");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JDK 19 ..." << endl;
                system("brew install openjdk@19");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JDK 19 ..." << endl;
            }
        }
    }
    void InstallJDK_18()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить JDK 18 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка JDK 18 ..." << endl;
                    system("winget install -e --id Oracle.JDK.18");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка JDK 18 ..." << endl;
                    system("brew install openjdk@18");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка JDK 18 ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка JDK 18 ..." << endl;
                system("winget install -e --id Oracle.JDK.18");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка JDK 18 ..." << endl;
                system("brew install openjdk@18");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка JDK 18 ..." << endl;
            }
        }
    }
    void InstallRust()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Rust (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Rust ..." << endl;
                    system("winget install -e --id Rustlang.Rust.MSVC");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Rust ..." << endl;
                    system("brew install rust");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Rust ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Rust ..." << endl;
                system("winget install -e --id Rustlang.Rust.MSVC");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Rust ..." << endl;
                system("brew install rust");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Rust ..." << endl;
            }
        }
    }
    void InstallNetFramework()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Microsoft DotNet Framework (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Microsoft DotNet Framework ..." << endl;
                    system("winget install -e --id Microsoft.DotNet.Framework.DeveloperPack_4");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Microsoft DotNet Framework ..." << endl;
                    system("brew install dotnet");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Microsoft DotNet Framework ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Microsoft DotNet Framework ..." << endl;
                system("winget install -e --id Microsoft.DotNet.Framework.DeveloperPack_4");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Microsoft DotNet Framework ..." << endl;
                system("brew install dotnet");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Microsoft DotNet Framework ..." << endl;
            }
        }
    }
    void InstallRuby()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Ruby (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Ruby ..." << endl;
                    system("winget install -e --id RubyInstallerTeam.Ruby.3.1");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Ruby ..." << endl;
                    system("brew install ruby");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Ruby ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Ruby ..." << endl;
                system("winget install -e --id RubyInstallerTeam.Ruby.3.1");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Ruby ..." << endl;
                system("brew install ruby");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Ruby ..." << endl;
            }
        }
    }
    void InstallMSYS2()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить MSYS2 (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка MSYS2 ..." << endl;
                    system("winget install -e --id MSYS2.MSYS2");
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка MSYS2 ..." << endl;
                system("winget install -e --id MSYS2.MSYS2");
            }
        }
    }
    void InstallNuget()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Microsoft NuGet (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Nuget ..." << endl;
                    system("winget install -e --id Microsoft.NuGet");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Nuget ..." << endl;
                    system("brew install nuget");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Nuget ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Nuget ..." << endl;
                system("winget install -e --id Microsoft.NuGet");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Nuget ..." << endl;
                system("brew install nuget");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Nuget ..." << endl;
            }
        }
    }
    void InstallGitHubDesktop()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить GitHub Desktop (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка GitHub Desktop ..." << endl;
                    system("winget install -e --id GitHub.GitHubDesktop");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка GitHub Desktop ..." << endl;
                    system("brew install --cask github");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка GitHub Desktop ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка GitHub Desktop ..."<< endl;
                system("winget install -e --id GitHub.GitHubDesktop");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка GitHub Desktop ..." << endl;
                system("brew install --cask github");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка GitHub Desktop ..." << endl;
            }
        }
    }
    void InstallGitHubCLi()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить GitHub CLI (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка GitHub CLI ..." << endl;
                    system("winget install -e --id GitHub.cli");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка GitHub CLI ..." << endl;
                    system("brew install gh");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка GitHub CLI ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка GitHub CLI ..." << endl;
                system("winget install -e --id GitHub.cli");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка GitHub CLI ..." << endl;
                system("brew install gh");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка GitHub CLI ..." << endl;
            }
        }
    }
    void InstallKubernetes()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Kubernetes (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Kubernetes ..." << endl;
                    system("winget install -e --id Kubernetes.kubectl");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Kubernetes ..." << endl;
                    system("brew install kubernetes-cli");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Kubernetes ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Kubernetes ..." << endl;
                system("winget install -e --id Kubernetes.kubectl");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Kubernetes ..." << endl;
                system("brew install kubernetes-cli");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Kubernetes ..." << endl;
            }
        }
    }
    void InstallVisualStudioCommunity()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Visual Studio Community (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Visual Studio Community ..." << endl;
                    system("winget install -e --id Microsoft.VisualStudio.2022.Community.Preview");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Visual Studio Community ..." << endl;
                    system("brew install --cask visual-studio");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Visual Studio Community ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Visual Studio Community ..." << endl;
                system("winget install -e --id Microsoft.VisualStudio.2022.Community.Preview");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Visual Studio Community ..." << endl;
                system("brew install --cask visual-studio");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Visual Studio Community ..." << endl;
            }
        }
    }

    void InstallVisualStudioProffessional()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Visual Studio Proffessional (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Visual Studio Proffessional ..." << endl;
                    system("winget install -e --id Microsoft.VisualStudio.2022.Professional.Preview");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Visual Studio Proffessional ..." << endl;
                    system("brew install --cask visual-studio");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Visual Studio Proffessional ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Visual Studio Proffessional ..." << endl;
                system("winget install -e --id Microsoft.VisualStudio.2022.Professional.Preview");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Visual Studio Proffessional ..." << endl;
                system("brew install --cask visual-studio");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Visual Studio Proffessional ..." << endl;
            }
        }
    }
    void InstallSlack()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Slack (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Slack ..." << endl;
                    system("winget install -e --id SlackTechnologies.Slack");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Slack ..." << endl;
                    system("brew install --cask slack");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Slack ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Slack ..." << endl;
                system("winget install -e --id SlackTechnologies.Slack");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Slack ..." << endl;
                system("brew install --cask slack");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Slack ..." << endl;
            }
        }
    }
    void InstallVim()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Vim (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Vim ..." << endl;
                    system("winget install -e --id vim.vim");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Vim ..." << endl;
                    system("brew install vim");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Vim ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Vim ..." << endl;
                system("winget install -e --id vim.vim");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Vim ..." << endl;
                system("brew install vim");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Vim ..." << endl;
            }
        }
    }
    void InstallNeoVim()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить NeoVim (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка NeoVim ..." << endl;
                    system("winget install -e --id Neovim.Neovim");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка NeoVim ..." << endl;
                    system("brew install neovim");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка NeoVim ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка NeoVim ..." << endl;
                system("winget install -e --id Neovim.Neovim");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка NeoVim ..." << endl;
                system("brew install neovim");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка NeoVim ..." << endl;
            }
        }
    }
    void InstallGoogleChrome()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Google Chrome (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Google Chrome ..." << endl;
                    system("winget install -e --id Google.Chrome");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Google Chrome ..." << endl;
                    system("brew install --cask google-chrome");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Google Chrome ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Google Chrome ..." << endl;
                system("winget install -e --id Google.Chrome");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Google Chrome ..." << endl;
                system("brew install --cask google-chrome");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Google Chrome ..." << endl;
            }
        }
    }
    void InstallAndroidStudio()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Android Studio (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Android Studio ..." << endl;
                    system("winget install -e --id Google.AndroidStudio");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Android Studio ..." << endl;
                    system("brew install --cask android-studio");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Android Studio ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Android Studio ..." << endl;
                system("winget install -e --id Google.AndroidStudio");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Android Studio ..." << endl;
                system("brew install --cask android-studio");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Android Studio ..." << endl;
            }
        }
    }
    void InstallEclipse()
    {
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Eclipse (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    cout << "Установка Eclipse ..." << endl;
                    system("winget install -e --id EclipseAdoptium.Temurin.18.JDK");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Eclipse ..." << endl;
                    system("brew install --cask eclipse-ide");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Eclipse ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Eclipse ..." << endl;
                system("winget install -e --id EclipseAdoptium.Temurin.18.JDK");
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Eclipse ..." << endl;
                system("brew install --cask eclipse-ide");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Eclipse ..." << endl;
            }
        }
    }
    void InstallKotlin()
    {
        if (OS_NAME == "Windows") {
            SetConsoleOutputCP(CP_UTF8);
        }
        if (TypeInstall == "open") {
            cout << "Вы хотите установить Kotlin (по умолчанию - да)?";
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                if (OS_NAME == "Windows") {
                    try {
                        cout << "Установка Kotlin ..." << endl;
                        int response = Download(KotlinUrl, KotlinDir);
                        if (response == 200) {
                            cout << "✅ Kotlin successfully installed" << endl;
                        }
                        else if (response == 502) {
                            cout << "❌ An error occurred while trying to install Kotlin" << endl;
                        }
                        filesystem::create_directory(NewKotlinDir);
                        string Command = "tar -xf" + ProjectDir + "/kotlin-compiler-1.8.22.zip " + "--directory " + NewKotlinDir;
                        system(Command.c_str());
                        string AddPathCommand = "start powershell.exe -file " + AddKotlinPathScript;
                        system("powershell.exe  C?\\Users\\Blackflame576\\Documents\\Blackflame576\\DigitalBit\\DeveloperTools\\Scripts\\AddKotlinPath.ps1");
                        system(AddPathCommand.c_str());
                        cout << AddKotlinPathScript << endl;
                        // std??filesystem??copy(KotlinDir,NewKotlinDir,std??filesystem??copy_options??recursive);
                        // auto ProjectDir = std??filesystem??current_path();
                        // cout << "Current Path?" << ProjectDir << endl;
                        // filesystem??create_directory();
                        // filesystem??copy();
                        // filesystem??remove_all();
                    }
                    catch (std::filesystem::filesystem_error& error) {
                        cout << error.what() << endl;
                    }
                    // system("winget install -e --id EclipseAdoptium.Temurin.18.JDK");
                }
                else if (OS_NAME == "macOS") {
                    cout << "Установка Kotlin ..." << endl;
                    system("brew install kotlin");
                }
                else if (OS_NAME == "Linux") {
                    cout << "Установка Kotlin ..." << endl;
                }
            }
        }
        else if (TypeInstall == "hidden") {
            if (OS_NAME == "Windows") {
                cout << "Установка Kotlin ..." << endl;
                int response = Download(KotlinUrl, KotlinDir);
                if (response == 200) {
                    cout << "✅ Kotlin successfully installed" << endl;
                }
                else if (response == 502) {
                    cout << "❌ An error occurred while trying to install Kotlin" << endl;
                }
                filesystem::create_directory(NewKotlinDir);
                string Command = "tar -xf" + ProjectDir + "/kotlin-compiler-1.8.22.zip " + "--directory " + NewKotlinDir;
                system(Command.c_str());
                string AddPathCommand = "powershell.exe -file " + AddKotlinPathScript;
                system(AddPathCommand.c_str());
            }
            else if (OS_NAME == "macOS") {
                cout << "Установка Kotlin ..." << endl;
                system("bbrew install kotlin");
            }
            else if (OS_NAME == "Linux") {
                cout << "Установка Kotlin ..." << endl;
            }
        }
    }

    map<string, funct_t> Packages{
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "JetBrains WebStorm", InstallWebStorm },
        { "Docker", InstallDocker }, { "Postman", InstallPostman }, { "JetBrains RubyMine", InstallRubyMine },
        { "JetBrains Aqua", InstallAqua }, { "JetBrains CLion", InstallCLion }, { "JetBrains DataGrip", InstallDataGrip },
        { "JetBrains DataSpell", InstallDataSpell }, { "JetBrains Fleet", InstallFleet }, { "GoLand", InstallGoLand },
        { "JetBrains IntelliJ Community", InstallIntelliJCommunity }, { "JetBrains IntelliJ Ultimate", InstallIntelliJUltimate },
        { "JetBrains ReSharper", InstallReSharper }, { "JetBrains Rider", InstallRider }, { "JetBrains PhpStorm", InstallPhpStorm },
        { "JetBrains dotUltimate", InstalldotUltimate }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        { "Postgresql", InstallPostgresql }, { "Clink", InstallCLink }, { "Ngrok", InstallNgrok }, { "Wget", InstallWget },
        { "Sublime Text", InstallSublimeText }, { "PyCharm Community", InstallPyCharmCommunity }, { "PyCharm Proffessional", InstallPyCharmProffessional },
        { "Microsoft PowerToys", InstallPowerToys }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "NodeJS", InstallNodeJS }, { "GoLang", InstallGoLang },
        { "Python 3.9", InstallPython3_9 }, { "Python 3.10", InstallPython3_10 }, { "Python 3.11", InstallPython3_11 },
        { "JDK 18", InstallJDK_18 }, { "JDK 19", InstallJDK_19 }, { "Rust", InstallRust }, { ".Net Framework", InstallNetFramework },
        { "Ruby", InstallRuby }, { "MSYS2", InstallMSYS2 }, { "Nuget", InstallNuget },
        { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome },
        { "Android Studio", InstallAndroidStudio }, { "Eclipse", InstallEclipse }, { "Kotlin", InstallKotlin }
    };
    map<string, funct_t> PythonDevelopmentTools{
        { "Python 3.9", InstallPython3_9 }, { "Python 3.10", InstallPython3_10 }, { "Python 3.11", InstallPython3_11 },
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "PyCharm Community", InstallPyCharmCommunity },
        { "PyCharm Proffessional", InstallPyCharmProffessional }, { "Sublime Text", InstallSublimeText }, { "Docker", InstallDocker },
        { "Postman", InstallPostman }, { "Postgresql", InstallPostgresql }, { "MongoDB", InstallMongoDB },
        { "MongoDB Atlas", InstallMongoDBAtlas }, { "MongoDB Compass", InstallMongoDBCompass },
        { "Wget", InstallWget }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "GitHub Desktop", InstallGitHubDesktop },
        { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes }, { "JetBrains Fleet", InstallFleet }, { "Visual Studio Proffessional", InstallVisualStudioProffessional },
        { "Visual Studio Community", InstallVisualStudioCommunity }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Slack", InstallSlack },
        { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> JavaScriptDevelopmentTools{
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "JetBrains WebStorm", InstallWebStorm },
        { "Docker", InstallDocker }, { "Postman", InstallPostman }, { "JetBrains Fleet", InstallFleet },
        { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        { "Discord", InstallDiscord }, { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer },
        { "MongoDB Compass", InstallMongoDBCompass }, { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        { "NodeJS", InstallNodeJS }, { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi },
        { "Kubernetes", InstallKubernetes }, { "Visual Studio Proffessional", InstallVisualStudioProffessional },
        { "Visual Studio Community", InstallVisualStudioCommunity }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> RustDevelopmentTools{
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker },
        { "Postman", InstallPostman }, { "JetBrains Fleet", InstallFleet }, { "Wget", InstallWget },
        { "Sublime Text", InstallSublimeText }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi },
        { "Kubernetes", InstallKubernetes }, { "Rust", InstallRust }, { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        { "NodeJS", InstallNodeJS }, { "MongoDB Compass", InstallMongoDBCompass }, { "Ngrok", InstallNgrok }, { "Kubernetes", InstallKubernetes },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> RubyDevelopmentTools{
        { "Ruby", InstallRuby }, { "RubyMine", InstallRubyMine }, { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker },
        { "Postman", InstallPostman }, { "JetBrains Fleet", InstallFleet }, { "Wget", InstallWget },
        { "Sublime Text", InstallSublimeText }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi },
        { "Kubernetes", InstallKubernetes }, { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        { "NodeJS", InstallNodeJS }, { "MongoDB Compass", InstallMongoDBCompass }, { "Ngrok", InstallNgrok }, { "Kubernetes", InstallKubernetes },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> CppDevelopmentTools{
        { "CLion", InstallCLion }, { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        { "JetBrains Fleet", InstallFleet }, { "Sublime Text", InstallSublimeText }, { "Ngrok", InstallNgrok },
        { "Wget", InstallWget }, { "Docker", InstallDocker }, { "Discord", InstallDiscord },
        { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer },
        { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "JetBrains Space", InstallSpace },
        { "JetBrains ToolBox", InstallToolBox }, { "MSYS2", InstallMSYS2 }, { "Postman", InstallPostman }, { "MongoDB Compass", InstallMongoDBCompass },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "Postgresql", InstallPostgresql },
        { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> CSDevelopmentTools{
        { "JetBrains Rider", InstallRider }, { ".Net Framework", InstallNetFramework }, { "Git", InstallGit }, { "VSCode", InstallVSCode },
        { "Postman", InstallPostman }, { "Nuget", InstallNuget }, { "GitHub Desktop", InstallGitHubDesktop },
        { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes }, { "Visual Studio Proffessional", InstallVisualStudioProffessional },
        { "Visual Studio Community", InstallVisualStudioCommunity }, { "JetBrains Fleet", InstallFleet }, { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText }, { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "JetBrains dotUltimate", InstalldotUltimate }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "Postgresql", InstallPostgresql },
        { "Slack", InstallSlack }, { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> CDevelopmentTools{
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "MSYS2", InstallMSYS2 }, { "Nuget", InstallNuget },
        { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText }, { "JetBrains Fleet", InstallFleet },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Slack", InstallSlack },
        { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> GoDevelopmentTools{
        { "GoLang", InstallGoLang }, { "JetBrains Fleet", InstallFleet }, { "GoLand", InstallGoLand },
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas }, { "GitHub Desktop", InstallGitHubDesktop },
        { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes }, { "Slack", InstallSlack },
        { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> JavaDevelopmentTools{
        { "JDK 18", InstallJDK_18 }, { "JDK 19", InstallJDK_19 },
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        { "JetBrains Fleet", InstallFleet }, { "JetBrains IntelliJ Community", InstallIntelliJCommunity }, { "JetBrains IntelliJ Ultimate", InstallIntelliJUltimate },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        { "Discord", InstallDiscord }, { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        { "Nuget", InstallNuget }, { "Slack", InstallSlack },
        { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }, { "Android Studio", InstallAndroidStudio },
        { "Eclipse", InstallEclipse }, { "Kotlin", InstallKotlin }
    };
    map<string, funct_t> PhpDevelopmentTools{
        { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        { "JetBrains Fleet", InstallFleet }, { "JetBrains PhpStorm", InstallPhpStorm }, { "Postgresql", InstallPostgresql },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox },
        { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        { "Discord", InstallDiscord }, { "Telegram", InstallTelegram },
        { "MongoDB Compass", InstallMongoDBCompass }, { "Slack", InstallSlack },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        { "Visual Studio Proffessional", InstallVisualStudioProffessional }, { "Visual Studio Community", InstallVisualStudioCommunity },
        { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }
    };
    map<string, funct_t> KotlinDevelopmentTools{
        { "Kotlin", InstallKotlin }, { "Git", InstallGit }, { "VSCode", InstallVSCode }, { "Docker", InstallDocker }, { "Postman", InstallPostman },
        { "JDK 18", InstallJDK_18 }, { "JDK 19", InstallJDK_19 }, { "JetBrains Fleet", InstallFleet }, { "JetBrains IntelliJ Community", InstallIntelliJCommunity }, { "JetBrains IntelliJ Ultimate", InstallIntelliJUltimate },
        { "JetBrains Space", InstallSpace }, { "JetBrains ToolBox", InstallToolBox }, { "Postgresql", InstallPostgresql },
        { "Ngrok", InstallNgrok }, { "Wget", InstallWget }, { "Sublime Text", InstallSublimeText },
        { "Discord", InstallDiscord }, { "Telegram", InstallTelegram }, { "VNC Server", InstallVNCServer }, { "VNC Viewer", InstallVNCViewer }, { "MongoDB Compass", InstallMongoDBCompass },
        { "MongoDB", InstallMongoDB }, { "MongoDB Atlas", InstallMongoDBAtlas },
        { "Nuget", InstallNuget }, { "Slack", InstallSlack },
        { "GitHub Desktop", InstallGitHubDesktop }, { "GitHub CLI", InstallGitHubCLi }, { "Kubernetes", InstallKubernetes },
        { "Vim", InstallVim }, { "NeoVim", InstallNeoVim }, { "Google Chrome", InstallGoogleChrome }, { "Android Studio", InstallAndroidStudio },
        { "Eclipse", InstallEclipse }
    };

    void PythonDevelopment()
    {
        for (const auto& element : PythonDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void JavaScriptDevelopment()
    {
        for (const auto& element : JavaScriptDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void RustDevelopment()
    {
        for (const auto& element : RustDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void RubyDevelopment()
    {
        for (const auto& element : RubyDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void CppDevelopment()
    {
        for (const auto& element : CppDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void CSDevelopment()
    {
        for (const auto& element : CSDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void CDevelopment()
    {
        for (const auto& element : CDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void GoDevelopment()
    {
        for (const auto& element : GoDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void JavaDevelopment()
    {
        for (const auto& element : JavaDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void PHPDevelopment()
    {
        for (const auto& element : PhpDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    void KotlinDevelopment()
    {
        for (const auto& element : KotlinDevelopmentTools) {
            string name = element.first;
            cout << name << endl;
            element.second();
        }
    }
    map<int, funct_t> DevelopmentPacks{
        {1,AppInstaller::PythonDevelopment},{2,AppInstaller::JavaDevelopment},
        {3,AppInstaller::CppDevelopment},{4,AppInstaller::JavaDevelopment},
        {5,AppInstaller::GoDevelopment},{6,AppInstaller::RustDevelopment},
        {7,AppInstaller::RubyDevelopment},{8,AppInstaller::CDevelopment},
        {9,AppInstaller::CSDevelopment},{10,AppInstaller::PHPDevelopment},
        {11,AppInstaller::KotlinDevelopment}
    };
}
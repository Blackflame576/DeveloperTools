// Импортирование необходимых библиотек
#include <iostream>
#include <cstdio>
#include <string>
#include "AppInstaller.hpp"
#include <map>
#include "Logger.hpp"
#include <regex>
#include <fstream>

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

using namespace std;
using funct_t = void(*)(void);
using namespace AppInstaller;
using namespace Logger;

// Переменные 
string LangReadySet;
string new_sentence;
string SelectPackages;

// string GetNameDistribution() {
//     if (OS_NAME == "Windows") {
//         ifstream stream("/etc/os-release");
//         string line;
//         regex nameRegex("^NAME=\"(.*?)\"$");
//         smatch match;
//         string name;
//         while (getline(stream,line)) {
//             if (regex_search(line,match,nameRegex)) {
//                 name = match[1].str();
//                 break;
//             }
//         }
//         return name;
//     } 
// }
// Функции
class Main {
    public:
        void CommandManager() {
            string InstallTools;
            cout << "1. Выбрать готовый набор DeveloperTools для конкретного языка программирования" << endl;
            cout << "2. Ручной выбор пакетов DeveloperTools" << endl;
            cout << "3. Установить все пакеты DeveloperTools" << endl;
            cout << "4. Выйти из приложения" << endl;
            cout << "Выберите вариант ответа (по умолчанию — 2):";
            getline(cin,InstallTools);
            if (InstallTools == "1") {
                ReadySet();
            }
            else if (InstallTools == "2" or InstallTools.empty()) {
                ManualSelection();
            }
            else if (InstallTools == "3") {
                InstallAllPackages();
            }
            else if (InstallTools == "4") {
                exit(0);
            }
            else {
                ManualSelection();
            }

        }
        void ManualSelection() {
            TypeInstall = "hidden";
            int i = 1;
            map<int,string> EnumeratePackages;
            for (const auto &element:Packages) {
                EnumeratePackages.insert(pair<int,string>(i,element.first));
                cout << i << ". "<< element.first << endl;
                i++;
            }
            cout << "Выберите номера пакетов для установки(через ,):";
            getline(cin,SelectPackages);
            string delimiter = ",";
            size_t pos = 0;
            string token;
            while ((pos = SelectPackages.find(delimiter)) != string::npos) {
                token = SelectPackages.substr(0, pos);
                string name = EnumeratePackages[stoi(token)];
                Packages[name]();
                SelectPackages.erase(0, pos + delimiter.length());
            }
            string NamePackage = EnumeratePackages[stoi(SelectPackages)];
            Packages[NamePackage]();
            CommandManager();
        }
        void ReadySet() {
            for(int i = 1;i < Languages.size() + 1;i++){
                cout << i << ". " << Languages[i] << endl;
            }
            cout << "Выберите нужный язык программирования:";
            getline(cin,LangReadySet);
            for(int i = 1;i < DevelopmentPacks.size();i++){
                if (LangReadySet == to_string(i)) {
                    DevelopmentPacks[i]();
                }
            }
            CommandManager();
        }
        void InstallAllPackages() {
            TypeInstall = "hidden";
            for (const auto &element:Packages) {
                string name = element.first;
                cout << name << ";";
            }
            cout << "" << endl;
            cout << "Вы точно хотите установить все пакеты (по умолчанию - да)?";
            getline(cin,Answer);
            Install = CheckAnswer(Answer);
            if (Install == true) {
                for (const auto &element:Packages) {
                    string name = element.first;
                    element.second();
                }
            }
            CommandManager();
        }
        Main () {
            // if (OS_NAME == "Windows") {
            //     InstallWinGet();
            // }
            // else if (OS_NAME == "macOS") {
            //     InstallBrew();
            // }
            // else if (OS_NAME == "Linux") {
            //     InstallSnap();
            // }
        }
        ~Main () {
            
        };
    private:
        void InstallBrew() {
            cout << "Установка Brew ..." << endl;
            system("bash ./Scripts/InstallBrew.sh");
        }
        
        void InstallWinGet() {
            cout << "Установка WinGet ..." << endl;
            string CommandInstallWinGet ="powershell.exe " + ProjectDir + "/Scripts/InstallWinGet.ps1";
            system(CommandInstallWinGet.c_str());
        }
        void InstallSnap() {
            cout << "Установка Snap ..." << endl;

        }
    // Main::Main();
    // Main::~Main();
        
};

int main() {
    // setlocale(LC_ALL, "Russian");
    #if defined(__linux__)
        OS_NAME = "Linux";
        // NameDistribution = GetNameDistribution();
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    Main main;
    main.CommandManager();
    // AppInstaller::InstallKotlin();
    // string url;
    // cin >> url;
    // main.Download(url,"file.exe");
    system("pause");
    return 0;
}
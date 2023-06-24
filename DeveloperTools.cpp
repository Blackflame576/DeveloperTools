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
bool Install;
string LangReadySet;
string Answer;
string new_sentence;
string SelectPackages;

size_t WriteData(void* ptr,size_t size,size_t nmemb,FILE* stream) {
    size_t WriteProcess = fwrite(ptr,size,nmemb,stream);
    return WriteProcess;
}

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
            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;
            while ((pos = SelectPackages.find(delimiter)) != std::string::npos) {
                token = SelectPackages.substr(0, pos);
                string name = EnumeratePackages[stoi(token)];
                Packages[name]();
                SelectPackages.erase(0, pos + delimiter.length());
            }
            std::cout << SelectPackages << std::endl;
            string NamePackage = EnumeratePackages[stoi(SelectPackages)];
            Packages[NamePackage]();
            CommandManager();
        }
        void ReadySet() {
            cout << "1. Python" << endl;
            cout << "2. JavaScript" << endl;
            cout << "3. C++" << endl;
            cout << "4. Java" << endl;
            cout << "5. Go" << endl;
            cout << "6. Rust" << endl;
            cout << "7. Ruby" << endl;
            cout << "8. C" << endl;
            cout << "9. C#" << endl;
            cout << "10. PHP" << endl;
            cout << "Выберите нужный язык программирования:";
            getline(cin,LangReadySet);
            if (LangReadySet == "1") {
                TypeInstall = "open";
                AppInstaller::PythonDevelopment();
            }
            else if (LangReadySet == "2") {
                TypeInstall = "open";
                AppInstaller::JavaDevelopment();
            }
            else if (LangReadySet == "3") {
                TypeInstall = "open";
                AppInstaller::CppDevelopment();
            }
            else if (LangReadySet == "4") {
                TypeInstall = "open";
                AppInstaller::JavaDevelopment();
            }
            else if (LangReadySet == "5") {
                TypeInstall = "open";
                AppInstaller::GoDevelopment();
            }
            else if (LangReadySet == "6") {
                TypeInstall = "open";
                AppInstaller::RustDevelopment();
            }
            else if (LangReadySet == "7") {
                TypeInstall = "open";
                AppInstaller::RubyDevelopment();
            }
            else if (LangReadySet == "8") {
                TypeInstall = "open";
                AppInstaller::CDevelopment();
            }
            else if (LangReadySet == "9") {
                TypeInstall = "open";
                AppInstaller::CSDevelopment();
            }
            else if (LangReadySet == "10") {
                TypeInstall = "open";
                AppInstaller::PHPDevelopment();
            }
            CommandManager();
        }
        void InstallAllPackages() {
            TypeInstall = "hidden";
            for (const auto &element:Packages) {
                string name = element.first;
                element.second();
            }
            CommandManager();
        }
        Main () {
            if (OS_NAME == "Windows") {
                InstallWinGet();
            }
            else if (OS_NAME == "macOS") {
                InstallBrew();
            }
            else if (OS_NAME == "Linux") {
                InstallSnap();
            }
        }
        ~Main () {
            
        };
    private:
        void InstallBrew() {
            system("bash ./Scripts/InstallBrew.sh");
        }
        
        void InstallWinGet() {
            string CommandInstallWinGet = ProjectDir + "/Scripts/InstallWinGet.ps1";
            system(CommandInstallWinGet.c_str());
        }
        void InstallSnap() {

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
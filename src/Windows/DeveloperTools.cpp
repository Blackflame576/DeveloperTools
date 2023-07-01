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
            cout << "4. Поиск нужного пакета" << endl;
            cout << "5. Выйти из приложения" << endl;
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
                SearchPackages();
            }
            else if (InstallTools == "5") {
                bool isExit = false;
                cout << "🚪Вы уверенны, что хотите выйти из программы (по умолчанию - нет)?";
                getline(cin, Answer);
                isExit = CheckAnswer(Answer);
                exit(0);
            }
            else {
                ManualSelection();
            }

        }
        void ManualSelection() {
            TypeInstall = "hidden";
            map<int,string> EnumeratePackages;
            for (int i = 1;const auto &element:Packages) {
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
        string Last_str_word(const string& text)
        {
            int i = text.length() - 1;
            
            if (isspace(text[i]))
                while (isspace(text[i])) i--;
            
            while (i != 0 && !isspace(text[i])) --i;
            
            string lastword = text.substr(i + 1);
            return lastword;
        }
        void SearchPackages() {
            string SearchingPackage;
            bool isSearched = false;
            map<int,string> EnumeratePackages;
            cout << "ℹ️ Имя пакета:";
            getline(cin,SearchingPackage);
            SearchingPackage = to_lower(SearchingPackage);
            for (int i = 1;const auto &element:Packages) {
                string name = to_lower(element.first);
                if (SearchingPackage == name || name.rfind(SearchingPackage,0) == 0) {
                    isSearched = true;
                    EnumeratePackages.insert(pair<int,string>(i,element.first));
                    i++;
                }
            }
            if (isSearched == true) {
                cout << "🔎 По вашему запросу найдены следующие пакеты:" << endl;
                for (const auto &element:EnumeratePackages) {
                    cout << element.first << ". " << element.second << endl;
                }
                cout << "Выберите номер нужного пакета (по умолчанию - выход):";
                getline(cin,SelectPackages);
                if (SelectPackages.empty() || SelectPackages == "\n") {
                    exit(0);
                }
                else {
                    if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end()) {
                        string NameSelectedPackage = EnumeratePackages[stoi(SelectPackages)];
                        Packages[NameSelectedPackage]();
                    }
                    else {
                        cout << "🙈 Пакета с таким номером нет!" << endl;
                    }
                }
            }
            else {
                cout << "⚠️ По вашему запросу не найдено ни одного пакета." << endl;
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
        // void InstallBrew() {
        //     cout << "Установка Brew ..." << endl;
        //     system("bash ./Scripts/InstallBrew.sh");
        // }
        
        // void InstallWinGet() {
        //     cout << "Установка WinGet ..." << endl;
        //     string CommandInstallWinGet ="powershell.exe " + ProjectDir + "/Scripts/InstallWinGet.ps1";
        //     system(CommandInstallWinGet.c_str());
        // }
        // void InstallSnap() {
        //     cout << "Установка Snap ..." << endl;
        // }
        
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
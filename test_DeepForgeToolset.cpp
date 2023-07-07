// Импортирование необходимых заголовков
#include "DeepForgeToolset.hpp"
#include "Logger.hpp"
#include "AppInstaller_Windows.cpp"

using namespace std;
using funct_t = void(*)(void);
using namespace Windows;
using namespace Logger;

// Функции
class Main {
    public:
        void SetLanguage() {
            string NumLang;
            cout << "1. Russian" << endl;
            cout << "2. English" << endl;
            cout << "Choose language (default - 1):";
            getline(cin,NumLang);
            if (NumLang == "1") {
                Language = "Russian";
                ReadJSON("Russian");
            }
            else if (NumLang == "2") {
                Language = "English";
                ReadJSON("English");
            }
        }

        void CommandManager() {
            cout << translate["CommandManager_1"].asString() << endl;
            cout << translate["CommandManager_2"].asString() << endl;
            cout << translate["CommandManager_3"].asString() << endl;
            cout << translate["CommandManager_4"].asString() << endl;
            cout << translate["CommandManager_5"].asString() << endl;
            cout << translate["CommandManager_ch_answ"].asString();
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
                cout << translate["ExitApp"].asString();
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
            cout << translate["SelectingPackages"].asString();
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
            cout << translate["ChooseLanguage"].asString();
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
            cout << translate["InstallAllPackages"].asString();
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

        // string Last_str_word(const string& text)
        // {
        //     int i = text.length() - 1;
            
        //     if (isspace(text[i]))
        //         while (isspace(text[i])) i--;
            
        //     while (i != 0 && !isspace(text[i])) --i;
            
        //     string lastword = text.substr(i + 1);
        //     return lastword;
        // }

        void SearchPackages() {
            string SearchingPackage;
            bool isSearched = false;
            map<int,string> EnumeratePackages;
            cout << translate["PackageName"].asString();
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
                cout << translate["Result"].asString() << endl;
                for (const auto &element:EnumeratePackages) {
                    cout << element.first << ". " << element.second << endl;
                }
                cout << translate["SelectNumber"].asString();
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
                        cout << translate["NotFoundPackage"].asString() << endl;
                    }
                }
            }
            else {
                cout << translate["QueryNotFound"].asString() << endl;
            }
            CommandManager();
        }

        void InstallWinGet() {
            cout << translate["InstallWinGet"].asString() << endl;
            string CommandInstallWinGet ="powershell.exe " + ProjectDir + "/Scripts/InstallWinGet.ps1";
            system(CommandInstallWinGet.c_str());
        }

        Main () {
            SetLanguage();
        }

        ~Main () {
            
        };
    private:
        void ReadJSON(string lang) {
            if (lang == "Russian") {
                ifstream f("locale/locale_ru.json");
                f >> translate;
            }
            else if(lang == "English") {
                ifstream f("locale/locale_en.json");
                f >> translate;
            }
        }
};

int main() {
    #if defined(__linux__)
        OS_NAME = "Linux";
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
        system("chcp 65001");
    #endif
    Main main;
    main.CommandManager();
    // AppInstaller::InstallKotlin();
    system("pause");
    return 0;
}
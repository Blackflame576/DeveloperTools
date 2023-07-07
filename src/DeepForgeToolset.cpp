#include "DeepForgeToolset.hpp"

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    
// cout << "Linux" << endl;
#elif __FreeBSD__
    // cout << "FreeBSD" << endl;
#elif __APPLE__
    // cout << "macOS" << endl;
#elif _WIN32
    #include "AppInstaller_Windows.cpp"
    using namespace Windows;
#endif

using namespace std;



class MainApp {
    public:
        void SetLanguage() {
            string NumLang;
            cout << "1. Russian" << endl;
            cout << "2. English" << endl;
            cout << "Choose language (default - 1):";
            getline(cin,NumLang);
            if (NumLang == "1" || NumLang.empty()) {
                Language = "Russian";
                ReadJSON("Russian");
            }
            else if (NumLang == "2") {
                Language = "English";
                ReadJSON("English");
            }
        }

        void CommandManager() {
            using funct_t = void(MainApp::*)(void);
            map<int,funct_t> Commands= {
                {1,MainApp::ReadySet},{2,MainApp::ManualSelection},
                {3,MainApp::InstallAllPackages},
                {4,MainApp::SearchPackages},{5,MainApp::ExitApp}
            };
            cout << translate["CommandManager_1"].asString() << endl;
            cout << translate["CommandManager_2"].asString() << endl;
            cout << translate["CommandManager_3"].asString() << endl;
            cout << translate["CommandManager_4"].asString() << endl;
            cout << translate["CommandManager_5"].asString() << endl;
            cout << translate["CommandManager_ch_answ"].asString();
            getline(cin,InstallTools);
            int NumCommand = 0;
            try {
                if (InstallTools.empty()) {
                    (this->*(Commands[1]))();
                }
                else {
                    int TempInstallTools = stoi(InstallTools);
                    for (int i = 1;const auto &element:Commands) {
                        if (TempInstallTools == element.first) {
                            NumCommand = element.first;
                            break;
                        }
                    }
                }
                if (Commands.find(NumCommand) != Commands.end()) {
                    (this->*(Commands[NumCommand]))();
                }
                else {
                    CommandManager();
                }
            }
            catch (exception& error) {
                cout << translate["AnswerNotCorrect"].asString() << endl;
                // CommandManager();
            }
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
                    (Installer.*(element.second))();
                }
            }
            CommandManager();
        }
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
                        (Installer.*(Packages[NameSelectedPackage]))();
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

        void ManualSelection() {
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
            if (SelectPackages.empty() == false) {
                while ((pos = SelectPackages.find(delimiter)) != string::npos) {
                    token = SelectPackages.substr(0, pos);
                    string name = EnumeratePackages[stoi(token)];
                    (Installer.*(Packages[name]))();
                    SelectPackages.erase(0, pos + delimiter.length());
                }
                string NamePackage = EnumeratePackages[stoi(SelectPackages)];
                (Installer.*(Packages[NamePackage]))();
            }
            CommandManager();
        }

        MainApp () {
            SetLanguage();
        };
        ~MainApp() {}
    private:
        void ReadJSON(string lang) {
            try {
                if (lang == "Russian") {
                    ifstream f("./locale/locale_ru.json");
                    if (f.is_open()) {
                        f >> translate;
                    }
                }
                else if(lang == "English") {
                    ifstream f("./locale/locale_en.json");
                    if (f.is_open()) {
                        f >> translate;
                    }
                }
            }
            catch (exception& error) {
                cout << error.what() << endl;
            }
        }
        void ExitApp() {
            exit(0);
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
    MainApp app;
    app.CommandManager();
    system("pause");
    return 0;
}
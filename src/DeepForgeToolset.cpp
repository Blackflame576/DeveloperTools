/*  The MIT License (MIT)

    Copyright (c) 2023 DeepForge Technology
    ============================================================================
    Company: DeepForge Technology
    ============================================================================
    Author: Blackflame576
    ============================================================================
    Created: 4 Juny 2023
    ============================================================================
*/
#include "DeepForgeToolset.hpp"

// Проверка названия операционной системы и импортрование нужных библиотек для этой системы
#if defined(__linux__)
    #include "AppInstaller_Linux.cpp"
    using namespace Linux;
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
            // Если пользователь вводит не цифру, то метод вызывается повторно
            else {
                SetLanguage();
            }
        }
        // Функция главного меню
        void CommandManager() {
            using funct_t = void(MainApp::*)(void);
            map<int,funct_t> Commands= {
                {1,&MainApp::ReadySet},{2,&MainApp::ManualSelection},
                {3,&MainApp::InstallAllPackages},
                {4,&MainApp::SearchPackages},{5,&MainApp::ExitApp}
            };
            // using funct_t = void(this->::*)(void);
            // map<int,funct_t> Commands= {
            //     {1,this->ReadySet},{2,this->ManualSelection},
            //     {3,this->InstallAllPackages},
            //     {4,this->SearchPackages},{5,this->ExitApp}
            // };
            // typedef void (MainApp::*funct_t)(void);
            // typedef std::map<std::int, funct_t> Commands_func_map_t;
            // Commands_func_map_t Commands = {
            //     {1,&MainApp::ReadySet},{2,&MainApp::ManualSelection},
            //     {3,&MainApp::InstallAllPackages},
            //     {4,&MainApp::SearchPackages},{5,&MainApp::ExitApp}
            // };
            // map<int, function<void()>> Commands = {
            //     {1,[this](){this->ReadySet();}}
            // };
            cout << translate["CommandManager_1"].asString() << endl;
            cout << translate["CommandManager_2"].asString() << endl;
            cout << translate["CommandManager_3"].asString() << endl;
            cout << translate["CommandManager_4"].asString() << endl;
            cout << translate["CommandManager_5"].asString() << endl;
            cout << translate["CommandManager_ch_answ"].asString();
            getline(cin,InstallTools);
            int NumCommand = 0;
            try {
                // Если пользователь ничего не вводит, то по умолчанию вызывается метод ручной установки приложений
                if (InstallTools.empty()) {
                    (this->*(Commands[2]))();
                }
                // Если пользователь ввёл цифру, то вызывается соответствующий метод установки
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
                // Если введённой цифры нет среди предложенного списка цифр, то вызывается главное меню
                else {
                    CommandManager();
                }
            }
            catch (exception& error) {
                cout << translate["AnswerNotCorrect"].asString() << endl;
                string ErrorText_1 = error.what();
                string ErrorText_2 = "AnswerNotCorrect -" + translate["AnswerNotCorrect"].asString();
                logger.Error(ErrorText_1.c_str());
                logger.Error(ErrorText_2.c_str());
                CommandManager();
            }
        }
        // Готовый toolset для конретного языка программирования
        void ReadySet() {
            try {
                for(int i = 1;i < Languages.size() + 1;i++){
                    cout << i << ". " << Languages[i] << endl;
                }
                cout << translate["ChooseLanguage"].asString();
                getline(cin,LangReadySet);
                for(int i = 1;i < DevelopmentPacks.size();i++){
                    if (LangReadySet == to_string(i)) {
                        InstallDevelopmentPack(DevelopmentPacks[i]);
                        cout << i << endl;
                    }
                }
            }
            catch (exception& error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            CommandManager();
        }
        // Функция установки всех пакетов
        void InstallAllPackages() {
            cout << translate["AllPackages"].asString() << endl;
            try {
                // Вывод названия всех приложений
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
                        cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                        // Установка приложения
                        output_func = (Installer.*(element.second))();
                        if (output_func == 0) {
                            cout << "✅ " << name << " " << translate["Installed"].asString() << endl;
                            string SuccessText = name + " " + translate["Installed"].asString();
                            logger.Success(SuccessText.c_str());
                        }
                        else {
                            // cout << "❌ " << translate["ErrorInstall"].asString() << " " << name << endl;
                            string ErrorText = translate["ErrorInstall"].asString() + " " + name;
                            logger.Error(ErrorText.c_str());
                        }
                    }
                }
            }
            catch (exception& error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            // Вызов главного меню
            CommandManager();
        }

        // Функция поиска приложений
        void SearchPackages() {
            // Объявление необходимых для поиска переменных и словарей
            string SearchingPackage;
            bool isSearched = false;
            map<int,string> EnumeratePackages;
            cout << translate["PackageName"].asString();
            // Ввод названия приложения
            getline(cin,SearchingPackage);
            try {
                SearchingPackage = to_lower(SearchingPackage);
                // Нумерация всех приложений
                for (int i = 1;const auto &element:Packages) {
                    string name = to_lower(element.first);
                    // Проверка совпадения названия приложения из словаря Packages с введённым названием приложения
                    if (SearchingPackage == name || name.rfind(SearchingPackage,0) == 0) {
                        isSearched = true;
                        EnumeratePackages.insert(pair<int,string>(i,element.first));
                        i++;
                    }
                }
                // Если  в процессе поиска найдено хоть одно приложение,то пользователь выбирает одно приложение из найденных
                if (isSearched == true) {
                    cout << translate["Result"].asString() << endl;
                    for (int i = 1;const auto &element:EnumeratePackages) {
                        // cout << element.first << ". " << element.second << endl;
                        string NamePackage = to_string(element.first) + ". " + element.second;
                        string getNewString = NewString(NamePackage);
                        if (EnumeratePackages.size() % 2 == 0) {
                            if (getNewString != "") {
                                cout << getNewString << endl;
                            }
                        }
                        else {
                            if (getNewString != "") {
                                cout << getNewString << endl;
                            }
                            if (i == EnumeratePackages.size()) {
                                cout << NamePackage << endl;
                            }
                        }
                        i++;
                    }
                    cout << translate["SelectNumber"].asString();
                    getline(cin,SelectPackages);
                    if (SelectPackages.empty() || SelectPackages == "\n") {
                        CommandManager();
                    }
                    else {
                        if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end()) {
                            string NameSelectedPackage = EnumeratePackages[stoi(SelectPackages)];
                            cout << translate["Installing"].asString() << " " << NameSelectedPackage << " ..." << endl;
                            output_func = (Installer.*(Packages[NameSelectedPackage]))();
                            if (output_func == 0) {
                                cout << "✅ " << NameSelectedPackage << " " << translate["Installed"].asString() << endl;
                                string SuccessText = NameSelectedPackage + " " + translate["Installed"].asString();
                                logger.Success(SuccessText.c_str());
                            }
                            else {
                                // cout << "❌ " << translate["ErrorInstall"].asString() << " " << NameSelectedPackage << endl;
                                string ErrorText = translate["ErrorInstall"].asString() + " " + NameSelectedPackage;
                                logger.Error(ErrorText.c_str());
                            }
                        }
                        else {
                            cout << translate["NotFoundPackage"].asString() << endl;
                        }
                    }
                }
                // Если в процессе поиска не найдено ни одного приложения,то выводится сообщение о том,что по данному запросу ничего не найдено
                else {
                    cout << translate["QueryNotFound"].asString() << endl;
                    string ErrorText = "QueryNotFound - " + translate["QueryNotFound"].asString();
                    logger.Error(ErrorText.c_str());
                }
            }
            catch (exception& error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            // Вызов главного меню
            CommandManager();
        }

        void ManualSelection() {
            map<int,string> EnumeratePackages;
            try {
                for (int i = 1;const auto &element:Packages) {
                    EnumeratePackages.insert(pair<int,string>(i,element.first));
                    string NamePackage = to_string(i) + ". " + element.first;
                    string getNewString = NewString(NamePackage);
                    if (Packages.size() % 2 == 0) {
                        if (getNewString != "") {
                            cout << getNewString << endl;
                        }
                    }
                    else {
                        if (getNewString != "") {
                            cout << getNewString << endl;
                        }
                        if (i == Packages.size()) {
                            cout << NamePackage << endl;
                        }
                    }
                    i++;
                }
                cout << translate["SelectingPackages"].asString();
                // Ввод номеров приложений
                getline(cin,SelectPackages);
                string delimiter = ",";
                size_t pos = 0;
                string token;
                if (SelectPackages.empty() == false) {
                    // Получение номеров приложений
                    while ((pos = SelectPackages.find(delimiter)) != string::npos) {
                        token = SelectPackages.substr(0, pos);
                        string name = EnumeratePackages[stoi(token)];
                        cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                        // Установка приложения
                        output_func = (Installer.*(Packages[name]))();
                        if (output_func == 0) {
                            cout << "✅ " << name << " " << translate["Installed"].asString() << endl;
                            string SuccessText = name + " " + translate["Installed"].asString();
                            logger.Success(SuccessText.c_str());
                        }
                        else  {
                            // cout << "❌ " << translate["ErrorInstall"].asString() << " " << name << endl;
                            string ErrorText = translate["ErrorInstall"].asString() + " " + name;
                            logger.Error(ErrorText.c_str());
                        }
                        SelectPackages.erase(0, pos + delimiter.length());
                    }
                    string NamePackage = EnumeratePackages[stoi(SelectPackages)];
                    cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                    // Установка приложения с самым последним введённым номером
                    output_func = (Installer.*(Packages[NamePackage]))();
                    if (output_func == 0) {
                        cout << "✅ " << NamePackage << " " << translate["Installed"].asString() << endl;
                        string SuccessText = NamePackage + " " + translate["Installed"].asString();
                        logger.Success(SuccessText.c_str());
                    }
                    else {
                        // cout << "❌ " << translate["ErrorInstall"].asString() << " " << NamePackage << endl;
                        string ErrorText = translate["ErrorInstall"].asString() + " " + NamePackage;
                        logger.Error(ErrorText.c_str());
                    }
                }
            }
            catch (exception& error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            // Вызов главного меню
            CommandManager();
        }

        void InstallWinGet() {
            string Command = "powershell.exe " + WinGetScriptPath;
            system(Command.c_str());
        }

        void InstallBrew() {
            system("bash ./Scripts/InstallBrew.sh");
        }

        void InstallSnap() {
            cout << NameDistribution << endl;
            if (NameDistribution == "Ubuntu" || NameDistribution == "Kali GNU/Linux") {
                result = system("snap --version");
                switch (result) {
                    case 1:
                        cout << translate["Installing"].asString() << " " << "snap" << " ..." << endl;
                        system("sudo apt-get update && sudo apt-get install -yqq daemonize dbus-user-session fontconfig");
                        system("sudo daemonize /usr/bin/unshare --fork --pid --mount-proc /lib/systemd/systemd --system-unit=basic.target");
                        system("sudo apt install snap snapd");
                        break;
                }
            }
        }

        MainApp () {
            // Настройка локализации
            SetLanguage();
            if (OS_NAME == "Linux") {
                NameDistribution =GetNameDistribution();
                InstallSnap();
            }
            else if (OS_NAME == "Windows") {
                InstallWinGet();
            }
            else if (OS_NAME == "MacOS") {
                InstallBrew();
            }
        };
        // ~MainApp() {}

    private:
        // Функция чтения JSON-файла с локализацией интерфейса
        void ReadJSON(string lang) {
            try {
                if (lang == "Russian") {
                    ifstream f("./locale/locale_ru.json");
                    // Проверка на открытие файла
                    if (f.is_open()) {
                        // Запись словаря с переводом
                        f >> translate;
                        f.close();
                    }
                }
                else if(lang == "English") {
                    ifstream f("./locale/locale_en.json");
                    // Проверка на открытие файла
                    if (f.is_open()) {
                        // Запись словаря с переводом
                        f >> translate;
                        f.close();
                    }
                }
            }
            catch (exception& error) {
                // Вывод ошибки
                cout << error.what() << endl;
            }
        }

        // Функция выхода из приложения
        void ExitApp() {
            exit(0);
        }

        string GetNameDistribution() {
            ifstream stream("/etc/os-release");
            string line;
            regex nameRegex("^NAME=\"(.*?)\"$");
            smatch match;
            string name;
            while (getline(stream,line)) {
                if (regex_search(line,match,nameRegex)) {
                    name = match[1].str();
                    break;
                }
            }
            return name;
            
        }

};

int main() {
    // Проверка операционной системы с последующей записью названия ОС в переменную
    #if defined(__linux__)
        OS_NAME = "Linux";
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
        // Изменение кодировки в консоли Windows
        system("chcp 65001");
    #endif
    // Импорт главного класса
    MainApp app;
    // Вызов главного меню
    app.CommandManager();
    system("pause");
    return 0;
}
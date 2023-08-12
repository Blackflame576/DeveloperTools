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
// Importing a Header File
#include "DeepForgeToolset.hpp"
// Checking the name of the operating system and importing the necessary libraries for this system
#if defined(__linux__)
    #include "AppInstaller_Linux.cpp"
    using namespace Linux;
// cout << "Linux" << endl;
#elif __FreeBSD__
    // cout << "FreeBSD" << endl;
#elif __APPLE__
    #include "AppInstaller_macOS.cpp"
    using namespace macOS;
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
            // If the user enters a non-digit, then the method is called again
            else {
                SetLanguage();
            }
            cout << InstallDelimiter << endl;
        }
        // Main menu function
        void CommandManager() {
            using funct_t = void(MainApp::*)(void);
            map<int,funct_t> Commands= {
                {1,&MainApp::ReadySet},
                {2,&MainApp::ManualSelection},
                {3,&MainApp::InstallAllPackages},
                {4,&MainApp::SearchPackages},
                {5,&MainApp::ExitApp}
            };
            cout << translate["CommandManager_1"].asString() << endl;
            cout << translate["CommandManager_2"].asString() << endl;
            cout << translate["CommandManager_3"].asString() << endl;
            cout << translate["CommandManager_4"].asString() << endl;
            cout << translate["CommandManager_5"].asString() << endl;
            cout << translate["CommandManager_ch_answ"].asString();
            getline(cin,InstallTools);
            cout << InstallDelimiter << endl;
            int NumCommand = 0;
            try {
                // If the user does not enter anything, then the manual application installation method is called by default.
                if (InstallTools.empty()) {
                    (this->*(Commands[2]))();
                }
                // If the user has entered a number, then the corresponding set method is called.
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
                // If the entered digit is not among the proposed list of digits, then the main menu is called
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
        // Ready-made toolset for a specific programming language
        void ReadySet() {
            try {
                for(int i = 1;i < Languages.size() + 1;i++){
                    cout << i << ". " << Languages[i] << endl;
                }
                cout << translate["ChooseLanguage"].asString();
                getline(cin,LangReadySet);
                cout << InstallDelimiter << endl; 
                for (const auto &element:DevelopmentPacks) {
                    if (LangReadySet == element.first) {
                        InstallDevelopmentPack(element.first);
                    }
                }
            }
            catch (exception& error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            CommandManager();
        }
        // Function to install all packages
        void InstallAllPackages() {
            // Update information about packages
            UpdateData();
            cout << translate["AllPackages"].asString() << endl;
            try {
                // Displaying the name of all applications
                for (const auto &element: Packages) {
                    string name = element.first;
                    cout << name << ";";
                }
                cout << "" << endl;
                cout << translate["InstallAllPackages"].asString();
                getline(cin, Answer);
                Install = CheckAnswer(Answer);
                cout << InstallDelimiter << endl;
                if (Install == true) {
                    for (const auto &element: Packages) {
                        string name = element.first;
                        cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                        // Application installation
                        output_func = Installer.MainInstaller(name);
                        if (output_func == 0) {
                            cout << "✅ " << name << " " << translate["Installed"].asString() << endl;
                            string SuccessText = name + " " + translate["Installed"].asString();
                            logger.Success(SuccessText.c_str());
                        } else {
                            // cout << "❌ " << translate["ErrorInstall"].asString() << " " << name << endl;
                            string ErrorText = translate["ErrorInstall"].asString() + " " + name;
                            logger.Error(ErrorText.c_str());
                        }
                        cout << InstallDelimiter << endl;
                    }
                }
            }
            catch (exception &error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            // Calling up the main menu
            CommandManager();
        }
        // Application search function
        void SearchPackages() {
            // Update information about packages
            UpdateData();
            // Declaring variables and dictionaries necessary for searching
            string SearchingPackage;
            bool isSearched = false;
            map<int,string> EnumeratePackages;
            cout << translate["PackageName"].asString();
            // Entering the name of the application
            getline(cin,SearchingPackage);
            try {
                SearchingPackage = to_lower(SearchingPackage);
                // Numbering of all applications
                for (int i = 1;const auto &element:Packages) {
                    string name = to_lower(element.first);
                    // Проверка совпадения названия приложения из словаря Packages с введённым названием приложения
                    if (SearchingPackage == name || name.rfind(SearchingPackage,0) == 0) {
                        isSearched = true;
                        EnumeratePackages.insert(pair<int,string>(i,element.first));
                        i++;
                    }
                }
                // If at least one application is found during the search, then the user selects one application from those found
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
                                haveString = "";
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
                            cout << InstallDelimiter << endl;
                            cout << translate["Installing"].asString() << " " << NameSelectedPackage << " ..." << endl;
                            output_func = Installer.MainInstaller(NameSelectedPackage);
                            if (output_func == 0) {
                                cout << "✅ " << NameSelectedPackage << " " << translate["Installed"].asString() << endl;
                                cout << InstallDelimiter << endl;
                                string SuccessText = NameSelectedPackage + " " + translate["Installed"].asString();
                                logger.Success(SuccessText.c_str());
                            }
                            else {
                                // cout << "❌ " << translate["ErrorInstall"].asString() << " " << NameSelectedPackage << endl;
                                string ErrorText = translate["ErrorInstall"].asString() + " " + NameSelectedPackage;
                                logger.Error(ErrorText.c_str());
                            }
                            cout << InstallDelimiter << endl;
                        }
                        else {
                            cout << translate["NotFoundPackage"].asString() << endl;
                        }
                    }
                }
                // If no applications are found during the search, a message is displayed stating that nothing was found for this request.
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
            cout << InstallDelimiter << endl;
            // Calling up the main menu
            CommandManager();
        }

        void ManualSelection() {
            // Update information about packages
            UpdateData();
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
                            haveString = "";
                        }
                    }
                    i++;
                }
                cout << translate["SelectingPackages"].asString();
                // Entering Application Numbers
                getline(cin,SelectPackages);
                string delimiter = ",";
                size_t pos = 0;
                string token;
                if (SelectPackages.empty() == false) {
                    // Getting Application Numbers
                    while ((pos = SelectPackages.find(delimiter)) != string::npos) {
                        token = SelectPackages.substr(0, pos);
                        string name = EnumeratePackages[stoi(token)];
                        cout << InstallDelimiter << endl;
                        cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                        // Application installation
                        output_func = Installer.MainInstaller(name);
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
                    cout << InstallDelimiter << endl;
                    cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                    // Installing the application with the most recently entered number
                    output_func = Installer.MainInstaller(NamePackage);
                    // output_func = (Installer.*(Packages[NamePackage]))();
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
                    cout << InstallDelimiter << endl;
                }
            }
            catch (exception& error) {
                string ErrorText = error.what();
                logger.Error(ErrorText.c_str());
            }
            // Calling up the main menu
            CommandManager();
        }

        MainApp () {
            cout << "DeepForge Toolset v" << __version__ << endl;
            cout << "Author: Blackflame576" << endl;
            cout << InstallDelimiter << endl;
            // Localization settings
            SetLanguage();
            if (OS_NAME == "Linux") {
                NameDistribution =GetNameDistribution();
                InstallSnap();
                cout << InstallDelimiter << endl;
            }
            else if (OS_NAME == "Windows") {
                InstallWinGet();
                cout << InstallDelimiter << endl;
            }
            else if (OS_NAME == "MacOS") {
                InstallBrew();
                cout << InstallDelimiter << endl;
            }
        };
        ~MainApp() {};

    private:
        // JSON file reading function with interface localization
        void ReadJSON(string lang) {
            try {
                if (lang == "Russian") {
                    ifstream f("./locale/locale_ru.json");
                    // File open check
                    if (f.is_open()) {
                        // Dictionary entry with translation
                        f >> translate;
                        f.close();
                    }
                }
                else if(lang == "English") {
                    ifstream f("./locale/locale_en.json");
                    // File open check
                    if (f.is_open()) {
                        // Dictionary entry with translation
                        f >> translate;
                        f.close();
                    }
                }
            }
            catch (exception& error) {
                // Error output
                cout << error.what() << endl;
            }
        }

        // Application exit function
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

        void InstallWinGet() {
            cout << "WinGet ";
            result = system("winget -v");
            if (result != 0) {
                cout << translate["Installing"].asString() << " " << "winget" << " ..." << endl;
                string Command = "powershell.exe " + ProjectDir + "/Scripts/InstallWinGet.ps1";
                system(Command.c_str());
                cout << "✅ " << "winget" << " " << translate["Installed"].asString() << endl;
            }
        }

        void InstallBrew() {
            cout << translate["Installing"].asString() << " " << "brew" << " ..." << endl;
            system("bash ./Scripts/InstallBrew.sh");
            cout << "✅ " << "brew" << " " << translate["Installed"].asString() << endl;
        }

        void InstallSnap() {
            cout << NameDistribution << endl;
            if (NameDistribution == "Ubuntu" || NameDistribution == "Kali GNU/Linux") {
                result = system("snap --version");
                if (result != 0) {
                    cout << translate["Installing"].asString() << " " << "snap" << " ..." << endl;
                    system("sudo apt-get update && sudo apt-get install -yqq daemonize dbus-user-session fontconfig");
                    // system("sudo daemonize /usr/bin/unshare --fork --pid --mount-proc /lib/systemd/systemd --system-unit=basic.target");
                    system("sudo apt install snap snapd");
                    system("sudo ln -s /var/lib/snapd/snap /snap");
                    system("sudo systemctl enable snapd.service");
                    system("sudo systemctl start snapd.service");
                    cout << "✅ " << "snap" << " " << translate["Installed"].asString() << endl;
                }
            }
        }

};

int main(int argc, char** argv) {
    // Checking the operating system and then writing the OS name to a variable
    #if defined(__linux__)
        OS_NAME = "Linux";
    #elif __FreeBSD__
        OS_NAME = "FreeBSD";
    #elif __APPLE__
        OS_NAME = "macOS";
    #elif _WIN32
        OS_NAME = "Windows";
        // Changing the encoding in the Windows console
        system("chcp 65001");
        cout << InstallDelimiter << endl;
    #endif
    // Main class import
    MainApp app;
    // Calling up the main menu
    app.CommandManager();
    system("pause");
    return 0;
}
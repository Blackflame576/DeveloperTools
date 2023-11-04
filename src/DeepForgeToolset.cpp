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
    Organization: DeepForge Technology
    ============================================================================
    Author: Blackflame576
    ============================================================================
    Created: 4 Juny 2023
    ============================================================================
*/
// Importing a Header File
// #include "DeepForgeToolset.hpp"
// Checking the name of the operating system and importing the necessary libraries for this system
#if defined(__linux__)
#include "DeepForgeToolset_Linux.hpp"
using namespace Linux;
// cout << "Linux" << endl;
#elif __FreeBSD__
// cout << "FreeBSD" << endl;
#elif __APPLE__
#include "DeepForgeToolset_macOS.hpp"
using namespace macOS;
// cout << "macOS" << endl;
#elif _WIN32
#include "DeepForgeToolset_Windows.hpp"
using namespace Windows;
#endif

#define __version__ 0.1
#define __channel__ "stable\\latest"

using namespace std;

class MainApp
{
public:
    void SetLanguage()
    {
        string NumLang;
        cout << "1. Russian" << endl;
        cout << "2. English" << endl;
        cout << "Choose language (default - 1):";
        getline(cin, NumLang);
        if (NumLang == "1" || NumLang.empty())
        {
            Language = "Russian";
            ReadJSON("Russian");
        }
        else if (NumLang == "2")
        {
            Language = "English";
            ReadJSON("English");
        }
        // If the user enters a non-digit, then the method is called again
        else
        {
            SetLanguage();
        }
        cout << InstallDelimiter << endl;
        CommandManager();
    }
    // Main menu function
    void CommandManager()
    {
        using funct_t = void (MainApp::*)(void);
        map<int, funct_t> Commands = {
            {1, &MainApp::ReadySet},
            {2, &MainApp::ManualSelection},
            {3, &MainApp::InstallAllPackages},
            {4, &MainApp::SearchPackages},
            {5, &MainApp::SetLanguage},
            {6, &MainApp::ExitApp}};
        for (int i = 1; i < Commands.size() + 1; i++)
        {
            string index = "CommandManager_" + to_string(i);
            cout << translate[index].asString() << endl;
        }
        cout << translate["CommandManager_ch_answ"].asString();
        getline(cin, InstallTools);
        cout << InstallDelimiter << endl;
        int NumCommand = 0;
        try
        {
            // If the user does not enter anything, then the manual application installation method is called by default.
            if (InstallTools.empty())
            {
                (this->*(Commands[2]))();
            }
            // If the user has entered a number, then the corresponding set method is called.
            else
            {
                int TempInstallTools = stoi(InstallTools);
                for (int i = 1; const auto &element : Commands)
                {
                    if (TempInstallTools == element.first)
                    {
                        NumCommand = element.first;
                        break;
                    }
                }
            }

            if (Commands.find(NumCommand) != Commands.end())
            {
                (this->*(Commands[NumCommand]))();
            }
            // If the entered digit is not among the proposed list of digits, then the main menu is called
            else
            {
                CommandManager();
            }
        }
        catch (exception &error)
        {
            cout << translate["AnswerNotCorrect"].asString() << endl;
            logger.WriteError(error.what());
            CommandManager();
        }
    }
    // Ready-made toolset for a specific programming language
    void ReadySet()
    {
        try
        {
            string NameDevelopmnetPack;
            /* The bellow code is a C++ code snippet that displays a list of languages and prompts the
            user to choose a language. It then checks if the user's choice matches any of the
            elements in the `DevelopmentPacks` container and calls the `InstallDevelopmentPack`
            function if there is a match. */
            for (int i = 1; i < Languages.size() + 1; i++)
            {
                cout << i << ". " << Languages[i] << endl;
            }
            cout << translate["ChooseLanguage"].asString();
            getline(cin, LangReadySet);
            cout << InstallDelimiter << endl;
            for (const auto &element : DevelopmentPacks)
            {
                if (LangReadySet == element.first)
                {
                    NameDevelopmnetPack = element.first;
                    break;
                }
            }
            InstallDevelopmentPack(NameDevelopmnetPack);
        }
        catch (exception &error)
        {
            string ErrorText = "==> ❌ " + string(error.what());
            logger.WriteError(error.what());
            cerr << ErrorText << endl;
        }
        CommandManager();
    }
    // Function to install all packages
    void InstallAllPackages()
    {
        try
        {
            // Update information about packages
            Installer.UpdateData();
            cout << translate["AllPackages"].asString() << endl;
            // Displaying the name of all applications
            for (const auto &element : Packages)
            {
                string name = element.first;
                cout << name << ";";
            }
            cout << "" << endl;
            cout << translate["InstallAllPackages"].asString();
            getline(cin, Answer);
            Install = CheckAnswer(Answer);
            cout << InstallDelimiter << endl;
            if (Install == true)
            {
                for (const auto &element : Packages)
                {
                    string name = element.first;
                    cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                    // Application installation
                    output_func = Installer.MainInstaller(name);
                    if (output_func == 0)
                    {
                        string SuccessText = "==> ✅ " + name + " " + translate["Installed"].asString();
                        cout << SuccessText << endl;
                    }
                    else if (output_func != 403)
                    {
                        string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + name;
                        cerr << ErrorText << endl;
                    }
                    cout << InstallDelimiter << endl;
                }
            }
        }
        catch (exception &error)
        {
            string ErrorText = "==> ❌ " + string(error.what());
            logger.WriteError(error.what());
            cerr << ErrorText << endl;
        }
        // Calling up the main menu
        CommandManager();
    }
    // Application search function
    void SearchPackages()
    {
        try
        {
            // Update information about packages
            Installer.UpdateData();
            // Declaring variables and dictionaries necessary for searching
            string SearchingPackage;
            bool isSearched = false;
            map<int, string> EnumeratePackages;
            string delimiter = ",";
            size_t pos = 0;
            string token;
            cout << translate["PackageName"].asString();
            // Entering the name of the application
            getline(cin, SearchingPackage);
        
            SearchingPackage = to_lower(SearchingPackage);
            /* The bellow code is iterating through the elements in the "Packages" dictionary. It checks
            if the application name from the dictionary matches the entered application name or if
            it starts with the entered application name. If there is a match, it adds the element to
            the "EnumeratePackages" dictionary with a key of "i" and increments "i". */
            for (int i = 1; const auto &element : Packages)
            {
                string name = to_lower(element.first);
                // Checking if the application name from the Packages dictionary matches the entered application name
                if (SearchingPackage == name || name.rfind(SearchingPackage, 0) == 0)
                {
                    isSearched = true;
                    EnumeratePackages.insert(pair<int, string>(i, element.first));
                    i++;
                }
            }
            /* The bellow code is checking if a variable `isSearched` is true. If it is true, it prints
            the value of `translate["Result"]` and then iterates over a collection
            `EnumeratePackages`. For each element in the collection, it creates a string
            `NamePackage` by concatenating the element's key and value. It then calls a function
            `NewString` with `NamePackage` as an argument and assigns the result to `getNewString`. */
            if (isSearched == true)
            {
                cout << translate["Result"].asString() << endl;
                /* The bellow code is iterating over a collection called `EnumeratePackages` and
                performing some operations on each element. */
                for (int i = 1; const auto &element : EnumeratePackages)
                {
                    // cout << element.first << ". " << element.second << endl;
                    /* The bellow code is concatenating the value of `element.first` (converted to a
                    string) with a period and the value of `element.second` to form the string
                    `NamePackage`. It then calls the function `NewString` with `NamePackage` as an
                    argument and assigns the returned value to `getNewString`. */
                    // Formatting output text
                    string NamePackage = to_string(element.first) + ". " + element.second;
                    string getNewString = NewString(NamePackage);
                    if (EnumeratePackages.size() % 2 == 0)
                    {
                        if (getNewString != "")
                        {
                            cout << getNewString << endl;
                        }
                    }
                    else
                    {
                        if (getNewString != "")
                        {
                            cout << getNewString << endl;
                        }
                        if (i == EnumeratePackages.size())
                        {
                            cout << NamePackage << endl;
                            haveString = "";
                        }
                    }
                    i++;
                }
                cout << translate["SelectNumber"].asString();
                getline(cin, SelectPackages);
                /* The bellow code is checking if the variable `SelectPackages` is empty or contains a
                newline character. If it is empty or contains a newline character, it calls the
                `CommandManager()` function. Otherwise, it processes the `SelectPackages` string by
                splitting it into tokens using a delimiter. It then checks if each token is a valid
                package number by looking it up in the `EnumeratePackages` map. If it is a valid
                package number, it retrieves the corresponding package name and proceeds to install
                the application using the `Installer.MainInstaller()` function. The installation
                status is then printed to the console */
                if (SelectPackages.empty() || SelectPackages == "\n")
                {
                    cout << InstallDelimiter << endl;
                    CommandManager();
                }
                else
                {
                    // Getting Application Numbers
                    /* The bellow code is a snippet written in C++. It appears to be a loop that
                    iterates through a string called `SelectPackages` and extracts tokens separated
                    by a delimiter. It then checks if the extracted token exists in a map called
                    `EnumeratePackages`. If it does, it performs some installation-related
                    operations using the extracted token as a key to retrieve the corresponding
                    package name from the `EnumeratePackages` map. The code also handles the case
                    where the entire `SelectPackages` string is a single token by checking if it
                    exists in the `EnumeratePackages` map. */
                    while ((pos = SelectPackages.find(delimiter)) != string::npos)
                    {
                        token = SelectPackages.substr(0, pos);
                        if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
                        {
                            string name = EnumeratePackages[stoi(token)];
                            cout << InstallDelimiter << endl;
                            cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                            // Application installation
                            output_func = Installer.MainInstaller(name);
                            if (output_func == 0)
                            {
                                string SuccessText = "==> ✅ " + name + " " + translate["Installed"].asString();
                                cout << SuccessText << endl;
                            }
                            else if (output_func != 403)
                            {
                                string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + name;
                                cerr << ErrorText << endl;
                            }
                            SelectPackages.erase(0, pos + delimiter.length());
                        }
                    }
                    if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
                    {
                        string NamePackage = EnumeratePackages[stoi(SelectPackages)];
                        cout << InstallDelimiter << endl;
                        cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                        // Installing the application with the most recently entered number
                        output_func = Installer.MainInstaller(NamePackage);
                        if (output_func == 0)
                        {
                            string SuccessText = "==> ✅ " + NamePackage + " " + translate["Installed"].asString();
                            cout << SuccessText << endl;
                        }
                        else if (output_func != 403)
                        {
                            string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                            cerr << ErrorText << endl;
                        }
                    }
                }
            }
            // If no applications are found during the search, a message is displayed stating that nothing was found for this request.
            else
            {
                cerr << translate["QueryNotFound"].asString() << endl;
            }
        }
        catch (exception &error)
        {
            string ErrorText = "==> ❌ " + string(error.what());
            logger.WriteError(error.what());
            cerr << ErrorText << endl;
        }
        cout << InstallDelimiter << endl;
        // Calling up the main menu
        CommandManager();
    }

    void ManualSelection()
    {
        try
        {
            // Update information about packages
            Installer.UpdateData();
            map<int, string> EnumeratePackages;
            string delimiter = ",";
            size_t pos = 0;
            string token;
            /* The bellow code is iterating over a map called "Packages" and performing some operations
            on each element. */
            for (int i = 1; const auto &element : Packages)
            {
                EnumeratePackages.insert(pair<int, string>(i, element.first));
                /* The bellow code is concatenating a string `NamePackage` with an integer `i` and a
                string `element.first`. It then calls a function `NewString` with `NamePackage` as
                an argument and assigns the result to `getNewString`. */
                // Formatting output text
                string NamePackage = to_string(i) + ". " + element.first;
                string getNewString = NewString(NamePackage);
                if (Packages.size() % 2 == 0)
                {
                    if (getNewString != "")
                    {
                        cout << getNewString << endl;
                    }
                }
                else
                {
                    if (getNewString != "")
                    {
                        cout << getNewString << endl;
                    }
                    if (i == Packages.size())
                    {
                        cout << NamePackage << endl;
                        haveString = "";
                    }
                }
                i++;
            }
            cout << translate["SelectingPackages"].asString();
            // Entering Application Numbers
            getline(cin, SelectPackages);
            if (SelectPackages.empty() == false)
            {
                // Getting Application Numbers
                while ((pos = SelectPackages.find(delimiter)) != string::npos)
                {
                    token = SelectPackages.substr(0, pos);
                    if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
                    {
                        string name = EnumeratePackages[stoi(token)];
                        cout << InstallDelimiter << endl;
                        cout << translate["Installing"].asString() << " " << name << " ..." << endl;
                        // Application installation
                        output_func = Installer.MainInstaller(name);
                        if (output_func == 0)
                        {
                            string SuccessText = "==> ✅ " + name + " " + translate["Installed"].asString();
                            cout << SuccessText << endl;
                        }
                        else if (output_func != 403)
                        {
                            string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + name;
                            cerr << ErrorText << endl;
                        }
                        SelectPackages.erase(0, pos + delimiter.length());
                    }
                }
                if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
                {
                    string NamePackage = EnumeratePackages[stoi(SelectPackages)];
                    cout << InstallDelimiter << endl;
                    cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                    // Installing the application with the most recently entered number
                    output_func = Installer.MainInstaller(NamePackage);
                    if (output_func == 0)
                    {
                        string SuccessText = "==> ✅ " + NamePackage + " " + translate["Installed"].asString();
                        cout << SuccessText << endl;
                    }
                    else if (output_func != 403)
                    {
                        string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                        cerr << ErrorText << endl;
                    }
                }
            }
        }
        catch (exception &error)
        {
            string ErrorText = "==> ❌ " + string(error.what());
            logger.WriteError(error.what());
            cerr << ErrorText << endl;
        }
        cout << InstallDelimiter << endl;
        // Calling up the main menu
        CommandManager();
    }

    MainApp()
    {
        cout << "DeepForge Toolset v" << __version__ << " " << __channel__ << " " << Architecture << endl;
        cout << "Organization: DeepForge Technology" << endl;
        cout << InstallDelimiter << endl;
        // Localization settings
        SetLanguage();
    };
    ~MainApp(){};

private:
    // JSON file reading function with interface localization
    void ReadJSON(string language)
    {
        try
        {
            if (language == "Russian")
            {
                ifstream file("./locale/locale_ru.json");
                // File open check
                if (file.is_open())
                {
                    // Dictionary entry with translation
                    file >> translate;
                    file.close();
                }
            }
            else if (language == "English")
            {
                ifstream file("./locale/locale_en.json");
                // File open check
                if (file.is_open())
                {
                    // Dictionary entry with translation
                    file >> translate;
                    file.close();
                }
            }
        }
        catch (exception &error)
        {
            // Error output
            logger.WriteError(error.what());
            logger.WriteError("Function: ReadJSON");
            logger.SendError(Architecture,__channel__,OS_NAME,"ReadJSON",error.what());
        }
    }

    // Application exit function
    void ExitApp()
    {
        // 👇
        // if (MODE != "DEV") {
        cout << translate["RebootSystem"].asString();
        getline(cin, Answer);
        string RebootCommand = database.GetValueFromDB("OS_Commands", "Reboot", OS_NAME);
        if (CheckAnswer(Answer) == true)
            system(RebootCommand != "Not Found" ? RebootCommand.c_str() : "");
        // }
        exit(0);
    }

    void GetArchitectureOS()
    {
#if defined(__x86_64__)
        Architecture = "amd64";
#elif __arm__ || __aarch64__ || _M_ARM64
        Architecture = "arm64";
#endif
    }
};

int main(int argc, char **argv)
{
// Checking the operating system and then writing the OS name to a variable
#if defined(_WIN32)
    // OS_NAME = "Windows";
    /* The bellow code is setting the console output code page to UTF-8 encoding in C++. */
    SetConsoleOutputCP(CP_UTF8);
#endif
    // Main class import
    MainApp app;
    // Calling up the main menu
    app.CommandManager();
    system("pause");
    return 0;
}
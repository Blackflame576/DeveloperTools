/*  GNU GENERAL PUBLIC LICENSE
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
#include <DeepForge-Toolset/DeepForge-Toolset.hpp>

using namespace std;

void Application::SetLanguage()
{
    std::string NumLang;
    LanguageChoices UserChoice;

    std::cout << "1. Russian" << std::endl;
    std::cout << "2. English" << std::endl;
    std::cout << "==> Choose language (default - 1): ";
    std::getline(cin, NumLang);

    if (NumLang.empty())
    {
        UserChoice = LanguageChoices::RUSSIAN;
    }
    else
    {
        UserChoice = static_cast<LanguageChoices>(stoi(NumLang) - 1);
    }

    switch (UserChoice)
    {
    case LanguageChoices::RUSSIAN:
        Language = "Russian";
        ReadJSON("Russian");
        break;
    case LanguageChoices::ENGLISH:
        Language = "English";
        ReadJSON("English");
        break;
    default:
        std::cout << InstallDelimiter << std::endl;
        std::cout << "Invalid choice, please choose again." << std::endl;
        std::cout << InstallDelimiter << std::endl;
        SetLanguage();
        break;
    }
    std::cout << InstallDelimiter << std::endl;
    CommandManager();
}

// Main menu function
void Application::CommandManager()
{
    using funct_t = void (Application::*)(void);
    std::unordered_map<int, funct_t> Commands = {
        {1, &Application::ReadySet},
        {2, &Application::ManualSelection},
        {3, &Application::InstallAllPackages},
        {4, &Application::SearchPackages},
        {5, &Application::SetLanguage},
        {6, &Application::ExitApp}};
    for (int i = 1; i < Commands.size() + 1; i++)
    {
        std::string index = "CommandManager_" + std::to_string(i);
        std::cout << translate[index].asString() << std::endl;
    }
    std::cout << translate["CommandManager_ch_answ"].asString();
    std::getline(cin, InstallTools);
    
    int NumCommand = 0;
    try
    {
        // If the user does not enter anything, then the manual application installation method is called by default.
        if (InstallTools.empty())
        {
            std::cout << InstallDelimiter << std::endl;
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
                    std::cout << InstallDelimiter << std::endl;
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
    catch (std::exception &error)
    {
        std::cout << translate["AnswerNotCorrect"].asString() << std::endl;
        logger.writeLog("Error", error.what());
        CommandManager();
    }
}

// Ready-made toolset for a specific programming language
void Application::ReadySet()
{
    try
    {
        std::string NameDevelopmnetPack;
        /* The bellow code is a C++ code snippet that displays a list of languages and prompts the
        user to choose a language. It then checks if the user's choice matches any of the
        elements in the `DevelopmentPacks` container and calls the `InstallDevelopmentPack`
        function if there is a match. */
        for (int i = 1; i < Languages.size() + 1; i++)
        {
            std::cout << i << ". " << Languages[i] << std::endl;
        }
        std::cout << translate["ChooseLanguage"].asString();
        std::getline(cin, LangReadySet);
        std::cout << InstallDelimiter << std::endl;
        if (LangReadySet.empty() == false)
        {
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
    }
    catch (std::exception &error)
    {
        std::string logText = "==> ❌ " + string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << logText << std::endl;
    }
    CommandManager();
}

// Function to install all packages
void Application::InstallAllPackages()
{
    try
    {
        // Update information about packages
        UpdateData();
        int output_func;
        std::cout << translate["AllPackages"].asString() << std::endl;
        // Displaying the name of all applications
        for (int i = 1; const auto &element : Packages)
        {
            std::string NamePackage = std::to_string(i) + ". " + element.first;
            std::string getNewString = NewString(NamePackage);
            if (Packages.size() % 2 == 0)
            {
                if (getNewString != "")
                {
                    std::cout << getNewString << std::endl;
                }
            }
            else
            {
                if (getNewString != "")
                {
                    std::cout << getNewString << std::endl;
                }
                if (i == Packages.size())
                {
                    std::cout << NamePackage << std::endl;
                    haveString = "";
                }
            }
            i++;
        }
        std::cout << translate["InstallAllPackages"].asString();
        std::getline(cin, Answer);
        Install = CheckAnswer(Answer);
        std::cout << InstallDelimiter << std::endl;
        if (Install == true)
        {
            for (const auto &element : Packages)
            {
                std::string name = element.first;
                std::cout << translate["Installing"].asString() << " " << name << " ..." << std::endl;
                // Application installation
                output_func = MainInstaller(name);
                if (output_func == 0)
                {
                    std::string SuccessText = "==> ✅ " + name + " " + translate["Installed"].asString();
                    std::cout << SuccessText << std::endl;
                }
                else if (output_func != 403)
                {
                    std::string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + name;
                    std::cerr << ErrorText << std::endl;
                }
                std::cout << InstallDelimiter << std::endl;
            }
        }
    }
    catch (std::exception &error)
    {
        std::string logText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << logText << std::endl;
    }
    // Calling up the main menu
    CommandManager();
}

// Application search function
void Application::SearchPackages()
{
    try
    {
        // Update information about packages
        UpdateData();
        // Declaring variables and dictionaries necessary for searching
        std::string SearchingPackage;
        bool isSearched = false;
        std::unordered_map<int, std::string> EnumeratePackages;
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;
        int output_func;
        std::cout << translate["PackageName"].asString();
        // Entering the name of the application
        std::getline(cin, SearchingPackage);

        SearchingPackage = to_lower(SearchingPackage);
        /* The bellow code is iterating through the elements in the "Packages" dictionary. It checks
        if the application name from the dictionary matches the entered application name or if
        it starts with the entered application name. If there is a match, it adds the element to
        the "EnumeratePackages" dictionary with a key of "i" and increments "i". */
        for (int i = 1; const auto &element : Packages)
        {
            std::string name = to_lower(element.first);
            // Checking if the application name from the Packages dictionary matches the entered application name
            if (SearchingPackage == name || name.rfind(SearchingPackage, 0) == 0)
            {
                isSearched = true;
                EnumeratePackages.insert(pair<int, std::string>(i, element.first));
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
            std::cout << translate["Result"].asString() << std::endl;
            /* The bellow code is iterating over a collection called `EnumeratePackages` and
            performing some operations on each element. */
            for (int i = 1; const auto &element : EnumeratePackages)
            {
                // std::cout << element.first << ". " << element.second << std::endl;
                /* The bellow code is concatenating the value of `element.first` (converted to a
                string) with a period and the value of `element.second` to form the string
                `NamePackage`. It then calls the function `NewString` with `NamePackage` as an
                argument and assigns the returned value to `getNewString`. */
                // Formatting output text
                std::string NamePackage = std::to_string(element.first) + ". " + element.second;
                std::string getNewString = NewString(NamePackage);
                if (EnumeratePackages.size() % 2 == 0)
                {
                    if (getNewString != "")
                    {
                        std::cout << getNewString << std::endl;
                    }
                }
                else
                {
                    if (getNewString != "")
                    {
                        std::cout << getNewString << std::endl;
                    }
                    if (i == EnumeratePackages.size())
                    {
                        std::cout << NamePackage << std::endl;
                        haveString = "";
                    }
                }
                i++;
            }
            std::cout << translate["SelectNumber"].asString();
            std::getline(cin, SelectPackages);
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
                std::cout << InstallDelimiter << std::endl;
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
                while ((pos = SelectPackages.find(delimiter)) != std::string::npos)
                {
                    token = SelectPackages.substr(0, pos);
                    if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
                    {
                        std::string name = EnumeratePackages[stoi(token)];
                        std::cout << InstallDelimiter << std::endl;
                        std::cout << translate["Installing"].asString() << " " << name << " ..." << std::endl;
                        // Application installation
                        output_func = MainInstaller(name);
                        if (output_func == 0)
                        {
                            std::string SuccessText = "==> ✅ " + name + " " + translate["Installed"].asString();
                            std::cout << SuccessText << std::endl;
                        }
                        else if (output_func != 403)
                        {
                            std::string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + name;
                            std::cerr << ErrorText << std::endl;
                        }
                        SelectPackages.erase(0, pos + delimiter.length());
                    }
                }
                if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
                {
                    std::string NamePackage = EnumeratePackages[stoi(SelectPackages)];
                    std::cout << InstallDelimiter << std::endl;
                    std::cout << translate["Installing"].asString() << " " << NamePackage << " ..." << std::endl;
                    // Installing the application with the most recently entered number
                    output_func = MainInstaller(NamePackage);
                    if (output_func == 0)
                    {
                        std::string SuccessText = "==> ✅ " + NamePackage + " " + translate["Installed"].asString();
                        std::cout << SuccessText << std::endl;
                    }
                    else if (output_func != 403)
                    {
                        std::string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                        std::cerr << ErrorText << std::endl;
                    }
                }
            }
        }
        // If no applications are found during the search, a message is displayed stating that nothing was found for this request.
        else
        {
            std::cerr << translate["QueryNotFound"].asString() << std::endl;
        }
    }
    catch (std::exception &error)
    {
        std::string logText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << logText << std::endl;
    }
    std::cout << InstallDelimiter << std::endl;
    // Calling up the main menu
    CommandManager();
}

void Application::ManualSelection()
{
    try
    {
        // Update information about packages
        UpdateData();
        std::unordered_map<int, std::string> EnumeratePackages;
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;
        int output_func;
        /* The bellow code is iterating over a map called "Packages" and performing some operations
        on each element. */
        for (int i = 1; const auto &element : Packages)
        {
            EnumeratePackages.insert(pair<int, std::string>(i, element.first));
            /* The bellow code is concatenating a string `NamePackage` with an integer `i` and a
            string `element.first`. It then calls a function `NewString` with `NamePackage` as
            an argument and assigns the result to `getNewString`. */
            // Formatting output text
            std::string NamePackage = std::to_string(i) + ". " + element.first;
            std::string getNewString = NewString(NamePackage);
            if (Packages.size() % 2 == 0)
            {
                if (getNewString != "")
                {
                    std::cout << getNewString << std::endl;
                }
            }
            else
            {
                if (getNewString != "")
                {
                    std::cout << getNewString << std::endl;
                }
                if (i == Packages.size())
                {
                    std::cout << NamePackage << std::endl;
                    haveString = "";
                }
            }
            i++;
        }
        std::cout << translate["SelectingPackages"].asString();
        // Entering Application Numbers
        std::getline(std::cin, SelectPackages);
        if (SelectPackages.empty() == false)
        {
            // Getting Application Numbers
            while ((pos = SelectPackages.find(delimiter)) != std::string::npos)
            {
                token = SelectPackages.substr(0, pos);
                if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
                {
                    std::string name = EnumeratePackages[stoi(token)];
                    std::cout << InstallDelimiter << std::endl;
                    std::cout << translate["Installing"].asString() << " " << name << " ..." << std::endl;
                    // Application installation
                    output_func = MainInstaller(name);
                    if (output_func == 0)
                    {
                        std::string SuccessText = "==> ✅ " + name + " " + translate["Installed"].asString();
                        std::cout << SuccessText << std::endl;
                    }
                    else if (output_func != 403)
                    {
                        std::string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + name;
                        std::cerr << ErrorText << std::endl;
                    }
                    SelectPackages.erase(0, pos + delimiter.length());
                }
            }
            if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
            {
                std::string NamePackage = EnumeratePackages[stoi(SelectPackages)];
                std::cout << InstallDelimiter << std::endl;
                std::cout << translate["Installing"].asString() << " " << NamePackage << " ..." << std::endl;
                // Installing the application with the most recently entered number
                output_func = MainInstaller(NamePackage);
                if (output_func == 0)
                {
                    std::string SuccessText = "==> ✅ " + NamePackage + " " + translate["Installed"].asString();
                    std::cout << SuccessText << std::endl;
                }
                else if (output_func != 403)
                {
                    std::string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                    std::cerr << ErrorText << std::endl;
                }
            }
        }
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
    }
    std::cout << InstallDelimiter << std::endl;
    // Calling up the main menu
    CommandManager();
}

// JSON file reading function with interface localization
void Application::ReadJSON(std::string language)
{
    try
    {
        if (language == "Russian")
        {
            std::string LocalePath = LocaleFolder + "/locale_ru.json";
            std::ifstream file(LocalePath);
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
            std::string LocalePath = LocaleFolder + "/locale_en.json";
            std::ifstream file(LocalePath);
            // File open check
            if (file.is_open())
            {
                // Dictionary entry with translation
                file >> translate;
                file.close();
            }
        }
    }
    catch (std::exception &error)
    {
        // Error output
        std::string logText = "Function: ReadJSON." + std::string(error.what());
        logger.writeLog("Error", logText);
        logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "ReadJSON", error.what());
    }
}

// Application exit function
void Application::ExitApp()
{
    // 👇
    // if (MODE != "DEV") {
    // std::cout << translate["RebootSystem"].asString();
    // std::getline(cin, Answer);
    // std::string RebootCommand = database.GetValueFromDB("OS_Commands", "Reboot", OS_NAME);
    // if (CheckAnswer(Answer) == true)
    //     system(RebootCommand != "Not Found" ? RebootCommand.c_str() : "");
    // }
    exit(0);
}

int main(int argc, char **argv)
{
    #if defined(__APPLE__)
    std::filesystem::path current_dir = argv[0];
    std::filesystem::current_path(current_dir.parent_path().generic_string());
    #endif
// Checking the operating system and then writing the OS name to a variable
#if defined(_WIN32)
    /* The bellow code is setting the console output code page to UTF-8 encoding in C++. */
    SetConsoleOutputCP(CP_UTF8);
#endif
    // Main class import
    Application app;
    // Calling up the main menu
    app.CommandManager();
    system("pause");
    return 0;
}
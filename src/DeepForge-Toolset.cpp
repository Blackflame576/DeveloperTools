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

void Application::SetLanguage()
{
    std::string NumLang;
    LanguageChoices UserChoice;

    std::cout << "1. Russian" << std::endl;
    std::cout << "2. English" << std::endl;
    std::cout << "==> Choose language (default - 1): ";
    std::getline(std::cin, NumLang);

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
        this->SetLanguage();
        break;
    }
    std::cout << InstallDelimiter << std::endl;
    CommandManager();
}

// Main menu function
void Application::CommandManager()
{
    try
    {
        int NumCommand = 0;
        using funct_t = void (Application::*)(void);
        std::unordered_map<int, funct_t> Commands = {
            {1, &Application::ReadySet},
            {2, &Application::ManualSelection},
            {3, &Application::InstallAllPackages},
            {4, &Application::SearchPackages},
            {5, &Application::SetLanguage},
            {6, &Application::Exit}};

        for (int i = 1; i < Commands.size() + 1; i++)
        {
            std::string index = "CommandManager_" + std::to_string(i);
            std::cout << translate[index].asString() << std::endl;
        }

        std::cout << translate["CommandManager_ch_answ"].asString();
        std::getline(std::cin, NumMenu);

        if (NumMenu.empty())
        {
            std::cout << InstallDelimiter << std::endl;
            (this->*(Commands[2]))();
        }
        else
        {
            removeNonDigits(NumMenu);
            NumCommand = stoi(NumMenu);
            std::cout << InstallDelimiter << std::endl;
            if (Commands.find(NumCommand) != Commands.end())
            {
                (this->*(Commands[NumCommand]))();
            }
            // If the entered digit is not among the proposed list of digits, then the main menu is called
            else
            {
                this->CommandManager();
            }
        }
    }
    catch (std::exception &error)
    {
        std::cout << translate["AnswerNotCorrect"].asString() << std::endl;
        logger.writeLog("Error", fmt::format("CommandManager.{}", error.what()));
        this->CommandManager();
    }
}

// Ready-made toolset for a specific programming language
void Application::ReadySet()
{
    try
    {
        int numLanguage;
        int LanguagesSize = database.GetArraySize("DevelopmentPacks","Language");
        std::string NameDevelopmnetPack;
        DB::DatabaseValues parameters;
        std::cout << LanguagesSize << std::endl;
        PrintFormatted(Languages,LanguagesSize);
        std::cout << translate["ChooseLanguage"].asString();
        std::getline(std::cin, LangReadySet);
        std::cout << InstallDelimiter << std::endl;
        if (!LangReadySet.empty())
        {
            removeNonDigits(LangReadySet);
            numLanguage = stoi(LangReadySet) - 1;
            if (LanguagesSize - numLanguage >=  0)
            {
                parameters = {{"Language",Languages[numLanguage]}};
                NameDevelopmnetPack = database.GetValueFromRow("DevelopmentPacks","Toolset",parameters);
                this->InstallDevelopmentPack(NameDevelopmnetPack);
            }   
        }
        std::cout << InstallDelimiter << std::endl;
    }
    catch (std::exception &error)
    {
        logger.writeLog("Error", fmt::format("ReadySet.{}",error.what()));
        std::cerr << fmt::format("==> ❌ ReadySet.{}", error.what()) << std::endl;
        std::cout << InstallDelimiter << std::endl;
    }
    this->CommandManager();
}

// Function to install all packages
void Application::InstallAllPackages()
{
    try
    {
        EnumStringHashMap EnumeratePackages;
        // Update information about packages
        this->UpdateData();
        std::cout << translate["AllPackages"].asString() << std::endl;
        // Displaying the name of all applications
        EnumeratePackages = Enumerate<EnumStringHashMap>(Packages);
        PrintFormatted(EnumeratePackages,EnumeratePackages.size());
        std::cout << translate["InstallAllPackages"].asString();
        std::getline(std::cin, Answer);
        Install = CheckAnswer(Answer);

        if (Install)
        {
            for (const auto &element : Packages)
            {
                this->MainInstaller(element.first);
            }
        }
        std::cout << InstallDelimiter << std::endl;
    }
    catch (std::exception &error)
    {
        logger.writeLog("Error", fmt::format("InstallAllPackages.{}",error.what()));
        std::cerr << fmt::format("==> ❌ InstallAllPackages.{}", error.what()) << std::endl;
        std::cout << InstallDelimiter << std::endl;
    }
    // Calling up the main menu
    this->CommandManager();
}

// Application search function
void Application::SearchPackages()
{
    try
    {
        // Update information about packages
        this->UpdateData();
        // Declaring variables and dictionaries necessary for searching
        int result;
        bool isSearched = false;
        std::string NamePackage;
        std::string SelectedPackages;
        std::string SearchingPackage;
        EnumStringHashMap EnumeratePackages;
        std::cout << translate["PackageName"].asString();
        // Entering the name of the application
        std::getline(std::cin, SearchingPackage);

        SearchingPackage = to_lower(SearchingPackage);

        for (int i = 1; const auto &element : Packages)
        {
            NamePackage = to_lower(element.first);
            // Checking if the application name from the Packages dictionary matches the entered application name
            if (SearchingPackage == NamePackage || NamePackage.rfind(SearchingPackage, 0) == 0)
            {
                isSearched = true;
                EnumeratePackages.insert(std::pair<int, std::string>(i, element.first));
                i++;
            }
        }

        if (isSearched)
        {
            std::cout << translate["Result"].asString() << std::endl;

            PrintFormatted(EnumeratePackages,EnumeratePackages.size());
            // PrintEnummeratedPackages(EnumeratePackages);

            std::cout << translate["SelectNumber"].asString();
            std::getline(std::cin, SelectedPackages);

            InstallIfFound(SelectedPackages,EnumeratePackages,MainInstallerLink);
        }
        // If no applications are found during the search, a message is displayed stating that nothing was found for this request.
        else
        {
            std::cerr << translate["QueryNotFound"].asString() << std::endl;
        }
        std::cout << InstallDelimiter << std::endl;
    }
    catch (std::exception &error)
    {
        logger.writeLog("Error", fmt::format("SearchPackages.{}",error.what()));
        std::cerr << fmt::format("==> ❌ SearchPackages.{}", error.what()) << std::endl;
        std::cout << InstallDelimiter << std::endl;
    }
    // Calling up the main menu
    this->CommandManager();
}

void Application::ManualSelection()
{
    try
    {
        // Update information about packages
        this->UpdateData();
        std::unordered_map<int, std::string> EnumeratePackages;
        std::string SelectedPackages;
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;
        EnumeratePackages = Enumerate<EnumStringHashMap>(Packages);
        PrintFormatted(EnumeratePackages,EnumeratePackages.size());
        // PrintEnummeratedPackages(EnumeratePackages);
        // PrintPackagesWithEnum(Packages,EnumeratePackages);

        std::cout << translate["SelectingPackages"].asString();
        // Entering Application Numbers
        std::getline(std::cin, SelectedPackages);

        InstallIfFound(SelectedPackages,EnumeratePackages,MainInstallerLink);
        std::cout << InstallDelimiter << std::endl;
    }
    catch (std::exception &error)
    {
        logger.writeLog("Error", fmt::format("ManualSelection.{}",error.what()));
        std::cerr << fmt::format("==> ❌ ManualSelection.{}", error.what()) << std::endl;
        std::cout << InstallDelimiter << std::endl;
    }
    // Calling up the main menu
    this->CommandManager();
}

// JSON file reading function with interface localization
void Application::ReadJSON(std::string language)
{
    try
    {
        std::string LocalePath;
        if (language == "Russian")
        {
            LocalePath = LocaleFolder + "/locale_ru.json";
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
            LocalePath = LocaleFolder + "/locale_en.json";
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
        logger.writeLog("Error", fmt::format("==> ❌ ReadJSON.", error.what()));
        logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "ReadJSON", error.what());
    }
}

// Application exit function
void Application::Exit()
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
    std::filesystem::path current_dir = argv[0];
    std::filesystem::current_path(current_dir.parent_path().generic_string());
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
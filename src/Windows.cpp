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
#include <DeepForge-Toolset/Windows.hpp>

int Windows::Installer::InstallMake()
{
    try
    {
        std::string NewMakeDir = database.GetValueFromDB("PackagesFromSource_Windows", "Make", "Directory");
        std::string ArchivePath = ProjectDir + "/utils/Make_3.81.zip ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewMakeDir;
        if (std::filesystem::exists(NewMakeDir) && std::filesystem::is_empty(NewMakeDir) == false)
        {
            std::cout << "✅ Make " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewMakeDir << std::endl;
            return 403;
        }
        /* The bellow code is checking if a directory named "NewMakeDir" exists using the
        std::filesystem::exists function. If the directory does not exist, it creates the
        directory using the std::filesystem::create_directory function. */
        if (std::filesystem::exists(NewMakeDir) == false)
        {
            std::filesystem::create_directory(NewMakeDir);
        }
        else if (std::filesystem::exists(NewMakeDir) && std::filesystem::is_empty(NewMakeDir) == true)
        {
            std::filesystem::remove_all(NewMakeDir);
            std::filesystem::create_directory(NewMakeDir);
        }
        unpackArchive(ArchivePath, NewMakeDir);
        system(Command_AddPath.c_str());
        std::cout << "Make " << translate["Located"].asString() << " " << NewMakeDir << std::endl;
        return 0;
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}
int Windows::Installer::InstallVCpkg()
{
    std::string NewVCpkgDir = database.GetValueFromDB("PackagesFromSource_Windows", "vcpkg", "Directory");
    std::string VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Windows", "vcpkg", "Url");
    std::string PathRepository = NewVCpkgDir + "vcpkg";
    std::string Command = "cd " + NewVCpkgDir + " && git clone " + VCpkgRepository;
    std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewVCpkgDir + "vcpkg";
    std::string Command_Install = NewVCpkgDir + "vcpkg\\bootstrap-vcpkg.bat -disableMetrics";
    if (std::filesystem::exists(PathRepository) && std::filesystem::is_empty(PathRepository) == false)
    {
        std::cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << PathRepository << std::endl;
        return 403;
    }
    MainInstaller("Git");
    result = system(Command.c_str());
    if (result == 0)
    {
        system(Command_Install.c_str());
        system(Command_AddPath.c_str());
        std::cout << "vcpkg " << translate["Located"].asString() << " " << PathRepository << std::endl;
        return 0;
    }
    else
    {
        return -1;
    }
}
int Windows::Installer::InstallPHP()
{
    try
    {
        std::string NewPHPDir = database.GetValueFromDB("PackagesFromSource_Windows", "PHP", "Directory");
        std::string ArchivePath = ProjectDir + "/utils/php-8.2.9.zip ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewPHPDir;
        if (std::filesystem::exists(NewPHPDir) && std::filesystem::is_empty(NewPHPDir) == false)
        {
            std::cout << "✅ PHP " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewPHPDir << std::endl;
            return 403;
        }
        if (std::filesystem::exists(NewPHPDir) == false)
        {
            std::filesystem::create_directory(NewPHPDir);
        }
        else if (std::filesystem::exists(NewPHPDir) == true && std::filesystem::is_empty(NewPHPDir) == true)
        {
            std::filesystem::remove_all(NewPHPDir);
            std::filesystem::create_directory(NewPHPDir);
        }
        unpackArchive(ArchivePath, NewPHPDir);
        system(Command_AddPath.c_str());
        std::cout << "PHP " << translate["Located"].asString() << " " << NewPHPDir << std::endl;
        return 0;
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}
int Windows::Installer::InstallEclipse()
{
    try
    {
        std::string EclipseUrl = database.GetValueFromDB("PackagesFromSource_Windows", "Eclipse IDE", "Url");
        std::string NewEclipseDir = database.GetValueFromDB("PackagesFromSource_Windows", "Eclipse IDE", "Directory");
        std::string ArchiveDir = ProjectDir + "/Downloads";
        std::string ArchivePath = ArchiveDir + "/eclipse-java-2023-06-R-win32-x86_64.zip ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewEclipseDir + "eclipse";
        if (std::filesystem::exists("C:\\eclipse") && std::filesystem::is_empty("C:\\eclipse") == false)
        {
            std::cout << "✅ Eclipse IDE " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewEclipseDir << "eclipse" << std::endl;
            return 403;
        }
        if (std::filesystem::exists(ArchiveDir) == false)
        {
            std::filesystem::create_directory(ArchiveDir);
        }
        download(EclipseUrl, ArchiveDir,true);
        unpackArchive(ArchivePath, NewEclipseDir);
        system(Command_AddPath.c_str());
        std::filesystem::remove(ArchivePath);
        std::cout << "Eclipse " << translate["Located"].asString() << " " << NewEclipseDir << "eclipse" << std::endl;
        return 0;
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}
int Windows::Installer::InstallKotlin()
{
    try
    {
        std::string NewKotlinDir = database.GetValueFromDB("PackagesFromSource_Windows", "Kotlin", "Directory");
        std::string KotlinUrl = database.GetValueFromDB("PackagesFromSource_Windows", "Kotlin", "Url");
        std::string ArchiveDir = ProjectDir + "/Downloads";
        std::string ArchivePath = ArchiveDir + "/kotlin-compiler-1.8.22.zip ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewKotlinDir;
        if (std::filesystem::exists("C:\\kotlinc") && std::filesystem::is_empty("C:\\kotlinc") == false)
        {
            std::cout << "✅ Kotlin " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewKotlinDir << "kotlinc" << std::endl;
            return 403;
        }
        if (std::filesystem::exists(ArchiveDir) == false)
        {
            std::filesystem::create_directory(ArchiveDir);
        }
        download(KotlinUrl, ArchiveDir,true);
        unpackArchive(ArchivePath, NewKotlinDir);
        system(Command_AddPath.c_str());
        std::filesystem::remove(ArchivePath);
        std::cout << "Kotlin " << translate["Located"].asString() << " " << NewKotlinDir << std::endl;
        return 0;
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}
int Windows::Installer::InstallWget()
{
    try
    {
        std::string NewWgetDir = database.GetValueFromDB("PackagesFromSource_Windows", "Wget", "Directory");
        std::string WgetUrl = database.GetValueFromDB("PackagesFromSource_Windows", "Wget", "Url");
        std::string ApplicationPath = NewWgetDir + "/wget.exe ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewWgetDir;
        if (std::filesystem::exists(NewWgetDir) && std::filesystem::is_empty(NewWgetDir) == false)
        {
            std::cout << "✅ Wget " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewWgetDir << std::endl;
            return 403;
        }
        if (std::filesystem::exists(NewWgetDir) == false)
        {
            std::filesystem::create_directory(NewWgetDir);
        }
        else if (std::filesystem::exists(NewWgetDir) == true && std::filesystem::is_empty(NewWgetDir) == true)
        {
            std::filesystem::remove_all(NewWgetDir);
            std::filesystem::create_directory(NewWgetDir);
        }
        download(WgetUrl, NewWgetDir,true);
        system(Command_AddPath.c_str());
        std::cout << "Wget " << translate["Located"].asString() << " " << NewWgetDir << std::endl;
        return 0;
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}
int Windows::Installer::InstallNginx()
{
    try
    {
        std::string NewNginxDir = database.GetValueFromDB("PackagesFromSource_Windows", "Nginx", "Directory");
        std::string ArchivePath = ProjectDir + "/utils/Nginx-1.25.1.zip ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewNginxDir + "Nginx-1.25.1";
        if (std::filesystem::exists("C:\\Nginx-1.25.1") && std::filesystem::is_empty("C:\\Nginx-1.25.1") == false)
        {
            std::cout << "✅ Nginx " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewNginxDir << "Nginx-1.25.1" << std::endl;
            return 403;
        }
        if (std::filesystem::exists(ArchivePath))
        {
            unpackArchive(ArchivePath, NewNginxDir);
            system(Command_AddPath.c_str());
            std::cout << "Nginx " << translate["Located"].asString() << " " << NewNginxDir << "Nginx-1.25.1" << std::endl;
            return 0;
        }
        else
        {
            std::string ErrorText = translate["LOG_ZIP_ARCHIVE_NOT_FOUND"].asString();
            logger.writeLog("Error", ErrorText);
            return -1;
        }
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}
int Windows::Installer::InstallRedis()
{
    try
    {
        std::string NewRedisDir = database.GetValueFromDB("PackagesFromSource_Windows", "Redis", "Directory");
        std::string RedisUrl = database.GetValueFromDB("PackagesFromSource_Windows", "Redis", "Url");
        std::string name = (RedisUrl.substr(RedisUrl.find_last_of("/")));
        std::string ArchiveDir = ProjectDir + "/Downloads";
        std::string ArchivePath = ArchiveDir + "/" + name + " ";
        std::string Command_AddPath = ProjectDir + "/utils/pathman.exe add " + NewRedisDir;
        if (std::filesystem::exists(NewRedisDir) && std::filesystem::is_empty(NewRedisDir) == false)
        {
            std::cout << "✅ Redis " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << NewRedisDir << std::endl;
            return 403;
        }
        if (std::filesystem::exists(ArchiveDir) == false)
        {
            std::filesystem::create_directory(ArchiveDir);
        }
        download(RedisUrl, ArchiveDir,true);
        if (std::filesystem::exists(NewRedisDir) == false)
        {
            std::filesystem::create_directory(NewRedisDir);
        }
        else if (std::filesystem::exists(NewRedisDir) && std::filesystem::is_empty(NewRedisDir) == true)
        {
            std::filesystem::remove_all(NewRedisDir);
            std::filesystem::create_directory(NewRedisDir);
        }
        unpackArchive(ArchivePath, NewRedisDir);
        system(Command_AddPath.c_str());
        std::filesystem::remove(ArchivePath);
        std::cout << "Redis " << translate["Located"].asString() << " " << NewRedisDir << std::endl;
        return 0;
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
        return 403;
    }
}

/**
 * The function checks if WinGet is installed and installs it if necessary.
 */
void Windows::Installer::InstallWinGet()
{
    std::cout << "WinGet ";
    result = system("winget -v");
    if (result != 0)
    {
        std::cout << translate["Installing"].asString() << " "
                  << "winget"
                  << " ..." << std::endl;
        std::string Command = "powershell.exe " + ProjectDir + "/Scripts/InstallWinGet.ps1";
        system(Command.c_str());
        std::cout << "✅ "
                  << "winget"
                  << " " << translate["Installed"].asString() << std::endl;
    }
}

void Windows::Installer::unpackArchive(std::string path_from, std::string path_to)
{
    std::string unpack_command = "tar -xf" + path_from + " --directory " + path_to;
    system(unpack_command.c_str());
}
void Windows::Installer::MakeDirectory(std::string dir)
{
    std::string currentDir;
    std::string fullPath = "";
    std::string delimiter = "\\";
    size_t pos = 0;
    while ((pos = dir.find(delimiter)) != std::string::npos)
    {
        currentDir = dir.substr(0, pos);
        if (fullPath != "")
        {
            fullPath = fullPath + "\\" + currentDir;
            if (std::filesystem::exists(fullPath) == false)
            {
                std::filesystem::create_directory(fullPath);
            }
        }
        else
        {
            fullPath = currentDir + "\\";
        }
        dir.erase(0, pos + delimiter.length());
    }
    if (fullPath != "")
    {
        fullPath = fullPath + "\\" + dir;
    }
    else
    {
        fullPath = dir + "\\";
    }
    if (std::filesystem::exists(fullPath) == false)
    {
        std::filesystem::create_directory(fullPath);
    }
}

int Windows::Installer::MainInstaller(std::string Name)
{
    std::string Value = database.GetValueFromDB("Applications", Name, "Windows");
    if (Value != "ManualInstallation")
    {
        result = system(Value.c_str());
    }
    else if (PackagesFromSource.find(Name) != PackagesFromSource.end())
    {
        result = (this->*(PackagesFromSource[Name]))();
    }
    else
    {
        std::string InstallCommand = database.GetValueFromDB("PackagesFromSource_Windows", Name, "Command");
        if (InstallCommand != "Empty")
            result = system(InstallCommand.c_str());
    }
    return result;
}

void Windows::Installer::UpdateData()
{
    try
    {
        database.open(&DatabasePath);
        Packages = database.GetAllValuesFromDB("Applications", "Windows");
        DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
    }
    catch (std::exception &error)
    {
        std::string LogText = translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString() + std::string(error.what());
        logger.writeLog("Error", LogText);
    }
}

void Windows::Installer::InstallDevelopmentPack(std::string n)
{
    try
    {
        UpdateData();
        // Init variables
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Windows");
        std::map<int, std::string> EnumeratePackages;
        std::string NamePackage;
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;
        /* The bellow code is retrieving values from a database for a specific development pack on the
        Windows platform. It then iterates over the retrieved values and creates a map of enumerated
        packages. It also creates a string representation of each package with its corresponding
        index. The code then checks if the number of packages is even or odd and prints the string
        representation accordingly. */
        for (int i = 1; const auto &element : DevelopmentPack)
        {
            /* The bellow code is inserting packages into a map called EnumeratePackages, where the
            key is an integer and the value is a string. It then creates a string called
            NamePackage by concatenating the key and the package name. It then calls a function
            called NewString with NamePackage as an argument and assigns the result to
            getNewString. */
            EnumeratePackages.insert(std::pair<int, std::string>(i, element.first));
            NamePackage = std::to_string(i) + ". " + element.first;
            // Formatting output text
            std::string getNewString = NewString(NamePackage);
            if (DevelopmentPack.size() % 2 == 0)
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
                if (i == DevelopmentPack.size())
                {
                    std::cout << NamePackage << std::endl;
                    haveString = "";
                }
            }
            i++;
        }
        std::cout << "" << std::endl;
        std::cout << translate["SelectingPackages"].asString();
        std::getline(std::cin, SelectPackages);
        if (SelectPackages.empty() == false)
        {
            /* The bellow code is splitting a string called `SelectPackages` into multiple tokens using a
            delimiter (","). It then checks if each token is present in a map called
            `EnumeratePackages`. If a token is found in the map, it retrieves the corresponding value
            (package name) and performs some installation-related operations. These operations include
            printing messages, calling a `MainInstaller` function with the package name, and logging
            success or error messages based on the output of the `MainInstaller` function. Finally, it
            removes the Bar::Processed token from the `SelectPackages` string and continues the loop until
            all tokens */
            while ((pos = SelectPackages.find(delimiter)) != std::string::npos)
            {
                token = SelectPackages.substr(0, pos);
                if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
                {
                    NamePackage = EnumeratePackages[stoi(token)];
                    // =============================
                    std::cout << InstallDelimiter << std::endl;
                    std::cout << translate["Installing"].asString() << " " << NamePackage << " ..." << std::endl;
                    // Install application
                    output_func = MainInstaller(NamePackage);
                    // Loggin and print messages
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
                    SelectPackages.erase(0, pos + delimiter.length());
                }
            }

            /* The bellow code is checking if a package with a specific ID exists in a map called
            EnumeratePackages. If the package exists, it retrieves the name of the package and proceeds
            to install it using the MainInstaller function from the Installer object. After
            installation, it logs and prints success or error messages based on the output of the
            installation Bar::Process. */
            if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
            {
                NamePackage = EnumeratePackages[stoi(SelectPackages)];
                if (NamePackage != "AllPackages")
                {
                    std::cout << InstallDelimiter << std::endl;
                    std::cout << translate["Installing"].asString() << " " << NamePackage << " ..." << std::endl;
                    // Install application
                    output_func = MainInstaller(NamePackage);
                    // Logging and print messages
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
                else
                {
                    DevelopmentPack.erase("AllPackages");
                    for (const auto &element : DevelopmentPack)
                    {
                        std::cout << InstallDelimiter << std::endl;
                        std::cout << translate["Installing"].asString() << " " << element.first << " ..." << std::endl;
                        output_func = MainInstaller(element.first);
                        if (output_func == 0)
                        {
                            std::string SuccessText = "==> ✅ " + element.first + " " + translate["Installed"].asString();
                            std::cout << SuccessText << std::endl;
                        }
                        else if (output_func != 403)
                        {
                            std::string ErrorText = "==> ❌ " + translate["ErrorInstall"].asString() + " " + element.first;
                            std::cerr << ErrorText << std::endl;
                        }
                    }
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
}

void Windows::Installer::downloadDatabase()
{
    try
    {
        /* This code block checks if the database file specified by `DatabasePath` exists.
        If the file does not exist, it proceeds to download the file from a specified URL using the libcurl library. */
        if (std::filesystem::exists(DatabasePath) == false)
        {
            std::string url = "https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/InstallerUtils/AppInstaller.db";
            std::string name = (url.substr(url.find_last_of("/")));
            std::string filename = ProjectDir + "/" + name.replace(name.find("/"), 1, "");
            FILE *file = fopen(filename.c_str(), "wb");
            CURL *curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
            curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
            CURLcode response = curl_easy_perform(curl);
            /* `curl_easy_cleanup(curl);` is a function call to clean up and release resources associated with a CURL handle. It is used to free the resources allocated by `curl_easy_init()` function, which initializes a CURL handle for making HTTP requests. This function should be called after the request is completed or when the handle is no longer needed to avoid memory leaks. */
            curl_easy_cleanup(curl);
            fclose(file);
            /* This code block is checking the response from the libcurl library after performing an HTTP request. If the response is not CURLE_OK (indicating a successful request), it enters the switch statement to handle different error cases. Depending on the specific error code, it logs an appropriate error message using the logger object. */
            if (response != CURLE_OK)
            {
                switch (response)
                {
                case CURLE_COULDNT_CONNECT:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_COULDNT_CONNECT"].asString());
                case CURLE_COULDNT_RESOLVE_HOST:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                case CURLE_COULDNT_RESOLVE_PROXY:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                case CURLE_UNSUPPORTED_PROTOCOL:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                case CURLE_SSL_CONNECT_ERROR:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                }
            }
        }
    }
    catch (std::exception &error)
    {
        std::string logText = translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString() + std::string(error.what());
        logger.writeLog("Error", logText);
    }
}

int Windows::Installer::download(std::string url, std::string dir,bool Progress)
{
    try
    {
        withProgress = Progress;
        std::string name = (url.substr(url.find_last_of("/")));
        std::string filename = dir + "/" + name.replace(name.find("/"), 1, "");
        FILE *file = fopen(filename.c_str(), "wb");
        CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &CallbackProgress);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        CURLcode response = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(file);
        /* The bellow code is checking the value of the variable "response" and performing
        different actions based on its value. If the value of "response" is not equal to
        CURLE_OK, it enters a switch statement. Inside the switch statement, it checks the
        value of "response" against different cases and performs specific actions for each
        case. The actions involve writing and logging different error messages based on the
        value of "response". */
        if (response != CURLE_OK)
        {
            switch (response)
            {
            case CURLE_COULDNT_CONNECT:
                throw std::domain_error(translate["LOG_ERROR_CURLE_COULDNT_CONNECT"].asString());
                break;
            case CURLE_COULDNT_RESOLVE_HOST:
                throw std::domain_error(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                break;
            case CURLE_COULDNT_RESOLVE_PROXY:
                throw std::domain_error(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                break;
            case CURLE_UNSUPPORTED_PROTOCOL:
                throw std::domain_error(translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                break;
            case CURLE_SSL_CONNECT_ERROR:
                throw std::domain_error(translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                break;
            }
        }
        if (Progress == true)
        {
            // If the progress bar is not completely filled in, then paint over manually
            for (int i = progressbar.progress; i < 100; i++)
            {
                progressbar.update(LastSize, LastTotalSize);
            }
            // Reset all variables and preferences
            progressbar.resetAll();
            Percentage = 0;
            TempPercentage = 0;
        }
    }
    catch (std::exception &error)
    {
        std::string logText = "==> ❌ " + std::string(error.what());
        logger.sendError(NameProgram, Architecture, __channel__, OS_NAME, "download()", error.what());
        std::cerr << logText << std::endl;
    }
}
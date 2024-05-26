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
#include <DeepForge-Toolset/Linux.hpp>

/*  The `unpackArchive` function takes two parameters: `path_from` and `path_to`.
    It uses the `Unzipper` class to extract the contents of an archive file located at `path_from` and saves them to the directory specified by `path_to`.
    After extracting the contents, the function closes the `Unzipper` object.
*/
void Linux::Installer::UnpackArchive(std::string path_from, std::string path_to)
{
    try
    {
        MakeDirectory(path_to);

        mz_zip_archive zip_archive;
        memset(&zip_archive, 0, sizeof(zip_archive));

        mz_zip_reader_init_file(&zip_archive, path_from.c_str(), 0);

        for (int i = 0; i < mz_zip_reader_get_num_files(&zip_archive); i++)
        {
            mz_zip_archive_file_stat file_stat;
            mz_zip_reader_file_stat(&zip_archive, i, &file_stat);

            std::string output_path = path_to + "/" + file_stat.m_filename;
            std::filesystem::path path(output_path);
            std::filesystem::create_directories(path.parent_path());
            if (endsWith(output_path, "/"))
            {
                MakeDirectory(output_path);
            }
            else
            {
                std::ofstream out(output_path, std::ios::binary);
                if (!out)
                {
                    std::cerr << "Failed to create file: " << output_path << std::endl;
                    continue;
                }
                size_t fileSize = file_stat.m_uncomp_size;
                void *fileData = mz_zip_reader_extract_to_heap(&zip_archive, file_stat.m_file_index, &fileSize, 0);
                if (!fileData)
                {
                    throw std::runtime_error("Failed to extract file: " + std::string(file_stat.m_filename));
                }

                out.write(static_cast<const char *>(fileData), fileSize);
                mz_free(fileData);

                out.close();
            }
        }

        mz_zip_reader_end(&zip_archive);
    }
    catch (std::exception &error)
    {
        std::string logText = "==> ❌ Function: UnpackArchive." + std::string(error.what());
        logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "UnpackArchive()", error.what());
        std::cerr << logText << std::endl;
    }
}

void Linux::Installer::InstallDevelopmentPack(std::string n)
{
    try
    {
        UpdateData();
        /* The above code is retrieving values from a database for a specific development pack on the
        Linux platform. It then iterates over the retrieved values and creates a map of enumerated
        packages. It also creates a string representation of each package with its corresponding
        index. The code then checks if the number of packages is even or odd and prints the string
        representation accordingly. */
#if defined(__x86_64__)
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Linux_amd64");
#elif __arm__ || __aarch64__ || _M_ARM64
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Linux_arm64");
#endif
        std::map<int, std::string> EnumeratePackages;
        std::string NamePackage;
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;
        int output_func;
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
        getline(std::cin, SelectPackages);
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
        std::string LogText = "==> ❌ " + std::string(error.what());
        logger.writeLog("Error", std::string(error.what()));
        std::cerr << LogText << std::endl;
    }
    std::cout << InstallDelimiter << std::endl;
}

int Linux::Installer::InstallGoogleChrome()
{
    std::string NewVCpkgDir;
    std::string VCpkgRepository;
    std::string PathRepository;
    std::string Command;
    std::string Command_AddPath;
    std::string Command_Install;
    int result;
#if defined(__x86_64__)
    NewVCpkgDir = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", "Directory");
    VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", "Url");
#elif __arm__ || __aarch64__ || _M_ARM64
    NewVCpkgDir = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", "Directory");
    VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", "Url");
#endif
    PathRepository = NewVCpkgDir + "vcpkg";
    std::cout << PathRepository << std::endl;
    if (std::filesystem::exists(PathRepository) && !std::filesystem::is_empty(PathRepository))
    {
        std::cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << PathRepository << std::endl;
        return 403;
    }
#if defined(__x86_64__)
    std::string InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
    std::string InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", PackageManager);
#endif
    Command = "cd " + NewVCpkgDir + " && sudo git clone " + VCpkgRepository;
    Command_Install = "sudo " + NewVCpkgDir + "vcpkg/bootstrap-vcpkg.sh -disableMetrics";
    Command_AddPath = "sudo ./utils/pathman-linux-amd64 add /usr/bin/vcpkg";
    system(InstallDependenciesCommand.c_str());
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

std::string Linux::Installer::GetNameDistribution()
{
    std::ifstream stream("/etc/os-release");
    std::string line;
    std::regex nameRegex("^NAME=\"(.*?)\"$");
    std::smatch match;
    std::string name;
    while (std::getline(stream, line))
    {
        if (std::regex_search(line, match, nameRegex))
        {
            name = match[1].str();
            break;
        }
    }
    return name;
}

/**
 * The function `InstallVCpkg()` installs vcpkg package manager on Windows.
 *
 * @return an integer value. The possible return values are:
 * - 403: Indicates that vcpkg is already installed in the specified directory.
 * - 0: Indicates that vcpkg has been successfully installed and located in the specified
 * directory.
 */
int Linux::Installer::InstallVCpkg()
{
    std::string NewVCpkgFolder;
    std::string VCpkgRepository;
    std::string PathRepository;
    std::string Command;
    std::string Command_AddPath;
    std::string Command_Install;
    std::string InstallDependenciesCommand;
    int result;
#if defined(__x86_64__)
    NewVCpkgFolder = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", "Directory");
    VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", "Url");
#elif __arm__ || __aarch64__ || _M_ARM64
    NewVCpkgFolder = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", "Directory");
    VCpkgRepository = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", "Url");
#endif
    PathRepository = NewVCpkgFolder + "vcpkg";
    if (std::filesystem::exists(PathRepository) && !std::filesystem::is_empty(PathRepository))
    {
        std::cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " " << translate["in"].asString() << " " << PathRepository << std::endl;
        return 403;
    }
#if defined(__x86_64__)
    InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "vcpkg", PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
    InstallDependenciesCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "vcpkg", PackageManager);
#endif
    Command = "cd " + NewVCpkgFolder + " && sudo git clone " + VCpkgRepository;
    Command_Install = "sudo " + NewVCpkgFolder + "vcpkg/bootstrap-vcpkg.sh -disableMetrics";
    Command_AddPath = "sudo ./utils/pathman-linux-amd64 add /usr/bin/vcpkg";
    system(InstallDependenciesCommand.c_str());
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

void Linux::Installer::UpdateData()
{
    try
    {
        database.open(&DatabasePath);
#if defined(__x86_64__)
        Packages = database.GetAllValuesFromDB("Applications", "Linux_amd64");
#elif __arm__ || __aarch64__ || _M_ARM64
        Packages = database.GetAllValuesFromDB("Applications", "Linux_arm64");
#endif
        NameDistribution = GetNameDistribution();
        DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
        PackageManager = database.GetValueFromDB("SupportedOS", NameDistribution, "PackageManager");
    }
    catch (std::exception &error)
    {
        std::string logText ="==> ❌ " + translate["LOG_ERROR_OPEN_DATABASE"].asString() + std::string(error.what());
        logger.writeLog("Error", translate["LOG_ERROR_OPEN_DATABASE"].asString() + std::string(error.what()));
        logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "UpdateData", logText);
    }
}

/**
 * The MainInstaller function installs an application on a Linux system based on the provided
 * name and architecture.
 *
 * @param Name The "Name" parameter is a string that represents the name of the application or
 * package that needs to be installed.
 *
 * @return the value of the variable "result".
 */
int Linux::Installer::MainInstaller(std::string Name)
{
    int result;
#if defined(__x86_64__)
    std::string Value = database.GetValueFromDB("Applications", Name, "Linux_amd64");
#elif __arm__ || __aarch64__ || _M_ARM64
    std::string Value = database.GetValueFromDB("Applications", Name, "Linux_arm64");
#endif
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
#if defined(__x86_64__)
        std::string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", Name, PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
        std::string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", Name, PackageManager);
#endif
        if (InstallCommand != "Empty")
            result = system(InstallCommand.c_str());
    }
    return result;
}

void Linux::Installer::InstallSnap()
{
    try
    {
        int result;
        UpdateData();
        std::cout << NameDistribution << std::endl;
        // If used wsl,that need enable systemd for use snap. How enable systemd on wsl: https://learn.microsoft.com/en-us/windows/wsl/systemd
        /* The above code is written in C++ and it is performing the following tasks: */
        result = system("snap --version > /dev/null");
        if (result == 0)
        {
            system("sudo ln -s /var/lib/snapd/snap /snap > /dev/null");
            system("sudo systemctl restart snapd.service > /dev/null");
        }
        else
        {
#if defined(__x86_64__)
            std::string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_amd64", "snap", PackageManager);
#elif __arm__ || __aarch64__ || _M_ARM64
            std::string InstallCommand = database.GetValueFromDB("PackagesFromSource_Linux_arm64", "snap", PackageManager);
#endif
            if (InstallCommand != "Empty")
                result = system(InstallCommand.c_str());
        }
    }
    catch (std::exception &error)
    {
        std::string ErrorText = "❌ " + translate["LOG_ERROR_INSTALL_SNAP"].asString();
        logger.writeLog("Error", translate["LOG_ERROR_INSTALL_SNAP"].asString());
        logger.writeLog("Error", error.what());
        std::cerr << ErrorText << std::endl;
    }
}

void Linux::Installer::DownloadDatabase()
{
    try
    {
        /* This code block checks if the database file specified by `DatabasePath` exists.
        If the file does not exist, it proceeds to download the file from a specified URL using the libcurl library. */
        if (std::filesystem::exists(DatabasePath) == false)
        {
            std::string url = "https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/InstallerUtils/AppInstaller.db";
            std::string name = (url.substr(url.find_last_of("/")));
            std::string filename = ProjectFolder + "/" + name.replace(name.find("/"), 1, "");
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
                    break;
                case CURLE_COULDNT_RESOLVE_HOST:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                    break;
                case CURLE_COULDNT_RESOLVE_PROXY:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                    break;
                case CURLE_UNSUPPORTED_PROTOCOL:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                    break;
                case CURLE_SSL_CONNECT_ERROR:
                    logger.writeLog("Error", translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                    break;
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

int Download(std::string url, std::string dir,bool Progress)
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
        logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "Download()", error.what());
        std::cerr << logText << std::endl;
    }
}


void Linux::Installer::MakeDirectory(std::string dir)
{
    try
    {
        std::string currentDir;
        std::string fullPath;
        std::string delimiter = ".";
        size_t pos = 0;
        while ((pos = dir.find(delimiter)) != std::string::npos)
        {
            currentDir = dir.substr(0, pos);
            if (!fullPath.empty())
            {
                fullPath = fullPath + "/" + currentDir;
                if (!std::filesystem::exists(fullPath))
                {
                    std::filesystem::create_directory(fullPath);
                }
            }
            else
            {
                fullPath = "/" + currentDir;
            }
            dir.erase(0, pos + delimiter.length());
        }
        fullPath = fullPath + "/" + dir;
        if (!std::filesystem::exists(fullPath))
        {
            std::filesystem::create_directory(fullPath);
        }
    }
    catch (std::exception &error)
    {
        logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "Logger.MakeDirectory", error.what());
    }
}
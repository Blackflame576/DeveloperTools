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
#include <DeepForge-Toolset/macOS.hpp>

/*  The `unpackArchive` function takes two parameters: `path_from` and `path_to`.
    It uses the `Unzipper` class to extract the contents of an archive file located at `path_from` and saves them to the directory specified by `path_to`.
    After extracting the contents, the function closes the `Unzipper` object.
*/
void Linux::Installer::unpackArchive(std::string path_from, std::string path_to)
{
    // std::string unpack_command = "tar -xf" + path_from + " --directory " + path_to;
    // system(unpack_command.c_str());
    try
    {
        makeDirectory(path_to);

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

            std::ofstream out(output_path, std::ios::binary);
            if (!out)
            {
                std::cerr << "Failed to create file: " << output_path << std::endl;
                continue;
            }

            void *fileData = mz_zip_reader_extract_to_heap(&zip_archive, file_stat.m_file_index, &file_stat.m_uncomp_size, 0); // You can adjust the flags parameter as needed
            if (!fileData)
            {
                std::cerr << "Failed to extract file: " << file_stat.m_filename << std::endl;
                continue;
            }

            out.write(static_cast<const char *>(fileData), file_stat.m_uncomp_size);
            mz_free(fileData);

            out.close();
        }

        mz_zip_reader_end(&zip_archive);
    }
    catch (std::exception &error)
    {
        std::string logText = "==> ❌ " + std::string(error.what());
        logger.sendError(NameProgram, Architecture, __channel__, OS_NAME, "unpackArchive()", error.what());
        std::cerr << logText << std::endl;
    }
}

void macOS::Installer::MakeDirectory(std::string dir)
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
        logger.sendError(NameProgram, Architecture, __channel__, OS_NAME, "Logger.MakeDirectory", error.what());
    }
}

void macOS::Installer::DownloadDatabase()
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

void macOS::Installer::download(std::string url, std::string dir, bool Progress)
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

void macOS::Installer::InstallDevelopmentPack(std::string n)
{
    try
    {
        UpdateData();
        /* The above code is retrieving values from a database for a specific development pack on
        macOS. It then creates a map called EnumeratePackages to store the values with their
        corresponding index. It also creates a string variable called NamePackage. */
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "macOS");
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

void macOS::Installer::UpdateData()
{
    try
    {
        database.open(&DatabasePath);
        Packages = database.GetAllValuesFromDB("Applications", "macOS");
        DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
    }
    catch (std::exception &error)
    {
        std::string logText = translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString() + std::string(error.what());
        logger.writeLog("Error", logText);
    }
}

/**
 * The function checks if Homebrew is installed and if not, it installs it.
 */
void macOS::Installer::InstallBrew()
{
    result = system("brew --version");
    if (result != 0)
    {
        std::cout << translate["Installing"].asString() << " "
                  << "brew"
                  << " ..." << std::endl;
        system("bash ./Scripts/InstallBrew.sh");
        std::cout << "✅ "
                  << "brew"
                  << " " << translate["Installed"].asString() << std::endl;
    }
}

int macOS::Installer::MainInstaller(std::string Name)
{
    std::string Value = database.GetValueFromDB("Applications", Name, "macOS");
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
        std::string InstallCommand = database.GetValueFromDB("PackagesFromSource_macOS", Name, "Command");
        if (InstallCommand != "Empty")
            result = system(InstallCommand.c_str());
    }
    return result;
}
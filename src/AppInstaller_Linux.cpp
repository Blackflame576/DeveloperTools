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
#define FMT_HEADER_ONLY
#include "AppInstaller_Linux.hpp"

namespace Linux
{

    int CallbackProgress(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (TotalToDownload <= 0.0)
        {
            return 0;
        }

        Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        // cout << Percentage << endl;
        if (TempPercentage != Percentage && TempPercentage <= 100)
        {
            progressbar.Update(NowDownloaded,TotalToDownload);
            LastSize = NowDownloaded;
            LastTotalSize = TotalToDownload;
            TempPercentage = Percentage;
        }
        return 0;
    }
    // Function for write data from curl
    size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }

    class AppInstaller
    {
    public:
        /**
         * The function `InstallVCpkg` installs vcpkg and adds it to the system path.
         *
         * @return an integer value. The possible return values are:
         * - 0: indicating successful installation of vcpkg
         * - 403: indicating that vcpkg is already installed in the specified directory
         */
        int InstallVCpkg()
        {
            string NewVCpkgDir = database.GetValueFromDB("PackagesFromSource", "vcpkg", "LinuxDir");
            string VCpkgRepository = database.GetValueFromDB("PackagesFromSource", "vcpkg", "Url");
            string PathRepository = NewVCpkgDir + "vcpkg";
            if (std::filesystem::exists(PathRepository) && std::filesystem::is_empty(PathRepository) == false)
            {
                cout << "✅ vcpkg " << translate["AlreadyInstalled"].asString() << " в " << PathRepository << endl;
                return 403;
            }
            string Command = "cd " + NewVCpkgDir + " && sudo git clone " + VCpkgRepository;
            string Command_Install = "sudo " + NewVCpkgDir + "vcpkg/bootstrap-vcpkg.sh -disableMetrics";
            string Command_AddPath = "sudo ./utils/pathman-linux-amd64 add /usr/bin/vcpkg";
            result = system(Command.c_str());
            if (result == 0)
            {
                system(Command_Install.c_str());
                system(Command_AddPath.c_str());
                cout << "vcpkg " << translate["Located"].asString() << " " << PathRepository << endl;
                return 0;
            }
            else
            {
                return -1;
            }
        }

        /* The above code is defining two function pointer types: `AppInstaller_funct_t` and
        `map_funct_t`. `AppInstaller_funct_t` is a function pointer type that points to a member
        function of the `AppInstaller` class that takes no arguments and returns an `int`.
        `map_funct_t` is a function pointer type that points to a function that takes no arguments
        and returns `void`. */
        using AppInstaller_funct_t = int (AppInstaller::*)(void);
        using map_funct_t = void (*)(void);

        map<string, AppInstaller_funct_t> PackagesFromSource{
            {"vcpkg", &AppInstaller::InstallVCpkg},
        };
        void UpdateData()
        {
            try
            {
                database.open(&DatabasePath);
                Packages = database.GetAllValuesFromDB("Applications", "macOS");
                DevelopmentPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
            }
            catch (exception &error)
            {
                logger.WriteError(translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString());
                logger.WriteError(error.what());
            }
        }
        /* The `GetNameDistribution()` function is used to retrieve the name of the Linux distribution that the code is running on. */
        string GetNameDistribution()
        {
            ifstream stream("/etc/os-release");
            string line;
            regex nameRegex("^NAME=\"(.*?)\"$");
            smatch match;
            string name;
            while (getline(stream, line))
            {
                if (regex_search(line, match, nameRegex))
                {
                    name = match[1].str();
                    break;
                }
            }
            return name;
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
        int MainInstaller(string Name)
        {
            try
            {
                string Value = database.GetValueFromDB("Applications", Name, "Linux");
                if (Value != "ManualInstallation" && Architecture == "arm64")
                {
                    result = system(Value.c_str());
                }
                else if (PackagesFromSource.find(Name) != PackagesFromSource.end())
                {
                    result = (this->*(PackagesFromSource[Name]))();
                }
                else
                {
                    string InstallCommand = database.GetValueFromDB("PackagesFromSource", Name, PackageManager);
                    if (InstallCommand != "Empty")
                        result = system(InstallCommand.c_str());
                }
                return result;
            }
            catch (exception &error)
            {
                cout << error.what() << endl;
            }
        }
        AppInstaller()
        {
            try
            {
                GetArchitectureOS();
                UpdateData();
                InstallSnap();
                cout << InstallDelimiter << endl;
            }
            catch (exception &error)
            {
                cout << error.what() << endl;
            }
        }

        ~AppInstaller()
        {
        }

    private:
        // Method for getting architecture of OS
        void GetArchitectureOS()
        {
#if defined(__x86_64__)
            Architecture = "amd64";
#elif __arm__
            Architecture = "arm64";
#endif
        }
        void InstallSnap()
        {
            try
            {
                UpdateData();
                cout << NameDistribution << endl;
                /* The above code is written in C++ and it is performing the following tasks: */
                system("bash ./Scripts/CheckWSL.sh");
                result = system("snap --version");
                if (result != 0)
                {
                    string InstallCommand = database.GetValueFromDB("PackagesFromSource", "snap", PackageManager);
                    if (InstallCommand != "Empty")
                        result = system(InstallCommand.c_str());
                }
                else
                {
                    system("sudo ln -s /var/lib/snapd/snap /snap");
                    system("sudo systemctl restart snapd.service");
                }
            }
            catch (exception &error)
            {
                logger.WRITE_AND_LOG_ERROR("❌ An error occurred while trying to download snap");
                logger.WRITE_AND_LOG_ERROR(error.what());
            }
            // if (PackageManager == "apt")
            // {
            //     result = system("snap --version");
            //     if (result != 0)
            //     {
            //         cout << translate["Installing"].asString() << " " << "snap" << " ..." << endl;
            //         system("sudo apt-get update && sudo apt-get install -yqq daemonize dbus-user-session fontconfig");
            //         // system("sudo daemonize /usr/bin/unshare --fork --pid --mount-proc /lib/systemd/systemd --system-unit=basic.target");
            //         system("sudo apt install snap snapd");
            //         system("sudo ln -s /var/lib/snapd/snap /snap");
            //         system("sudo systemctl enable snapd.service");
            //         system("sudo systemctl start snapd.service");
            //         cout << "✅ " << "snap"<< " " << translate["Installed"].asString() << endl;
            //     }
            //     system("sudo ln -s /var/lib/snapd/snap /snap");
            //     system("sudo systemctl restart snapd.service");
            // }
        }
        void DownloadDatabase()
        {
            try
            {
                /* This code block checks if the database file specified by `DatabasePath` exists.
                If the file does not exist, it proceeds to download the file from a specified URL using the libcurl library. */
                if (filesystem::exists(DatabasePath) == false)
                {
                    string url = "https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/InstallerUtils/AppInstaller.db";
                    string name = (url.substr(url.find_last_of("/")));
                    string filename = ProjectDir + "/" + name.replace(name.find("/"), 1, "");
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
                            logger.WriteError(translate["LOG_ERROR_CURLE_COULDNT_CONNECT"].asString());
                        case CURLE_COULDNT_RESOLVE_HOST:
                            logger.WriteError(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                        case CURLE_COULDNT_RESOLVE_PROXY:
                            logger.WriteError(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                        case CURLE_UNSUPPORTED_PROTOCOL:
                            logger.WriteError(translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                        case CURLE_SSL_CONNECT_ERROR:
                            logger.WriteError(translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                        }
                    }
                }
            }
            catch (exception &error)
            {
                logger.WriteError(translate["LOG_ERROR_DOWNLOAD_DATABASE"].asString());
                logger.WriteError(error.what());
            }
        }
        /**
         * The function `Download` downloads a file from a given URL and saves it to a specified
         * directory, while also displaying a progress bar.
         *
         * @param url The URL of the file you want to download.
         * @param dir The `dir` parameter is a string that represents the directory where the
         * downloaded file will be saved.
         *
         * @return an integer value. If the download is successful, it returns 200. If there is an
         * error, it returns 502.
         */
        int Download(string url, string dir)
        {
            string name = (url.substr(url.find_last_of("/")));
            string filename = dir + "/" + name.replace(name.find("/"), 1, "");
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
                    throw domain_error(translate["LOG_ERROR_CURLE_COULDNT_CONNECT"].asString());
                case CURLE_COULDNT_RESOLVE_HOST:
                    throw domain_error(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_HOST"].asString());
                case CURLE_COULDNT_RESOLVE_PROXY:
                    throw domain_error(translate["LOG_ERROR_CURLE_COULDNT_RESOLVE_PROXY"].asString());
                case CURLE_UNSUPPORTED_PROTOCOL:
                    throw domain_error(translate["LOG_ERROR_CURLE_UNSUPPORTED_PROTOCOL"].asString());
                case CURLE_SSL_CONNECT_ERROR:
                    throw domain_error(translate["LOG_ERROR_CURLE_SSL_CONNECT_ERROR"].asString());
                }
            }
            // If the progress bar is not completely filled in, then paint over manually
            if (Process < 100 && Process != Percentage)
            {
                for (int i = (Process - 1); i < 99; i++)
                {
                    progressbar.Update(LastSize, LastTotalSize);
                }
            }
            // Reset all variables and preferences
            progressbar.ResetAll();
            Percentage = 0;
            TempPercentage = 0;
            return 200;
        }
    };
    // Function to create a string with two application names
    string NewString(string sentence)
    {
        string new_sentence = "";
        // If the string is empty, then the first application name is added.
        if (haveString == "")
        {
            haveString = sentence;
            return new_sentence;
        }
        else
        {
            // Formatting string with two columns
            /* If the string already contains the name of the application,
            then the second name of the application is added and the formatted string is returned */
            new_sentence = fmt::format("{:<40} {:<15}\n", haveString, sentence);
            haveString = "";
            return new_sentence;
        }
    }
    // Function of make string to lower
    string to_lower(string sentence)
    {
        string new_sentence = "";
        for (int i = 0; i < sentence.length(); i++)
        {
            char ch = sentence[i];
            // cout << ch << endl;
            ch = tolower(ch);
            new_sentence += ch;
        }
        return new_sentence;
    }
    // Function for check of answer
    bool CheckAnswer(string answer)
    {
        bool status;
        // string Answer = to_lower(answer);

        /* The above code is checking if the string variable "Answer" matches any of the elements in
        the "TrueVarious" vector. It also checks if "Answer" is empty or if it matches certain
        predefined strings ("да", "ДА", "Да"). If any of these conditions are true, the boolean
        variable "status" is set to true. */
        string Answer = answer;
        for (int i = 0; i < TrueVarious->size(); i++)
        {
            if (Answer == TrueVarious[i] || Answer.empty() || Answer == "\n" || Answer == "да" || Answer == "ДА" || Answer == "Да")
            {
                status = true;
                break;
            }
        }
        return status;
    }
    // Initialization class
    AppInstaller Installer;
    // Function for install of DevelopmentPack(ready pack for certain programming language
    void InstallDevelopmentPack(string n)
    {
        Installer.UpdateData();
        /* The above code is retrieving values from a database for a specific development pack on the
        Linux platform. It then iterates over the retrieved values and creates a map of enumerated
        packages. It also creates a string representation of each package with its corresponding
        index. The code then checks if the number of packages is even or odd and prints the string
        representation accordingly. */
        auto DevelopmentPack = database.GetAllValuesFromDB(DevelopmentPacks[n], "Linux");
        map<int, string> EnumeratePackages;
        string NamePackage;
        for (int i = 1; const auto &element : DevelopmentPack)
        {
            EnumeratePackages.insert(pair<int, string>(i, element.first));
            NamePackage = to_string(i) + ". " + element.first;
            string getNewString = NewString(NamePackage);
            if (DevelopmentPack.size() % 2 == 0)
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
                if (i == DevelopmentPack.size())
                {
                    cout << NamePackage << endl;
                    haveString = "";
                }
            }
            i++;
        }
        cout << "" << endl;
        cout << translate["SelectingPackages"].asString();
        getline(cin, SelectPackages);
        /* The above code is splitting a string called `SelectPackages` into multiple tokens using a
        delimiter (","). It then checks if each token is present in a map called
        `EnumeratePackages`. If a token is found in the map, it retrieves the corresponding value
        (package name) and performs some installation-related operations. These operations include
        printing messages, calling a `MainInstaller` function with the package name, and logging
        success or error messages based on the output of the `MainInstaller` function. Finally, it
        removes the processed token from the `SelectPackages` string and continues the loop until
        all tokens */
        string delimiter = ",";
        size_t pos = 0;
        string token;
        while ((pos = SelectPackages.find(delimiter)) != string::npos)
        {
            token = SelectPackages.substr(0, pos);
            if (EnumeratePackages.find(stoi(token)) != EnumeratePackages.end())
            {
                NamePackage = EnumeratePackages[stoi(token)];
                // =============================
                cout << InstallDelimiter << endl;
                cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
                // Install application
                output_func = Installer.MainInstaller(NamePackage);
                // Loggin and print messages
                if (output_func == 0)
                {
                    string SuccessText = "✅ " + NamePackage + " " + translate["Installed"].asString();
                    logger.WRITE_AND_LOG_SUCCESS(SuccessText.c_str());
                }
                else if (output_func != 403)
                {
                    string ErrorText = "❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                    logger.WRITE_AND_LOG_ERROR(ErrorText.c_str());
                }
                SelectPackages.erase(0, pos + delimiter.length());
            }
        }
        /* The above code is checking if a package with a specific ID exists in a map called
        EnumeratePackages. If the package exists, it retrieves the name of the package and proceeds
        to install it using the MainInstaller function from the Installer object. After
        installation, it logs and prints success or error messages based on the output of the
        installation process. */
        if (EnumeratePackages.find(stoi(SelectPackages)) != EnumeratePackages.end())
        {
            NamePackage = EnumeratePackages[stoi(SelectPackages)];
            // =============================
            cout << InstallDelimiter << endl;
            cout << translate["Installing"].asString() << " " << NamePackage << " ..." << endl;
            // Install application
            output_func = Installer.MainInstaller(NamePackage);
            // Logging and print messages
            if (output_func == 0)
            {
                string SuccessText = "✅ " + NamePackage + " " + translate["Installed"].asString();
                logger.WRITE_AND_LOG_SUCCESS(SuccessText.c_str());
            }
            else if (output_func != 403)
            {
                string ErrorText = "❌ " + translate["ErrorInstall"].asString() + " " + NamePackage;
                logger.WRITE_AND_LOG_ERROR(ErrorText.c_str());
            }
        }
        cout << InstallDelimiter << endl;
    }
}
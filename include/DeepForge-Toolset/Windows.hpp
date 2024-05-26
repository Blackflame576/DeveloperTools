#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_
#include <DeepForge-Toolset/Advanced.hpp>

#define OS_NAME "Windows"

namespace Windows
{
    class Installer
    {
    public:
        /**
         * The function `InstallMake` installs the Make utility by extracting it from a zip archive and
         * adding it to the specified directory.
         *
         * @return an integer value.
         */
        int InstallMake();

        /**
         * The function `InstallVCpkg()` installs vcpkg package manager on Windows.
         *
         * @return an integer value. The possible return values are:
         * - 403: Indicates that vcpkg is already installed in the specified directory.
         * - 0: Indicates that vcpkg has been successfully installed and located in the specified
         * directory.
         */
        int InstallVCpkg();

        /**
         * The function `InstallPHP` installs PHP by extracting a zip archive to a specified directory
         * and adds the directory to the system's PATH.
         *
         * @return an integer value.
         */
        int InstallPHP();
        /**
         * The function `InstallEclipse` downloads and installs Eclipse IDE on Windows.
         *
         * @return an integer value.
         */
        int InstallEclipse();

        /**
         * The function `InstallKotlin` installs the Kotlin programming language by downloading and
         * extracting the Kotlin compiler from a specified URL.
         *
         * @return an integer value.
         */
        int InstallKotlin();

        /**
         * The function `InstallWget` installs the Wget package by downloading it from a specified URL
         * and adding it to the system's PATH.
         *
         * @return an integer value.
         */
        int InstallWget();

        /**
         * The function `InstallNginx` installs Nginx by extracting a zip archive and adding the
         * installation path to the system's PATH variable.
         *
         * @return an integer value. The possible return values are:
         * - 403: Nginx is already installed in the specified directory.
         * - 0: Nginx is successfully installed and located in the specified directory.
         * - Throws a logic_error exception if the zip archive is not found.
         */
        int InstallNginx();

        /**
         * The function `InstallRedis` installs Redis by downloading it from a specified URL,
         * extracting the archive, adding the installation directory to the system path, and returning
         * an appropriate status code.
         *
         * @return an integer value. The possible return values are:
         * - 403: Redis is already installed in the specified directory.
         * - 0: Redis installation is successful.
         * - Throws a domain_error exception with the message "Unable to connect" if the result is 500.
         */
        int InstallRedis();

        /* The bellow code is defining two function pointer types: `Installer_funct_t` and
        `map_funct_t`. `Installer_funct_t` is a function pointer type that points to a member
        function of the `Installer` class that takes no arguments and returns an `int`.
        `map_funct_t` is a function pointer type that points to a function that takes no arguments
        and returns `void`. */
        using Installer_funct_t = int (Installer::*)(void);
        using map_funct_t = void (*)(void);

        std::map<std::string, Installer_funct_t> PackagesFromSource{
            {"Eclipse IDE", &Installer::InstallEclipse},
            {"Kotlin", &Installer::InstallKotlin},
            {"vcpkg", &Installer::InstallVCpkg},
            {"PHP", &Installer::InstallPHP},
            {"Make", &Installer::InstallMake},
            {"Wget", &Installer::InstallWget},
            {"Nginx", &Installer::InstallNginx},
            {"Redis", &Installer::InstallRedis}};

        /**
         * The MainInstaller function checks if an application requires manual installation or if it
         * can be installed automatically, and then installs it accordingly.
         *
         * @param Name The parameter "Name" is a string that represents the name of an application.
         *
         * @return an integer value.
         */
        int MainInstaller(std::string Name);
        // Function for update information from database about packages and development packs
        void UpdateData();
        // Function for install of DevelopmentPack(ready pack for certain programming language
        void InstallDevelopmentPack(std::string n);
        Installer()
        {
            UpdateData();
            InstallWinGet();
            std::cout << InstallDelimiter << std::endl;
        }

        ~Installer()
        {
        }

    protected:
        /**
         * The function checks if WinGet is installed and installs it if necessary.
         */
        void InstallWinGet();
        /*  The `unpackArchive` function takes two parameters: `path_from` and `path_to`.
            It uses the `Unzipper` class to extract the contents of an archive file located at `path_from` and saves them to the directory specified by `path_to`.
            After extracting the contents, the function closes the `Unzipper` object.
        */
        void UnpackArchive(std::string path_from, std::string path_to);
        /* The 'MakeDirectory' function is used to create a directory (folder) in the file system.*/
        void MakeDirectory(std::string dir);

        void DownloadDatabase();

        int Download(std::string url, std::string dir,bool Progress);
    };

}
#endif
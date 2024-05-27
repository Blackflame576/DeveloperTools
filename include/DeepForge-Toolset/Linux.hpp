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
#ifndef LINUX_HPP_
#define LINUX_HPP_
#include <DeepForge-Toolset/Advanced.hpp>

#define OS_NAME "Linux"

namespace Linux
{
    class Installer
    {
    public:
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
         * The function `InstallGoogleChrome()` installs vcpkg package manager on Windows.
         *
         * @return an integer value. The possible return values are:
         * - 403: Indicates that vcpkg is already installed in the specified directory.
         * - 0: Indicates that vcpkg has been successfully installed and located in the specified
         * directory.
         */
        int InstallGoogleChrome();

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
            try
            {
                UpdateData();
                InstallSnap();
                std::cout << InstallDelimiter << std::endl;
            }
            catch (std::exception &error)
            {
                std::cout << error.what() << std::endl;
            }
        }

    protected:
        std::string GetNameDistribution();
        void InstallSnap();
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

    /* The above code is defining two function pointer types: `AppInstaller_funct_t` and
        `map_funct_t`. `AppInstaller_funct_t` is a function pointer type that points to a member
        function of the `AppInstaller` class that takes no arguments and returns an `int`.
        `map_funct_t` is a function pointer type that points to a function that takes no arguments
        and returns `void`. */
    using Installer_funct_t = int (Installer::*)(void);
    using map_funct_t = void (*)(void);

    std::unordered_map<std::string, Installer_funct_t> PackagesFromSource{
        {"vcpkg", &Installer::InstallVCpkg},
    };
}
#endif
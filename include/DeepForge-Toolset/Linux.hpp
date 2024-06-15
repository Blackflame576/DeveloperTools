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

namespace Linux
{
    class Installer
    {
    public:
        int MainInstaller(std::string Name);

        int UpdateData();

        int InstallDevelopmentPack(std::string LanguageTable);
        Installer()
        {
                std::string filename;
                std::string pathFile;
                std::string url;
                DownloadDatabase();
                UpdateData();
                InstallSnap();
                MakeDirectory(ArchivesFolder);
                #if defined(__x86_64__)
                    url = PATHMAN_AMD64_URL;
                #elif __arm__ || __aarch64__ || _M_ARM64
                    url = PATHMAN_ARM64_URL;
                #endif
                filename =  (url.substr(url.find_last_of("/")));
                pathFile = ArchivesFolder + "/" + filename;
                Download(url,ArchivesFolder, false);
                UnpackArchive(pathFile, ArchivesFolder);
                std::cout << InstallDelimiter << std::endl;
        }

    protected:
        std::function<int(std::string)> MainInstallerLink = [this](std::string Name){ return this->MainInstaller(Name); };;
        std::string GetNameDistribution();

        int InstallPackages(const std::string &Name,const std::string &Command);

        int InstallSnap();
        
        int UnpackArchive(std::string path_from, std::string path_to);
        /* The 'MakeDirectory' function is used to create a directory (folder) in the file system.*/
        int MakeDirectory(std::string dir);

        int DownloadDatabase();

        int Download(std::string url, std::string dir,bool Progress);
    };
    // using Installer_funct_t = int (Installer::*)(void);
    // using map_funct_t = void (*)(void);
}
#endif
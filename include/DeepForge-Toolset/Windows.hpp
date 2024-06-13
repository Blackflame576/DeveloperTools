#ifndef WINDOWS_HPP_
#define WINDOWS_HPP_
#include <DeepForge-Toolset/Advanced.hpp>

#define OS_NAME "Windows"

namespace Windows
{
    class Installer
    {
    public:
        // using Installer_funct_t = int (Installer::*)(void);
        // using map_funct_t = void (*)(void);

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
        int UpdateData();
        // Function for install of DevelopmentPack(ready pack for certain programming language
        int InstallDevelopmentPack(std::string LanguageTable);
        Installer()
        {
            std::string filename;
            std::string pathFile;
            std::string url;
            DownloadDatabase();
            UpdateData();
            //InstallWinGet();
            MakeDirectory(ArchivesFolder);
            url = PathmanURL_AMD64;
            filename =  (url.substr(url.find_last_of("/")));
            pathFile = ArchivesFolder + "/" + filename;
            Download(url,ArchivesFolder, false);
            UnpackArchive(pathFile, ArchivesFolder);
            std::cout << InstallDelimiter << std::endl;
        }

        ~Installer()
        {
        }

    protected:
        std::function<int(std::string)> MainInstallerLink = [this](std::string Name){ return this->MainInstaller(Name); };;
        int InstallPackages(const std::string &Name,const std::string &Command);
        /**
         * The function checks if WinGet is installed and installs it if necessary.
         */
        int InstallWinGet();
        /*  The `unpackArchive` function takes two parameters: `path_from` and `path_to`.
            It uses the `Unzipper` class to extract the contents of an archive file located at `path_from` and saves them to the directory specified by `path_to`.
            After extracting the contents, the function closes the `Unzipper` object.
        */
        int UnpackArchive(std::string path_from, std::string path_to);
        /* The 'MakeDirectory' function is used to create a directory (folder) in the file system.*/
        int MakeDirectory(std::string dir);

        int DownloadDatabase();

        int Download(std::string url, std::string dir,bool Progress);
    };

}
#endif
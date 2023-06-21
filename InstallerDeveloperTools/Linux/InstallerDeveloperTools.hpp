#define MAINICON  "icon.ico"
#include <filesystem>
#include <iostream>

using namespace  std;

namespace InstallerDeveloperTools {
    string OS_NAME;
    int Percentage;
    int TempPercentage = 0;
    string ProjectDir = std::filesystem::current_path().generic_string();
    const string DownloadURL = "https://github.com/JetBrains/kotlin/releases/download/v1.8.22/kotlin-compiler-1.8.22.zip";
    const string InstallPath = "kotlin-compiler-1.8.22.zip";
    const string BetaDownloadURL = "";
    const string BetaInstallPath = "";
    string Answer;
    const string NewOrganizationFolder = "/usr/bin/DigitalBitTechnologies";
    const string NewApplicationFolder = "/usr/bin/DigitalBitTechnologies/DeveloperTools";
    // string NewApplicationFolder = 'C:/ProgramData/DigitalBitTechnologies/DeveloperTools';

    size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream)
    {
        size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
        return WriteProcess;
    }
    int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        // ensure that the file to be downloaded is not empty
        // because that would cause a division by zero error later on
        if (TotalToDownload <= 0.0) {
            return 0;
        }

        int percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
        if (TempPercentage != percentage && TempPercentage <= 100) {
            bar.update();
            TempPercentage = percentage;
        }
        return 0;
    }
}
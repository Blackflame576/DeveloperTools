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
    const string NewOrganizationFolder = "C:\\ProgramData\\DigitalBitTechnologies";
    const string NewApplicationFolder = "C:\\ProgramData\\DigitalBitTechnologies\\DeveloperTools";
    // string NewApplicationFolder = 'C:/ProgramData/DigitalBitTechnologies/DeveloperTools';
}
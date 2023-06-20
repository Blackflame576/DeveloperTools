#include <filesystem>
#include <iostream>

using namespace  std;

namespace InstallerDeveloperTools {
    int Percentage;
    int TempPercentage = 0;
    string OS_NAME;
    string ProjectDir = std::filesystem::current_path().generic_string();
}
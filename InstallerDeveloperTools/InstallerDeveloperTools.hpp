#include <filesystem>
#include <iostream>

using namespace  std;

namespace InstallerDeveloperTools {
    string OS_NAME;
    int Percentage;
    int TempPercentage = 0;
    string NameDistribution;
    string ProjectDir = std::filesystem::current_path().generic_string();
}
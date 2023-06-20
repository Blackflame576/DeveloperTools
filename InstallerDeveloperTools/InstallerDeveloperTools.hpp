#include <filesystem>
#include <iostream>

using namespace  std;

namespace InstallerDeveloperTools {
    string ProjectDir = std::filesystem::current_path().generic_string();
}
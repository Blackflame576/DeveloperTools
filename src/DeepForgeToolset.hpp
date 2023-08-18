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
// Importing Libraries
#include <iostream>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "Progressbar.hpp"
#include <cctype>
#include <exception>
#include <filesystem>

// Checking the name of the operating system and importing the necessary libraries for this system
#if defined(__linux__)
// cout << "Linux" << endl;
#elif __FreeBSD__
// cout << "FreeBSD" << endl;
#elif __APPLE__
// cout << "macOS" << endl;
#elif _WIN32
    #include <conio.h>
    #include <Windows.h>
#endif

// Variables
string OS_NAME;
string Architecture;
string Language;
string SelectPackages;
string Answer;
string InstallTools;
bool Install;
string __version__ = "0.1";
string MODE = "DEV";
// string LogoBanner;
// string ProjectDir = std::filesystem::current_path().generic_string();
// namespace DeepForgeToolset {
//     class MainApp {
//         public:
//             MainApp() {
//                 AppInstaller Installer;
//                 Packages
//             }
//     }
// }
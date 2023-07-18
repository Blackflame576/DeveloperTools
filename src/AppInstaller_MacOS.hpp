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
    Company: DeepForge Technology
    ============================================================================
    Author: Blackflame576
    ============================================================================
    Created: 4 Juny 2023
    ============================================================================
*/
// Импортирование библиотек
// Importing Libraries
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "Progressbar.hpp"
#include <cctype>
#include <fstream>
#include <json/json.h>
#include <functional>
#include "Logger.cpp"

using namespace std;
using namespace Json;
using namespace Logger;
// using namespace std::fmt;
 
// Переменные
// Variables
MainLogger logger(true,"logs/DeepForgeToolset.log");
progressbar bar(100);
int TempPercentage = 0;
const string TrueVarious[3] = { "yes", "y", "1"};
string new_sentence;
Value translate;
string LangReadySet;
map<int, string> Languages{
    {1,"Python"},{2,"JavaScript"},{3,"C++"},{4,"Java"},
    {5,"Go"},{6,"Rust"},{7,"Ruby"},{8,"C"},
    {9,"C#"},{10,"PHP"},{11,"Kotlin"}
};
int result;
int output_func;
string haveString = "";
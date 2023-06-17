// #include <Windows.h>
#include "Progressbar.hpp"
#include <stdlib.h> 
#include <iostream>
#include <cstdlib>
// #include <Windows.h>

using namespace std;

int main() {
    // SetConsoleOutputCP(CP_UTF8);
    progressbar bar(100);
    // bar.set_todo_char("#");
    // bar.set_done_char("#");
    // bar.set_opening_bracket_char("{");
    // bar.set_closing_bracket_char("}");
    for (int i = 0; i < 100; ++i) {
        bar.update();
        // ... the program
    }
    cout << "" << endl;
    // system("mklink /d \\MyFolder \\Users\\User1\\Documents");
    // system("PowerShell.exe Set-ExecutionPolicy RemoteSigned \n");
    // putenv("PATH=C:\\Kotlin");
    system("start powershell.exe C:\\Users\\Blackflame576\\Documents\\Blackflame576\\DigitalBit\\DeveloperTools\\Scripts\\AddKotlinPath.ps1");
    // cout << result << endl;
    system("pause");
    return 0;
}
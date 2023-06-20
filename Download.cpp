#include <iostream>
#include<Windows.h>
#include<string>
#pragma comment(lib, "urlmon.lib")

using namespace std;
int main()
{
    string dwnld_URL = "https://filesamples.com/samples/document/txt/sample2.txt";
    string savepath = "filename.txt";
    URLDownloadToFile(NULL, dwnld_URL.c_str(), savepath.c_str(), 0, NULL);

    return 0;
}
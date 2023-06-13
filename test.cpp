#include <iostream>
#include <map>

using namespace std;
using funct_t = void(*)(void);
void InstallGit() {
    cout << "Git installer" << endl;
}
map<string,funct_t> apps {
    {"Git",InstallGit}
};


int main() {
    apps["Git"]();
    system("pause");
    return 0;
}
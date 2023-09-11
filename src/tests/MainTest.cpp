#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../DatabaseConnect.cpp"
#include <filesystem>
#include <map>
#include <iostream>

using namespace std;
using namespace DB;

const char *ch = "/src/DB/AppInstaller.db";
std::filesystem::path current_path = std::filesystem::current_path().generic_string();
string DB_PATH = current_path.parent_path().string() + ch;
Database database;
string NameApp = "TestApp";
string Windows_Command = "Test_Windows_Command";
string macOS_Command = "Test_macOS_Command";
string Linux_Command = "Test_Linux_Command";
string Table = "Test";

class DatabaseTests
{
    public:
        DatabaseTests()
        {

        }
        ~DatabaseTests();
    private:
};

TEST(DatabaseGroup, CreateValue)
{
    database.open(&DB_PATH);
    int RESULT = database.InsertApplicationsToTable(Table, NameApp, Windows_Command, macOS_Command, Linux_Command);
    EXPECT_EQ(RESULT, 0);
    // print();
}

TEST(DatabaseGroup, GetValue)
{
    string RESULT;
    RESULT = database.GetValueFromDB(Table, NameApp, "Windows");
    delete[] &AnswerDB;
    EXPECT_STREQ(Windows_Command.c_str(), RESULT.c_str());
    RESULT = database.GetValueFromDB(Table, NameApp, "Linux");
    delete[] &AnswerDB;
    EXPECT_STREQ(Linux_Command.c_str(), RESULT.c_str());
    RESULT = database.GetValueFromDB(Table, NameApp, "macOS");
    delete[] &AnswerDB;
    EXPECT_STREQ(macOS_Command.c_str(), RESULT.c_str());
}

TEST(DatabaseGroup, DeleteValue)
{
    int RESULT = database.RemoveApplicationsFromTable(Table, NameApp);
    EXPECT_EQ(0, RESULT);
}

TEST(DatabaseGroup, GetAllValues)
{
    map<string, string> Packages = database.GetAllValuesFromDB("Applications", "Windows");
    EXPECT_LE(1, Packages.size());
}

TEST(DatabaseGroup, GetDevPack)
{
    map<string, string> DevelopmetPacks = database.GetDevPackFromDB("DevelopmentPacks", "Language");
    EXPECT_LE(1, DevelopmetPacks.size());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
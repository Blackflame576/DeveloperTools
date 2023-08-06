#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <map>

using namespace std;

namespace DB {
    int ArraySize;
    sqlite3 *db;
    sqlite3_stmt *statement;
    int RESULT_SQL;
    string SQL_COMMAND;
    string* AnswerDB;

    class Database {
        public:
            Database() {
                /* Open database */
                RESULT_SQL = sqlite3_open("DB/AppInstaller.db", &db);
                // if result of open database != SQLITE_OK, that send error
                if (RESULT_SQL != SQLITE_OK) {
                    throw runtime_error("Failed to connect to database");
                }
            }
            ~Database() {
                sqlite3_close(db);
            }
            string* GetValueFromDB(string Name,string OS_NAME);
            map<string,string> GetAllValuesFromDB(string NamePack,string OS_NAME);
            map<string,string> GetDevPackFromDB(string NameTable,string OS_NAME);
            // string* GetAllValuesFromDB(string NameTable,string OS_NAME);
        private:
            int GetArraySize(string NameTable,string NameColumn);
    };
}
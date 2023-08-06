#include "DatabaseConnect.hpp"

using namespace std;
using namespace DB;

string* Database::GetValueFromDB(string NameApp,string NameColumn) {
    ArraySize = GetArraySize("Applications",NameColumn);
    string* AnswerDB = new string[ArraySize];
    // Create SQL statement 
    SQL_COMMAND = "SELECT " + NameColumn +  " from Applications WHERE Name='" + NameApp + "'";
    // Execute SQL statement 
    int RESULT_SQL = sqlite3_prepare_v2(db, SQL_COMMAND.c_str(), SQL_COMMAND.length(), &statement, nullptr);
    // if result of execute sql statement != SQLITE_OK, that send error
    if (RESULT_SQL != SQLITE_OK) {
        throw runtime_error("Not Found");
    }
    int i = 0;
    // Loop through the results, a row at a time.
    while ((RESULT_SQL = sqlite3_step(statement)) == SQLITE_ROW) {
        // printf("%s\n", sqlite3_column_text(statement, 0));
        AnswerDB[i] = (string(reinterpret_cast<const char*>(
            sqlite3_column_text(statement, 0)
        )));
        i++;
    }
    // Free the statement when done.
    sqlite3_finalize(statement);
    return AnswerDB;
}
// string* Database::GetAllValuesFromDB(string NameTable,string NameColumn) {
//     ArraySize = GetArraySize(NameTable,NameColumn);
//     string* AnswerDB = new string[ArraySize];
//     // Create SQL statement 
//     SQL_COMMAND = "SELECT " + NameColumn +  " from " + NameTable;
//     // Execute SQL statement 
//     int RESULT_SQL = sqlite3_prepare_v2(db, SQL_COMMAND.c_str(), SQL_COMMAND.length(), &statement, nullptr);
//     // if result of execute sql statement != SQLITE_OK, that send error
//     if (RESULT_SQL != SQLITE_OK) {
//         throw runtime_error("Not Found");
//     }
//     int i = 0;
//     // Loop through the results, a row at a time.
//     while ((RESULT_SQL = sqlite3_step(statement)) == SQLITE_ROW) {
//         // printf("%s\n", sqlite3_column_text(statement, 0));
//         AnswerDB[i] = (string(reinterpret_cast<const char*>(
//             sqlite3_column_text(statement, 0)
//         )));
//         i++;
//     }
//     // Free the statement when done.
//     sqlite3_finalize(statement);
//     return AnswerDB;
// }
map<string,string> Database::GetAllValuesFromDB(string NameTable,string NameColumn) {
    map<string,string> WriteMap;
    
    // Create SQL statement 
    SQL_COMMAND = "SELECT Name," + NameColumn + " from " + NameTable;
    // Execute SQL statement 
    int RESULT_SQL = sqlite3_prepare_v2(db, SQL_COMMAND.c_str(), SQL_COMMAND.length(), &statement, nullptr);
    // if result of execute sql statement != SQLITE_OK, that send error
    if (RESULT_SQL != SQLITE_OK) {
        // throw runtime_error("Not Found");
    }
    int i = 0;
    // Loop through the results, a row at a time.
    while ((RESULT_SQL = sqlite3_step(statement)) == SQLITE_ROW) {
        WriteMap.insert(pair<string,string>(string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0))),string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)))));
        i++;
    }
    // Free the statement when done.
    sqlite3_finalize(statement);
    // return Names,Commands;
    return WriteMap;
}
map<string,string> Database::GetDevPackFromDB(string NameTable,string NameColumn) {
    map<string,string> WriteMap;
    
    // Create SQL statement 
    SQL_COMMAND = "SELECT Number," + NameColumn + " from " + NameTable;
    // SQL_COMMAND = "SELECT Number,Language FROM DevelopmentPacks";
    // Execute SQL statement 
    int RESULT_SQL = sqlite3_prepare_v2(db, SQL_COMMAND.c_str(), SQL_COMMAND.length(), &statement, nullptr);
    // if result of execute sql statement != SQLITE_OK, that send error
    if (RESULT_SQL != SQLITE_OK) {
        // throw runtime_error("Not Found");
    }
    int i = 0;
    // Loop through the results, a row at a time.
    while ((RESULT_SQL = sqlite3_step(statement)) == SQLITE_ROW) {
        WriteMap.insert(
            pair<string,string>(
                string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0))),
                string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)))));
        i++;
    }
    // Free the statement when done.
    sqlite3_finalize(statement);
    // return Names,Commands;
    return WriteMap;
}
int Database::GetArraySize(string NameTable,string NameColumn) {
    // Create SQL statement 
    SQL_COMMAND = "SELECT count(" + NameColumn + ") " +  " FROM " + NameTable;
    // SQL_COMMAND = "SELECT count(Windows) FROM Applications";
    // Execute SQL statement 
    int RESULT_SQL = sqlite3_prepare_v2(db, SQL_COMMAND.c_str(), SQL_COMMAND.length(), &statement, nullptr);
    // if result of execute sql statement != SQLITE_OK, that send error
    if (RESULT_SQL != SQLITE_OK) {
        // throw runtime_error("Not Found");
    }
    // Loop through the results, a row at a time.
    while ((RESULT_SQL = sqlite3_step(statement)) == SQLITE_ROW) {
        // printf("%s\n", sqlite3_column_text(statement, 0)); 
        ArraySize = sqlite3_column_int(statement, 0);
    }
    // Free the statement when done.
    sqlite3_finalize(statement);
    return ArraySize;
}

// int main(int argc, char* argv[]) {
//     Database database;
//     string* value;
//     // Names = database.GetAllValuesFromDB("Applications","Windows");
//     // for (int i = 0;i < value->size();i++) {
//     //     cout << value[i] << endl;
//     // }
//     // delete[] AnswerDB;
//     // value_1,value_2 = database.GetValuesFromTable("Applications","Windows");
//     // for (int i = 0;i < value_1->size();i++) {
//     //     cout << value_1[i] << endl;
//     // }
//     Packages = database.GetAllValuesFromDB("DevelopmentPacks","Language");
//     for (const auto &element:Packages) {
//         cout << element.first << ". " << element.second << endl;
//     }
//     // delete[] AnswerDB;
//     // value = database.GetAllValuesFromDB("Applications","Windows");
//     // for (int i = 0;i < value->size();i++) {
//     //     cout << value[i] << endl;
//     // }
//     // delete[] AnswerDB;
//     // printf(value->c_str());
    
//     return 0;
// }

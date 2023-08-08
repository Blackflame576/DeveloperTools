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
#ifndef DATABASECONNECT_H_
#define DATABASECONNECT_H_
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <map>
#include <filesystem>

using namespace std;

 namespace DB {
     int ArraySize;
     sqlite3 *db;
     sqlite3_stmt *statement;
     int RESULT_SQL;
     string SQL_COMMAND;
     string* AnswerDB;
     string DatabesePath = std::filesystem::current_path().generic_string() + "/DB/AppInstaller.db";

     class Database {
     public:
         Database() {
             /* Open database */
             RESULT_SQL = sqlite3_open(DatabesePath.c_str(), &db);
             // if result of open database != SQLITE_OK, that send error
             if (RESULT_SQL != SQLITE_OK) {
                 throw runtime_error("Failed to connect to database");
             }
         }
         ~Database() {
             sqlite3_close(db);
         }
         string* GetValueFromDB(string Name,string OS_NAME);
         map<string,string> GetAllValuesFromDB(string NameTable,string OS_NAME);
         map<string,string> GetDevPackFromDB(string NameTable,string OS_NAME);
     private:
         int GetArraySize(string NameTable,string NameColumn);
     };
 }

#endif

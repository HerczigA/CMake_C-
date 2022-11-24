#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql::mysql;

class DatabaseHandler{
    public:
        
        DatabaseHandler(const string & user, const string & password, const string & dbName, const string & hostname, const int & port);
        enum DriverType{
            MSSQL,
            MYSQL,
            SQLITE,
            POSTGRESQL,
            INFLUXDB,
            ORACLE,
            NOSQL
        };

        // virtual int insertInto(const string & query ) = 0;
        // virtual void selectFrom(const string & query, string & result) = 0;
        int insertInto(const string & query );
        void selectFrom(const string & query, string & result);
        virtual int connectToDb() =0;
    private:
        
        string mHostName;
        string mUserName;
        string mPassword;
        string mDbName;
        int mPort;
        
        sql::Driver *mDriver;
        sql::Connection *mConn;
        sql::Statement *mState;
        sql::ResultSet *mRes;

};
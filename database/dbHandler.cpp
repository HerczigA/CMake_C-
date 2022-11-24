#include "dbHandler.h"


DatabaseHandler::DatabaseHandler(const string & user, const string & password, const string & dbName, const string & hostname, const int & port) 
    : mHostName(hostname)
    , mUserName(user)
    , mPassword(password)
    , mDbName(dbName) 
    , mPort(port)
{
    /* Create a connection */
  mDriver = get_driver_instance();
 
  string address = mHostName + ":" + to_string(mPort);
  mConn = mDriver->connect(address, mUserName, mPassword);
  /* Connect to the MySQL test database */
  mConn->setSchema("test");
  mState = mConn->createStatement();
  
  while (mRes->next()) {
    cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    cout << mRes->getString("_message") << endl;
    cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    cout << mRes->getString(1) << endl;
  }
}

void DatabaseHandler::selectFrom(const string & query, string & result) 
{
  mRes = mState->executeQuery(query);

}

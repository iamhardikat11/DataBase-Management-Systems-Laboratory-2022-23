#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

int main(void)
{
   SQLHENV env;
   SQLHDBC dbc;
   SQLRETURN ret;

   /* Allocate an environment handle */
   ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
   if (!SQL_SUCCEEDED(ret))
   {
      printf("Error allocating environment handle\n");
      return 1;
   }

   /* Set the ODBC version environment attribute */
   ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
   if (!SQL_SUCCEEDED(ret))
   {
      printf("Error setting ODBC version\n");
      return 1;
   }

   /* Allocate a connection handle */
   ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
   if (!SQL_SUCCEEDED(ret))
   {
      printf("Error allocating connection handle\n");
      return 1;
   }

   /* Connect to the database */
   ret = SQLConnect(dbc, (SQLCHAR *) "postgresql", SQL_NTS, (SQLCHAR *) "postgres", SQL_NTS, (SQLCHAR *) "1234", SQL_NTS);
   if (!SQL_SUCCEEDED(ret))
   {
      printf("Error connecting to the database\n");
      return 1;
   }

   printf("Successfully connected to the database\n");

   /* Disconnect and free up resources */
   SQLDisconnect(dbc);
   SQLFreeHandle(SQL_HANDLE_DBC, dbc);
   SQLFreeHandle(SQL_HANDLE_ENV, env);

   return 0;
}

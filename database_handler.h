#pragma once
#include <mariadb/mysql.h>
#include <string>
#include "user.h"
#include <vector>
namespace handlers 
{
	class database_handler
	{
	private:
		MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES *res;
		int qstate = 0;
	public:
		database_handler(std::string host, std::string user, std::string password);
		models::user* findUserByID(int id);
		bool findUserByIdAndUpdate(int id, std::string name = NULL, std::string email = NULL, std::string password = NULL);
		bool insertUser(models::user u);
		bool deleteUserById(int id);
		std::vector<models::user> findAll();
	};

}


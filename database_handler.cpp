#include "database_handler.h"
#include <mariadb/mysql.h>
#include <sstream>
#include <string>
#include <vector>
#include "user.h"
using namespace std;
using namespace handlers;
static void display_warnings(MYSQL *conn)
{
	MYSQL_RES *sql_result;
	MYSQL_ROW row;
	if ((conn == NULL) || mysql_query(conn, "SHOW WARNINGS"))
	{
		printf("Can not display list of errors/warnings!\n");
		return;
	}

	sql_result = mysql_store_result(conn);
	if ((sql_result == NULL) || (sql_result->row_count == 0))
	{
		printf("Can not display list of errors/warnings!\n");
		if (sql_result)
			mysql_free_result(sql_result);
		return;
	}

	row = mysql_fetch_row(sql_result);
	if (row == NULL)
	{
		printf("Can not display list of errors/warnings!\n");
		mysql_free_result(sql_result);
		return;
	}

	do
	{
		// Format: "message [Type: number]"
		printf("%s [%s: %s]\n", row[2], row[0], row[1]);
		row = mysql_fetch_row(sql_result);
	} while (row);
	mysql_free_result(sql_result);
}

database_handler::database_handler(string host, string user, string password) {
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), "testdb", 3306, NULL, 0);
		if (!conn) {
			throw "Couldnt connect to database";
		}
		stringstream table_query_builder;
		table_query_builder << "CREATE TABLE IF NOT EXISTS `user` (";
		table_query_builder << "`id` INT unsigned NOT NULL AUTO_INCREMENT,";
		table_query_builder << "`name` VARCHAR(50) DEFAULT NULL,";
		table_query_builder << "`email` VARCHAR(50) DEFAULT NULL,";
		table_query_builder << "`password` VARCHAR(50) DEFAULT NULL,";
		table_query_builder << "PRIMARY KEY(`id`))" << ";";


		string table_query = table_query_builder.str();
		qstate = mysql_query(conn, table_query.c_str());
		mysql_store_result(conn);
		display_warnings(conn);
		if (qstate) { throw "Couldnt create user table"; }
	}
	models::user* database_handler::findUserByID(int id) {
		stringstream query_builder;
		query_builder << "SELECT * FROM `user` WHERE `id` =" << id;
		string query = query_builder.str();
		qstate = mysql_query(conn, query.c_str());
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		display_warnings(conn);
		models::user *u;
		u = nullptr;
		if (row) {
			u = new models::user(stoi(row[0]), row[1], row[2], row[3]);
		}
		return u;
	}
	bool database_handler::findUserByIdAndUpdate(int id, string name, string email, string password) {
		stringstream query_builder;
		query_builder << "UPDATE `user`";
		query_builder << "SET name=" << "'" << name <<     "'" << ",";
		query_builder << "email=" <<    "'" << email <<    "'" << ",";
		query_builder << "password=" << "'" << password << "'" << ";";


		string query = query_builder.str();
		qstate = mysql_query(conn, query.c_str());
		display_warnings(conn);
		return !qstate;
	}
	bool database_handler::insertUser(models::user u) {
		stringstream query_builder;
		query_builder << "INSERT INTO user (name, email, password)";
		query_builder << " VALUES(";
		query_builder << "'" << u.getName() <<     "'" << ",";
		query_builder << "'" << u.getEmail() <<    "'" << ",";
		query_builder << "'" << u.getPassword() << "'" << ");";

		string query = query_builder.str();
		qstate = mysql_query(conn, query.c_str());
		display_warnings(conn);
		return !qstate;
	}
	bool database_handler::deleteUserById(int id) {
		stringstream query_builder;
		query_builder << "DELETE FROM `user`";
		query_builder << "WHERE `id` =" << id;

		string query = query_builder.str();
		qstate = mysql_query(conn, query.c_str());
		display_warnings(conn);
		return !qstate;
	}
	vector<models::user> database_handler::findAll() {
		vector<models::user> users;
		string query = "SELECT * from user";
		qstate = mysql_query(conn, query.c_str());
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				models::user u(stoi(row[0]), row[1], row[2], row[3]);
				users.push_back(u);
			}
		}
		display_warnings(conn);
		return users;
	}
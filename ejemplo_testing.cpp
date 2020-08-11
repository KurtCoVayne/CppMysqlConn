#include "user.h"
#include <iostream>
#include "database_handler.h"
using namespace std;
using namespace models;
using namespace handlers;
int main(int argc, char** argv) {
	/*
		create user, test serialization.
		initialize db, test if connected.
		insert user,
		get all users,
		get user,
		update user,
		delete user
	*/
	try
	{
		bool check;
		user us(-1, "pablo", "pablo@gmail.com", "pablo123");
		cout << us <<endl;
		auto dbh = database_handler("192.168.0.14", "testuser", "marta321");
		check = dbh.insertUser(us);
		cout << check <<endl;
		auto users = dbh.findAll();
		int myuser_id = -1;
		for (auto& u : users) {
			cout << u << endl;
			if (u.getName() == "pablo") {
				myuser_id = u.getID();
			}
		}
		user* us2 = dbh.findUserByID(myuser_id);
		check = dbh.findUserByIdAndUpdate(myuser_id, "pablito", "pablo@gmail.com", "pablo123");
		cout << check <<endl;
		check = dbh.deleteUserById(myuser_id);
		cout << check <<endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
		return -1;
	}
	
	return 0;
}
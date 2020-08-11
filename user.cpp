#include "user.h"
#include <string>
using namespace std;
using namespace models;
	user::user(int _id, string _name, string _email, string _password)
	{
		id = _id;
		name = _name;
		email = _email;
		password = _password;
	}
	void user::setID(int _id) { id = _id; }
	void user::setName(string _name) { name = _name; }
	void user::setEmail(string _email) { email = _email; }
	void user::setPassword(string _password) { password = _password; }

	int user::getID() { return id; }
	string user::getName() { return name; }
	string user::getEmail() { return email; }
	string user::getPassword() { return password; }

	
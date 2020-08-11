#pragma once
#include <string>
#include <iostream>
namespace models
{
	class user
	{
	private:
		int id;
		std::string name;
		std::string email;
		std::string password;
	public:
		user(int _id, std::string _name, std::string _email, std::string _password);
		void setID(int _id);
		void setName(std::string _name);
		void setEmail(std::string _email);
		void setPassword(std::string _password);
		int getID();
		std::string getName();
		std::string getEmail();
		std::string getPassword();
		friend std::ostream& operator<<(std::ostream& out, user& U) {
			out << U.getID() << " " << U.getName() << " " << U.getEmail();
			return out;
		}
	};
	

}

#ifndef _SQLite_H_
#define _SQLite_H_

#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>

struct DatabaseManager
{
public:
	// Constructor: Opens or creates the database
	DatabaseManager(const std::string &dbPath);

	// Creates the users table
	void createTable();

	// Inserts a new user into the table
	void insertUser(const std::string &name, int age);

	// Updates a user's name and age by ID
	void updateUser(int id, const std::string &name, int age);

	// Shows all users in the table
	void showAllUsers();

	// Shows a single user by ID
	void showUserByID(int id);

	// Deletes a user by ID
	void deleteUser(int id);

private:
	SQLite::Database db; // SQLite database object
};

// Constructor: Opens or creates the database
DatabaseManager::DatabaseManager(const std::string &dbPath)
	: db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
	std::cout << "Database opened successfully: " << db.getFilename() << std::endl;
}

// Creates the users table
void DatabaseManager::createTable()
{
	db.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)");
	std::cout << "Table 'users' created or already exists." << std::endl;
}

// Inserts a new user into the table
void DatabaseManager::insertUser(const std::string &name, int age)
{
	SQLite::Statement query(db, "INSERT INTO users (name, age) VALUES (?, ?)");
	query.bind(1, name);
	query.bind(2, age);
	query.exec();
	std::cout << "User inserted: " << name << ", " << age << std::endl;
}

// Updates a user's name and age by ID
void DatabaseManager::updateUser(int id, const std::string &name, int age)
{
	SQLite::Statement query(db, "UPDATE users SET name = ?, age = ? WHERE id = ?");
	query.bind(1, name);
	query.bind(2, age);
	query.bind(3, id);
	query.exec();
	std::cout << "User updated: ID " << id << " -> " << name << ", " << age << std::endl;
}

// Shows all users in the table
void DatabaseManager::showAllUsers()
{
	SQLite::Statement query(db, "SELECT id, name, age FROM users");
	std::cout << "\nAll Users:" << std::endl;
	while (query.executeStep())
	{
		int id = query.getColumn(0);
		std::string name = query.getColumn(1);
		int age = query.getColumn(2);
		std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age << std::endl;
	}
}

// Shows a single user by ID
void DatabaseManager::showUserByID(int id)
{
	SQLite::Statement query(db, "SELECT id, name, age FROM users WHERE id = ?");
	query.bind(1, id);
	if (query.executeStep())
	{
		std::string name = query.getColumn(1);
		int age = query.getColumn(2);
		std::cout << "User found: ID " << id << ", Name: " << name << ", Age: " << age << std::endl;
	}
	else
	{
		std::cout << "User with ID " << id << " not found." << std::endl;
	}
}

// Deletes a user by ID
void DatabaseManager::deleteUser(int id)
{
	SQLite::Statement query(db, "DELETE FROM users WHERE id = ?");
	query.bind(1, id);
	query.exec();
	std::cout << "User deleted: ID " << id << std::endl;
}

#endif

#include <Sqlite.h>

int main()
{
    DatabaseManager dbManager("test.db");

    // Create the table
    dbManager.createTable();

    // Insert users
    dbManager.insertUser("Alice", 25);
    dbManager.insertUser("Bob", 30);

    // Show all users
    dbManager.showAllUsers();

    // Update a user
    dbManager.updateUser(1, "Alice Smith", 26);

    // Show a specific user by ID
    dbManager.showUserByID(1);

    // Delete a user
    dbManager.deleteUser(2);

    // Show all users after deletion
    dbManager.showAllUsers();

    return 0;
}
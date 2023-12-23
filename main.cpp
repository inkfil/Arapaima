#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>

int main() {
    try {
        // sql::mysql::MySQL_Driver 
        sql::Driver *driver;
        sql::Connection *con;

        // Create a MySQL driver instance
        driver = sql::mysql::get_mysql_driver_instance();

        // Connect to the MySQL database
        con = driver->connect("tcp://localhost:3306", "root", "#InkFil123");
        
        // Use a specific database
        con->setSchema("school");

        // Create a statement
        sql::Statement *stmt = con->createStatement();

        // Query to get all table names
        sql::ResultSet *res = stmt->executeQuery("SHOW TABLES");

        // Print the list of table names
        while (res->next()) {
            std::cout << "Table Name: " << res->getString(1) << std::endl;
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return 0;
}

/*

[16:44:04] macbookpro:build git:(trunk*) $ g++ -o hello_world tml.cpp -I/usr/include/mysql -lmysqlclient


// to build the program
g++ tmp2.cpp -L/usr/local/mysql-connector-c++-8.2.0/lib64/ -lmysqlcppconn -I/usr/local/mysql-connector-c++-8.2.0/include/ --std=c++11 -o hello_world

export DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++-8.2.0/lib64/:$DYLD_LIBRARY_PATH

mysql -h hostname -u username -p -P port_number database_name


*/


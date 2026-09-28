#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;


// 5. SQL Injection - simulated exampleeeee
void sqlInjection() {
    string username;

    cout << "Username: ";
    cin >> username;

    string query = "SELECT * FROM users WHERE name = '" + username + "'";

    cout << query << endl;
}

int main() {
    sqlInjection();

    return 0;
}
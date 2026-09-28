#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

// 1. Command Injection
void commandInjection() {
    string input;

    cout << "Enter command: ";
    getline(cin, input);

    system(input.c_str());
}

// 2. Hardcoded Secret
void hardcodedSecret() {
    string password = "SuperSecretPassword123!";
    cout << password << endl;
}

// 3. Buffer Overflow
void bufferOverflow() {
    char buffer[10];

    cout << "Enter text: ";
    cin >> buffer;

    cout << buffer << endl;
}

// 4. Unsafe Memory Operation
void unsafeCopy() {
    char source[] = "This is a very long string";
    char destination[5];

    strcpy(destination, source);

    cout << destination << endl;
}

// 5. SQL Injection - simulated example
void sqlInjection() {
    string username;

    cout << "Username: ";
    cin >> username;

    string query = "SELECT * FROM users WHERE name = '" + username + "'";

    cout << query << endl;
}

int main() {
    commandInjection();
    hardcodedSecret();
    bufferOverflow();
    unsafeCopy();
    sqlInjection();

    return 0;
}
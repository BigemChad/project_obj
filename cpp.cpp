#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Prototypy (wrzucić do drugiego pliku)
void commandCD(const string& object);
void commandHelp(const string& object);
void commandExit(const string& object);

// definicja typu komendy
typedef void (*CommandFunction)(const string&);

// Struktura komendy
struct Command {
    string name;
    CommandFunction function;
};

// Lista komend
Command commands[] = {
    {"cd", commandCD},
    {"help", commandHelp},
    {"exit", commandExit}
};

// Parsowanie komendy od użytkownika
void parseInput(const string& input) {
    istringstream iss(input);
    string command, argument = "blank";
    iss >> command;
    getline(iss, argument);

    for (const auto& cmd : commands) {
        if (cmd.name == command) {
            cmd.function(argument);
            return;
        }
    }
    cout << "Zła komenda wpisz help\n";
}

// Komendy 
void commandCD(const string& object) {
    cout << "Zmiana węzła: " << object << '\n';
    //CD LOGIKA TODO
}

void commandHelp(const string& object) {
    cout << "Dostepne komendy:\n";
    for (const auto& cmd : commands) {
        cout << cmd.name << endl;
    }
}

void commandExit(const string& object) {
    cout << "Wyjscie.\n";
    exit(0);
}

int main() {
    string input;
    cout << "Menu Moment\n";
    cout << "Lista komend polecenie help\n";

    while (true) {
        cout << "-> ";
        getline(cin, input);
        parseInput(input);
    }

    return 0;
}

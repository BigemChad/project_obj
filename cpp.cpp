//Windows
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <vector>

//Linux
#include<bits/stdc++.h>

using namespace std;

struct Node {
    string name;
    Node* next;
};


//class leaf
class leaf{
    public:
        char name;
        void addMember(Node &head, string toAdd){
            Node* temp = &head;
            while(temp->next!= NULL){
                temp = temp->next;
            }
            temp->next = new Node;
            temp = temp->next;
            temp->name = toAdd;
            temp->next = NULL;
        }

        void printList(Node &head) {
            Node* temp = &head;
            int i = 1;
            while(temp->next!= NULL){
                cout << i << temp->name << '\n';
                temp = temp->next;
                i++;
            }
            i++;
            cout << temp->name << endl;
        }
    private:
    int value;
    Node* head = new Node;

};

//class branch
class branch{
    public:
        char name;
        int n;
        branch(int hM, char letter){
            n = hM;
            name = letter;
        }
        void displayMembers(vector<leaf>& leaves) {
           for(auto el : leaves)
                cout << el.name << " ";
            cout << '\n';
        }
        void addMembers(vector<leaf>& leaves, int &n) {
            leaf temp;
            for(int i = 0; i < n; i++)
                leaves.push_back(temp);
        }

    private:
        int value;
        vector<leaf> leaves;

};

class root{
    public:
        char name = 'A';
        vector<branch> branches;
        void addBranches(vector<branch>& branches) {
            branch temp1(1, 'B');
            branch temp2(2, 'C');
            branch temp3(3, 'D');
            branches.push_back(temp1);
            branches.push_back(temp2);
            branches.push_back(temp3);
        }

    private:
        int value = 1;
};

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

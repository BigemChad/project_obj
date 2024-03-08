//Windows
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <vector>

//Linux
#include<bits/stdc++.h>

using namespace std;

//ascii dla liter B i E
const int branch_pos = 66;
const int leaf_pos = 69;

string pos_global = "-> ";

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
        vector<leaf> leaves;
        char name;
        int n;
        branch(int hM, char letter){
            n = hM;
            name = letter;
        }
        void displayMembers() {
           for(auto el : leaves)
                cout << el.name << " ";
            cout << '\n';
        }
        void addMembers(int n, vector<char> names) {
            leaf temp;
            for(int i = 0; i < n; i++)
                temp.name = names[i];
                leaves.push_back(temp);
        }

    private:
        int value;
        

};

class root{
    public:
        char name = 'A';
        vector<branch> branches;
        void addBranches() {
            branch temp1(2, 'B');
            branch temp2(1, 'C');
            branch temp3(3, 'D');
            branches.push_back(temp1);
            branches.push_back(temp2);
            branches.push_back(temp3);
        }

    private:
        int value = 1;
};

//stworzenie głównego węzła
root MainRoot;

//pozycja w menu
union current {
    leaf *current_l;
    branch *current_b;
    root *current_r;
};

current cd;
string current_node;


// Prototypy (wrzucić do drugiego pliku)
void commandCD(const string& object);
void commandHelp(const string& object);
void commandExit(const string& object);

// definicja typu komendy
typedef void (*CommandArgument)(const string&);

// Struktura komendy
struct Command {
    string name;
    CommandArgument function;
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
    
        if(object == "A")
        {
            cd.current_r = &MainRoot;
            current_node = "root " + object;
        }
        if(object == "B" || object == "C" || object == "D"){
            char temp = object[0];
            cd.current_b = &MainRoot.branches[int(temp) - branch_pos];
            current_node = "branch " + object;
        }
        if(object == "E" || object == "F" || object == "G" || object == "H" || object == "I" || object == "J"){
            char temp = object[0];
            int branch_pos;

            //w której gałęzi jest liść
            if(object == "E" || object == "F" )
                branch_pos = 0;
            if(object == "G" || object == "H")
                branch_pos = 1;
            if(object == "I" || object == "J")
                branch_pos = 2;
            
            cd.current_l = &MainRoot.branches[branch_pos].leaves[int(temp) - leaf_pos];
            current_node = "leaf " + object;

        cout << current_node << '1' << endl;
        }
    cout << current_node << endl;
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

void createTree() {
    MainRoot.addBranches();
    vector<char> namesB = {'E','F'};
    vector<char> namesC = {'G'};
    vector<char> namesD = {'H' ,'I', 'J'};

    MainRoot.branches[0].addMembers(2, namesB);
    MainRoot.branches[1].addMembers(1, namesC);
    MainRoot.branches[2].addMembers(3, namesD);
}

int main() {
    string input;
    current_node = "";
    

    cout << "Menu Moment\n";
    cout << "Lista komend polecenie help\n";

    while (true) {
        cout << current_node << " " << pos_global;
        getline(cin, input);
        parseInput(input);
        // cout << current_node;
    }

    return 0;
}

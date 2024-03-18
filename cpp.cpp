#ifdef _WIN32
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <cctype>
#elif __linux__
#include <bits/stdc++.h>
#endif
#include "githubCopyright.h"

using namespace std;
//savefile to przykładowy plik do zapisu danych z liscia

//TODO
// NOTHING

//gitignore
// a.exe
// a.out
// README.md


//ascii dla liter
const int branch_pos = 66;
int leaf_pos = 0;
//zabezpieczenie przed brakiem cd
bool isAfterFirstCd = false;

string * pos_global = new string();

const string arrow_pos = "-> ";

struct Node {
    string name;
    Node* next = nullptr;
};

//Prototypy funkcji
void commandCD(const string& object);
void commandHelp(const string& object);
void commandExit(const string& object);
void makeObject(const string& object);
void deleteObject(const string& object);
void modifyObject(const string& object);
void github(const string& object);
void commandDir(const string& object);
void commandShow(const string& object);
void printTree(const string& object);
void saveList(const string& object);
void saveAll(const string& object);
void loadList(const string& object);
void loadAll(const string& object);
int generateUniqueId(int seed);


//class leaf
class LeafBase {
public:
    char name;

    LeafBase(char name) {
        this->name = name;
    }

protected:
    int uniqueId = generateUniqueId(int(name));
};

class leaf : public LeafBase {
public:
    
    leaf(char n) : LeafBase(n) {}

    Node* head = nullptr;
    int classId = 3;
    bool isListNotEmpty = false;

    void addMember(string toAdd){
            if(head == nullptr) {
                head = new Node();
                head->name = toAdd;
                isListNotEmpty = true;
            }
            else {
                Node* temp = head;
                while(temp->next!= nullptr){
                    temp = temp->next;
                }
                temp->next = new Node();
                temp->next->name = toAdd;
            }
        }

         void deleteMember(string toDelete) {
            Node* temp = head;
            Node* prev = nullptr;
                if (temp != nullptr && temp->name == toDelete) {
                    head = temp->next;
                    delete temp;
                    return;
                }
                while (temp != nullptr && temp->name != toDelete) {
                    prev = temp;
                    temp = temp->next;
                }
                 if (temp == nullptr){
                    head = nullptr;
                    cout << "Lista jest pusta\n";
                     return;
                 }
                 
                prev->next = temp->next;
    
                delete temp;
         }

         void modifyMember(string toChange,string newName){
            Node* temp = head;
                if (temp != nullptr && temp->name == toChange) {
                    head->name = (" " + newName);
                    return;
                }
                while (temp != nullptr && temp->name != toChange) {
                    temp = temp->next;
                }
                 if (temp == nullptr){
                    head = nullptr;
                    cout << "Lista jest pusta\n";
                     return;
                 } 
                
                temp->name = (" " + newName);
         }
        void printList() {
            Node* temp = head;
            int i = 1;
            while(temp->next!= NULL){
                cout << i << temp->name << '\n';
                temp = temp->next;
                i++;
            }
            cout<< i << temp->name << endl;
        }
        void displayInfo() {
            cout << "Id klasy obiektu: "<< classId << endl;
            cout << "Id obiektu: " << uniqueId << endl;
        }

        bool listStatus() {
            return isListNotEmpty;
        }

        string getListInfo() {
            string result = "";
            Node* temp = head;
            while (temp != nullptr) {
                result += temp->name + ";";
                temp = temp->next;
            }
            return result;
}

        Node** passList() {
            return &head;
        }
        
};

class BranchBase {
public:
    char name;
    vector<leaf> leaves;

    BranchBase(int hM, char letter) : name(letter) {}

protected:
    int uniqueId = generateUniqueId(time(NULL));
};

class branch : public BranchBase {
public:
    int n;

    branch(int hM, char letter) : BranchBase(hM, letter), n(hM) {}

      void displayMembers() {
           for(auto el : leaves)
                cout << el.name << " ";
            cout << '\n';
        }
        void addMembers(int n, vector<char> names) {
            for(int i = 0; i < n; i++)
                leaves.push_back(leaf(names[i]));
        }
        void displayInfo() {
            cout << "Id klasy obiektu: "<< classId << endl;
            cout << "Id obiektu: " << uniqueId << endl;
            cout << "Ilosc elementow: " << n << endl;
            cout << "Nalezace do obiektu:" << endl;
            for(auto el : leaves) 
                cout << el.name << " ";
            cout << '\n';
        }

    private:
        int classId = 2;
        
    protected:
        int uniqueId = generateUniqueId(int(name));
};

class RootBase {
public:
    char name = 'A';
    vector<branch> branches;

    void addBranches() {
        branches.emplace_back(2, 'B');
        branches.emplace_back(1, 'C');
        branches.emplace_back(3, 'D');
    }

protected:
    int uniqueId = generateUniqueId(time(NULL));
};


class root : public RootBase{
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

        void displayInfo() {
            cout << "Id klasy obiektu: "<< classId << endl;
            cout << "Id obiektu: " << uniqueId << endl;
            cout << "Ilosc elementow: " << branches.size() << endl;
            cout << "Nalezace do obiektu:" << endl;
            for(auto el : branches)
                cout << el.name << endl;
            cout << '\n';
        }

    private:
        int classId = 1;
        
    protected:
        int uniqueId = generateUniqueId(int(name));
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

// definicja typu komendy
typedef void (*FunctionAsArgument)(const string&);

// Struktura komendy
struct Command {
    string name;
    FunctionAsArgument function;
};

// Lista komend
Command commands[] = {
    {"cd", commandCD},
    {"help", commandHelp},
    {"exit", commandExit},
    {"mo", makeObject},
    {"do", deleteObject},
    {"mdo", modifyObject},
    {"dir", commandDir},
    {"show", commandShow},
    {"tree", printTree},
    {"save", saveList},
    {"load", loadList},
    {"saveall", saveAll},
    {"loadall", loadAll},
    {"github", github}
    
};
//bool
bool isInArrayLeaf(char name) {
    // cout << name << '\n';
    char arr[6] = {'E', 'F', 'G', 'H', 'I', 'J'};
    for(int i = 0; i < 6; i++) {
        if(arr[i] == name)
            return true;
    }
    return false;
}

bool isStringNotEmpty(string temp) {
    return !temp.empty() && temp[0] == ' ';
}

bool isRoot(string root){
    string rootLetter = " A";
    if(root == rootLetter)
    return true;

    return false;
}

bool isBranch(string branch) {
    vector<string> branches = {" B"," C"," D"};
    for(auto el : branches)
        if(branch == el)
            return true;
    
            return false;
}

bool isLeaf(string leaf){
    vector<string> leaves = {" E"," F"," G"," H"," I"," J"};
    for(auto el : leaves)
        if(leaf == el)
            return true;
    
            return false;
}

// Parsowanie komendy od użytkownika
void parseInput(const string& input) {
    istringstream iss(input);
    string command, argument = "blank";
    iss >> command;
    getline(iss, argument);

    for (const auto& cmd : commands) {
        if (cmd.name == command) {
            // cout << "parse work\n";
            cmd.function(argument);
            return;
        }
    }
}

string removeSpaces(const string& str) {
    string result;
    for(char c : str){
        if(c != ' ')
            result += c;
    }
    return result;
}

string getLineFromFile(const string& filename, int line) {
    fstream file;
    file.open(filename);
    string result = "";
    int i = 0;
    while(i < line) {
        string line;
        getline(file, line);
        i++;
    }
    getline(file, result, '\n');
    file.close();
    return result;
}

// Komendy 
void commandCD(const string& object) {
    
    //temp w celu porównania z nazwą drzewa
    bool result = false;
    string temp = object;
    // cout << temp << '\n';
    if(temp == " A")
        {
            cd.current_r = &MainRoot;
            // cout << cd.current_r->name << endl;
            current_node = "root" + temp;
            result = true;
        }
        if(isBranch(temp)){
            // cout << "parse work3\n";
            char temp_char = temp[1];
            cd.current_b = &MainRoot.branches[int(temp_char) - branch_pos];
            current_node = "branch" + temp;
            // cd.current_b->displayMembers();
            result = true;
        }
        if(isLeaf(temp)){
            char temp_char = temp[1];
            // cout << temp_char << '\n';

            int branch_pos;

            //w której gałęzi jest liść
            if(temp == " E" || temp == " F" )
                branch_pos = 0;
            if(temp == " G")
                branch_pos = 1;
            if(temp == " I" || temp == " J" || temp == " H")
                branch_pos = 2;
            
            //który liść
            switch(temp_char){
                case 'E':
                leaf_pos = 0;
                break;
                case 'F':
                leaf_pos = 1;
                break;
                case 'G':
                leaf_pos = 0;
                break;
                case 'H':
                leaf_pos = 0;
                break;
                case 'I':
                leaf_pos = 1;
                break;
                case 'J':
                leaf_pos = 2;
                break;
            }
            cd.current_l = &MainRoot.branches[branch_pos].leaves[leaf_pos];
            // cout << int(temp[1]) << " " << cd.current_l->name << '\n';
            // cout << cd.current_l->name << '\n';
            current_node = "leaf" + temp;
            result = true;
        }
        if(!result){
            cout << "Nie istnieje taki wezel\n";
        }
        if(!isAfterFirstCd)
            isAfterFirstCd = true;
}   
void makeObject(const string& temp){
    if(!isAfterFirstCd)
        return;
    // cout << "s" << temp<< "s" << endl;
    // cout << isStringNotEmpty(temp) << endl;

    if(isInArrayLeaf(cd.current_l->name) && isStringNotEmpty(temp)){

        cout << "Dodajesz do listy obiekt" << temp << '\n';
        cd.current_l->addMember(temp);
    }
    else{
        cout << "Nie jestes w obiekcie typu leaf\n";
        cout << "lub nie podales nazwy wezla\n";
}
}

void deleteObject(const string& object){
    if(!isAfterFirstCd)
        return;

    if(isInArrayLeaf(cd.current_l->name) && isStringNotEmpty(object) && cd.current_l->head != nullptr){
        if(cd.current_l->head == nullptr)
        {
            cout << "Lista jest pusta\n";
            return;
        }
        cout << "Usuwasz z listy obiekt" << object << '\n';
        cd.current_l->deleteMember(object);
    }
    else{
        cout << "Nie jestes w obiekcie typu leaf\n";
        cout << "nie podales nazwy wezla\n";
        cout << "lub lista jest pusta\n";
}
}

void modifyObject(const string& object){
    if(!isAfterFirstCd)
        return;

    if(isInArrayLeaf(cd.current_l->name) && isStringNotEmpty(object)){
        if(cd.current_l->head == nullptr)
        {
            cout << "Lista jest pusta\n";
            return;
        }
        string newName;
        cout << "Edytujesz obiekt" << object << '\n';
        cout << "Jak chcesz nazwac obiekt:\n";
        cin >> newName;
        cd.current_l->modifyMember(object, newName);
        cin.ignore();
    }
    else{
        cout << "Nie jestes w obiekcie typu leaf\n";
        cout << "lub nie podales nazwy wezla\n";
}
}

void commandDir(const string& object){
    if(!isAfterFirstCd)
        return;
    if(!(cd.current_l->listStatus()))
        return;
    if(cd.current_l->head == nullptr)
    {
        return;
        cout << "Lista jest pusta\n";
    }

    if(isInArrayLeaf(cd.current_l->name)){
        cd.current_l->printList();
    }
    else{
        cout << "Nie jestes w obiekcie typu leaf\n";
    }
}

void commandShow(const string& object){
    if(!isAfterFirstCd)
        return;

    cout << current_node << " info:" << '\n';
    string last_letter_node = current_node;
    char last_letter = last_letter_node.back();
    cout << last_letter << endl;
    string temp;
    temp+=" ";
    temp+=last_letter;
    if(temp == " A")
        {
           root* used = &MainRoot;
           used->displayInfo();
           return;
        }
        if(isBranch(temp)){
            // cout << "parse work3\n";
            char temp_char = temp[1];
           branch* used = &MainRoot.branches[int(temp_char) - branch_pos];
            used->displayInfo();
            return;
        }
        if(isLeaf(temp)){
            char temp_char = temp[1];
            int branch_pos;
            if(temp == " E" || temp == " F" )
                branch_pos = 0;
            if(temp == " G")
                branch_pos = 1;
            if(temp == " I" || temp == " J" || temp == " H")
                branch_pos = 2;

            switch(temp_char){
                case 'E':
                leaf_pos = 0;
                break;
                case 'F':
                leaf_pos = 1;
                break;
                case 'G':
                leaf_pos = 0;
                break;
                case 'H':
                leaf_pos = 0;
                break;
                case 'I':
                leaf_pos = 1;
                break;
                case 'J':
                leaf_pos = 2;
                break;
            }
            leaf* used = &MainRoot.branches[branch_pos].leaves[leaf_pos];
            used->displayInfo();
            return;
        }
}

void saveList(const string& filename){
    if(!isAfterFirstCd)
        return;
    if(!(cd.current_l->listStatus()))
        return;
    if(cd.current_l->head == nullptr)
    {
        return;
        cout << "Lista jest pusta\n";
    }

    if(isInArrayLeaf(cd.current_l->name)){
        string trimmed = removeSpaces(filename);
        ofstream f(trimmed, ofstream::out | ofstream::trunc);
            if(!f.is_open()){
                cout << "Nie otworzony plik\n";
                return;
            }

    string testCase = "";
    testCase += cd.current_l->getListInfo();
    trimmed = removeSpaces(testCase);
    f << trimmed;
    f.close();
    cout << "Zapis wykonany w pliku" + filename << '\n';
    }
    else{
        cout << "Nie jestes w obiekcie typu leaf\n";
    }

}

void saveAll(const string& filename) {
     if (!isAfterFirstCd)
        return;
    
     if(isInArrayLeaf(cd.current_l->name)){
        string trimmed = removeSpaces(filename);
        ofstream f(trimmed, ofstream::out | ofstream::trunc);
            if(!f.is_open()){
                cout << "Nie otworzony plik\n";
                return;
            }

        for (int i = 0; i < MainRoot.branches.size(); ++i) {
            // cout << 't' + i + '\n';
            for (int j = 0; j < MainRoot.branches[i].leaves.size(); ++j) {
                // cout << 't' + j + '\n';
                auto& leaf = MainRoot.branches[i].leaves[j];

                string leafData = leaf.getListInfo();
                string trimmedData = removeSpaces(leafData);
                if (leafData == "") {
                    f << ";\n";
                } else {
                    f << trimmedData << '\n';
                }
            }
        }

    f.close();
    cout << "Zapis wykonany w pliku" << filename << '\n';
     }
     else{
        cout << "Nie jestes w obiekcie typu leaf\n";
     }
}

void loadList(const string& filename){
    if(!isAfterFirstCd)
            return;
    
       if(isInArrayLeaf(cd.current_l->name)){
        string trimmed = removeSpaces(filename);
        fstream f;
        f.open(trimmed);
            if(!f.is_open()){
                cout << "Nie otworzony plik\n";
                return;
            }
        
        vector<string> tempList;
                    string toLoad, item;
                    getline(f, toLoad);
                    stringstream ss(toLoad);
                    while(getline(ss, item, ';'))
                        tempList.push_back(item);
                    cout << "Wczytywanie do liscia " << cd.current_l->name << '\n';
                    if(!(tempList.empty()))
                    for(auto el : tempList)
                    {
                        if(!(el.empty()))
                        cd.current_l->addMember((' ' + el));
                        else
                        cout << "Plik jest pusty\n";
                        
                    }
                    else
                        cout << "Plik jest pusty\n";
            f.close();
                }
        else{
            cout << "Nie jestes w obiekcie typu leaf\n";
        }
        
}

void loadAll(const string& filename) {
        if(!isAfterFirstCd)
            return;
    
        if(isInArrayLeaf(cd.current_l->name)){
            string trimmed = removeSpaces(filename),toLoad,item;
            vector<string> tempList;
            fstream f;
            f.open(trimmed);
                if(!f.is_open()){
                    cout << "Nie otworzony plik\n";
                    return;
                }
            f.close();
            int lineNumber = 0;
        
         for (int i = 0; i < MainRoot.branches.size(); ++i) {
            // cout << 't' + i + '\n';
            for (int j = 0; j < MainRoot.branches[i].leaves.size(); ++j) {
                // cout << 't' + j + '\n';
                auto& leaf = MainRoot.branches[i].leaves[j];
                toLoad = getLineFromFile(trimmed, lineNumber);
                // cout << toLoad << '\n';
                stringstream ss(toLoad);
                tempList.clear();
                while(getline(ss, item, ';')){
                    tempList.push_back(item);
                }

                for(auto el : tempList){
                    if(!(el.empty())){
                    string temp = " " + el;
                    leaf.addMember(temp);
                    }
                }

                lineNumber++;
            }
        
        }
        cout << "Wczytywanie zakonczone pomyslnie\n";
        }
        else{
            cout << "Nie jestes w obiekcie typu leaf\n";
        }
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

void printTree(const string& blank) {
    cout << "                  A\n";
    cout << "           /      |      \\\n";
    cout << "         B        C       D\n";
    cout << "      /    \\       \\     / | \\\n";
    cout << "    E       F       G   H  I  J\n";
}

int generateUniqueId(int seed) {
    srand(seed); 
    return rand() % 90000 + 10000; 
}

void github(const string& object) {
    openLink("https://github.com/BigemChad");
}

int main() {
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
    string input;
    current_node = "";
    createTree();
    cout << "Menu Moment\n";
    cout << "Lista komend polecenie help\n";
    while (true) {
        cout << current_node << " " << arrow_pos;
        getline(cin, input);
        parseInput(input);
    }

    return 0;
}

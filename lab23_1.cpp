#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename);
    string textline;
    
    // Use sscanf %[^:]
    while(getline(source, textline)){
        char name[100];
        int score1 = 0, score2 = 0, score3 = 0;
        sscanf(textline.c_str(), "%[^:]: %d %d %d", name, &score1, &score2, &score3);
        names.push_back(name);
        int score = score1 + score2 + score3;
        scores.push_back(score);
        grades.push_back(score2grade(score));
    }
}


void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    // Use sscanf to parse the command and key
    
    getline(cin, line);
    char command_c[100], key_c[100];
    sscanf(line.c_str(), "%s %[^\n]", command_c, key_c);
    command = command_c;
    key = key_c;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int school_size = names.size();
    int found_index = -1;
    for(int i = 0; i < school_size; i++){
        if(toUpperStr(names[i]) == key){
            found_index = i;
            break;
        }
    }
    
    cout << "---------------------------------\n";
    if(found_index != -1){
        cout << names[found_index] << "'s score = " << scores[found_index] << "\n";
        cout << names[found_index] << "'s grade = " << grades[found_index] << "\n";
    }
    else{
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    
    int school_size = names.size();
    vector<int> found_indices;
    for(int i = 0; i < school_size; i++){
        if(grades[i] == toupper(key[0])){
            found_indices.push_back(i);
        }
    }
    
    cout << "---------------------------------\n";
    
    for(unsigned i = 0; i < found_indices.size(); i++){
        int index = found_indices[i];
        cout << names[index] << " (" << scores[index] << ")\n";
    }
    if(found_indices.size() == 0){
        cout << "Cannot found.\n";
    }
    
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}

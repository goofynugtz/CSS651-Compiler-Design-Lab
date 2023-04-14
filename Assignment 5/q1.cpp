#include<bits/stdc++.h>
using namespace std;

char startSymbol;
bool startSymbolUnset = true;
map<pair<char, char>, string> parsingTable;

vector<char> readProductions(map<char, vector<string>>& productions){
  int n;
  cout << "Enter #n of production: "; cin >> n;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  cout.flush();
  vector<char> nonTerminals;
  cout << "Productions:\n";
  while(n--){
    string line; getline(cin,line);
    if (startSymbolUnset){
      startSymbol = line[0];
      startSymbolUnset = false;
    }
    string _temp; int index;
    for(int i = 0; i < line.size(); i++){
      if(line[i] == '>'){
        index = i+1;
        break;
      }
    }
    for(int i = index; i < line.size(); i++){
      if(line[i] == '|'){
        while(_temp.back()==' ') _temp.pop_back();
        productions[line[0]].push_back(_temp);
        _temp.clear();
      }
      else if(line[i] != 32)
      _temp.push_back(line[i]);
    }
    productions[line[0]].push_back(_temp);
    nonTerminals.push_back(line[0]);
  }
  return nonTerminals;
}

bool isTerminal(char ch){
  if(ch <= 'A' || ch >= 'Z') return 1;
  return 0;
}

bool isNonTerminal(char ch){
  if(ch >= 'A' && ch <= 'Z') return 1;
  return 0;
}

set<char> findFirst(char x, map<char, vector<string>>& productions){
  set<char> f;
  for(auto it: productions[x]){
    if(isTerminal(it[0])) f.insert(it[0]);
    else {
      set<char> f2 = findFirst(it[0], productions);
      for(auto it: f2) f.insert(it);
    }
  }
  return f;
}

void generateParsingTable(char x, map<char, vector<string>>& productions, 
map<char, set<char>>& first, map<char,set<char>>& follow){
  for(auto i: productions[x]){
    string parseTableEntry = "";
    parseTableEntry.push_back(x);
    parseTableEntry += "->" + i;
    if(isTerminal(i[0])){
      if(i[0] != '#') parsingTable[{x,i[0]}] = parseTableEntry;
      else for(auto it: follow[x]) parsingTable[{x,it}] = parseTableEntry;
    } else for(auto it: first[i[0]]) parsingTable[{x,it}] = parseTableEntry;
  }
}

set<char> findFollow(char x, map<char, vector<string>>& productions, 
map<char, set<char>>& firstSet, map<char, set<char>>& followSet){
  set<char> f;
  for(auto i: productions){
    for(auto j: i.second){
      int n = j.size();
      for(int k = 0; k < n; k++){
        if(j[k] == x){
          if(k != n-1){
            if(isNonTerminal(j[k+1])){
              for(auto &it: firstSet[j[k+1]]){
                if(it == '#'){
                  set<char> temp = findFollow(j[k+1], 
                  productions, firstSet, followSet);
                  for(auto &it: temp) followSet[x].insert(it);
                } else {
                  f.insert(it);
                  followSet[x].insert(it);
                }
              }
            } else {
              f.insert(j[k+1]);
              followSet[x].insert(j[k+1]);
            }
          } else {
            if(i.first == x) continue;
            set<char> followOfParent = findFollow(i.first, 
            productions, firstSet, followSet);
            for(auto it: followSet[i.first]) f.insert(it);
            for(auto it: followOfParent) f.insert(it);
          }
        }
      }
    }
  }
  return f;
}

int main(){
  map<char, vector<string>> productions;
  vector<char> nonTerminals = readProductions(productions);
  set<char> terminals;
  cout << "\nAccepted Production: \n";
  for (auto it: productions){
    cout << it.first << ": ";
    for (auto j: it.second) cout << j << " ";
    cout << "\n";
  }
  cout << "\n";

  map<char, set<char>> first;
  for(auto &i: nonTerminals){
    set<char> f = findFirst(i, productions);
    first[i] = f;
  }

  for(auto it: first){
    cout<<"First("<<it.first<<") -> ";
    cout<<"{ ";
    int count = 0;
    for(auto &j: it.second){
      cout << j;
      count++;
      if(count < it.second.size()) cout << " ";
    }
    cout << " }\n";
  }
  cout << "\n";

  map<char, set<char>> follow;
  follow[startSymbol].insert('$');
  for(auto &i: nonTerminals){
    set<char> f = findFollow(i, productions, first, follow);
    for (auto j: f) follow[i].insert(j);
  }
  
  for (auto i: follow)
    if (i.second.find('#') != i.second.end()) 
      i.second.erase('#');

  for(auto it: follow){
    cout << "Follow("<<it.first<<") -> ";
    cout << "{ ";
    int count = 0;
    for(auto &j: it.second){
      cout << j;
      count++;
      if(count < it.second.size()) cout << " ";
    }
    cout << " }\n";
  }

  for(auto i: first)
    for(auto j: i.second)
      terminals.insert(j);    
  
  for(auto i: follow)
    for(auto j: i.second)
      terminals.insert(j);

  int WIDTH = 8;
  cout << "\nParsing Table:\n\n";
  if(terminals.find('#') != terminals.end()) terminals.erase('#');
  cout << setw(WIDTH) << " |  ";
  for(auto j: terminals){
    cout << setw(WIDTH) << left << j << "|  ";
  }
  cout << "\n";
  for(auto i: nonTerminals){
    cout << setfill(' ') << setw(4) << right << i << " |  " << left;
    generateParsingTable(i, productions, first, follow);
    for(auto &j: terminals)
      cout << setfill(' ') << setw(WIDTH) << parsingTable[{i,j}] << "|  ";
    cout << "\n";
  }
  return 0;
}

/*
5
S -> AB
B -> +AB | #
A -> CD
D -> *CD | #
C -> (S) | i

4
S -> aB | bC | cD
B -> d | #
C -> e | #
D -> f

6
S -> bCEi
C -> dD
D -> cD | #
E -> FG
F -> h | #
G -> g | # 
*/

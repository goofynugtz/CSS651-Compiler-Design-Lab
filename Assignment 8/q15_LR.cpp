#include <bits/stdc++.h>
using namespace std;

#define EPSILON '#'
#define EPSILONSTR "#"
#define COL_SIZE 10

struct state;
string startSymbol;
bool startSymbolUnset = true;
map<string, vector<string>> productions;
map<string, string> reduce;
map<pair<string, string>, int> prodNo;
map<map<string, vector<string>>, int> stateToNode;
int prodCount = 1;

vector<string> readProductions(){
  cout << "Enter lines of production: ";
  int n; cin >> n;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cout.flush();
  vector<string> nonTerminals;
  cout << "Enter Productions:\n";
  while (n--){
    string x, temp, key = "";
    getline(cin, x);
    int idx;
    for (int i = 0; i < x.size(); i++){
      if (x[i] == '>'){
        idx = i + 1;
        break;
      }
    }
    key = x.substr(0, idx - 2);
    if (startSymbolUnset){
      startSymbol = key;
      startSymbolUnset = false;
    }
    while ((!isalnum(key.back())) || key.back() == ' '){
      key.pop_back();
    }
    for (int i = idx; i < x.size(); i++){
      if (x[i] == '|'){
        while (temp.back() == ' '){
          temp.pop_back();
        }
        productions[key].push_back(temp);
        reduce[temp] = key;
        prodNo[{key, temp}] = prodCount++;
        temp.clear();
      } else if (x[i] != 32) temp.push_back(x[i]);
    }
    productions[key].push_back(temp);
    reduce[temp] = key;
    nonTerminals.push_back(key);
    prodNo[{key, temp}] = prodCount++;
  }
  return nonTerminals;
}

bool isNonTerminal(char ch){
  if (ch >= 'A' && ch <= 'Z') return 1;
  return 0;
}

int currNode = -1;
map<pair<int, string>, vector<int>> adj;
set<map<string, vector<string>>> currStates;
map<int, state *> stateID;
map<string, set<string>> FIRST, FOLLOW;
map<pair<int, string>, vector<string>> parsingTable;
set<string> terminalSet;

struct state {
  map<string, vector<string>> prod, initProd;
  map<string, map<string, vector<string>>> nextState;
  int node;
  state(){
    node = ++currNode;
  }

  state(map<string, vector<string>> p){
    node = ++currNode;
    stateID[node] = this;
    prod = p;
  }

  void printProd(){
    for (auto &i : prod)
      for (auto &j : i.second)
        cout << "\t" << i.first << "->" << j << "\n";
  }

  void processProd(){
    while (1){
      map<string, vector<string>> newProd;
      for (auto &i : prod){
        for (auto &j : i.second){
          int dot = j.find('.');
          string nonTerminal = "";
          nonTerminal.push_back(j[dot + 1]);
          if (isNonTerminal(nonTerminal[0]))
            for (auto &k : productions[nonTerminal])
              if (find(prod[nonTerminal].begin(), 
              prod[nonTerminal].end(), "." + k) == prod[nonTerminal].end())
                newProd[nonTerminal].push_back("." + k);
        }
      }
      for (auto &i : newProd)
        for (auto &it : i.second)
          prod[i.first].push_back(it);
      if (newProd.empty()) break;
    }
  }

  void progressProd(){
    for (auto &i : prod){
      for (auto &j : i.second){
        int dot = j.find('.');
        if (dot == j.size() - 1){
          if (j[dot - 1] == startSymbol[0])
            parsingTable[{node, "$"}].push_back("Accept");
          else {
            for (auto &k : terminalSet){terminalSet
              string check = "";
              for (auto &ptr : j){
                if (ptr == '.')
                  continue;
                check.push_back(ptr);
              }
              adj[{node, k}].push_back(-(prodNo[{i.first, check}]));
            }
          }
        }
        else {
          string nextCharConsumed = j.substr(dot + 1, 1);
          string nextString = j;
          swap(nextString[dot], nextString[dot + 1]);
          (nextState[nextCharConsumed])[i.first].push_back(nextString);
        }
      }
    }
    for (auto &i : nextState){
      if (currStates.find(i.second) == currStates.end()){
        currStates.insert(i.second);
        state *t = new state();
        stateID[currNode] = t;
        t->prod = i.second;
        stateToNode[i.second] = currNode;
        adj[{node, i.first}].push_back(currNode);
      }
      else {
        adj[{node, i.first}].push_back(stateToNode[i.second]);
      }
    }
  }
};

set<string> findFirst(string x){
  set<string> f;
  for (auto &i : productions[x]){
    if (!(i[0] >= 'A' && i[0] <= 'Z'))
      f.insert(i.substr(0, 1));
    else {
      if (x[0] == i[0]) continue;
      set<string> f2 = findFirst(i.substr(0, 1));
      for (auto &it : f2)
        f.insert(it.substr(0, 1));
    }
  }
  return f;
}

set<string> findFollow(string x, map<string, 
set<string>> &FIRST, map<string, set<string>> &FOLLOW){
  set<string> f;
  for (auto &i : productions){
    for (auto j : i.second){
      int sz = j.size();
      for (int k = 0; k < sz; k++){
        if (j[k] == x[0]){
          if (k != sz - 1){
            if (isNonTerminal(j[k + 1])){
              for (auto &it : FIRST[j.substr(k + 1, 1)]){
                if (it[0] == EPSILON){
                  set<string> temp = findFollow(j.substr(k + 1, 1), 
                  FIRST, FOLLOW);
                  for (auto &itr : temp)
                    FOLLOW[x].insert(itr.substr(0, 1));
                } else {
                  f.insert(it.substr(0, 1));
                  FOLLOW[x].insert(it.substr(0, 1));
                }
              }
            } else {
              f.insert(j.substr(k + 1, 1));
              FOLLOW[x].insert(j.substr(k + 1, 1));
            }
          } else {
            if (i.first == x)
              continue;
            set<string> followOfParent = findFollow(i.first, FIRST, FOLLOW);
            for (auto &itr : FOLLOW[i.first])
              f.insert(itr.substr(0, 1));
            for (auto &itr : followOfParent)
              f.insert(itr.substr(0, 1));
          }
        }
      }
    }
  }
  return f;
}

int main(){
  vector<string> nonTerminals = readProductions();
  for (auto &i : productions){
    for (auto &j : i.second){
      for (auto &k : j){
        if (isNonTerminal(k) == false){
          string temp = "";
          temp.push_back(k);
          terminalSet.insert(temp);
        }
      }
    }
  }
  vector<string> terminals;
  for (auto &i : terminalSet) terminals.push_back(i);
  terminals.push_back("$");
  terminalSet.insert("$");
  string augStartSymbol = startSymbol + "\'";
  vector<state> States;
  map<string, vector<string>> initProd;
  initProd[augStartSymbol].push_back("." + startSymbol);
  state init;
  init.prod = initProd;
  cout << "\nState 0:" << "\n";
  init.processProd();
  init.printProd();
  init.progressProd();
  cout << "\n";
  for (int i = 1; i <= currNode; i++){
    cout << "State " << stateID[i]->node << ":" << "\n";
    stateID[i]->processProd();
    stateID[i]->printProd();
    stateID[i]->progressProd();
    cout << "\n";
  }
  for (int i = 0; i <= currNode; i++){
    for (auto &j : terminals){
      if (adj.find({i, j}) != adj.end()){
        for (auto &it : adj[{i, j}]){
          if (it < 0){
            string temp = "R";
            temp += to_string(-it);
            parsingTable[{i, j}].push_back(temp);
          } else {
            string temp = "S";
            temp += to_string(it);
            parsingTable[{i, j}].push_back(temp);
          }
        }
      }
    }
    for (auto &j : nonTerminals){
      if (adj.find({i, j}) != adj.end())
        for (auto &it : adj[{i, j}])
          parsingTable[{i, j}].push_back(to_string(it));
    }
  }
  cout << "LR(0) Parsing Table" << "\n";
  cout << left << setw(COL_SIZE) << " ";
  for (auto &j : terminals){
    cout << setw(COL_SIZE) << " " + j;
  }
  for (auto &j : nonTerminals){
    cout << setw(COL_SIZE) << " " + j;
  }
  cout << "\n";
  for (int i = 0; i <= currNode; i++){
    string row = "";
    row += to_string(i);
    cout << left << setw(COL_SIZE) << row;
    for (auto &j : terminals){
      string x = " ";
      for (auto &it : parsingTable[{i, j}]){
        x = x + it;
        if (it != parsingTable[{i, j}].back())
          x += ",";
      }
      cout << setw(COL_SIZE) << x;
    }
    for (auto &j : nonTerminals){
      string x = " ";
      for (auto &it : parsingTable[{i, j}]){
        x = x + it;
        if (it != parsingTable[{i, j}].back())
          x += ",";
      }
      cout << setw(COL_SIZE) << x;
    }
    cout << "\n";
  }
  cout << "----------------------------------------------------\n";
  cout << "\nInput parse string: ";
  string s; cin >> s;
  deque<char> inpBuffer, inpStack;
  inpStack.push_back('0');
  for (auto &it : s)
    inpBuffer.push_back(it);
  inpBuffer.push_back('$');
  while (!inpBuffer.empty()){
    string f = "";
    f.push_back(inpBuffer.front());
    if (parsingTable.find({inpStack.back() - 48, f}) 
    == parsingTable.end()){
      cout << inpStack.back() << " " << f << "\n";
      cout << "\n[!] Rejected due to parsing error." << "\n";
      return 2;
    }
    if (parsingTable[{inpStack.back() - 48, f}].size() > 1){
      cout << "\nShift-Reduce Conflict exists @";
      cout << "ParseTable [" << inpStack.back() << "][" << f << "] -> ";
      for (auto &itr : parsingTable[{inpStack.back() - 48, f}]){
        cout << itr;
        if (itr != parsingTable[{inpStack.back() - 48, f}].back())
          cout << ",";
      }
      cout << "\n>> Rejected." << "\n";
      return 2;
    }
    for (auto &itr : parsingTable[{inpStack.back() - 48, f}]){
      if (itr == "Accept"){
        cout << "\n>> Accepted" << "\n";
        return 1;
      }
      if (itr[0] == 'S'){
        int stateToShift = stoi(itr.substr(1));
        inpStack.push_back(inpBuffer.front());
        inpBuffer.pop_front();
        inpStack.push_back((stateToShift) + 48);
        string tempStack = "";
        for (auto &i : inpStack)
          tempStack.push_back(i);
        string tempBuffer = "";
        for (auto &i : inpBuffer)
          tempBuffer.push_back(i);
        cout << setw(COL_SIZE + 5) << tempStack;
        cout << setw(COL_SIZE + 5) << tempBuffer;
        string instr = "Shift ";
        instr.push_back((stateToShift) + 48);
        cout << setw(COL_SIZE + 5) << instr << "\n";
      } else if (itr[0] == 'R'){
        int prodNumberToReduce = stoi(itr.substr(1));
        pair<string, string> redProd;
        for (auto &i : prodNo){
          if (i.second == prodNumberToReduce){
            redProd = i.first;
            break;
          }
        }
        for (int i = 0; i < redProd.second.size(); i++){
          inpStack.pop_back();
          inpStack.pop_back();
        }
        int gotoState = stoi(parsingTable[{inpStack.back() - 48, 
        redProd.first}].front());
        for (auto &it : redProd.first)
          inpStack.push_back(it);
        inpStack.push_back(gotoState + 48);
        string tempStack = "";
        for (auto &i : inpStack)
          tempStack.push_back(i);
        string tempBuffer = "";
        for (auto &i : inpBuffer)
          tempBuffer.push_back(i);
        cout << setw(COL_SIZE + 5) << tempStack;
        cout << setw(COL_SIZE + 5) << tempBuffer;
        string instr = "Reduce ";
        instr.push_back(char((prodNumberToReduce) + 48));
        cout << setw(COL_SIZE + 5) << instr << "\n";
      } else {
        cout << "Rejected\n";
        return 3;
      }
    }
  }
  return 0;
}

/*
E->E+T | T
T->T*F | F
F->(E) | x
*/

/*
2
S->A
A->Ab|a
*/

/*
S->AA
A->aA|b
*/
// abab
// abb
#include <bits/stdc++.h>
using namespace std;

vector<char> readProd(map<char,vector<string>> & prod){
  int n; cin >> n;
  vector<char> nonTerminals;
  while (--n){
    string x;
    getline(cin, x);
    string temp;
    int index = x.find_first_of('=');
    for (int i = index; i < x.size(); i++){
      if (x[i] == '|'){
        prod[x[0]].push_back(temp);
        temp.clear();
      } else if (isalpha(x[i]) && x[i] != 32) temp.push_back(x[i]);
    }
    nonTerminals
  }
}

bool isNonTerminal(char ch){
  if (islower(ch)) return 0;
  return 1;
}

set<char> findFirst(char x, map<char, vector<string>> prod){
  set<char> f;
  for (auto it: prod[x]){
    if (isNonTerminal(it[0])){
      f.insert(it[0]);
    } else {
      findFirst(it[0], prod);
    }
  }
}

int main(void){
  map<char,vector<string>> production;  
  vector<char> nonTerminals = readProd(production);
  map<char,set<char>> first;

  // Print productions
  for (auto it: production){
    cout << it.first << "";
  }

  for (auto it: nonTerminals){
    set<char> f = findFirst(it, production);
    first[it] = f;
  }
  for (auto it: first){
    cout << "{ ";
    for (auto j: it.second){
      cout << j << " ";
    }
    cout << "\n";
  }
  return 0;
}
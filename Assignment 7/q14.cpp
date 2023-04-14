#include <bits/stdc++.h>
using namespace std;

bool isTerminal(string ch){
  if(ch <= "A" || ch >= "Z") return 1;
  return 0;
}

int main(void){
  map<string, pair<vector<string>, bool>> production;
  production["S"] = {{"S+T", "aA"}, 0};
  production["A"] = {{"Ab", "cB"}, 0};
  production["B"] = {{"d"}, 0};
  production["T"] = {{"e"}, 0};

  for (auto &it: production){
    vector<string> _t;
    for (int i = 0; i < it.second.first.size(); i++){
      string _comp;
      _comp += it.second.first[i][0];
      string prime = it.first + "'";
      if (_comp == it.first){
        it.second.second = 1;
        string _temp = it.second.first[i].substr(1, it.second.first[i].length()-1);
        _temp += prime;
        production[prime].first.push_back(_temp);
        it.second.first.erase(it.second.first.begin()+i);
      }
    }
    for (int i = 0; i < it.second.first.size(); i++){
      if (it.first[it.first.length()-1] == '\'') continue;
      if (isTerminal(it.second.first[i]) || it.second.second == 0) continue;
      it.second.first[i] += it.first + "'";
    }
  }

  for (auto it: production){
    cout << it.first << ": "; 
    for (auto i: it.second.first)
      cout << i << "    ";
    cout << "\n";
  }
  return 0;
}

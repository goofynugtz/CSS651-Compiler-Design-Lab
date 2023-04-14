#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::string;
using std::vector;

void stateAorB(vector<char>& a, vector<char>& b, vector<string>& ans){
  vector<string> s2;
  for (auto &it: ans){
    string t = it;
    for (auto &j: a){
      t.push_back(j);
      s2.push_back(t);
      t.pop_back();
    }
    for (auto &j: b){
      t.push_back(j);
      s2.push_back(t);
      t.pop_back();
    }
  }
  ans = s2;
}

void stateA(vector<char>& a, vector<string>& ans){
  vector<string> s2;
  for (auto it: ans){
    string t = it;
    for (auto j: a){
      t.push_back(j);
      s2.push_back(t);
      t.pop_back();
    }
  }
  ans = s2;
}

void computeRegex1(vector<char>& a, vector<char>& b){
  cout << "\n>> For (a|b)(a|b) \n";
  vector<string> ans = {""};
  stateAorB(a, b, ans);
  stateAorB(a, b, ans);
  cout << "{  ";
  for (auto it: ans) cout << it << " ";
  cout << " }\n";
}

void computeRegex2(vector<char>& a, vector<char>& b){
  cout << "\n>> For a(a|b)b \n";
  vector<string> ans = {""};
  stateA(a,ans);
  stateAorB(a, b, ans);
  stateA(b,ans);
  cout << "{  ";
  for (auto it: ans) cout << it << " ";
  cout << " }\n";
}

int main(void){
  vector<char> a = {'a'};
  vector<char> b = {'b'};
  computeRegex1(a,b);
  computeRegex2(a,b);
  return 0;
}
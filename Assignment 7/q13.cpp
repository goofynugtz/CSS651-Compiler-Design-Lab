#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& out, const vector<string>& v) {
  string _temp;
  for (string it: v) _temp += it;
  cout << _temp;
  return out;
}

int main(void){
  unordered_map<string, vector<string>> production;
  // production["S"] = {"S+S", "S*S", "i"};
  production["S"] = {"S*S", "S+S", "i"};
  string inputString = "i+i*i";
  
  inputString.push_back('$');
  string startSymbol = "S";

  vector<string> stack;
  stack.push_back("$");

  int WIDTH = 15;
  cout << setw(WIDTH) << left << "Stack" << "| " << setw(WIDTH) 
  << "Input Buffer" << "| " << setw(WIDTH) << "Parsing Action" << "\n";

  while(1){
    bool action = true;
    int i = 0;
    while(i < production[startSymbol].size()){
      if (stack.back() == production[startSymbol][i]){
        stack.pop_back();
        stack.push_back(startSymbol);
        cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) 
        << inputString << "| " << "Reduce S->" << 
        production[startSymbol][i] << "\n";
        i = -1;
        action = false; 
      }
      i++;
    }
    if (inputString.length() > 1){
      string _temp;
      _temp += inputString[0];
      stack.push_back(_temp);
      inputString = inputString.substr(1, inputString.length()-1);
      cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) 
      << inputString << "| " << setw(WIDTH) << "Shift" << setw(0) << "\n";
      action = false;
    }
    if (inputString == "$" 
    && stack[0] == "$" 
    && stack[1] == startSymbol 
    && stack.size() == 2){
      cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) 
      << inputString << "| " << setw(WIDTH) << "Accepted" << setw(0) << "\n";
      break;
    }
    if (action){
      cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) 
      << inputString << "| " << setw(WIDTH) << "Rejected" << setw(0) << "\n";
      break;
    }
  }

  return 0;
}
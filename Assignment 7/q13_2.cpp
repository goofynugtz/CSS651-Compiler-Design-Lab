#include <bits/stdc++.h>
using namespace std;


int main(void){
  map<char, vector<string>> production;
  production['S'] = {"S+S", "", "i"};
  // production['S'] = {"S*S", "S+S", "i"};
  string inputString = "i+i*i";
  inputString.push_back('$');
  char startSymbol = 'S';

  string stack;
  stack.push_back('$');

  int WIDTH = 15;
  cout << "\n" << setw(WIDTH) << left << "Stack" << "| " << setw(WIDTH) << "Input Buffer" << "| " << setw(WIDTH) << "Parsing Action" << "\n";

  while(1){
    bool action = true;
    int i = 0;
    while(i < production[startSymbol].size()){
      if (stack.find(production[startSymbol][i]) != string::npos){
        string _temp;
        _temp += startSymbol;
        stack.replace(stack.find(production[startSymbol][i]),production[startSymbol][i].length(), _temp);
        cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) << inputString << "| " << "Reduce S->" << production[startSymbol][i] << "\n";
        i = -1;
        action = false; 
      }
      i++;
    }
    if (inputString.length() > 1){
      stack.push_back(inputString[0]);
      inputString = inputString.substr(1, inputString.length()-1);
      cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) << inputString << "| " << setw(WIDTH) << "Shift" << setw(0) << "\n";
      action = false;
    }
    if (inputString == "$" && stack[0] == '$' && stack[1] == startSymbol && stack.size() == 2){
      cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) << inputString << "| " << setw(WIDTH) << "Accepted" << setw(0) << "\n";
      break;
    }
    if (action){
      cout << left << setw(WIDTH) << stack << "| " << setw(WIDTH) << inputString << "| " << setw(WIDTH) << "Rejected" << setw(0) << "\n";
      break;
    }
  }

  return 0;
}
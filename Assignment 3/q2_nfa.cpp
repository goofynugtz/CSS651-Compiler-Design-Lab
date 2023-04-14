#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::string;

bool s1(string& s, int i);
bool s2(string& s, int i);
bool s3(string& s, int i);
bool s4(string& s, int i);

bool s1(string& s, int i){
  if (i >= s.length()) return false;
  if (s[i] == 'a'){
    cout << "0-a-";
    return s2(s, i+1);
  }
  return false;
}
bool s2(string& s, int i){
  if (i >= s.length()) return false;
  if (s[i] == 'b'){
    cout << "1-b-";
    return s3(s, i+1);
  }
  return false;
}
bool s3(string& s, int i){
  if (i >= s.length()) return false;
  if (s[i] == 'a'){
    cout << "2-a-";
    return s4(s, i+1);
  }
  return false;
}
bool s4(string& s, int i){
  if (i >= s.length()) return true;
  if (s[i] == 'a'){
    cout << "3-a-";
    return s4(s, i+1);
  }
  return false;
}

int main(void){
  while(1){
    cout << "\n>> Input string: ";
    string s; cin >> s;
    (s1(s, 0)) ? cout << "\nAccepted\n\n" : cout << "\nRejected\n\n";
  }
}
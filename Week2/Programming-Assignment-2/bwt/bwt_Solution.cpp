#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";

  // write your code here
  vector <string> Temp;
  Temp.push_back(text);
  for(int i=1; i<text.size(); i++){
     string s=Temp[i-1];
     char c= s.back();
     s.pop_back();
     s=c+s;
     Temp.push_back(s);
  }
  sort(Temp.begin(),Temp.end());
  for(int i=0; i<Temp.size(); i++)
    result.push_back(Temp[i][text.size()-1]);
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}

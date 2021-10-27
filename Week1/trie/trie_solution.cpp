#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  int start;
  int end_=1;
  // write your code here
   edges root;
   t.push_back(root);
  for(int i=0; i< patterns.size(); i++) {
    start=0;
    for(int j=0; j<patterns[i].size();j++) {
      char Current_Char=patterns[i][j];
      edges::iterator endgIt=t[start].find(Current_Char);
       if(endgIt!=t[start].end()) {
        start=endgIt->second;     
       }
       else{
        t[start].insert(make_pair(Current_Char,end_));
        start=end_;
        end_++;
        edges temp;
        t.push_back(temp); 
       }

    }       
  
  
  }


  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
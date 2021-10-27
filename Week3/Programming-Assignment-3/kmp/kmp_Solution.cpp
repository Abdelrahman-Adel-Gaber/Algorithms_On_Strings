#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;



vector<int>Computr_Prefix_Function(const string& p ) {
    vector<int>s(p.size());
    s[0]=0;
    int border=0;
    for(int i=1;i<p.size(); i++) {
        while((border>0)&&(p[i])!=p[border])
         border=s[border-1];

        if(p[i]==p[border])
         border=border+1;
        else
         border=0;

        s[i]=border;
    }


return s;
}
// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string temp=pattern+'$'+text;
  vector<int>s=Computr_Prefix_Function(temp);
   int l=pattern.size();
  for(int i=l+1; i<temp.size(); i++) {
      if(s[i]==l)
       result.push_back(i-2*l);
  }



  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
bool sort_helper(const pair<string,int>&A,const pair<string,int>&B) {
    return A.first<B.first;
}

vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  // Implement this function yourself
  vector<pair<string,int>> Temp;
  string S=text;
  for(int i=0; S.size()>0; i++) {
      Temp.push_back(make_pair(S,i));
      S.erase(S.begin());
  }
  sort(Temp.begin(),Temp.end(),sort_helper);
   for(int i=0; i<Temp.size(); i++)
    result.push_back(Temp[i].second);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}

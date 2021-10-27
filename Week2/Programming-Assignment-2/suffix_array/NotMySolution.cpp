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
bool comp ( const pair<string, int>& l, const pair<string, int>& r)
{
   return l.first < r.first;
}

vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  vector<pair<string, int> > suffixes;
  for (int i = 0; i < text.size(); i++)
  {
    string temp = text.substr(i) ;
    pair<string, int> tempPair(temp, i);
    suffixes.push_back(tempPair);
  }
  sort(suffixes.begin(), suffixes.end(), comp);
  for (pair<string, int> tempSuffix : suffixes)
  {
    result.push_back(tempSuffix.second);
  }
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
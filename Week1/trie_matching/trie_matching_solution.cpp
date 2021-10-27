#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(const vector<string> & patterns) {
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


vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
    trie t=build_trie(patterns);
   // write your code here
	for(int i=0; i<text.size(); i++) {
		int current_positins=0;
		edges::iterator edgIt=t[current_positins].find(text[i]);
		int v=i;
		while(edgIt!=t[current_positins].end()) {
            v++;
			if(v<text.size()){
			 current_positins=edgIt->second;
			 edgIt=t[current_positins].find(text[v]);
           }
 	       else{
            current_positins=edgIt->second;
		    break;
	       }
             	}
        edges::iterator itr=t[current_positins].find('$');
        if(itr!=t[current_positins].end())
		result.push_back(i);
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	    patterns[i].push_back('$');
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}

/*****************************Large Memory Size*********************************/
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void Recursive_Function(vector<string>&result,vector<string>&text) {
vector<vector<int>>occurance(4);

  for(int i=0; i<text.size();i++ ) {
     switch (text[i][0]) {
          case 'A':
          occurance[0].push_back(i);
          break;
          case 'T':
          occurance[1].push_back(i);
          break;
          case 'G':
          occurance[2].push_back(i);
          break;
          case 'C':
          occurance[3].push_back(i);
          break;
          default:
          result.push_back("$");
          break;
        }

  }
  string symbols="ATGC";
  for(int i=0; i<4; i++){
        if(occurance[i].size()==0){
          //do noting
        }
       else if(occurance[i].size()==1) {
          result.push_back(text[occurance[i][0]]);
       }
       else{
          vector<string>temp;
          for(int j=0; j<occurance[i].size(); j++) {
            string s=text[occurance[i][j]].substr(1,text[occurance[i][j]].size());
            temp.push_back(s);
           }
           string s;
           s.push_back(symbols[i]);
           int v=1;
           while(v!=0)
            {
                for(int i=1;i<temp.size();i++) {
                    if(temp[0][0]!=temp[i][0]){
                        v=0;
                        break;
                    }
                }
                if(v!=0) {
                    s.push_back(temp[0][0]);
                    for(int i=0;i<temp.size();i++)
                      temp[i].erase(temp[i].begin());

                }
            }
           result.push_back(s);
           Recursive_Function(result,temp);
       }
     }

}


// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  vector<vector<int>>occurance(4);
  // Implement this function yourself
   for(int i=0; i<text.size(); i++) {
        switch (text[i]) {
          case 'A':
          occurance[0].push_back(i);
          break;
          case 'T':
          occurance[1].push_back(i);
          break;
          case 'G':
          occurance[2].push_back(i);
          break;
          case 'C':
          occurance[3].push_back(i);
          break;
          default:
          result.push_back("$");
          break;
        }
     }
     string symbols="ATGC";
     for(int i=0; i<4; i++){
        if(occurance[i].size()==0){
          //do noting
        }
       else if(occurance[i].size()==1) {
         result.push_back(text.substr(occurance[i][0],text.size()));
       }
       else{
          vector<string>temp;
          for(int j=0; j<occurance[i].size(); j++) {
            temp.push_back(text.substr(occurance[i][j]+1,text.size()));
           }
           string s;
           s.push_back(symbols[i]);
           int v=1;
           while(v!=0)
            {
                for(int i=1;i<temp.size();i++) {
                    if(temp[0][0]!=temp[i][0]){
                        v=0;
                        break;
                    }
                }
                if(v!=0) {
                    s.push_back(temp[0][0]);
                    for(int i=0;i<temp.size();i++)
                      temp[i].erase(temp[i].begin());

                }
            }
           result.push_back(s);
         Recursive_Function(result,temp);
       }
     }

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}

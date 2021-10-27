#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void Recursive_Function(vector<string>&result,vector<int>&temp_,const string& text) {
vector<vector<int>>occurance(4);

  for(int i=0; i<temp_.size();i++ ) {
     switch (text[temp_[i]]) {
          case 'A':
          occurance[0].push_back(temp_[i]);
          break;
          case 'T':
          occurance[1].push_back(temp_[i]);
          break;
          case 'G':
          occurance[2].push_back(temp_[i]);
          break;
          case 'C':
          occurance[3].push_back(temp_[i]);
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

          vector<int>temp;
          for(int j=0; j<occurance[i].size(); j++) {
            temp.push_back(occurance[i][j]+1);
           }
           string s;
           s.push_back(symbols[i]);
           int v=1;
           while(v!=0)
            {
                for(int i=v;i<temp.size();i++) {
                    if(text[temp[0]]!=text[temp[i]]){
                        v=0;
                        break;
                    }
                }
                if(v!=0) {
                    s.push_back(text[temp[0]]);
                    for(int i=0;i<temp.size();i++)
                      temp[i]=1+temp[i];

                }
            }
           result.push_back(s);
         Recursive_Function(result,temp,text);
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
          vector<int>temp;
          for(int j=0; j<occurance[i].size(); j++) {
            temp.push_back(occurance[i][j]+1);
           }
           string s;
           s.push_back(symbols[i]);
           int v=1;
           while(v!=0)
            {
                for(int i=v;i<temp.size();i++) {
                    if(text[temp[0]]!=text[temp[i]]){
                        v=0;
                        break;
                    }
                }
                if(v!=0) {
                    s.push_back(text[temp[0]]);
                    for(int i=0;i<temp.size();i++)
                      temp[i]=1+temp[i];

                }
            }
           result.push_back(s);
         Recursive_Function(result,temp,text);
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

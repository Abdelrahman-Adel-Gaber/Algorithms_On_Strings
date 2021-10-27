#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

using namespace std;
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

/*******************************************************************/
vector<int>SortCharacters(const string& S) {
    vector<int>order(S.size());
    map<char,int>count__;
    count__['$']=0;
    count__['A']=0;
    count__['C']=0;
    count__['G']=0;
    count__['T']=0;


    for(int i=0; i<S.size(); i++) {
       count__[S[i]] =count__[S[i]]+1;
     }

    for( map<char,int>::iterator itr=count__.begin();
    itr!=count__.end(); itr++) {
        if(next(itr,1)==count__.end())
          break;
        next(itr,1)->second=next(itr,1)->second+itr->second;
    }

    for(int i=0; i<S.size(); i++) {
        char c=S[i];
        count__[c]=count__[c]-1;
        order[count__[c]]=i;
    }

return order;
}

/*******************************************************************/

vector<int>ComputeCharClasses(const string& S,const vector<int> &order) {
    vector <int> classes(S.size());
    classes[order[0]]=0;

    for(int i=1; i<S.size(); i++) {
        if(S[order[i]]!=S[order[i-1]])
          classes[order[i]]=classes[order[i-1]]+1;
        else
          classes[order[i]]=classes[order[i-1]];
    }
 return classes;
}

/*******************************************************************/

vector<int>SortDoubled(const string& S,int l, const vector<int>& order, const vector<int>& classes) {
   int L_S=S.size();
    vector<int>count_(L_S,0);
    vector<int>new_order(L_S,0);

    for(int i=0; i<L_S; i++)
     count_[classes[i]]=count_[classes[i]]+1;
    for(int i=1; i<L_S; i++)
     count_[i]=count_[i]+count_[i-1];

  for(int i=L_S-1; i>=0; i--) {
      int start = (order[i]-l+L_S)%L_S;
      int cl=classes[start];
      count_[cl]=count_[cl]-1;
      new_order[count_[cl]]=start;
  }
return new_order;
}

/******************************************************************/
vector<int>UpdateClasses( const vector<int>& new_order, const vector<int>& classes, int l) {

    int n=new_order.size();
    vector<int>new_class(n);
    new_class[new_order[0]]=0;

    for(int i=1; i<n; i++) {
        int cur =new_order[i];
        int prev=new_order[i-1];
        int mid=(cur+l)%n;
        int mid_prev=(prev+l)%n;

        if( classes[cur]!=classes[prev] || classes[mid]!=classes[mid_prev] )
         new_class[cur]=new_class[prev]+1;
        else
         new_class[cur]=new_class[prev];
    }

return new_class;
}
/******************************************************************/
vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  // Implement this function yourself
  result=SortCharacters(text);
  vector <int> classes=ComputeCharClasses(text,result);
  int l=1;


  while(l<text.size()) {
      result= SortDoubled(text,l,result,classes);
      classes= UpdateClasses(result,classes,l);
      l=l*2;
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

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

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

vector<int> FindOccurrences(const string& pattern, string& text, const vector<int>& suffix_array) {
  vector<int> result;

  // write your code here
 int start;
 int end_ ;
 int l= pattern.size();
 int minIndex = 0;
 int maxIndex = text.size();

 while(minIndex < maxIndex ) {
     int midIndex = (maxIndex+minIndex)/2 ;
     bool decision = pattern > text.substr(suffix_array[midIndex],l<text.size()-suffix_array[midIndex]?l:text.size()-suffix_array[midIndex]);
     if(decision)
      minIndex = midIndex + 1;
     else 
     maxIndex = midIndex; 
 }
 start = minIndex;
 maxIndex = text.size(); 

  while(minIndex < maxIndex ) {
     int midIndex = (maxIndex+minIndex)/2 ;
     bool decision = pattern < text.substr(suffix_array[midIndex],l<text.size()-suffix_array[midIndex]?l:text.size()-suffix_array[midIndex]);
     if(decision)
      maxIndex = midIndex;
     else 
     minIndex = midIndex+1; 
 }
 end_ = maxIndex;
 if(start<=end_)
 for(int i =start; i<end_; i++)
  result.push_back(suffix_array[i]);

return result;

}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}

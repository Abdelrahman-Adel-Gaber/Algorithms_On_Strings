#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position
//       of this character in the sorted array of
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt,
                   map<char, int>& starts,
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  int A=0,C=0,G=0,T=0;
     occ_count_before['A']={};
     occ_count_before['C']={};
     occ_count_before['G']={};
     occ_count_before['T']={};

     occ_count_before['A'].push_back(A);
     occ_count_before['C'].push_back(C);
     occ_count_before['G'].push_back(G);
     occ_count_before['T'].push_back(T);

  for(int i=0;i<bwt.size();i++) {
     switch (bwt[i])
     {
     case 'A':
         A++;
         break;
     case 'C':
         C++;
         break;
     case 'G':
         G++;
         break;
     case 'T':
         T++;
         break;
   default:
         break;

     }

     occ_count_before['A'].push_back(A);
     occ_count_before['C'].push_back(C);
     occ_count_before['G'].push_back(G);
     occ_count_before['T'].push_back(T);


     }

     starts['A']=1;
     starts['C']=starts['A']+A;
     starts['G']=starts['C']+C;
     starts['T']=starts['G']+G;
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences( string& pattern,
                      string& bwt,
                      map<char, int>& starts,
                      map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
int top =0;
int buttom=bwt.size()-1;
string Temp=pattern;
while(top<=buttom) {
  if(!Temp.empty()) {
      char currnt_sympol=Temp[Temp.size()-1];
      Temp.pop_back();
      if(top<occ_count_before[currnt_sympol].size())
      top=starts[currnt_sympol]+occ_count_before[currnt_sympol][top];
      else{
        return 0;}
      if(buttom+1 <occ_count_before[currnt_sympol].size())
      buttom=starts[currnt_sympol]+occ_count_before[currnt_sympol][buttom+1]-1;
      else
        return 0;
   }else
  {
      return buttom-top+1;
  }
}
  return 0;
}


int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}

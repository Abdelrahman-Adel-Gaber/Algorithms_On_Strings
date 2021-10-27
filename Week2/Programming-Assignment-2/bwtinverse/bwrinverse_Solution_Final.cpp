#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string InverseBWT(const string& bwt) {
  string text = "";
  // write your code here
 map<pair<char,int>,int>First_column;
 map<pair<char,int>,int>Last_column;

 int A1=0,C1=0,G1=0,T1=0;
 int A2=0,C2=0,G2=0,T2=0;

 for(int i=0; i<bwt.size(); i++) {
    switch(bwt[i]) {
case 'A':
    Last_column.insert(make_pair(make_pair(bwt[i],A1),i));
    A1++;
    break;
case 'C':
    Last_column.insert(make_pair(make_pair(bwt[i],C1),i));
    C1++;
    break;
case 'G':
    Last_column.insert(make_pair(make_pair(bwt[i],G1),i));
    G1++;
    break;
case 'T':
    Last_column.insert(make_pair(make_pair(bwt[i],T1),i));
    T1++;
    break;
default:
    Last_column.insert(make_pair(make_pair(bwt[i],0),i));
    break;
    }
 }
 First_column.insert(make_pair(make_pair('$',0),0));
    if(A1!=0) {
     int i=0;
     while(A1!=0) {
     First_column.insert(make_pair(make_pair('A',i),First_column.size()));
     i++;A1--;
     }
    }

  if(C1!=0) {
     int i=0;
     while(C1!=0) {
     First_column.insert(make_pair(make_pair('C',i),First_column.size()));
     i++;C1--;
     }
    }

  if(G1!=0) {
     int i=0;
     while(G1!=0) {
     First_column.insert(make_pair(make_pair('G',i),First_column.size()));
     i++;G1--;
     }
    }

  if(T1!=0) {
     int i=0;
     while(T1!=0) {
     First_column.insert(make_pair(make_pair('T',i),First_column.size()));
     i++;T1--;
     }
    }


 char second='$';
 int pos=0;
 int index;
 for(int i=0; i<bwt.size(); i++) {
   index=Last_column[make_pair(second,pos)];
   pair<char,int>temp;
   map<pair<char,int>,int>::iterator itr=next(First_column.begin(),index);

   temp=itr->first;
   second=temp.first;
   text.push_back(second);
   pos=temp.second;

 }


  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}

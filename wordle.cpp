#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wdfs(int, int , std::set<std::string>& , std::string , std::multiset<char> , const std::set<std::string>& );

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  std::set<std::string> res;
  std::multiset<char> fl;
  for(int i=0; i<floating.length(); i++){
    fl.insert(floating[i]);
  }
  int freen=0;
  for(int i=0; i<in.length(); i++){
    if(in[i]=='-')
      freen++;
  }
  wdfs(freen, 0, res, in, fl, dict);
  return res;
}

// Define any helper functions here
void wdfs(int freen, int p, std::set<std::string>& res, std::string in, std::multiset<char> floating, const std::set<std::string>& dict){
  if(p>=in.length()){
    if(dict.find(in)!=dict.end() ){
      //std::cout<<in<<endl;
      res.insert(in);
    }
      
    return;
  }

  if(in[p]!='-'){
    wdfs(freen, p+1, res, in, floating, dict);
    return;
  }

  if(floating.size()>0 && freen==floating.size()){
    for(std::multiset<char>::iterator itr=floating.begin(); itr!=floating.end(); itr++){
      std::multiset<char> fl=floating;
      fl.erase(fl.find(*itr));
      in[p]=*itr;
      wdfs(freen-1, p+1, res, in, fl, dict);
    }
  }
  else{
    for(std::multiset<char>::iterator itr=floating.begin(); itr!=floating.end(); itr++){
      std::multiset<char> fl=floating;
      fl.erase(fl.find(*itr));
      in[p]=*itr;
      wdfs(freen-1, p+1, res, in, fl, dict);
    }
    for(char i='a'; i<='z'; i++){
      if(floating.find(i)!=floating.end())
        continue;
      in[p]=i;
      wdfs(freen-1, p+1, res, in, floating, dict);
    }
  }
  
}
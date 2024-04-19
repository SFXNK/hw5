#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool sdfs(int, const AvailabilityMatrix& , const size_t , std::vector<int> , DailySchedule& );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    sched.resize(avail.size());;
    for(int i=0; i<sched.size(); i++){
      sched[i].resize(dailyNeed);
    }
    // Add your code below
    std::vector<int> shiftsleft;
    for(int i=0; i<avail[0].size(); i++){
      shiftsleft.push_back(maxShifts);
    }
    return sdfs(0, avail, dailyNeed, shiftsleft, sched);
}

bool sdfs(
    int task,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    std::vector<int> shiftsleft,
    DailySchedule& sched)
{


  if(task==avail.size()*dailyNeed){
    return true;
  }
  //cout<<"day: "<<task/dailyNeed<<" task: "<<task%dailyNeed<<endl;
  for(int j=0; j<avail[0].size(); j++){
    if(avail[task/dailyNeed][j] && shiftsleft[j]>0 && (task%dailyNeed>0 ? sched[task/dailyNeed][task%dailyNeed-1]!=j : true) ){
      shiftsleft[j]--;
      sched[task/dailyNeed][task%dailyNeed]=j;
      ///cout<<"day: "<<task/dailyNeed<<" task: "<<task%dailyNeed<<" worker: "<<j<<" left: "<<shiftsleft[j]<<endl;
      if(sdfs(task+1, avail, dailyNeed, shiftsleft, sched))
        return true;
      shiftsleft[j]++;
      sched[task/dailyNeed][task%dailyNeed]=0;
    }
  }
  //cout<<"nothing"<<endl;
  return false;
}

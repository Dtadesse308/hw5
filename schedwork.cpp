#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


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
    
    int row = avail.size();
    int col = avail[0].size();


    //create a vect to track num of shifts per worker
    vector<int> workersAvail;

    for (int i = 0; i < col; i++){
        workersAvail.push_back(0);
    }


    sched.resize(row);
    for(int i = 0; i < (int)sched.size() ; i++)
    {
        sched[i].resize(dailyNeed);
    }
    //sched[0].resize(dailyNeed);
    
   // std::cout << "printing: "<<sched[1].size() << " " << dailyNeed << std::endl;

    for (int i = 0; i < row; i++){       //needed per day
        for (int j =0; j < (int)dailyNeed; j++){     //num of days
            sched[i][j] = -1;
        }
    }   
    

    return ( solver(dailyNeed, maxShifts,avail, sched, workersAvail, 0, 0));

    // Add your code below
}

    bool solver (const size_t dailyNeed, const size_t maxShifts, const AvailabilityMatrix& avail,
        DailySchedule& sched, vector<int> shiftsWorked, int row, int col){

            

            if  (row == sched.size()) {
                return true;        //solved
            }

        


    for (int i = 0; i < (int)avail[row].size(); i ++){         //go through all workers
        //check if they are available 
        if ( (avail[row][i]) && (shiftsWorked[i] < maxShifts) ){
            sched [row][col] = i;
            shiftsWorked[i] ++;
            bool temp;
                
            if (col == (int)sched[0].size()-1){
                temp = solver (dailyNeed, maxShifts, avail, sched, shiftsWorked, row+1, 0);
            }
             else {
                temp = solver (dailyNeed, maxShifts, avail, sched, shiftsWorked, row, col+1);
            }

            if (temp){
                return true;        
            }
            else if (!temp) {
                shiftsWorked[i]--;
                sched [row][col] = -1;
            }
        }

        
    }  
          return false;
    
    }

    

   


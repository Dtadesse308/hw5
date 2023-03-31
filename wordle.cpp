#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <queue>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    queue<char>floats;

    for (int i = 0; i < (int)floating.size(); i++){
        floats.push(floating[i]);
        
    }

    


    int index = 0;
    string input = in;

    set<string> words;
    helper(input, floats, dict,index, words);

    return words;


}

void helper(
     std::string& in,
     std::queue<char>& floating,
    const std::set<std::string>& dict,
    int index, set<string>& words)
{
    // Add your code here

    if (in.size() == 0){
        return;
    }



    if (index == (int)in.size()){
            if (dict.find(in) != dict.end()){
                if (floating.size() == 0){
                    words.insert(in);       
                }                       
            }
            return;
        }
    
   if ( (in.size() - index) < floating.size() ){
            return;
        
        }
        

    if ( in[index] == '-'){

        
           

            queue<char> temp = floating;      //temp set so we dont remove from same set from iteration
            
            for (int i = 0; i < (int)floating.size(); i++){         //iterate through floating nums
                in[index] = temp.front();
                temp.pop(); 
                if ( (in.size() - index) < temp.size() ){
                    return;   
                }   
                helper (in,temp,dict,index+1,words);    //recurse            
                temp.push(in[index]);
                in[index] = '-';
                
        }
        
        if ( (in.size() - index - 1) < floating.size() ){
            return;
        }   

        for (char i = 'a'; i <= 'z'; i++){
            in[index] = i;
            helper (in,floating,dict,index+1,words);    //recurse 
            in[index] = '-';
        } 
    
          

    }

     else  {
        helper (in,floating,dict,index+1,words); 
    }

    




}




// Define any helper functions here

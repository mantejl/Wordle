// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle(const std::set<std::string>& wordBank, size_t marker, std::string floatPtr, std::string check, std::set<std::string>& correct);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> final; 

    // recursive call to wordle  
    wordle(dict, 0, floating, in, final);

    // returning final 
    return final;

}

// Define any helper functions here
void wordle(const std::set<std::string>& wordBank, size_t marker, std::string floatPtr, std::string check, std::set<std::string>& correct){
    // dash variables and float variable 
    int dash = 0;
    string carry = floatPtr; 

    // checking if float is empty and if marker is equal to the string we are checking 
    if(floatPtr.empty() && marker == check.size()){ 
        // if the word is in the wordBank then we are going to add it to the our set 
        if(wordBank.find(check) != wordBank.end()){
            correct.insert(check);
        }
        return; 
    }
 
    // checking if the word has a dash 
    if(check[marker] != '-'){
        // recursive call 
        wordle(wordBank,  marker+1, floatPtr, check, correct);
        return;
    }

    // counting the amount of times dashes appear 
    for(int i = 0; i <= (int)check.size()-1; i++){
        if(check[i] == '-'){
            dash = dash + 1;
        }
    }

    // size of the carry 
    int checker = (int)carry.size(); 

    // if number of dashes equals checker
    if(dash == checker){
        for(int i = 0; i <= (checker-1); i++){
            check[marker] = carry[i];
            string tmp = carry;
            tmp.erase(i, 0+1);
            wordle(wordBank, marker + 1, tmp,  check, correct);
        }
    }
    // if number of dashes is greater than checker
    else if(dash > checker){
        // looping through z and a 
        for(char c = 'z'; c >= 'a'; c--){
            if((int)carry.find(c) == -1){
                check[marker] = c;
                wordle(wordBank, marker+1, carry, check, correct);
            }
            else if ((int)carry.find(c)!= -1){
                check[marker] = c;
                string tmp = carry;
                tmp.erase(carry.find(c), 1);
                wordle(wordBank, marker + 1, tmp, check, correct);
            }
        }
    }
}
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
bool wordleHelp ( std::string in, std::string floating,const std::set<std::string>& dict, int ind, std::set<std::string>& words, int dashCounter);


/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in,const std::string& floating,const std::set<std::string>& dict)
{
    int ind =0;
    std::set<std::string> words;

    if (in.size() == 0)
        return words;

    int dashCounter;
    for (int i = ind; i < in.size() ; i++) {
        if (in.at(i) == '-') dashCounter++;
    }

    wordleHelp(in,floating,dict,ind,words, dashCounter);

    return words;

}

// Define any helper functions here
bool wordleHelp (std::string in, std::string floating,const std::set<std::string>& dict, int ind, std::set<std::string>& words, int dashCounter) {

    if (ind > in.size() -1) {
        //and make sure that in has all the original floating values 
        if (dict.find(in) != dict.end() && floating.size() == 0) {
            words.insert(in);
            return true;
        }
        else
            return false;
    }

    if (in.at(ind) != '-'){
        return wordleHelp(in, floating, dict, ind+1, words, dashCounter);
    }

    std::string letters;

    if (dashCounter < floating.size()) {
        return false;
    }
    else if (dashCounter > floating.size()) {
        //in all cases, do we really need to put a-z here?
        //what if overlaps between floating and a-z
        //maybe check if what we have UP TO HERE matches the prefixes of any words
        letters ="abcdefghijklmnopqrstuvwxyz" ;
    }
    else {
        letters = floating;
    }

    bool success = false;

    for (int i = 0; i<letters.size(); i++) {
        char c = letters.at(i);
        in.at(ind) = c;

        string floatingCopy = floating;
        size_t loc = floatingCopy.find(c);
        if (loc != string::npos){
            floatingCopy.erase(loc, 1);
        }
        if (wordleHelp(in, floatingCopy, dict, ind+1,words, dashCounter-1)) success = true;

    }

    return success;

 }
 
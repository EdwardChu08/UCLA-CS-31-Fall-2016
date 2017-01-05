//
//  main.cpp
//  CS 31 Assignment 5
//
//  Created by Edward Chu on 10/11/2016.
//  Copyright (c) 2016 Puffins. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH = 20;

void printArray(char array[][201], int n);
void printArray(char array[][MAX_WORD_LENGTH+1], int n);
void printArray(int array[], int n);
void removeRule(char word1[][MAX_WORD_LENGTH+1],
                char word2[][MAX_WORD_LENGTH+1],
                int distance[],
                int& pos, int& numGoodRules);
void toLowerWord(char word[]);
bool isGoodWord(char word[]);
int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[],
                   int nRules);
int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[],
                          int nRules,
                          const char document[]);


//Prints the array out
void printArray(char array[][201], int n){
    //cerr << array[0];
    for(int i = 0; i < n; i++){
        cerr << " " << array[i];
    }
    cerr << endl;
}


void printArray(char array[][MAX_WORD_LENGTH+1], int n){
    for(int i = 0; i < n; i++){
        cerr << array[i] << endl;
    }
    cerr << endl;
}

void printArray(int array[], int n){
    for(int i = 0; i < n; i++){
        cerr << array[i] << endl;
    }
    cerr << endl;
}

//Remove the rule at pos from the three arrays
void removeRule(char word1[][MAX_WORD_LENGTH+1],
                char word2[][MAX_WORD_LENGTH+1],
                int distance[],
                int& pos, int& numGoodRules){
    
    for(int i = pos+1; i < numGoodRules; i++){
        strcpy(word1[i-1], word1[i]);
        strcpy(word2[i-1], word2[i]);
        distance[i-1] = distance[i];
    }
    
    if(pos != numGoodRules - 1) //Check if rule is the last rule, otherwise infinite loop
        pos--;
    numGoodRules--;
}

//Turns all letters in word to lower
void toLowerWord(char word[]){
    for(int i = 0; word[i] != '\0'; i++){
        word[i] = tolower(word[i]);
    }
}

//Check if the word is a good word: i.e. all letters
bool isGoodWord(char word[]){
    
    if(strlen(word) == 0)
        return false;
    
    for(int i = 0; word[i] != '\0'; i++){
        if(!isalpha(word[i]))
            return false;
    }
    
    return true;
}

/*
    Function 1: normalizeRules
*/

int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[],
                   int nRules){
    
    if(nRules <= 0)
        return 0;
    int numGoodRules = nRules;
    
    //Check for negative distance and if words are empty/has non-letter chars
    for(int i = 0; i < numGoodRules; i++){
        //cerr << i << ": " << distance [i] << " " << (distance[i] < 1) << " " << word1[i] << isGoodWord(word1[i]) << " " << word2[i] << isGoodWord(word2[i]) <<endl;
        if(distance[i] < 1 || !isGoodWord(word1[i]) || !isGoodWord(word2[i])){
            removeRule(word1, word2, distance, i, numGoodRules);
        }
    }
    
    //Sort rules by turning words to lowercase and switching them s.t. word1 < word2 for each rule
    for(int i = 0; i < numGoodRules; i++){
        toLowerWord(word1[i]);
        toLowerWord(word2[i]);
        
        if(strcmp(word1[i], word2[i]) > 0){
            char wordTemp[MAX_WORD_LENGTH+1];
            strcpy(wordTemp, word2[i]);
            strcpy(word2[i], word1[i]);
            strcpy(word1[i], wordTemp);
        }
    }
    
    //For each rule, search whether if there's a rule with the same w1 and w2, and remove the rule with the smaller distance
    for(int i = 0; i < numGoodRules; i++){
        for(int j = i; j < numGoodRules; j++){
            //Don't compare against yourself!
            if(i == j) continue;
            
            if(strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0){
                //Compare distance
                if((distance[i] > distance[j]))
                    removeRule(word1, word2, distance, j, numGoodRules);
                else {
                    removeRule(word1, word2, distance, i, numGoodRules);
                    break;
                }
            }
        }
    }
    
    return numGoodRules;
}

/*
 Function 2: calculateSatisfaction
 */

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[],
                          int nRules,
                          const char document[]){
    
    int satisfaction = 0;
    
    //Check if nRules is negative or zero
    if(nRules <= 0)
        return 0;
    
    //Check if document is empty
    if(strlen(document) == 0)
        return 0;
    
    char documentCopy[201];
    strcpy(documentCopy, document);
    cerr << documentCopy << endl;
    
    //Remove non-letters except spaces and turn letters lowercase
    for(int i = 0; i < strlen(documentCopy); i++){
        //To lowercase
        documentCopy[i] = tolower(documentCopy[i]);
        
        //Remove and shift characters left
        if(!isalpha(documentCopy[i]) && documentCopy[i] != ' '){
            for(int j = i; j < strlen(documentCopy); j++){
                documentCopy[j] = documentCopy[j+1];
            }
            i--;
        }
    }
    
    //Seperate words in document into an array
    char wordsInDocument[100][201];
    char* pch = strtok (documentCopy," ");
    int numWords = 0;
    for(int i = 0; pch != NULL; i++)
    {
        strcpy(wordsInDocument[i], pch);
        pch = strtok (NULL, " ");
        numWords++;
    }
    
    cerr << numWords << endl;
    printArray(wordsInDocument, numWords);
    
    //Search wordsInDocument for words in word1, then search words around it to see if it fits the rule
    for(int i = 0; i < nRules; i++){
        for(int j = 0; j < numWords; j++){
            if(strcmp(wordsInDocument[j], word1[i]) == 0){
                
                //Words in front
                for(int k = j+1; k-j <= distance[i] && k < numWords; k++){
                    if(strcmp(wordsInDocument[k], word2[i]) == 0){
                        satisfaction++;
                        goto nextRule; //I'm so sorry
                    }
                }
                
                //Words in back
                for(int k = j-1; j-k <= distance[i] && k >= -1; k--){
                    if(strcmp(wordsInDocument[k], word2[i]) == 0){
                        satisfaction++;
                        goto nextRule; //I'm so sorry
                    }
                }
            }
        }
        
    nextRule:; //Please forgive me
    }
    
    cerr << "Score: " << satisfaction << endl << "---" <<endl;
    return satisfaction;
}

void testNormalize(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int distance[], int nRules){
    int n = normalizeRules(word1, word2, distance, nRules);
    
    cerr << "Num Rules: " << n << endl;
    
    cerr << "Array1: " << endl;
    printArray(word1, n);
    
    cerr << "Array2: " << endl;
    printArray(word2, n);
    
    cerr << "Array3: " << endl;
    printArray(distance, n);
}

int main() {
    
    const int TEST1_NRULES = 8;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "","deranged", "!", "plot", "have", "mad", "plot", ""
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",  "WRong", "nefarious","mad", "have", "nefaRious", "badrule"
    };
    int test1dist[TEST1_NRULES] = {
        2,-4,2,5,13, 4, 5, 4
    };
    
    
    int n1 = normalizeRules(test1w1, test1w2, test1dist, TEST1_NRULES);
    
    cerr << "Num Rules: " << n1 << endl;
    
    cerr << "Array1: " << endl;
    printArray(test1w1, n1);
    
    cerr << "Array2: " << endl;
    printArray(test1w2, n1);
    
    cerr << "Array3: " << endl;
    printArray(test1dist, n1);
    
    
    const int TEST2_NRULES = 6;
    char test2w1[TEST2_NRULES][MAX_WORD_LENGTH+1] = {
        "alpha", "alpha", "beta", "gamma", "beta", ""
    };
    char test2w2[TEST2_NRULES][MAX_WORD_LENGTH+1] = {
        "beta", "beta", "gamma", "delta", "gamma", ""
    };
    int test2dist[TEST2_NRULES] = {
        2, 3, 5, 4, 2, 2
    };
    
    int n2 = normalizeRules(test2w1, test2w2, test2dist, TEST2_NRULES);
    assert(normalizeRules(test2w1, test2w2, test2dist, -1) == 0);
    cerr << "Num Rules: " << n2 << endl;
    
    cerr << "Array1: " << endl;
    printArray(test2w1, n2);
    
    cerr << "Array2: " << endl;
    printArray(test2w2, n2);
    
    cerr << "Array3: " << endl;
    printArray(test2dist, n2);
    
    const int TEST10_NRULES = 6;
    char test10w1[TEST10_NRULES][MAX_WORD_LENGTH+1] = {
        "alpha", "Alpha", "beta", "alphA", "beta", ""
    };
    char test10w2[TEST10_NRULES][MAX_WORD_LENGTH+1] = {
        "beta", "beta", "gamma", "beta", "gamma", ""
    };
    int test10dist[TEST10_NRULES] = {
        2, 3, -5, 4, 2, -2
    };
    
    testNormalize(test10w1, test10w2, test10dist, TEST10_NRULES);
    
    const int TEST4_NRULES = 2;
    char test4w1[TEST4_NRULES][MAX_WORD_LENGTH+1] = {
        "", ""
    };
    char test4w2[TEST4_NRULES][MAX_WORD_LENGTH+1] = {
        "!!", "lol'"
    };
    int test4dist[TEST4_NRULES] = {
        1, 1
    };
    
    int n4 = normalizeRules(test4w1, test4w2, test4dist, TEST4_NRULES);
    assert(n4 == 0);
    cerr << "Num Rules: " << n4 << endl;
    
    cerr << "Array1: " << endl;
    printArray(test4w1, n4);
    
    cerr << "Array2: " << endl;
    printArray(test4w2, n4);
    
    cerr << "Array3: " << endl;
    printArray(test4dist, n4);
    
    assert(calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES, "@@")==0);
    calculateSatisfaction(test2w1, test2w2, test2dist, TEST2_NRULES, "I'm upset that on Nov. 15th, 2016, my 2 brand-new BMW M760Lis were stolen!!");
    
    
    const int TEST3_NRULES = 4;
    char test3w1[TEST3_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test3w2[TEST3_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test3dist[TEST3_NRULES] = {
        2,           4,          1,           13
    };
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "H!ELP I'm  being oppressed!!!") == 0);
    
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "The mad UCLA scientist unleashed    a deranged robot...") == 2);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "**** 2016 ****") == 0);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "") == 0);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "  That plot: NEFARIOUS!") == 1);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "deranged deranged robot deranged robot robot") == 1);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "That scientist said two mad scientists suffer from deranged-robot fever.") == 0);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 0);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a aa") == 0);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "!!! !!!") == 0);
    assert(calculateSatisfaction(test3w1, test3w2, test3dist, TEST3_NRULES,
                                 "") == 0);
    
    const int TEST11_NRULES = 4;
    char test11w1[TEST11_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test11w2[TEST11_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test11dist[TEST11_NRULES] = {
        2,           4,          1,           13
    };
    assert(calculateSatisfaction(test11w1, test11w2, test11dist, -4,
                                 "The mad UCLA scientist unleashed a deranged evil giant robot.") == 0);
    assert(calculateSatisfaction(test11w1, test11w2, test11dist, -4,
                                 "The mad UCLA scientist unleashed    a deranged robot...") == 0);
    assert(calculateSatisfaction(test11w1, test11w2, test11dist, -4,
                                 "**** 2016 ****") == 0);
    assert(calculateSatisfaction(test11w1, test11w2, test11dist, 0,
                                 "") == 0);
    assert(calculateSatisfaction(test11w1, test11w2, test11dist, -4,
                                 "  That plot: NEFARIOUS!") == 0);
    assert(calculateSatisfaction(test11w1, test11w2, test11dist, 0,
                                 "deranged deranged robot deranged robot robot") == 0);
    
    cerr << "All tests suceeded" << endl;
    
    return 0;
}

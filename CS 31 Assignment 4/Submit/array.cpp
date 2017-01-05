//
//  main.cpp
//  CS 31 Assignment 4
//
//  Created by Edward Chu on 2/11/2016.
//  Copyright (c) 2016 Puffins. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);


int appendToAll(string a[], int n, string value){
    //Negative length
    if(n < 0){
        return -1;
    }
    
    //Append value to each element in array
    for(int i = 0; i < n; i++){
        a[i] += value;
    }
    
    return n;
}


int lookup(const string a[], int n, string target){
    //Negative length
    if(n < 0){
        return -1;
    }
    
    //Search array for target
    for(int i = 0; i < n; i++){
        if(a[i] == target){
            return i;
        }
    }
    
    //Target not found
    return -1;
}


int positionOfMax(const string a[], int n){
    //Negative length
    if(n < 0){
        return -1;
    }
    
    //Search array for max value
    int currMax = 0;
    
    for(int i = 1; i < n; i++){
        if(a[i] > a[currMax]){
            currMax = i;
        }
    }
    
    return currMax;
}


int rotateLeft(string a[], int n, int pos){
    //Negative length or pos out of scope
    if(n < 0 || pos > n){
        return -1;
    }
    
    string temp = a[pos];
    
    //Shift values after pos to the left by one
    for(int i = pos+1; i < n; i++){
        a[i-1] = a[i];
    }
    
    //Value at pos
    a[n-1] = temp;
    
    return pos;
}


int countRuns(const string a[], int n){
    //Negative length
    if(n < 0){
        return -1;
    }
    
    int numConseq = 0;
    
    //Loop through all elements in array
    for(int i = 0; i < n; i++){
        
        //Outside interesting elements
        if(i+1 >= n){
            break;
        }
        
        //Skip conseq elements
        while(a[i] == a[i+1]){
            i++;
            
            //Break if outside interesting elements
            if(i+1 >= n){
                break;
            }
        }
        
        numConseq++;
    }
    

    return numConseq;
}


int flip(string a[], int n){
    //Negative length
    if(n < 0){
        return -1;
    }
    
    //Flip elements
    for(int i = 0; i < n/2; i++){
        string temp = a[n-i-1];
        a[n-i-1] = a[i];
        a[i] = temp;
    }
    
    return n;
}


int differ(const string a1[], int n1, const string a2[], int n2){
    //Negative length
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    
    int currPos = 0;
    
    //Loops until first difference is found
    while(a1[currPos] == a2[currPos]){
        currPos++;
        
        //Check if current pos is outside of scope
        if(currPos == n1 || currPos == n2){
            if(n1 > n2)
                return n2;
            else
                return n1;
            
        }
    }
    
    return currPos;
}


int subsequence(const string a1[], int n1, const string a2[], int n2){
    //Negative length
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    
    //Empty subsequence string
    if(n2 == 0){
        return 0;
    }
    
    int currPos = 0;
    int lengthOfCurrExamine = 0;
    
    for(int i = 0; i < n1; i++){
        currPos = i;
        
        while(a1[i] == a2[lengthOfCurrExamine]){
            i++;
            lengthOfCurrExamine++;
            //Substring found
            if(lengthOfCurrExamine >= n2){
                
                return currPos;
            }
            
            //Outside of scope
            if(i >= n1){
                return -1;
            }
        }
        
        lengthOfCurrExamine = 0;
        
    }
    
    //Substring not found
    return -1;
}


int lookupAny(const string a1[], int n1, const string a2[], int n2){
    //Negative length
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    
    //Loops through each element in a1
    for(int i = 0; i < n1; i++){
        
        //Compare against each element in a2
        for(int j = 0; j < n2; j++){
            if(a1[i] == a2[j])
                return i;
        }
    }
    
    //No elements found
    return -1;
}


int separate(string a[], int n, string separator){
    //Negative length
    if(n < 0){
        return -1;
    }
    
    //Count elements less than seperator and less-than-or-equal-to separator
    int numElementsBeforeGreater = 0;
    int numElementsLessThan = 0;
    for(int i = 0; i < n; i++){
        if(a[i] <= separator)
            numElementsBeforeGreater++;
        if(a[i] < separator)
            numElementsLessThan++;
    }
    
    //Move elements greater than separator to back
    for(int j = 0; j < n; j++){
        if(a[j] > separator && j < numElementsBeforeGreater){
            
            rotateLeft(a, n, j);
            j--;
        }
    }
    
    //For elements equal to seperator
    for(int i = 0; i < numElementsBeforeGreater; i++){
        if(a[i] == separator && i < numElementsLessThan){
            rotateLeft(a, numElementsBeforeGreater, i);
            i--;
        }
    }
    
    //Return
    if(numElementsLessThan != 0){
         return numElementsLessThan;
    } else {
        return n;
    }
   
        
}

int main() {
    // Append to all
    string g[4] = { "jill", "hillary", "gary", "mindy" };
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "jill?" && g[3] == "mindy?");
    
    
    string j[2] = {"jill", "mandy"};
    assert(appendToAll(g, -5, "") == -1);
    assert(appendToAll(g, 4, "") == 4 && j[0] == "jill" && j[1] == "mandy");
    
    //lookup
    string people[6] = { "hillary", "gary", "donald", "jill", "evan", "gary" };
    assert(lookup(people, 3, "evan") == -1);
    assert(lookup(people, 4, "gary") == 1);
    assert(lookup(people, 3, "hillary") == 0);
    assert(lookup(people, 6, "gary") == 1);
    
    //PosOfMAx
    string cand[6] = { "jill", "hillary", "timothy", "tim", "timothy", "tim" };
    assert(positionOfMax(cand, 6) == 2);
    assert(positionOfMax(cand, 0) == 0);
    
    //Rotate left
    string lames[4] = { "jill?", "hillary?", "gary?", "mindy?" };
    assert(rotateLeft(lames, 4, 5) == -1); //Out of scope
    assert(rotateLeft(lames, -4, 1) == -1); //Negative length
    assert(rotateLeft(lames, 4, 1) == 1 && lames[0] == "jill?" && lames[1] == "gary?" && lames[2] == "mindy?" && lames[3] == "hillary?");
    
    string games[4] = { "jill", "hillary", "gary", "mindy" };
    assert(rotateLeft(games, 4, 3) == 3 && games[0] == "jill" && games[1] == "hillary" && games[2] == "gary" && games[3] == "mindy");
    assert(rotateLeft(games, 4, 0) == 0 && games[0] == "hillary" && games[1] == "gary" && games[2] == "mindy" && games[3] == "jill");
    
    
    //countRuns
    string d[9] = {
        "tim", "ajamu", "mike", "mike", "donald", "donald", "donald", "mike", "mike"
    };
    assert(countRuns(d, 9) == 5);
    
    string fames[2] = {"gary", "gary"};
    assert(countRuns(fames, 2) == 1);
    assert(countRuns(fames, 0) == 0);
    
    
    
    //Flip
    string f[3] = { "gary", "donald", "mike" };
    assert(flip(f, 3) == 3);
    assert(f[0] == "mike" && f[2] == "gary" && f[1] == "donald");
    
    assert(flip(f, 0) == 0);
    assert(f[0] == "mike" && f[2] == "gary" && f[1] == "donald");
    
    string k[4] = { "gary", "donald", "mike", "james"};
    assert(flip(k, 4) == 4);
    assert(k[0] == "james" && k[1] == "mike" && k[2] == "donald" && k[3] == "gary");
    
    //Differ
    string folks[6] = { "ajamu", "mike", "", "tim", "mindy", "bill" };
    string group[5] = { "ajamu", "mike", "bill", "", "tim" };
    assert(differ(folks, -6, group, 5) == -1 && differ(folks, 6, group, -5) == -1);
    assert(differ(folks, 6, group, 5) == 2);
    assert(differ(folks, 2, group, 1) == 1);
    
    string pple[7] = { "ajamu", "mike", "", "tim", "mindy", "bill", "lol" };
    assert(differ(folks, 6, pple, 7) == 6);
    assert(differ(folks, 6, pple, 5) == 5);
    
    string ppl[2] = { "Bob", "Jack"};
    assert(differ(folks, 2, ppl, 1) == 0);
    
    //Subsequence
    string names[10] = { "evan", "hillary", "mindy", "jill", "ajamu", "gary" };
    
    string names1[10] = { "hillary", "mindy", "jill" };
    assert(subsequence(names, -6, names1, 3) == -1 && subsequence(names, 6, names1, -3) == -1 );
    assert(subsequence(names, 6, names1, 3) == 1);
    string names2[10] = { "evan", "jill" };
    assert(subsequence(names, 5, names2, 2) == -1);
    string names3[10] = { "ajamu", "gary", "jill"};
    assert(subsequence(names, 5, names3, 3) == -1);
    
    //LookupAny
    string set1[10] = { "bill", "ajamu", "jill", "hillary" };
    assert(lookupAny(names, 6, set1, 4) == 1);
    assert(lookupAny(names, -6, set1, 4) == -1 && lookupAny(names, 6, set1, -4) == -1);
    string set2[10] = { "tim", "donald" };
    assert(lookupAny(names, 6, set2, 2) == -1);
    assert(lookupAny(names, 6, set2, 0) == -1);
    assert(lookupAny(names, 0, set2, 2) == -1);
    
    //Seperate
    string h[7] = { "jill", "hillary", "donald", "tim", "", "evan", "gary" };
    assert(separate(h, 7, "gary") == 3);
    
    
    string cand2[6] = { "donald", "jill", "hillary", "tim", "evan", "bill" };
    assert(separate(cand2, 6, "gary") == 3);
    for(int i = 0; i < 6; i++){
        cerr << cand2[i] << endl;
    }
    
    cerr << endl << "---" << endl;
    
    string cand3[4] = { "gary", "hillary", "jill", "donald" };
    assert(separate(cand3, 4, "hillary") == 2);
    for(int i = 0; i < 4; i++){
        cerr << cand3[i] << endl;
    }
    
    cerr << endl << "---" << endl;
    
    string cand4[4] = { "gary", "hillary", "hillary", "donald" };
    assert(separate(cand4, 4, "hillary") == 2);
    for(int i = 0; i < 4; i++){
        cerr << cand4[i] << endl;
    }
    
    cerr << endl << "---" << endl;
    
    string cand5[4] = { "hillary", "hillary", "hillary", "hillary" };
    assert(separate(cand5, 4, "hillary") == 4);
    for(int i = 0; i < 4; i++){
        cerr << cand5[i] << endl;
    }
    
    cerr << endl << "---" << endl;
    
    string cand6[4] = { "hillary", "hillary", "jill", "hillary" };
    assert(separate(cand6, 4, "hillary") == 4);
    for(int i = 0; i < 4; i++){
        cerr << cand6[i] << endl;
    }
    
    
    cout << "All tests succeeded";
    return 0;
}

//
//  main.cpp
//  poll
//
//  Created by Edward Chu on 22/10/2016.
//  Copyright (c) 2016 Puffins. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//Function prototypes
bool isValidUppercaseStateCode(string stateCode);
bool hasCorrectSyntax (string pollData);
int countVotes(string pollData, char party, int& voteCount);

bool hasCorrectSyntax (string pollData){
    
    //Check if empty string or one letter string
    if(pollData.empty()){
        return true;
    } else if(pollData.length() == 1){
        return false;
    }
    
    //Turn string to uppercase
    for(int i = 0; i < pollData.length(); i++){
        if(islower(pollData[i])){
            pollData[i] = toupper(pollData[i]);
        }
    }
    
    for(int i = 0; i < pollData.length(); i++){
        //Check if state code is valid
        if(!isValidUppercaseStateCode(pollData.substr(i, 2))){
            return false;
        }
        
        else {
            //Scroll past state code
            i += 2;
            
            //check whether if end of string is reached
            if(i >= pollData.length()){
                return false;
            }
            if(!isdigit(pollData[i])){
                return false;
            }
            
            //Scroll past number of electoral votes
            while(isdigit(pollData[i]) && i < pollData.length()){
                i++;
            }
            
            //Check if party is valid letter or end of poll data is reached
            if(i >= pollData.length() || !isalpha(pollData[i])){
                return false;
            }
            
        }
        
    }
    return true;
}

int countVotes(string pollData, char party, int& voteCount){
    
    //Turn string to uppercase
    for(int i = 0; i < pollData.length(); i++){
        if(islower(pollData[i])){
            pollData[i] = toupper(pollData[i]);
        }
    }
    
    //Incorrect syntax
    if(!hasCorrectSyntax(pollData))
        return 1;
    
    //Zero electoral votes for any state
    for(int i = 0; i < pollData.length(); i++){
        i += 2;
        string temp = "";
        while(isdigit(pollData[i])){
            temp += pollData[i];
            i++;
        }
        //State with zero votes
        if(stoi(temp)==0){
            return 2;
        }
        
    }
    
    //Party not letter
    if(!isalpha(party)){
        return 3;
    }
    
    //Initialize voteCount &  Turn party name to upper case
    party = toupper(party);
    voteCount = 0;
    
    //Count votes
    for(int i = 0; i < pollData.length(); i++){
        //Skipping state name
        i += 2;
        
        //Appending vote count to temp, then turning temp into an integer
        string temp;
        while(isdigit(pollData[i])){
            temp += pollData[i];
            i++;
        }
        if(pollData[i] == party){
            voteCount += stoi(temp);
        }
        
    }
    
    return 0;
    
}


bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
    "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
    "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

int main() {
    /*
    string data;
    int voteCount = -99;
    char party;
    
    cout << "Poll data string: ";
    getline(cin, data);
    
    cout << "Party: ";
    cin >> party;
    
    cout << hasCorrectSyntax(data) << endl;
    
    cout << countVotes(data, party, voteCount) << endl;
    
    cout << voteCount;
     */
    
    assert(hasCorrectSyntax("TX38RCA55D")); //Normal correct
    assert(hasCorrectSyntax("VA3RCA55DAL55LUT677777777777D")); //Normal correct
    assert(hasCorrectSyntax("TX38RCA00000000D")); //State with 0 votes, should be true
    assert(hasCorrectSyntax("")); //Empty string, should be true
    
    assert(!hasCorrectSyntax("MX38RCA55D")); //Wrong state code at start, should be false
    assert(!hasCorrectSyntax("TX38RCA55")); //Missing party name at end
    assert(!hasCorrectSyntax("AZRCA55D")); //Missing vote number in middle
    assert(!hasCorrectSyntax("TX38RA55D")); //Missing party name in middle
    assert(!hasCorrectSyntax("TX38%CA55D")); //Symbols for party names, should be false
    assert(!hasCorrectSyntax("TX38RCD55D")); //Wrong state code in middle
    assert(!hasCorrectSyntax("tx38rCA55DMs6rnY29dUT06LL")); //Extra letter on the end
    assert(!hasCorrectSyntax("INVALIDSTRING")); //String with no numbers
    assert(!hasCorrectSyntax("AZD")); //String with no numbers
    assert(!hasCorrectSyntax("AZ")); //String with no numbers
    assert(!hasCorrectSyntax("A")); //One letter string
    assert(!hasCorrectSyntax("AZ38DC27D")); //Missing party name in middle
    assert(!hasCorrectSyntax("AZ38RDC27")); //Missing party name at end
    assert(!hasCorrectSyntax("AZ38R DC27R")); //Space in string
    
    
    int votes;
    votes = -999;
    assert(countVotes("TX38RCA55DMs6rnY29dUT06L", 'R', votes) == 0  &&  votes == 44); //Normal
    votes = -999;
    assert(countVotes("TX38RCA55DMs6rnY29dUT06L", 'L', votes) == 0  &&  votes == 6); //Normal
    votes = -999;
    assert(countVotes("TX38RCA55DMs6rnY29dUT06L", 'd', votes) == 0  &&  votes == 84); //Lowercase party
    votes = -999;
    assert(countVotes("", 'R', votes) == 0 && votes == 0); //Empty string
    
    votes = -999;
    assert(countVotes("TX38RCA55D", '%', votes) == 3  &&  votes == -999); //Party name not letter
    votes = -999;
    assert(countVotes("INVALIDSTRING", 'D', votes) == 1 && votes == -999); //Invalid pollData
    votes = -999;
    assert(countVotes("TX38%CA55D", 'D', votes) == 1 && votes == -999); //Invalid pollData with non-letter
    votes = -999;
    assert(countVotes("TX38RCA55DMs6rnY00dUT09L", 'R', votes) == 2 && votes == -999); //State with 0 votes
    votes = -999;
    assert(countVotes("TX000000000RCA55DMs6rnY10dUT09L", 'R', votes) == 2 && votes == -999); //State with 0 votes at start
    
    
    cout << "All tests succeeded" << endl;
    
    return 0;
}

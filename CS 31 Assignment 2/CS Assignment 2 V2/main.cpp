//
//  main.cpp
//  CS Assignment 2 V2
//
//  Created by Edward Chu on 7/10/2016.
//  Copyright (c) 2016 Puffins. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//Function that returns license fee with expected revenue and country as input
double licenseFee(double expectedRevenue, string country){
    const double first20milRate = 0.181;
    const double turkeyUaeRate = 0.217;
    const double normalNext30milRate = 0.203;
    const double after50milRate = 0.230;
    
    double fee = 0;
    
    //First 20 mil
    if(expectedRevenue<=20){
        fee = expectedRevenue * first20milRate;
        return fee;
    } else {
        expectedRevenue = expectedRevenue - 20;
        fee += 20 * first20milRate;
    }
    
    //Next 30 mil
    if(expectedRevenue<=30 && (country == "Turkey" || country == "UAE")){
        fee += expectedRevenue * turkeyUaeRate;
        return fee;
        
    } else if(expectedRevenue<=30){
        fee += expectedRevenue * normalNext30milRate;
        return fee;
        
    } else if(country == "Turkey" || country == "UAE"){
        expectedRevenue = expectedRevenue - 30;
        fee += 30 * turkeyUaeRate;
    } else {
        expectedRevenue = expectedRevenue - 30;
        fee += 30 * normalNext30milRate;
    }
    
    //Over 50 mil
    fee += expectedRevenue*after50milRate;
    return fee;
}



int main() {
    //Enter identification
    string identification;
    cout << "Identification: ";
    getline(cin, identification);
    
   
    
    
    //Enter Revenue
    double revenue;
    cout << "Expected revenue (in millions): ";
    cin >> revenue;
    cin.ignore(10000, '\n');
    
    
    //Enter Country
    string country;
    cout << "Country: ";
    getline(cin, country);
    
    
    
    
    //Output
    
    cout << "---" << endl;
    
    
    //Errors output
    if(identification.empty()){
        cout << "You must enter a property identification." << endl;
        return 1;
    }
    
    if(revenue < 0){
        cout << "The expected revenue must be nonnegative." << endl;
        return 1;
    }
    
    if(country.empty()){
        cout << "You must enter a country." << endl;
        return 1;
    }
    
    //Correct Output
    cout.setf(ios::fixed);
    cout.precision(3);
    
    cout << "The license fee for " << identification << " is $" << licenseFee(revenue, country) << " million." << endl;
    
    
    return 0;
}
// File: HouseFunc
// Created by Hugo Valle on 11/22/2017.
// Copyright (c) 2017 WSU
//

#include <iostream>
#include <vector>
#include <map>
#include "HouseFunc.h"
#include "HousePrice.h"
#include "csv.h" // library to read csv files
#include <algorithm>

using namespace std;

/*!
 * Read CSV Mock Data. Parses each record in the file to
 * an object of HousePrice house. Then, populate a vector
 * of HousePrice objects with all the records.
 * It uses special library to parse CSV file "csv.h"
 * @param fileIn File name <string>
 * @param hp Reference to Vector of HousePrice Objects
 */
void readCSV(const string fileIn,vector<HousePrice>& hp)
{
    io::CSVReader<7> in(fileIn);
    in.read_header(io::ignore_extra_column, "id","number","street","city","state","postalCode","price");
    int id; int number; string street; string city; string state; int postalCode; double price;

    while(in.read_row(id, number, street, city, state, postalCode, price))
    {
        HousePrice house(id, number, street, city, state, postalCode, price);
        hp.push_back(house);

        cout<<"Id: "<<id<<" ";
        cout<<"Number: "<<number<<" ";
        cout<<"Street: "<<street<<" ";
        cout<<"City: "<<city<<" ";
        cout<<"State: "<<state<<" ";
        cout<<"PostalCode: "<<postalCode<<" ";
        cout<<"Price: "<<price<<" "<<endl;
    }
}

/*!
 * Sort the Vector of HousePrice Objects by price. Display the most affordable
 * and the most expensive house from the vector.
 * @param hp Reference to vector<HousePrice>
 */
void houseMarketValues(vector<HousePrice> &hp)
{
    // Sort by Price
    std::sort(hp.begin(), hp.end(), [](const HousePrice& lhs, const HousePrice& rhs)
    { return lhs.getPrice() < rhs.getPrice(); });

    HousePrice cheapest = hp.at(0);
    int lastIndex = hp.size() - 1;
    HousePrice priciest = hp.at(lastIndex);

    cout<<"Most affordable home: "<< cheapest<<endl;
    cout<<"Most expensive home: "<<priciest<<endl;
}

/*!
 * Sort the Vector of HousePrice Objects by state. Display the
 * number of houses per state.
 * It uses a map to count instances per state.
 * @param hp Reference to vector<HousePrice>
 */
void houseMarketPerState(vector<HousePrice> &hp)
{
    map<string, int> states;

    for(auto ip = hp.begin(); ip != hp.end(); ip++)
    {
        string state = ip->getState();

        if(states.count(state) <= 0){
            states[state] = 1;
        }
        else {
            int currentCount = states[state];
            states[state] = currentCount + 1;
        }
    }

    int i =0;
    // Sort by State
    for(auto ip = states.begin(); ip != states.end(); ip++)
    {
        if(i % 10  == 0)
        {
            cout << endl;
        }
        i++;
        string state = ip->first;
        cout<<" "<<state<<" "<< states[state];

    }

}
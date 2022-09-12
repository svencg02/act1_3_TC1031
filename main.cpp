// =================================================================
//
// File: main.cpp
// Author: Sergio Garnica González - A01704025, Sven Chávez García A01704151
// Date:10/09/2022
//
// =================================================================
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <time.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include "insertion.h"

int main(int argc, char *argv[])
{
  ifstream inputFile;
  ofstream outputFile;

  if (argc != 3)
  {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  outputFile.open(argv[2]);

  if (!inputFile.is_open())
  {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  int n;
  std::string idSearch, date, hour, port, id;

  // Ship struct
  struct shipStruct
  {
    int year;
    int month;
    int day;
    std::string dateString;
    std::string hour;
    std::string port;
    std::string id;
  };
  // Ships vector
  vector<shipStruct> ships;

  // Read file
  inputFile >> n;
  inputFile >> idSearch;

  for (int i = 0; i < n; i++)
  {
    // Read file
    inputFile >> date >> hour >> port >> id;

    // Parse date
    std::string day = date.substr(0, date.find("-"));
    std::string month = date.substr(3, date.find("-"));
    std::string year = date.substr(6);

    // Find ships with idSearch in id
    std::size_t found = id.rfind(idSearch);
    if (found != string::npos)
    {
      // Add ship to ships vector
      ships.push_back({stoi(year), stoi(month), stoi(day), date, hour, port, id});
    }
  }

  // Sort ships vector by day and then my month with insertion sort algorithm
  insertionSortDay(ships);
  insertionSortMonth(ships);

  // Write output file
  for (int i = 0; i < ships.size(); i++)
  {
    outputFile << ships[i].dateString << " " << ships[i].hour << " " << ships[i].port << " " << ships[i].id << "\n";
  }

  inputFile.close();
  outputFile.close();

  return 0;
}
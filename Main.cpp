#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <vector>
#include "DLL.h"
#include "MinHeap.h"


  using namespace std;

  // GLOBAL VARIABLES
  vector<vector<double>> table;           //will hold file we read in
  int start;                           //where the gremlin will start
  int finish;                          //where the twinkie is
  DLL<int> nonbricks;                     //will hold the available locations
  MinHeap<int> options;                   //will hold all the options
  int *dist;      //will hold distance to each spot
  int *parent;    //will hold the parent of each spot



  void FileInput(){
    // get table from text file
    cout << "Please enter file name: " << endl;
    string file;
    cin >> file;

    ifstream inFile;
    inFile.open(file);

    string line;

    while(getline(inFile,line)){
      istringstream ss(line);
      vector<double> columns;

      string token;
      while(getline(ss,token,',')){
        double v = atof(token.c_str());
        columns.push_back(v);
      }
      table.push_back(columns);

    }

    // get starting and ending locations
    cout << "Please enter start location: " << endl;
    cin >> start;

    cout << "Please enter end location: " << endl;
    cin >> finish;
  }

  void FindNonbricks(vector<vector<double>> table){

    for(unsigned i = 0; i<table.size(); i++){       //for the columns
      for (unsigned j = 0; j<table.size(); j++){    //for the rows
        if (table[j][i] > 0){                         //if there is a possible move in that column
          nonbricks.addLast(i);                     //add it to nonbricks
          j = table.size();                         //pop out of that column
        }//end if
      }//end rows
    }//end columns
  }//end FindBricks


  void InitializeStructures(){
      // initialize distance and parent arrays to hold the correct number of locations
      dist = new int[table.size()];
      parent = new int[table.size()];

      options.insert(start,0);  // place the starting location as the first value in the heap
      dist[start-1] = 0;        // set the distance of the start value to 0

      // loop through every location
      for (unsigned i = 0; i < table.size(); i++){

          // if the current location is not a brick, and not the starting location...
          if (nonbricks.contains(i) && i != start-1u){
              dist[i] = INT_MAX;            // initialize the distance to 'i' as INFINITY
              parent[i] = 0;                // initialize the parent of 'i' as zero
              options.insert(i+1, INT_MAX);   // insert 'i' into the MinHeap
          }
      }
  }


  // Main method
  int main(){

    // Read in the file and determine start/finish locations
    FileInput();

    // find accessible locations
    FindNonbricks(table);

    // initialize MinHeap, Distance array, and Parent array
    InitializeStructures();

    cout << options << endl;

    return EXIT_SUCCESS;

  }

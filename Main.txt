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
#include "Stack.h"

/**
* Authors: Charley Burtwistle, Chase Stone, Brian Spencer
* Date: December 11, 2017
* Project: Final Project (Gremlins and twinkies)
*
*
*The output of your program should be a list of the hexes Spike must traverse,
*in order, to get to the Twinkies in the most efficient manner.
*If there is more than one route with equally minimal cost,
*simply output one. If there is no path to the Twinkies at all,
*output an empty list.
*
*
*Notes:
* - Had to add a DecreaseKey Method to our MinHeap.h file in order to
*   change the priority of an element in the MinHeap.
* - Developed algorithm based off "Dijsktra's shortest path algorithm"
*       -Specifically from www.geeksfromgeeks.org/greedy-algorithms-set-6-dijkstra-shortest-path-algorithm/
*
*
*/



  using namespace std;

  // GLOBAL VARIABLES
  vector<vector<double>> table;           //will hold file we read in
  int start;                              //where the gremlin will start
  int finish;                             //where the twinkie is
  MinHeap<int> options;                   //will hold all the options
  int *dist;                              //will hold distance to each spot
  int *parent;                            //will hold the parent of each spot
  vector<int> finalPath;                  //will be used to print out final path
  DLL<int> nonbricks;                     //will be used to find available blocks


  //gets the table from the text file
  void FileInput(){
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

  //will find avaiable blocks
  void FindNonbricks(vector<vector<double>> table){

      for(unsigned i = 0; i<table.size(); i++){       //for the columns
        for (unsigned j = 0; j<table.size(); j++){    //for the rows
          if (table[j][i] > 0){                       //if there is a possible move in that column
            nonbricks.addLast(i);                     //add it to nonbricks
            j = table.size();                         //pop out of that column
          }//end if
        }//end rows
      }//end columns
    }//end FindBricks

  //will fill parent and distance arrays and create/fill MinHeap
  void InitializeStructures(){

      // initialize distance and parent arrays to hold the correct number of locations
      dist = new int[table.size()];
      parent = new int[table.size()];

      dist[start-1] = 0;        // set the distance of the start value to 0

      // loop through every location
      for (unsigned i = 0; i < table.size(); i++){
        if(i != start-1){                 //if i is not the starting location
          dist[i] = INT_MAX;              // initialize the distance to 'i' as INFINITY
          parent[i] = 0;                  // initialize the parent of 'i' as zero
        }
        // if the current location is not a brick
        if (nonbricks.contains(i)){
          options.insert(i, dist[i]);   // insert 'i' into the MinHeap
          }
      }
  }

  //find minimum path
  void FindPath(){
    // loop while we still have options in our MinHeap
    while(!options.isEmpty()){
      int minimum = options.removeMin();  // get the min value from options

      for(int i = 0; i < table.size(); i++){
        if(nonbricks.contains(i)){

          // check if we need to update distance in the distance array
          int check = dist[minimum] + table[minimum][i];

          // if its a possible move and a distance can be updated
          if(table[minimum][i] >= 0 && check < dist[i]){
            dist[i] = check;      //update distance
            parent[i] = minimum;  //update parent
            options.DecreaseKey(i, check);  //place new optimal move in front
          }//end if
        }//end if

      }//end for
      //once we reach the goal, break out of the while
      if(minimum==finish-1){
        break;
      }
    }//end while

  }//end FindPath

//method to print path
void PrintPath(){

  //set spots to goal
  int spots = finish-1;

  //while spots isnt at the start
  while(spots != start-1) {
      //add it to the path
      finalPath.push_back(spots+1);
      //get next spot
      spots = parent[spots];
  }

  //add final spot to the path
  finalPath.push_back(spots+1);

  cout<<"[ ";
  //print out the vector in reverse order
  for(int i = finalPath.size()-1 ; i>=0; i--){
    cout<<finalPath[i] << " ";
  }
  cout<<"]";
}
  // Main method
  int main(){

    // Read in the file and determine start/finish locations
    FileInput();

    // find accessible locations
    FindNonbricks(table);

    // initialize MinHeap, Distance array, and Parent array
    InitializeStructures();

    // find the shortest path to the end location
    FindPath();

    //print out the path
    PrintPath();



    return EXIT_SUCCESS;

  }

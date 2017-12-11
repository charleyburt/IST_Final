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
#include "Stack.h"
#include "MinHeap.h"

  using namespace std;

  vector<vector<double>> rows;
  vector<DLL<double>> paths;



  void FindShortestPath(double spot_curr, double spot_end, DLL<double> pathList, DLL<double>deadEnds){
    vector<double>* options = new vector<double>();
    if (spot_curr == spot_end){ //if you reach the destination
        pathList.addLast(spot_curr);
        paths.push_back(pathList); //add the DLL pathList to the vector paths
      }//end if


    else if (spot_curr != spot_end){

        // find movement options
        for (int i = 0 ; i < rows[spot_curr].size() ; i++){
            if (rows[spot_curr][i] > 0 && pathList.contains(i) == false && deadEnds.contains(i) == false ){
                options->push_back(i);
              }//end if
        }//end for
        // if there's only one place to go

        // if (find(options->begin(),options->end(),spot_end) != options->end()){
        //   pathList.addLast(spot_curr);
        //   spot_curr = spot_end;
        //   FindShortestPath(spot_curr, spot_end, pathList, deadEnds);   // find the shortest path starting at the new current spot
        //
        // }

        if (options->size() == 1){
            pathList.addLast(spot_curr);                                 // add current spot to pathList
            spot_curr = options->back();                                  // set new current spot
            FindShortestPath(spot_curr, spot_end, pathList, deadEnds);   // find the shortest path starting at the new current spot
          }//end if

        // if there's multiple options
        else if (options->size() > 1){
            pathList.addLast(spot_curr);                     // add current spot to pathList
            for (int i : *options){
                FindShortestPath(i, spot_end, pathList, deadEnds);
            }
            //
            // // choose next spot based on min cost of possible spots and numerical order they appear
            // int min = rows[spot_curr][options->front()];
            // for (int i : options){
            //     if (rows[spot_curr][i] < min){
            //         min = rows[spot_curr][i];
            //     }//end if
            // }//end for
            //
            // // choose the first option that has the minimum cost
            // int idx = 0;
            // while (rows[spot_curr][options->at(idx)] != min){
            //     idx++;
            //   }


          }//end else if
        // else there are zero options
          else if (options->size() == 0){
            deadEnds.addLast(spot_curr);         // current spot has no options, so add it to deadEnds
            spot_curr = pathList.removeLast();   // change current spot to the previous location
            FindShortestPath(spot_curr, spot_end, pathList, deadEnds);
          }//end else if

  }//end else if

  delete options;

  }//end method

void Test(double spot_curr){
    // for(const auto& v : rows){
    //   for (auto value : v){
    //     cout << value << ",";
    //   }
    //   cout<<endl;
    // }


    // create new vector: "options"
    vector<double> options;

    // find movement options
    for (double option : rows[spot_curr]){
                  cout<<option<<endl;
    }//end for
}

int finalShortest(DLL<double> pathList){
  int sum = 0;
  for(int i = 0; i < pathList.size() -1 ; i++){
    int x = pathList.get(i);
    int y = pathList.get(i+1);
    sum += rows[x][y];
  }
  return sum;
}

int main()
{


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
      rows.push_back(columns);

  }



  cout << "Please enter start location: " << endl;
  double start;
  cin >> start;

  cout << "Please enter end location: " << endl;
  double end;
  cin >> end;


  DLL<double> pathList;
  DLL<double> deadEnds;



  FindShortestPath(start-1,end-1,pathList,deadEnds);


  for(const auto& v : paths){
    finalShortest(v);
    for (auto value : v){
      cout << value + 1  << ",";
    }
    cout<<endl;
  }

  return EXIT_SUCCESS;


  }

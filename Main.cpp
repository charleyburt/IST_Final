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

void FindShortestPath(double spot_curr, double spot_end, DLL<double> pathList, DLL<double>deadEnds){
  std::cout<<"working"<<std::endl;
}


int main()
{
  using namespace std;

  cout << "Please enter file name: " << endl;
  string file;
  cin >> file;

  ifstream inFile;
  inFile.open(file);


  vector<vector<double>> rows;
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

//outputs the entire file
  // for(const auto& v : rows){
  //   for (auto value : v){
  //     cout << value << ",";
  //   }
  //   cout<<endl;
  // }

  cout << "Please enter start location: " << endl;
  double start;
  cin >> start;

  cout << "Please enter end location: " << endl;
  double end;
  cin >> end;

  vector<DLL<double>> paths;
  DLL<double> pathList;
  DLL<double> deadEnds;

  FindShortestPath(start,end,pathList,deadEnds);


  }

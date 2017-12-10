#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <vector>
int main()
{
  using namespace std;


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

  for(const auto& v : rows){
    for (auto value : v){
      cout << value << ",";
    }
    cout<<endl;
  }

}

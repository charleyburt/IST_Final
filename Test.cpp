#include "MinHeap.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <stdlib.h>
#include "Stack.h"


int main() {
    using namespace std;

    // Choose hex map to use
    string file = "20x20.txt";

    // Find the number of tiles in the game
    int tiles = 0;
    ifstream checkTilesFile(file);
    string junk;
    while(getline(checkTilesFile, junk)) {
        tiles++;
    }

    // Notify user of the board size and ask for starting ending infromation
    cout << "There are " << tiles << " tiles." << endl;
    cout << "Choose between 1 and " << tiles << " for start and finish" << endl;

    // Ask user to enter where the gremlin starts
    cout << "Enter starting tile: ";
    int start;
    cin >> start;

    // Ask user to enter where the twinkies are located
    cout << "Enter ending tile: ";
    int finish;
    cin >> finish;

    // Create a 2 dimensional array to house the hex map
    double gameTiles [tiles][tiles];

    // Create file stream to read in values from selected text file
    ifstream inFile(file);

    //
    int k = 0;
    double num = 0.0;
    int times = 0;
    string token;
    for(int i = 0; i < tiles*tiles; i++) {

        inFile >> token;

        size_t pos = token.find(",");
        string sub = token.substr(0,pos);

        num = stod (sub);

        gameTiles[k][times%tiles] = num;

        times++;
        if(times%tiles == 0) {
            k++;
        }
    }

    // Close file stream
    inFile.close();

//     double gameTiles[tiles][tiles] = {{0.0, -1.0, -1.0, -1.0, 4.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
// {1.0, 0.0, 1.0, -1.0, 4.0, 1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
// {-1.0, -1.0, 0.0, 1.0, -1.0, 1.0, 4.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
// {-1.0, -1.0, 1.0, 0.0, -1.0, -1.0, 4.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
// {1.0, -1.0, -1.0, -1.0, 0.0, 1.0, -1.0, 2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 },
// {-1.0, -1.0, 1.0, -1.0, 4.0, 0.0, 4.0, -1.0, -1.0, 2.0, -1.0, -1.0, -1.0, -1.0 },
// {-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 0.0, -1.0, -1.0, 2.0, 4.0, -1.0, -1.0, -1.0 },
// {-1.0, -1.0, -1.0, -1.0, 4.0, -1.0, -1.0, 0.0, -1.0, -1.0, -1.0, 2.0, -1.0, -1.0},
// {-1.0, -1.0, -1.0, -1.0, 4.0, 1.0, -1.0, 2.0, 0.0, 2.0, -1.0, 2.0, 1.0, -1.0},
// {-1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 4.0, -1.0, -1.0, 0.0, 4.0, -1.0, 1.0, 1.0},
// {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 4.0, -1.0, -1.0, 2.0, 0.0, -1.0, -1.0, 1.0},
// {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.0, -1.0, -1.0, -1.0, 0.0, 1.0, -1.0},
// {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.0, -1.0, 2.0, 0.0, 1.0 },
// {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 2.0, 4.0, -1.0, 1.0, 0.0}};

    // Create boolean array to track brick tiles of hex map
    bool *isBrick = new bool[tiles];

    // Iterate over isBrick array ensuring all values are true
    for(int i = 0; i < tiles; i++) {
        isBrick[i] = true;
    }

    // Iterate over isBrick array checking associated tiles in hex map, if they are
    // not brick set the value in isBrick array to false
    for(int i = 0; i < tiles; i++) {
        for(int j = 0; j < tiles; j++) {
            if(gameTiles[j][i] != -1 && i != j) {
                isBrick[i] = false;
                j = tiles;
            }
        }
    }

    int *dist = new int[tiles];

    int *prev = new int[tiles];

    // dist[source] <- 0
    dist[start-1] = 0;

    // create vertex set Q
    MinHeap<int> Q;

//########################################################################

    // for each vertex v in Graph:
    //       if v ≠ source
    //          dist[v] ← INFINITY       // Unknown distance from source to v
    //          prev[v] ← UNDEFINED      // Predecessor of v

    //      Q.add_with_priority(v, dist[v])

    for(int i = 0; i < tiles; i++) {
        if(i != start-1) {
            dist[i] = INT_MAX;
            prev[i] = 0;
        }
        if(!isBrick[i]) {
            Q.insert(i, dist[i]);
        }

    }

    cout << Q << endl;
    cout << INT_MAX + 1 <<endl;

//########################################################################

    // while Q is not empty:                // The main loop
    //      u ← Q.extract_min()             // Remove and return best vertex
    //      for each neighbor v of u:       // only v that is still in Q
    //          alt ← dist[u] + length(u, v)
    //          if alt < dist[v]
    //              dist[v] ← alt
    //              prev[v] ← u
    //              Q.decrease_priority(v, alt)

    while(!Q.isEmpty()) {
        int u = Q.removeMin();

        for(int i = 0; i < tiles; i++) {
            if(!isBrick[i]) {
                int alt = dist[u] + gameTiles[u][i];
                if(gameTiles[u][i] >= 0 && alt < dist[i]) {
                    dist[i] = alt;
                    prev[i] = u;
                    Q.decrease_priority(i, alt);
                }
            }
        }
        if(u == finish-1) {
            break;
        }
    }

//########################################################################
    // from here on is printing off the shortest path
    int createPathStack = finish-1;

    Stack<int> stack;

    while(createPathStack != start-1) {
        stack.push(createPathStack+1);
        createPathStack = prev[createPathStack];
    }

    stack.push(createPathStack+1);

    cout << "[";

    while(stack.size() > 0) {
        if(stack.size() > 1) {
            cout << stack.pop() << ", ";
        } else {
            cout << stack.pop();
        }
    }

    cout << "]" << endl;

}

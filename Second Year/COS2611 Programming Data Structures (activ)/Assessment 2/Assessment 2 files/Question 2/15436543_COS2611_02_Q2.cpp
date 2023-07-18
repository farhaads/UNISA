#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

//Farhaad Sallie
//Student Number: 15436543
//Search prompt: "C++ code that will implement Prim’s algorithm using ADT with a timecomplexity of O(n^2)"

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjacencyList.resize(numVertices);
    }

    void addEdge(int src, int dest, int weight) {
        adjacencyList[src].push_back(make_pair(dest, weight));
        adjacencyList[dest].push_back(make_pair(src, weight));
    }

    

    vector<pair<int, int>> primMST() {
        vector<pair<int, int>> mst;  // Minimum Spanning Tree
        vector<bool> visited(numVertices, false);
        vector<int> key(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);

        // Create a priority queue (min-heap)
        // to store vertices along with their key values
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Start with the first vertex
        int startVertex = 0;
        pq.push(make_pair(0, startVertex));
        key[startVertex] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            visited[u] = true;

            // Explore all adjacent vertices of u
            for (auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push(make_pair(key[v], v));
                }
            }
        }

        // Construct the MST
        for (int i = 1; i < numVertices; i++) {
            mst.push_back(make_pair(parent[i], i));
        }

        return mst;
    }

    


    
};

int main() {
    //I have added the fstream library import aswell as integrating the readFromFile method
    // from Question one to read in the datatest2.txt file into the vectors for the algorithm 
    fstream myFile("C:\\data\\datatest2.txt", ios_base::in);
    int numVertices, numEdges;
    myFile >> numVertices >> numEdges;

    Graph graph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int vertex, edge, weight;
        myFile >> vertex >> edge >> weight;
        graph.addEdge(vertex, edge, weight);
    }
    myFile.close();

    vector<pair<int, int>> mst = graph.primMST();

    cout << "Minimum Spanning Tree edges:" << endl;
    for (auto& edge : mst) {
        cout << edge.first << " - " << edge.second << endl;
    }

    return 0;
}






#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <tuple> 
using namespace std;



// Class to represent the Metro system
class MetroApp {
    int V; // Number of stations
    vector<tuple<int, int, string>> *adj; // Adjacency list (station, distance, line color)

public:
    MetroApp(int V) {
        this->V = V;
        adj = new vector<tuple<int, int, string>>[V];
    }

    // Function to add an edge between stations with a distance and line color
    void addEdge(int u, int v, int w, string color) {
        adj[u].push_back(make_tuple(v, w, color));
        adj[v].push_back(make_tuple(u, w, color));
    }

    // Function to find shortest path using Dijkstra's algorithm
    void dijkstra(int src, int dest) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1); // To store the parent of each node in the shortest path
        vector<string> lineColor(V); // To store the line color of each station
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Traverse adjacent stations
            for (auto edge : adj[u]) {
                int v = get<0>(edge);
                int weight = get<1>(edge);
                string color = get<2>(edge);

                // Relax the edge
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                    parent[v] = u; // Update parent
                    lineColor[v] = color; // Store the color of the line used
                }
            }
        }

        // Print shortest path with distances and line changes
        if (dist[dest] == INT_MAX) {
            cout << "No path found!" << endl;
        } else {
            cout << "Shortest Distance: " << dist[dest] << endl;
            cout << "Path with distances and line changes: "<<endl<<endl;
            float a=0;
            float b=0;
            
            cout<<"Start your journey from ";
            printPathWithLineChange(parent, lineColor, src, dest, dist,a,b);
            cout << endl;
            float c=dist[dest]+a*0.5+(b-1)*5;
            cout<<"Total Time = "<<c;//including halt time and changing time
            
            cout << endl;
        }
    }

    // Function to print the path along with distances and handle line changes
    void printPathWithLineChange(vector<int> &parent, vector<string> &lineColor, int src, int j, vector<int> &dist, float &a, float &b){
        if (j == src) {
            cout << j;
            return;
        }
        printPathWithLineChange(parent, lineColor, src, parent[j], dist,a,b); // Recursive call to print the path

        // Check for line change, but don't print change for the source station
        a++;
        if (lineColor[j] != lineColor[parent[j]]) {
            b++;
            a--;
            cout << "\nGo to " << lineColor[j] << " line ";
        }

        cout << " -> (" << dist[j] - dist[parent[j]] << "km) -> " << j << " (" << lineColor[j] << ")";
    }
};

int main() {
    int V = 6; // Number of metro stations
    MetroApp metro(V);

    // Example metro connections with colors
    metro.addEdge(0, 1, 4, "Red");
    metro.addEdge(0, 2, 2, "Blue");
    metro.addEdge(1, 2, 1, "Red");
    metro.addEdge(1, 3, 5, "Green");
    metro.addEdge(2, 3, 8, "Blue");
    metro.addEdge(2, 4, 10, "Blue");
    metro.addEdge(3, 4, 2, "Green");

    int source, destination;
    cout << "Enter source station: ";
    cin >> source;
    cout << "Enter destination station: ";
    cin >> destination;

    metro.dijkstra(source, destination);

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;
    vector<string> landmarks;
    int numLandmarks;

public:
    Graph(int n) {
        numLandmarks = n;
        adjMatrix.resize(n, vector<int>(n, 0));
        adjList.resize(n);
        landmarks.resize(n);
    }

    void inputLandmarks() {
        cout << "Enter names of " << numLandmarks << " landmarks:\n";
        for (int i = 0; i < numLandmarks; i++) {
            cout << "Landmark " << i << ": ";
            cin >> landmarks[i];
        }
    }

    void addConnections() {
        int edges;
        cout << "Enter number of connections (edges): ";
        cin >> edges;

        cout << "Enter connections between landmarks (use indices 0 to " << numLandmarks - 1 << "):\n";
        for (int i = 0; i < edges; i++) {
            int u, v;
            cout << "Connection " << i + 1 << " (landmark1 landmark2): ";
            cin >> u >> v;
            if (u >= 0 && u < numLandmarks && v >= 0 && v < numLandmarks) {
                adjMatrix[u][v] = adjMatrix[v][u] = 1;
                adjList[u].push_back(v);
                adjList[v].push_back(u);
            } else {
                cout << "Invalid landmark index. Please enter values between 0 and " << numLandmarks - 1 << ".\n";
                i--; // Retry this edge
            }
        }
    }

    void displayAdjMatrix() {
        cout << "\nAdjacency Matrix:\n\t";
        for (const auto& lm : landmarks)
            cout << lm << "\t";
        cout << "\n";
        for (int i = 0; i < numLandmarks; i++) {
            cout << landmarks[i] << "\t";
            for (int j = 0; j < numLandmarks; j++) {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    void DFSUtil(int node, vector<bool>& visited) {
        cout << landmarks[node] << " ";
        visited[node] = true;
        for (int i = 0; i < numLandmarks; i++) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS(int start) {
        if (start < 0 || start >= numLandmarks) {
            cout << "Invalid starting index for DFS.\n";
            return;
        }

        cout << "\nDFS Traversal: ";
        vector<bool> visited(numLandmarks, false);
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        if (start < 0 || start >= numLandmarks) {
            cout << "Invalid starting index for BFS.\n";
            return;
        }

        cout << "\nBFS Traversal: ";
        vector<bool> visited(numLandmarks, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << landmarks[node] << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int n, start;
    cout << "Enter number of landmarks: ";
    cin >> n;

    if (n <= 0) {
        cout << "Number of landmarks must be greater than 0.\n";
        return 1;
    }

    Graph g(n);
    g.inputLandmarks();
    g.addConnections();
    g.displayAdjMatrix();

    cout << "Enter starting landmark index for DFS and BFS: ";
    cin >> start;

    g.DFS(start);
    g.BFS(start);

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>  // For std::find
#include <random>      // For random number generation
#include <cstdlib>     // For rand()

using namespace std;

class Node {
public:
    int data;
    Node(int value) : data(value) {}
};

class Graph {
private:
    vector<Node> nodes;
    vector<vector<int>> adjacencyList;

public:
    Graph() {}

    // Function to add a new node to the graph
    void addNode(int value) {
        Node newNode(value);
        nodes.push_back(newNode);
        adjacencyList.push_back(vector<int>());
    }

    // Function to add an undirected edge between two nodes
    void addEdge(int source, int destination) {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }

    // Function to remove an undirected edge between two nodes
    void deleteEdge(int source, int destination) {
        auto& sourceNeighbors = adjacencyList[source];
        sourceNeighbors.erase(remove(sourceNeighbors.begin(), sourceNeighbors.end(), destination), sourceNeighbors.end());

        auto& destinationNeighbors = adjacencyList[destination];
        destinationNeighbors.erase(remove(destinationNeighbors.begin(), destinationNeighbors.end(), source), destinationNeighbors.end());
    }

    // Function to delete a node and its edges
    void deleteNode(int nodeIndex) {
        if (isEmpty() || nodeIndex < 0 || nodeIndex >= nodes.size()) {
            cout << "Invalid node index. Cannot delete node." << endl;
            return;
        }

        for (int neighbor : getAdjacentNodes(nodeIndex)) {
            auto& neighbors = adjacencyList[neighbor];
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), nodeIndex), neighbors.end());
        }

        nodes.erase(nodes.begin() + nodeIndex);
        adjacencyList.erase(adjacencyList.begin() + nodeIndex);

        for (auto& neighbors : adjacencyList) {
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), nodeIndex), neighbors.end());
        }
    }

    // Function to get the number of nodes in the graph
    int getVertexCount() const {
        return nodes.size();
    }

    // Function to get the number of edges in the graph
    int getEdgeCount() const {
        return adjacencyList.size() / 2;  // Each edge is counted twice
    }

    // Function to check if the graph is empty
    bool isEmpty() const {
        return nodes.empty();
    }

    // Function to get the value of a node at a given index
    int getNodeValue(int index) const {
        return nodes[index].data;
    }

    // Function to get the neighbors of a node at a given index
    vector<int> getAdjacentNodes(int index) const {
        return adjacencyList[index];
    }

    // Function to perform Breadth-First Traversal starting from a given node
    void breadthFirstTraversal(int startNode) const {
        vector<char> visited(nodes.size(), 0); // 0 represents unvisited, 1 represents visited
        queue<int> q;
        q.push(startNode);
        visited[startNode] = 1;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << getNodeValue(current) << " ";

            for (int neighbor : getAdjacentNodes(current)) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = 1;
                }
            }
        }
        cout << endl;
    }

    // Function to insert a node as the child of a specific node
    void insertNodeAsChild(int parentNodeIndex, int childValue) {
        if (parentNodeIndex < 0 || parentNodeIndex >= nodes.size()) {
            cout << "Invalid parent node index." << endl;
            return;
        }

        addNode(childValue);

        int newNodeIndex = nodes.size() - 1;

        if (newNodeIndex < 0 || newNodeIndex >= adjacencyList.size()) {
            cout << "Invalid new node index." << endl;
            return;
        }

        addEdge(parentNodeIndex, newNodeIndex);
    }

    // Function to insert a node randomly
    void insertNodeRandomly(int nodeValue) {
        if (isEmpty()) {
            cout << "Graph is empty. Cannot insert node." << endl;
            return;
        }

        addNode(nodeValue);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, nodes.size() - 1);

        int randomNodeIndex = dis(gen);
        addEdge(randomNodeIndex, nodes.size() - 1);
    }
};

int main() {
    Graph myGraph;

    // Add nodes
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);
    myGraph.addNode(4);

    // Add edges
    myGraph.addEdge(0, 1);
    myGraph.addEdge(1, 2);
    myGraph.addEdge(2, 3);
    myGraph.addEdge(3, 0);

    cout << "Original Graph:" << endl;
    myGraph.breadthFirstTraversal(0);

    // Insert a node as the child of a specific node
    myGraph.insertNodeAsChild(1, 5);
    cout << "Graph after inserting a node as the child of node 2:" << endl;
    myGraph.breadthFirstTraversal(0);

    // Insert a node randomly
    myGraph.insertNodeRandomly(6);
    cout << "Graph after inserting a node randomly:" << endl;
    myGraph.breadthFirstTraversal(0);

    // Delete an edge
    myGraph.deleteEdge(1, 2);
    cout << "Graph after deleting edge between nodes 2 and 3:" << endl;
    myGraph.breadthFirstTraversal(0);

    // Delete a node
    myGraph.deleteNode(2);
    cout << "Graph after deleting node 3:" << endl;
    myGraph.breadthFirstTraversal(0);

    return 0;
}

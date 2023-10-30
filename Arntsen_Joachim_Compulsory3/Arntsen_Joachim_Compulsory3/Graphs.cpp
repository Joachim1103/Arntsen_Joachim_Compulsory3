#include <iostream>
#include <vector>
#include <queue>
#include <utility>

class Node 
{
public:
    int data;

    Node(int value) : data(value) {}
};

class Graph 
{
private:
    std::vector<Node*> nodes;
    std::vector<std::vector<bool>> adjacencyMatrix;

public:
    // Constructor
    Graph(int numNodes) 
    {
        nodes.reserve(numNodes);
        adjacencyMatrix.assign(numNodes, std::vector<bool>(numNodes, false));
    }

    // Access Functions //
    int getNumNodes() 
    {
        return nodes.size();
    }

    //Access Funtion for Return Node Information
    Node* getNode(int value) 
    {
        for (Node* node : nodes) 
        {
            if (node->data == value) 
            {
                return node;
            }
        }
        return nullptr;
    }

    // Access Function for Adjacent Nodes
    std::vector<Node*> getAdjacentNodes(int value) 
    {
        std::vector<Node*> adjacentNodes;
        Node* node = getNode(value);
        if (node) 
        {
            int nodeIndex = std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), node));
            for (int i = 0; i < nodes.size(); i++) 
            {
                if (adjacencyMatrix[nodeIndex][i]) 
                {
                    adjacentNodes.push_back(nodes[i]);
                }
            }
        }
        return adjacentNodes;
    }

    // Access Function for Vertices in Graph
    std::vector<int> getVertices() 
    {
        std::vector<int> vertices;
        for (Node* node : nodes) 
        {
            vertices.push_back(node->data);
        }
        return vertices;
    }

    // Access Function for Edges in Graph
    std::vector<std::pair<int, int>> getEdges() 
    {
        std::vector<std::pair<int, int>> edges;
        for (int i = 0; i < nodes.size(); ++i) 
        {
            for (int j = 0; j < nodes.size(); ++j) 
            {
                if (adjacencyMatrix[i][j]) 
                {
                    edges.push_back(std::make_pair(nodes[i]->data, nodes[j]->data));
                }
            }
        }
        return edges;
    }

    // Query Functions //
    bool hasNode(int value) 
    {
        return getNode(value) != nullptr;
    }

    bool hasEdge(int source, int destination) 
    {
        if (source >= 0 && source < nodes.size() && destination >= 0 && destination < nodes.size()) 
        {
            return adjacencyMatrix[source][destination];
        }
        return false;
    }

    // Query Function for Size
    int size() 
    {
        int edgeCount = 0;
        for (int i = 0; i < nodes.size(); ++i) 
        {
            for (int j = 0; j < nodes.size(); ++j) 
            {
                if (adjacencyMatrix[i][j]) 
                {
                    edgeCount++;
                }
            }
        }
        return edgeCount;
    }

    // Query Function for isEmpty
    bool isEmpty() 
    {
        return nodes.empty();
    }

    // Insertion and Deletion of nodes
    void addNode(int value) 
    {
        if (!hasNode(value)) 
        {
            Node* newNode = new Node(value);
            nodes.push_back(newNode);
        }
    }

    // Insertion of Nodes at random
    void insertNodeAtRandom(int value) 
    {
        addNode(value);
        if (nodes.size() > 1) 
        {
            int randomPosition = rand() % (nodes.size() - 1);
            for (int i = nodes.size() - 1; i > randomPosition; --i) 
            {
                std::swap(nodes[i], nodes[i - 1]);
            }
        }
    }

    // Insertion of Nodes as the child of a specific node
    void insertNodeAsChild(int value, int parentValue) 
    {
        Node* newNode = new Node(value);
        Node* parentNode = getNode(parentValue);
        if (parentNode) 
        {
            int parentIndex = std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), parentNode));
            nodes.push_back(newNode);
            adjacencyMatrix.push_back(std::vector<bool>(nodes.size(), false));
            for (int i = 0; i < nodes.size() - 1; ++i) 
            {
                adjacencyMatrix[i].push_back(false);
            }
            adjacencyMatrix[parentIndex][nodes.size() - 1] = true;
        }
        else
        {
            delete newNode;
        }
    }

    // Deletion of Nodes
    void removeNode(int value) 
    {
        for (int i = 0; i < nodes.size(); i++) 
        {
            if (nodes[i]->data == value) 
            {
                nodes.erase(nodes.begin() + i);
                adjacencyMatrix.erase(adjacencyMatrix.begin() + i);
                for (std::vector<bool>& row : adjacencyMatrix) 
                {
                    row.erase(row.begin() + i);
                }
                return;
            }
        }
    }

    // Insertion of Edges
    void addEdge(int source, int destination) 
    {
        if (source >= 0 && source < nodes.size() && destination >= 0 && destination < nodes.size() && !hasEdge(source, destination)) 
        {
            adjacencyMatrix[source][destination] = true;
        }
    }

    // Deletion of Edges
    void removeEdge(int source, int destination) 
    {
        if (source >= 0 && source < nodes.size() && destination >= 0 && destination < nodes.size()) 
        {
            adjacencyMatrix[source][destination] = false;
        }
    }

    // Breadth First Search Traversal
    void breadthTraversal(int startNode) 
    {
        if (startNode < 0 || startNode >= nodes.size()) 
        {
            return;
        }

        std::vector<bool> visited(nodes.size(), false);
        std::queue<int> bfsQueue;

        visited[startNode] = true;
        bfsQueue.push(startNode);

        while (!bfsQueue.empty()) 
        {
            int current = bfsQueue.front();
            bfsQueue.pop();
            std::cout << nodes[current]->data << " ";

            for (int neighbor = 0; neighbor < nodes.size(); ++neighbor) 
            {
                if (adjacencyMatrix[current][neighbor] && !visited[neighbor]) 
                {
                    visited[neighbor] = true;
                    bfsQueue.push(neighbor);
                }
            }
        }

        std::cout << std::endl;
    }
};

int main() 
{
    Graph myGraph(5);

    myGraph.addNode(0);
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);
    myGraph.addNode(4);

    myGraph.addEdge(0, 1);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(1, 3);
    myGraph.addEdge(2, 4);
    myGraph.addEdge(3, 4);

    std::cout << "Breadth-First Traversal starting from node 0: ";
    myGraph.breadthTraversal(0);

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

public:

////////////// Members //////////////

//Node Information
struct Node
{
    int key;
    vector<Node*>child;
};

//List of Children



////////////// FUNCTIONS //////////////

//Constructor


//Access functions


//Query Functions


//Insertion


//Deletion


//Type of Traversial
void BreadthTraversal(Node* root)
{
    if (root == NULL)
        return;

    queue<Node*> q;  
    q.push(root); 
    while (!q.empty())
    {
        int n = q.size();

        while (n > 0)
        {
            Node* p = q.front();
            q.pop();
            cout << p->key << " ";

            for (int i = 0; i < p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }

        cout << endl;
    }
}



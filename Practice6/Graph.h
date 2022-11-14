#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Graph {
	int nodeCounter = 1;
	class Node {
	public:
		int id;
		vector<Node*> nodes = vector<Node*>();
		vector<int> lengthConnections = vector<int>();
		Node(int id) {
			this->id = id;
		}
	};
	vector<Node*> allNodes = vector<Node*>();
public:

	Graph() {
		this->allNodes.push_back(new Node(0));
	}


	/*Node* FindNode(int id), currentNode {
		
	}*/

	void AddNewNode(int connection, int length) {
		Node * newNode = new Node(nodeCounter);
		nodeCounter++;
		allNodes.push_back(newNode);
		//Add newNode to other nodes 
		allNodes[connection]->nodes.push_back(newNode);
		//Add length between nodes to other nodes
		allNodes[connection]->lengthConnections.push_back(length);

		//Add length between nodes to newNode
		newNode->lengthConnections.push_back(length);

		//Add other nodes to newNode
		newNode->nodes.push_back(allNodes[connection]);

	}
	void AddNewNode(vector<int> connections, vector<int> lengths) {
		Node * newNode = new Node(nodeCounter);
		allNodes.push_back(newNode);
		nodeCounter++;
		for (int i = 0; i < connections.size(); i++) {

			//Add newNode to other nodes 
			allNodes[connections[i]]->nodes.push_back(newNode);
			//Add length between nodes to other nodes
			allNodes[connections[i]]->lengthConnections.push_back(lengths[i]);

			//Add length between nodes to newNode
			newNode->lengthConnections.push_back(lengths[i]);

			//Add other nodes to newNode
			newNode->nodes.push_back(allNodes[connections[i]]);
		}

	}
	void FindDiameter() {
		int inf = 420424;
		vector<vector<int>> CostTable = vector<vector<int>>(allNodes.size());

		//fill costTable zeros and inf
		for (int i = 0; i < allNodes.size(); i++) {
			CostTable[i] = vector<int>(allNodes.size());
			for (int j = 0; j < allNodes.size(); j++) {
				if (i == j) {
					CostTable[i][j] = 0;
				}
				else {
					CostTable[i][j] = inf;

				}
				
			}
		}

		//Fill length
		for (int i = 0; i < allNodes.size(); i++) {
			for (int j = i; j < allNodes[i]->nodes.size(); j++) {
				CostTable[i][allNodes[i]->nodes[j]->id] = allNodes[i]->lengthConnections[j];
				CostTable[allNodes[i]->nodes[j]->id][i] = allNodes[i]->lengthConnections[j];
			}
		}
		
		//Get Floyd Table
		FloydWarshallAlgorithm(CostTable);
		for (int i = 0; i < CostTable.size(); i++) {
			for (int j = 0; j < CostTable.size(); j++) {
				cout << CostTable[i][j] << ' ';

			}
			cout << endl;
		}

		int diameter = -1;
		for (int i = 0; i < CostTable.size(); i++) {
			for (int j = i; j < CostTable.size(); j++) {
				diameter = max(diameter, CostTable[i][j]);
			}
		}
		cout << "Diameter equals: " << diameter;
	}
	void FloydWarshallAlgorithm(vector<vector<int>> & CostTable) {
		for (int i = 0; i < CostTable.size(); i++) {
			for (int u = 0; u < CostTable.size(); u++) {
				for (int v = 0; v < CostTable.size(); v++) {
					CostTable[u][v] = min(CostTable[u][v], CostTable[u][i] + CostTable[i][v]);
				}
			}
		}
	}
	

};

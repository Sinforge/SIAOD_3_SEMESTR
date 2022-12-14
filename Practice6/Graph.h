#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;
class Graph {
	int nodeCounter = 1;
	class Node {
	public:
		int id;

		//Pair of NodeId and Length 
		vector<pair<int, int>> connections = vector<pair<int, int>>();
		Node(int id) {
			this->id = id;
		}
		Node(int id, pair<int, int> connection) {
			this->id = id;
			connections.push_back(connection);
		}
	};
	vector<Node*> allNodes = vector<Node*>();
public:
	
	Graph() {
		this->allNodes.push_back(new Node(0));
	}

//???????? ????? ???????
void AddNewNode(pair<int, int> connection) {
	//Create new node and and connection
	Node * newNode = new Node(nodeCounter, connection);
	//Add node to all nodes of Graph
	allNodes.push_back(newNode);
	//Add connection to other node
	allNodes[connection.first]->connections.push_back(make_pair(nodeCounter, connection.second));
	nodeCounter++;


}
//???????? ????? ???????
void AddNewNode(vector<pair<int, int>> connections) {
	Node * newNode = new Node(nodeCounter);
	allNodes.push_back(newNode);
	for (int i = 0; i < connections.size(); i++) {
		newNode->connections.push_back(connections[i]);
		allNodes[connections[i].first]->connections.push_back(make_pair(nodeCounter, connections[i].second));
	}
	nodeCounter++;


}
//???????? ?????
void AddConnection(int id, pair<int, int> connection) {
	allNodes[id]->connections.push_back(connection);
}
//????? ???????
int FindDiameter() {
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
		for (int j = i; j < allNodes[i]->connections.size(); j++) {
			CostTable[i][allNodes[i]->connections[j].first] = allNodes[i]->connections[j].second;
			CostTable[allNodes[i]->connections[j].first][i] = allNodes[i]->connections[j].second;
		}
	}
	
	//Get Floyd Table
	FloydWarshallAlgorithm(CostTable);

	//Get diameter
	int diameter = -1;
	for (int i = 0; i < CostTable.size(); i++) {
		for (int j = i; j < CostTable.size(); j++) {
			diameter = max(diameter, CostTable[i][j]);
		}
	}
	return diameter;
}
//???????? ??????-????????
void FloydWarshallAlgorithm(vector<vector<int>> & CostTable) {
	for (int i = 0; i < CostTable.size(); i++) {
		for (int u = 0; u < CostTable.size(); u++) {
			for (int v = 0; v < CostTable.size(); v++) {
				CostTable[u][v] = min(CostTable[u][v], CostTable[u][i] + CostTable[i][v]);
			}
		}
	}
}
//????? ?????
void PrintGraph() {
	cout << "\nYour Graph\n";
	for (int i = 0; i < allNodes.size(); i++) {
		cout << i << ":\t";
		for (int j = 0; j < allNodes[i]->connections.size(); j++) {
			cout << "(" << allNodes[i]->connections[j].first << ", " << allNodes[i]->connections[j].second << " ) ";
		}
		cout << endl;
	}
}
//???????? ?????
 void PrimAlgorithm() {
	//Choose Random node
	int randomNumber = rand() % allNodes.size();

	//Contains visited nodes id
	vector<int> visited = vector<int>{randomNumber};
	//Contains unvisited nodes
	vector<int> unvisited = vector<int>();
	
	//Edge-length vector
	vector<pair<pair<int, int>, int>> choosedEdges = vector<pair<pair<int, int>, int>>();

	//Fill unvisited nodes
	for (int i = 0; i < allNodes.size(); i++) {
		if (i != randomNumber) {
			unvisited.push_back(i);
		}
	}
	

	while (unvisited.size() != 0) {
		int minLength = INT_MAX;
		int minNodeId = -1;
		//Edge - example (0, 1) or (2, 3), and length of edge
		pair<pair<int, int>, int> foundedEdge = pair<pair<int, int>, int>();
		for (int i = 0; i < visited.size(); i++) {
			for (int j = 0; j < allNodes[visited[i]]->connections.size(); j++) {
				if (!isVisited(visited, allNodes[visited[i]]->connections[j].first)) {
					if (allNodes[visited[i]]->connections[j].second < minLength) {
						minLength = allNodes[visited[i]]->connections[j].second;
						minNodeId = allNodes[visited[i]]->connections[j].first;
						foundedEdge.first = make_pair(min(visited[i], allNodes[visited[i]]->connections[j].first), max(visited[i], allNodes[visited[i]]->connections[j].first) );
					}
				}
			}
		}
		
		foundedEdge.second = minLength;
		choosedEdges.push_back(foundedEdge);
		//Add to visited
		visited.push_back(minNodeId);

		//Delete from unvisited
		for (int j = 0; j < unvisited.size(); j++) {
			if (unvisited[j] == minNodeId) {
				unvisited.erase(unvisited.begin() + j);
				break;
			}
		}
	}
	PrintOstovTree(choosedEdges);


	
	
}
 //????????? ???????? ??????
 void PrintOstovTree(vector < pair<pair<int, int>, int>> choosedEdges) {
	 struct node {
		 int id;
		 int level;
		 vector<node*> nodes = vector<node*>();
	 };
	 vector<node*> allVertex = vector<node*>(allNodes.size());
	 for (int i = 0; i < allNodes.size(); i++) {
		 allVertex[i] = new node();
		 allVertex[i]->id = i;
	 }
	 for (int i = 0; i < choosedEdges.size(); i++) {
		 allVertex[choosedEdges[i].first.first]->nodes.push_back(allVertex[choosedEdges[i].first.second]);
	 }
	 queue<node*> queueNodes;
	 allVertex[0]->level = 0;
	 queueNodes.push(allVertex[0]);
	 int currentLevel = -1;
	 while (!queueNodes.empty()) {
		 node* currentNode = queueNodes.front();

		 if (currentLevel != currentNode->level) {
			 cout << endl;
			 for (int i = 0; i < 7 - currentNode->level; i++) {
				 cout << "   ";
			 }
			 currentLevel = currentNode->level;
		 }
		 cout << currentNode->id << "   ";
		 for (int i = 0; i < currentNode->nodes.size(); i++) {
			 currentNode->nodes[i]->level = currentNode->level + 1;
			 queueNodes.push(currentNode->nodes[i]);
		 }
		 queueNodes.pop();
	 }
}
 //????????? ???????? ?? ??????? ??? ???
bool isVisited(vector<int> visited, int id) {
	bool flag = false;
	for (int i = 0; i < visited.size(); i++) {
		if (visited[i] == id) {
			flag = true;
			break;
		}
	}
	return flag;
}
	

};

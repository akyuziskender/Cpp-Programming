/* @Author
*  Student Name: Iskender Akyuz
*  Student ID : 150150150
*  Date: 22.04.2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

enum Person {
	Joseph,
	Lucy
};

struct TravelPlan {
	int homeNode, destNode;
};

struct Edge {
	int src, dest, weight;
};

struct Node {
	int vertex, weight;
};

struct comp {
	bool operator() (const Node &lhs, const Node &rhs) const {
		return lhs.weight > rhs.weight;
	}
};

typedef pair<int, int> Pair;

class Graph {
private:
	int numberOfNodes;
	vector<vector<Pair>> adjList;
	int getCost(int, int) const;
public:
	Graph(vector<Edge> const&, int);		// Constructor
	Graph(const Graph &, Pair);				// Copy Constructor
	vector<int> DijkstraSP(int);
	void getPath(vector<int> &, int, int, vector<Pair> &);
};

Graph::Graph(vector<Edge> const& edges, int n) {		// Constructor
	numberOfNodes = n;
	adjList.resize(numberOfNodes);

	for (auto& edge : edges)
		adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
}

Graph::Graph(const Graph& graph, Pair edge) {	// copying the class without the edge that causeS the intersection
	numberOfNodes = graph.numberOfNodes;
	adjList.resize(numberOfNodes);
	for (int i = 0; i < numberOfNodes; i++) {
		for (auto p : graph.adjList[i]) {
			if (i == edge.first && p.first == edge.second)	continue;		// skipping the edge
			adjList[i].push_back(p);
		}
	}
}

vector<int> Graph::DijkstraSP(int source) {
	priority_queue<Node, vector<Node>, comp> minHeap;
	minHeap.push({source, 0});

	vector<int> dist(numberOfNodes, INT_MAX);
	dist[source] = 0;

	vector<bool> done(numberOfNodes, false);
	done[source] = true;

	vector<int> prev(numberOfNodes, -1);

	while (!minHeap.empty()) {
		// get the best vertex
		Node node = minHeap.top();
		minHeap.pop();

		int u = node.vertex;

		for (auto i : adjList[u]) {
			int v = i.first;
			int weight = i.second;

			if (!done[v] && (dist[u] + weight) < dist[v]) {
				dist[v] = dist[u] + weight;
				prev[v] = u;
				minHeap.push({v, dist[v]});
			}
		}
		done[u] = true;
	}

	return prev;
}

int Graph::getCost(int src, int dest) const {
	if (src == -1)	return 0;
	for (auto p : adjList[src]) {
		if (p.first == dest)	return p.second;
	}
}

void Graph::getPath(vector<int>& prev, int i, int startTime, vector<Pair>& pathAndCost) {
	if (i < 0)	return;

	getPath(prev, prev[i], startTime, pathAndCost);
	int timeCost = startTime;
	if (!pathAndCost.empty())
		timeCost = pathAndCost.back().second + getCost(prev[i], i);
	pathAndCost.push_back(make_pair(i, timeCost));
}

void ReadFile(string, int&, vector<Edge>&, TravelPlan*);
void ArrangeTravelPlans(Graph, TravelPlan*);
bool OneWayTravel(Graph, vector<Pair>&, vector<Pair>&, TravelPlan*, Pair, bool);
int CheckIntersection(vector<Pair>, vector<Pair>);
void FindAlternativePath(Graph, vector<Pair>&, vector<Pair>&, TravelPlan*, Pair, Pair, int, bool);
void PrintPaths(vector<Pair>, vector<Pair>, vector<Pair>, vector<Pair>);

int main(int argc, char* argv[]) {
	// necessary variables
	string filename(argv[1]);
	int numberOfNodes;
	vector<Edge> edges;
	TravelPlan plans[2];

	ReadFile(filename, numberOfNodes, edges, plans);

	Graph graph(edges, numberOfNodes);			// creating the graph
	ArrangeTravelPlans(graph, plans);

	return 0;
}

void ReadFile(string fileName, int &numberOfNodes, vector<Edge> &edges, TravelPlan *plans) {
	ifstream testFile(fileName);	// opening the file for reading
	string line;
	int lineNo = 0;
	while (getline(testFile, line)) {	// reading the file line by line
		istringstream ss(line);
		lineNo++;
		if (lineNo == 1) {
			int nodeNumber;
			ss >> nodeNumber;
			numberOfNodes = nodeNumber;
			continue;
		}
		else if (lineNo == 2) {
			int JosephHome, JosephDest, LucyHome, LucyDest;
			ss >> JosephHome >> JosephDest >> LucyHome >> LucyDest;
			plans[Joseph].homeNode = JosephHome;
			plans[Joseph].destNode = JosephDest;
			plans[Lucy].homeNode = LucyHome;
			plans[Lucy].destNode = LucyDest;
		}
		else {
			int src, dest, weight;
			ss >> src >> dest >> weight;
			Edge newEdge = { src, dest, weight };
			edges.push_back(newEdge);
		}
	}
	return;
}

void ArrangeTravelPlans(Graph graph, TravelPlan* plans) {
	vector<Pair> JosephHomeToDestPath, LucyHomeToDestPath;
	if (!OneWayTravel(graph, JosephHomeToDestPath, LucyHomeToDestPath, plans, { 0, 0 }, true)) {		// travelling from home to dest
		cout << "No solution!" << endl;
		return;
	}

	vector<Pair> JosephDestToHomePath, LucyDestToHomePath;
	if (!OneWayTravel(graph, JosephDestToHomePath, LucyDestToHomePath, plans, { JosephHomeToDestPath.back().second + 30, LucyHomeToDestPath.back().second + 30 }, false)) {		// travelling from dest to home
		cout << "No solution!" << endl;
		return;
	}

	PrintPaths(JosephHomeToDestPath, LucyHomeToDestPath, JosephDestToHomePath, LucyDestToHomePath);
}

int CheckIntersection(vector<Pair> JosephPathAndCost, vector<Pair> LucyPathAndCost) {
	for (vector<Pair>::iterator it = JosephPathAndCost.begin(); it != JosephPathAndCost.end(); ++it)
		for (vector<Pair>::iterator it2 = LucyPathAndCost.begin(); it2 != LucyPathAndCost.end(); ++it2)
			if (it->first == it2->first && it->second == it2->second)
				return it->first;

	if (JosephPathAndCost.front().second == 0) {		// checking Joseph's waiting when he goes to his destination
		for (vector<Pair>::iterator it2 = LucyPathAndCost.begin(); it2 != LucyPathAndCost.end(); ++it2)
			if (JosephPathAndCost.back().first == it2->first && (it2->second >= JosephPathAndCost.back().second && it2->second <= JosephPathAndCost.back().second + 30))
				return it2->first;
	}
	else {			// checking Joseph's waiting when he goes back to his home
		for (vector<Pair>::iterator it2 = LucyPathAndCost.begin(); it2 != LucyPathAndCost.end(); ++it2)
			if (JosephPathAndCost.front().first == it2->first && (it2->second >= JosephPathAndCost.front().second - 30 && it2->second <= JosephPathAndCost.front().second))
				return it2->first;
	}
	if (LucyPathAndCost.front().second == 0) {		// checking Lucy's waiting when he goes to his destination
		for (vector<Pair>::iterator it = JosephPathAndCost.begin(); it != JosephPathAndCost.end(); ++it)
			if (LucyPathAndCost.back().first == it->first && (it->second >= LucyPathAndCost.back().second && it->second <= LucyPathAndCost.back().second + 30))
				return it->first;
	}
	else {			// checking Lucy's waiting when he goes back to his home
		for (vector<Pair>::iterator it = JosephPathAndCost.begin(); it != JosephPathAndCost.end(); ++it)
			if (LucyPathAndCost.front().first == it->first && (it->second >= LucyPathAndCost.front().second - 30 && it->second <= LucyPathAndCost.front().second))
				return it->first;
	}
	return -1;		// could not find any intersection
}

bool OneWayTravel(Graph graph, vector<Pair>& JosephPathAndCost, vector<Pair>& LucyPathAndCost, TravelPlan* plans, Pair startTimes, bool goingToDest) {
	// Joseph's path
	vector<int> JosephPath = graph.DijkstraSP(goingToDest ? plans[Joseph].homeNode : plans[Joseph].destNode);
	graph.getPath(JosephPath, goingToDest ? plans[Joseph].destNode : plans[Joseph].homeNode, startTimes.first, JosephPathAndCost);
	if (goingToDest && JosephPathAndCost[0].first != (goingToDest ? plans[Joseph].homeNode : plans[Joseph].destNode))		// could not find a path
		return false;

	// Lucy's path
	vector<int> LucyPath = graph.DijkstraSP(goingToDest ? plans[Lucy].homeNode : plans[Lucy].destNode);
	graph.getPath(LucyPath, goingToDest ? plans[Lucy].destNode : plans[Lucy].homeNode, startTimes.second, LucyPathAndCost);
	if (goingToDest && LucyPathAndCost[0].first != (goingToDest ? plans[Lucy].homeNode : plans[Lucy].destNode))			// could not find a path
		return false;

	int intersectionNode = CheckIntersection(JosephPathAndCost, LucyPathAndCost);
	if (intersectionNode != -1) {
		Pair startingNodes = { JosephPath[intersectionNode], LucyPath[intersectionNode] };
		FindAlternativePath(graph, JosephPathAndCost, LucyPathAndCost, plans, startTimes, startingNodes, intersectionNode, goingToDest);
		if (JosephPathAndCost.empty() || LucyPathAndCost.empty())
			return false;
	}
	return true;
}

void FindAlternativePath(Graph graph, vector<Pair>& JosephPathAndCost, vector<Pair>& LucyPathAndCost, TravelPlan* plans, Pair startTimes, Pair startingNodes, int intersectionNode, bool goingToDest) {
	int JosephTravelTime = JosephPathAndCost.back().second - JosephPathAndCost.front().second,
		LucyTravelTime = LucyPathAndCost.back().second - LucyPathAndCost.front().second,
		JosephAltTravelTime = -1, LucyAltTravelTime = -1;
	bool altPathFound = true;

	// Joseph - Alternative path
	Graph copyGraphJoseph = Graph(graph, { startingNodes.first, intersectionNode });
	vector<int> JosephAltHomeToDestPath = copyGraphJoseph.DijkstraSP(goingToDest ? plans[Joseph].homeNode : plans[Joseph].destNode);
	vector<Pair> JosephAltPathAndCost;
	copyGraphJoseph.getPath(JosephAltHomeToDestPath, goingToDest ? plans[Joseph].destNode : plans[Joseph].homeNode, startTimes.first, JosephAltPathAndCost);
	if (JosephAltPathAndCost[0].first == (goingToDest ? plans[Joseph].homeNode : plans[Joseph].destNode))		// found an alternative path
		JosephAltTravelTime = JosephAltPathAndCost.back().second - JosephAltPathAndCost.front().second;

	// Lucy - Alternative path
	Graph copyGraphLucy = Graph(graph, { startingNodes.second, intersectionNode });
	vector<int> LucyAltHomeToDestPath = copyGraphLucy.DijkstraSP(goingToDest ? plans[Lucy].homeNode : plans[Lucy].destNode);
	vector<Pair> LucyAltPathAndCost;
	copyGraphLucy.getPath(LucyAltHomeToDestPath, goingToDest ? plans[Lucy].destNode : plans[Lucy].homeNode, startTimes.second, LucyAltPathAndCost);
	if (LucyAltPathAndCost[0].first == (goingToDest ? plans[Lucy].homeNode : plans[Lucy].destNode))			// found an alternative path
		LucyAltTravelTime = LucyAltPathAndCost.back().second - LucyAltPathAndCost.front().second;

	if (JosephAltTravelTime != -1 && LucyAltTravelTime != -1) {		// alternative paths exist for both of them
		bool JosephAltPathIntersect = CheckIntersection(JosephAltPathAndCost, LucyPathAndCost) != -1;		// checking if alt path causes intersection
		bool LucyAltPathIntersect = CheckIntersection(JosephPathAndCost, LucyAltPathAndCost) != -1;			// checking if alt path causes intersection
		if (!JosephAltPathIntersect && !LucyAltPathIntersect) {
			if ((JosephAltTravelTime + LucyTravelTime) <= (JosephTravelTime + LucyAltTravelTime))			// Joseph's alt path takes less time
				JosephPathAndCost = JosephAltPathAndCost;
			else if ((JosephTravelTime + LucyAltTravelTime) <= (JosephAltTravelTime + LucyTravelTime))		// Lucy's alt path takes less time 
				LucyPathAndCost = LucyAltPathAndCost;
		}
		else if (!JosephAltPathIntersect)
			JosephPathAndCost = JosephAltPathAndCost;
		else if (!LucyAltPathIntersect)
			LucyPathAndCost = LucyAltPathAndCost;
		else		// both alternative paths also cause intersection, no solution
			altPathFound = false;
	}
	else if (JosephAltTravelTime != -1) {				// only Joseph may take an alt path
		if (CheckIntersection(JosephAltPathAndCost, LucyPathAndCost) == -1)		// Joseph's alt path does not cause intersection
			JosephPathAndCost = JosephAltPathAndCost;
		else						// the alt path is not valid
			altPathFound = false;
	}
	else if (LucyAltTravelTime != -1) {				// only Lucy may take an alt path
		if (CheckIntersection(JosephPathAndCost, LucyAltPathAndCost) == -1)		// Lucy's alt path does not cause intersection
			LucyPathAndCost = LucyAltPathAndCost;
		else						// the alt path is not valid
			altPathFound = false;
	}
	else		// no alterantive paths for any of them
		altPathFound = false;

	if (!altPathFound) {		// could not find any alternative paths, so clear the previous paths
		JosephPathAndCost.clear();
		LucyPathAndCost.clear();
	}
}

void PrintPaths(vector<Pair> JosephHomeToDestPath, vector<Pair> LucyHomeToDestPath, vector<Pair> JosephDestToHomePath, vector<Pair> LucyDestToHomePath) {
	cout << "Joseph's Path, duration: " << JosephDestToHomePath.back().second << endl;
	for (std::vector<Pair>::iterator it = JosephHomeToDestPath.begin(); it != JosephHomeToDestPath.end(); ++it)
		cout << "Node: " << it->first << " Time: " << it->second << endl;
	cout << "-- return --" << endl;
	for (std::vector<Pair>::iterator it = JosephDestToHomePath.begin(); it != JosephDestToHomePath.end(); ++it)
		cout << "Node: " << it->first << " Time: " << it->second << endl;

	cout << "\nLucy's Path, duration: " << LucyDestToHomePath.back().second << endl;
	for (std::vector<Pair>::iterator it = LucyHomeToDestPath.begin(); it != LucyHomeToDestPath.end(); ++it)
		cout << "Node: " << it->first << " Time: " << it->second << endl;
	cout << "-- return --" << endl;
	for (std::vector<Pair>::iterator it = LucyDestToHomePath.begin(); it != LucyDestToHomePath.end(); ++it)
		cout << "Node: " << it->first << " Time: " << it->second << endl;
}
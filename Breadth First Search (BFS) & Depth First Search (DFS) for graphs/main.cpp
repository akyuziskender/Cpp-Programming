#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <chrono>

using namespace std;

class Pokemon {
private:
	int HP;     // health point
	int PP;     // power point
public:
	Pokemon(int, int);	// Constructor
	int getHP() const;
	int getPP() const;
	void Attack(int, int, int ,int);
};

Pokemon::Pokemon(int hp, int pp) {      // Constructor
	this->HP = hp;
	this->PP = pp;
}

int Pokemon::getHP() const { return HP; }
int Pokemon::getPP() const { return PP; }

void Pokemon::Attack(int pp, int accuracy, int damage, int firstUsage) {

}

class Stats {
private:
	char turn;
	float prob;
	int level;
	bool isLeaf;
public:
	Stats(char, float, int, bool);      // Constructor
	char getTurn() const;
	float getProb() const;
	int getLevel() const;
	bool getIsLeaf() const;
	void setIsLeaf(bool);
};

int Stats::getLevel() const { return level; }
char Stats::getTurn() const { return turn; }
float Stats::getProb() const { return prob; }
bool Stats::getIsLeaf() const { return isLeaf; }
void Stats::setIsLeaf(bool value) { this->isLeaf = value; }

Stats::Stats(char turn, float prob, int level, bool isLeaf) {
	this->turn = turn;
	this->prob = prob;
	this->level = level;
	this->isLeaf = isLeaf;
}

class Node {
private:
	static int ID;
	int thisId;
	Pokemon* pikachu;
	Pokemon* blastoise;
	Stats* stats;
	string attackName;
	bool isAttackEffective;
	Node* parent;
	vector<Node*> children;
	int childrenCount;
public:
	Node(Pokemon*, Pokemon*, Stats*, Node*, string, bool);      // Constructor
	int getId() const;
	Pokemon* getPikachu() const;
	Pokemon* getBlastoise() const;
	Stats* getStats() const;
	string getAttackName() const;
	bool getIsAttackEffective() const;
	Node* getParent() const;
	vector<Node*> getChildren() const;
	int getChildrenCount() const;
	void addChild(Node*);
	void deleteChild();
	void print() const;
};

Node::Node(Pokemon* pikachu, Pokemon* blastoise, Stats* stats, Node* parent, string attackName, bool isEffective) {
	this->thisId = ID++;
	this->pikachu = pikachu;
	this->blastoise = blastoise;
	this->stats = stats;
	this->parent = parent;
	this->childrenCount = 0;
	this->attackName = attackName;
	this->isAttackEffective = isEffective;
}

int Node::getId() const { return thisId; }
Pokemon* Node::getPikachu() const { return pikachu; }
Pokemon* Node::getBlastoise() const { return blastoise; }
Stats* Node::getStats() const {	return stats; }
string Node::getAttackName() const { return attackName; }
bool Node::getIsAttackEffective() const { return isAttackEffective; }
Node* Node::getParent() const { return parent; }
vector<Node*> Node::getChildren() const { return children; }
int Node::getChildrenCount() const { return childrenCount; }

void Node::addChild(Node* newChild) {
	this->children.push_back(newChild);
	childrenCount++;
}

void Node::deleteChild() { 
	this->childrenCount--;
	this->children.pop_back();
}

void Node::print() const {
	cout << "P_HP:" << pikachu->getHP() << " P_PP:" << pikachu->getPP() << " B_HP:" << blastoise->getHP() << " B_PP:" << blastoise->getPP() << " PROB:" << stats->getProb() << endl;
}

class Graph {
private:
	Node* root;
	int counter;
	int winPath[2];
	void DFSUtil(Node*, bool [], vector<Node*>*, int, bool*, int);
	void deleteUtil(Node*, bool []);
public:
	Graph();
	Node* getRoot() const;
	int getCounter() const;
	int getWinPath(int) const;
	vector<Node*> getAllNodesInLastLevel(int);
	void setRoot(Node*);
	void setWinPath(int, int);
	void increaseCounter(int);
	void BFS() const;
	vector<Node*> DFS(int, int);
	void printLeaves();
	void deleteGraph();
};

Graph::Graph() {
	root = NULL;
	counter = 0;
	winPath[0] = winPath[1] = 0;
}

Node* Graph::getRoot() const { return root; }
int Graph::getCounter() const { return counter; }
int Graph::getWinPath(int index) const { return winPath[index]; }

vector<Node*> Graph::getAllNodesInLastLevel(int lastLevel) {
	return DFS(3, lastLevel);
}

void Graph::setRoot(Node* root) { this->root = root; }
void Graph::setWinPath(int index, int value) { this->winPath[index] = value; }
void Graph::increaseCounter(int value) { this->counter += value; }

void Graph::BFS() const {
	bool *visited = new bool[counter];
	for(int i = 0; i < counter; i++)
		visited[i] = false; 
  
	list<Node*> queue; 
	Node* node = root;
	int nodeId = node->getId();
 
	visited[nodeId] = true; 
	queue.push_back(node);
  
	while(!queue.empty()) {
		node = queue.front();
		nodeId = node->getId();
		queue.pop_front();

		if (node->getChildrenCount() > 0) {
			vector<Node*> children = node->getChildren();
			for (vector<Node*>::size_type i = 0; i != children.size(); i++) {
				int childId = children[i]->getId();
				if (!visited[childId]) {
					visited[childId] = true;
					queue.push_back(children[i]);
				}
			}
		}
	}
	delete[] visited;
}

void Graph::DFSUtil(Node* node, bool visited[], vector<Node*>* nodes, int searchValue, bool* found, int searchMode) {
	if (searchMode == 1 && *found)
		return;

	int nodeId = node->getId();
	visited[nodeId] = true;

	if (searchMode == 1) {
		nodes->push_back(node);
		if (nodeId == searchValue) {
			*found = true;
			return;
		}
	}
	else if (searchMode == 2 && node->getStats()->getIsLeaf())
		nodes->push_back(node);
	else if (searchMode == 3 && node->getStats()->getLevel() == searchValue)
		nodes->push_back(node);

	if (node->getChildrenCount() > 0) {
		vector<Node*> children = node->getChildren();

		for (vector<Node*>::size_type i = 0; i != children.size(); i++)
			if (!visited[children[i]->getId()]) {
				DFSUtil(children[i], visited, nodes, searchValue, found, searchMode);
				if (searchMode == 1) {
					if (*found)	return;
					else	nodes->pop_back();
				}
			}
	}
}

void Graph::deleteUtil(Node* node, bool visited[]) {
	int nodeId = node->getId();
	visited[nodeId] = true;

	if (node->getChildrenCount() > 0) {
		vector<Node*> children = node->getChildren();
		for (vector<Node*>::reverse_iterator i = children.rbegin(); i != children.rend(); ++i)
			deleteUtil(*i, visited);
	}

	delete node->getPikachu();
	delete node->getBlastoise();
	delete node->getStats();
	if (node->getParent())		// check if it is the root
		node->getParent()->deleteChild();
	delete node;
}

vector<Node*> Graph::DFS(int searchMode, int searchValue) {
	vector<Node*> nodes;
	bool found = false;
	bool *visited = new bool[counter];		// marking all the vertices as not visited 
	for (int i = 0; i < counter; i++)
		visited[i] = false;
  
	DFSUtil(root, visited, &nodes, searchValue, &found, searchMode);
	delete[] visited;		// deleting memory
	return nodes;
}

void Graph::deleteGraph() {
	bool* visited = new bool[counter];		// marking all the vertices as not visited 
	for (int i = 0; i < counter; i++)
		visited[i] = false;
	deleteUtil(root, visited);
	delete[] visited;		// deleting memory
}

void Graph::printLeaves() {
	vector<Node*> leaves = DFS(2, 0);		// searchMode = 2, second parameter doesn't matter.

	for (vector<Node*>::size_type i = 0; i != leaves.size(); i++)
		leaves[i]->print();
}

class Attack {
private:
	string name;
	int PP;
	int accuracy;
	int damage;
	int firstUsage;
public:
	Attack(string, int, int, int, int);
	string getName() const;
	int getPP() const;
	int getAccuracy() const;
	int getDamage() const;
	int getFirstUsage() const;
};

Attack::Attack(string name, int pp, int accuracy, int damage, int firstUsage) {
	this->name = name;
	this->PP = pp;
	this->accuracy = accuracy;
	this->damage = damage;
	this->firstUsage = firstUsage;
}

string Attack::getName() const { return name; }
int Attack::getPP() const { return PP; }
int Attack::getAccuracy() const { return accuracy; }
int Attack::getDamage() const { return damage; }
int Attack::getFirstUsage() const { return firstUsage; }

void Part1(Graph*, int, string);
void Part2(Graph*, int, char*);
void Part3(Graph*, char*);
void PrintWinPath(vector<Node*>);
void ReadFile(string, vector<Attack*>*);
void InitializeGraph(Graph*);
bool TurnHandler(Graph*, char, int, vector<Node*>, vector<Attack*>, string);
void AttackOpponent(char, Node*, Attack*, vector<Attack*>, int, bool);
float CalculateProb(vector<Attack*>, int, int, float);

int Node::ID = 0;

int main(int argc, char* argv[]) {
	Graph* nodeGraph = new Graph();

	if (strcmp(argv[1], "part1") == 0) {
		Part1(nodeGraph, atoi(argv[2]), "part1");			// graph creation
	}
	else if (strcmp(argv[1], "part2") == 0) {
		Part1(nodeGraph, atoi(argv[2]), "part2");			// graph creation
		Part2(nodeGraph, atoi(argv[2]), argv[3]);		// traversing the graph
	}
	else if(strcmp(argv[1], "part3") == 0) {
		Part1(nodeGraph, 9, "part3");			// graph creation
		Part3(nodeGraph, argv[2]);
	}
	nodeGraph->deleteGraph();				// delete all nodes
	delete nodeGraph;						// delete graph
	return 0;
}

void Part1(Graph* nodeGraph, int maxLevel, string partNo) {
	int currentLevel = 0;

	vector<Attack*> pikachuAttacks;
	vector<Attack*> blastoiseAttacks;

	ReadFile("pikachu.txt", &pikachuAttacks);
	ReadFile("blastoise.txt", &blastoiseAttacks);

	InitializeGraph(nodeGraph);

	while (currentLevel != maxLevel) {
		vector<Node*> allNodesInCurrLevel = nodeGraph->getAllNodesInLastLevel(currentLevel);		
		char turn = (allNodesInCurrLevel[0]->getStats())->getTurn();		// getting the current turn
		if (turn == 'P') {		// Pikachu is attacking
			if (TurnHandler(nodeGraph, 'P', currentLevel, allNodesInCurrLevel, pikachuAttacks, partNo))
				break;
		}
		else if (turn == 'B') {		// Blastoise is attacking
			if (TurnHandler(nodeGraph, 'B', currentLevel, allNodesInCurrLevel, blastoiseAttacks, partNo))
				break;
		}
		currentLevel++;
	}

	if (partNo.compare("part1") == 0)
		nodeGraph->printLeaves();

	for(vector<Attack*>::size_type i = 0; i != pikachuAttacks.size(); i++)
		delete pikachuAttacks[i];		// deleting memory

	for(vector<Attack*>::size_type i = 0; i != blastoiseAttacks.size(); i++)
		delete blastoiseAttacks[i];		// deleting memory
}

void Part2(Graph* nodeGraph, int maxLevel, char* algorithm) {
	auto t1 = chrono::high_resolution_clock::now();
	if (strcmp(algorithm, "bfs") == 0) {
		nodeGraph->BFS();
	}
	else if (strcmp(algorithm, "dfs") == 0) {
		nodeGraph->DFS(0, 0);		// 0 mode: classic traverse
	}
	auto t2 = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
	cout << "Time taken by " << algorithm << " function is : " << fixed  << (double)duration / 1000000 << " sec" << endl;
	cout << "Node count: " << nodeGraph->getCounter() << endl;
}

void Part3(Graph* nodeGraph, char* pokemon) {
	if (strcmp(pokemon, "pikachu") == 0) {
		vector<Node*> pikachuWinPath = nodeGraph->DFS(1, nodeGraph->getWinPath(0));		// 0 for pikachu
		cout << "Pikachu's win:" << endl;
		if (pikachuWinPath.size() > 1)
			PrintWinPath(pikachuWinPath);
		else
			cout << "Could not win in given maxLevel." << endl;
	}
	else if (strcmp(pokemon, "blastoise") == 0) {
		vector<Node*> blastoiseWinPath = nodeGraph->DFS(1, nodeGraph->getWinPath(1));	// 1 for blastoise
		cout << "Blastoise's win:" << endl;
		if (blastoiseWinPath.size() > 1)
			PrintWinPath(blastoiseWinPath);
		else
			cout << "Could not win in given maxLevel." << endl;
	}
	else
		cout << "Wrong pokemon name. Try again." << endl;
}

void PrintWinPath(vector<Node*> path) {
	for (vector<Node*>::size_type i = 1; i != path.size(); i++) {
		char attacker = (path[i]->getStats()->getTurn() == 'B') ? 'P' : 'B';
		cout << (attacker == 'P' ? "Pokemon" : "Blastoise") << " used " << path[i]->getAttackName() << ". It's ";
		cout << (path[i]->getIsAttackEffective() ? "effective" : "uneffective");
		cout << ". (P:" << path[i]->getPikachu()->getHP() << ", B:" << path[i]->getBlastoise()->getHP() << ")" << endl;
	}
	cout << "Level count: " << path[path.size() - 1]->getStats()->getLevel() << endl;
	cout << "Probability: " << path[path.size() - 1]->getStats()->getProb() << endl;
}

void InitializeGraph(Graph* nodeGraph) {
	Pokemon* Pikachu = new Pokemon(200, 100);
	Pokemon* Blastoise = new Pokemon(200, 100);

	Stats* stats = new Stats('P', 1, 0, true);

	Node* root = new Node(Pikachu, Blastoise, stats, NULL, "", false);

	nodeGraph->setRoot(root);
	nodeGraph->increaseCounter(1);
}

bool TurnHandler(Graph* nodeGraph, char turn, int currentLevel, vector<Node*> allNodesInCurrLevel, vector<Attack*> allAttacks, string partNo) {
	for (vector<Node*>::size_type i = 0; i != allNodesInCurrLevel.size(); i++) {
		Node *currNode = allNodesInCurrLevel[i];
		int attackerHP = (turn == 'P') ? currNode->getPikachu()->getHP() : currNode->getBlastoise()->getHP();
		int attackerPP = (turn == 'P') ? currNode->getPikachu()->getPP() : currNode->getBlastoise()->getPP();
		if (attackerHP > 0) {		// if the attacker isn't dead, pokemon can attack
			for (vector<Attack*>::size_type j = 0; j != allAttacks.size(); j++) {
				Attack* attack = allAttacks[j];
				if (attack->getFirstUsage() <= currentLevel && (attackerPP >= attack->getPP() || attack->getName().compare("Skip") == 0)) {		// checking if the attack is usable
					if (attack->getAccuracy() == 100) {		// one possible node
						AttackOpponent(turn, currNode, attack, allAttacks, currentLevel, true);
						nodeGraph->increaseCounter(1);	// a new node
					}
					else {	// two possibilities
						AttackOpponent(turn, currNode, attack, allAttacks, currentLevel, true);		// effective case

						AttackOpponent(turn, currNode, attack, allAttacks, currentLevel, false);		// uneffective case
						nodeGraph->increaseCounter(2);	// 2 new nodes
					}
				}
				else {		// attack is not usable, skip it
					continue;
				}
			}
		}
		else if (partNo.compare("part3") == 0 && nodeGraph->getWinPath(0) != 0 && nodeGraph->getWinPath(1) != 0)
			return true;
		else if (nodeGraph->getWinPath(0) == 0 || nodeGraph->getWinPath(1) == 0) {
			if (turn == 'B' && nodeGraph->getWinPath(0) == 0)
				nodeGraph->setWinPath(0, currNode->getId());
			else if (turn == 'P' && nodeGraph->getWinPath(1) == 0)
				nodeGraph->setWinPath(1, currNode->getId());
		}
	}
	return false;
}

void AttackOpponent(char turn, Node* currNode, Attack* attack, vector<Attack*> allAttacks, int currentLevel, bool isEffective) {
	int blastoiseNewHP = 0,  blastoiseNewPP = 0, pikachuNewHP = 0, pikachuNewPP = 0;
	char nextTurn = (turn == 'P') ? 'B' : 'P';

	if (turn == 'P') {
		blastoiseNewHP = (isEffective) ? currNode->getBlastoise()->getHP() - attack->getDamage() : currNode->getBlastoise()->getHP();
		blastoiseNewPP = currNode->getBlastoise()->getPP();

		pikachuNewHP = currNode->getPikachu()->getHP();
		pikachuNewPP = currNode->getPikachu()->getPP() + attack->getPP();
	}
	else if (turn == 'B') {
		blastoiseNewHP = currNode->getBlastoise()->getHP();
		blastoiseNewPP = currNode->getBlastoise()->getPP() + attack->getPP();

		pikachuNewHP = (isEffective) ? currNode->getPikachu()->getHP() - attack->getDamage() : currNode->getPikachu()->getHP();
		pikachuNewPP = currNode->getPikachu()->getPP();
	}

	Pokemon* Pikachu = new Pokemon(pikachuNewHP, pikachuNewPP);
	Pokemon* Blastoise = new Pokemon(blastoiseNewHP, blastoiseNewPP);

	float prob = (isEffective) ? CalculateProb(allAttacks, currentLevel, attack->getAccuracy(), currNode->getStats()->getProb())
								: CalculateProb(allAttacks, currentLevel, 100 - attack->getAccuracy(), currNode->getStats()->getProb());

	Stats* stats = new Stats(nextTurn, prob, currentLevel + 1, true);

	Node* newNode = new Node(Pikachu, Blastoise, stats, currNode, attack->getName(), isEffective);
	currNode->addChild(newNode);
	currNode->getStats()->setIsLeaf(false);
}

float CalculateProb(vector<Attack*> attacks, int currentLevel, int attackAccuracy, float parentProb) {
		int availableAttacks = 0;
		for(vector<Attack*>::size_type i = 0; i != attacks.size(); i++)
			if (attacks[i]->getFirstUsage() <= currentLevel)
				availableAttacks++;
		return (1 / (float)availableAttacks) * ((float)attackAccuracy / 100) * parentProb;
}

void ReadFile(string filename, vector<Attack*> *attacks) {
	ifstream pokemonFile(filename);	// opening the file for reading
	bool first_line = true;
	if (pokemonFile.is_open()) {
		string line;
		while( getline(pokemonFile, line) ) {
			stringstream ss(line);

			if (first_line) {		// skip the first line in input file
				first_line = false;
				continue;
			}
			string name, PP, accuracy, damage, firstUsage;
			getline(ss, name, ',');
			getline(ss, PP, ',');
			getline(ss, accuracy, ',');
			getline(ss, damage, ',');
			getline(ss, firstUsage, ',');

			Attack* attack = new Attack(name, stoi(PP), stoi(accuracy), stoi(damage), stoi(firstUsage));
			(*attacks).push_back(attack);
		}
	}
	return;
}
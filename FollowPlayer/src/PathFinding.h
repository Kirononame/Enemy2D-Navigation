#pragma once
#include <string>
#include <algorithm>
#include <string.h>

#include "App.h"

class App;

class PathFinding
{

public:
	PathFinding();
	App* app;

public:

	struct sNode
	{
		bool bObstacle = false;			// Is the node an obstruction?
		bool bVisited = false;			// Have we searched this node before?
		float fGlobalGoal;				// Distance to goal so far
		float fLocalGoal;				// Distance to goal if we took the alternative route
		int x;							// Nodes position in 2D space
		int y;
		std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent;					// Node connecting to this node that offers shortest parent
	};

	sNode *nodes = nullptr;
	int nMapWidth = 15;
	int nMapHeight = 15;

	int nNodeSize = 8;
	int nNodeBorder = 3;

	int nNodeDrawSize = 4;

	sNode *nodeStart = nullptr;
	sNode *nodeEnd = nullptr;

	std::vector<sNode*> wayNodes;
	sNode *way = NULL;

	int nodeNumber = 0;

	int maximumNodes = 0;

	bool astarAlgo = true;
	bool dfsAlgo = false;
	bool bfsAlgo = false;
	bool bfsLocalAlgo = false;
	bool dfsLocalAlgo = false;

	bool vert = false;

	bool enemyMoveCalculate = false;

	bool calculated = false;
	bool wayCalculated = false;

	std::string s;


public:
	bool OnUserCreate();

	float GetX(sNode* s);
	float GetY(sNode* s);

	float GetXFirst();
	float GetYFirst();

	void NextNode();
	bool WayExist();

	bool Solve_AStar();
	bool Solve_DFS();
	bool Solve_BFS();
	bool Solve_DFSLocal();
	bool Solve_BFSLocal();

	void CreateConnections();

	bool OnUserUpdate(float fElapsedTime);

};

#include <iostream>
#include <math.h>

#include "App.h"
#include "AStar.h"

PathFinding::PathFinding()
{
	app = App::getInstance();
}

bool PathFinding::WayExist()
{
	if (way)
		return true;

	return false;
}

float PathFinding::GetX(sNode* s)
{
	return s->x*nNodeSize + nNodeBorder;
}

float PathFinding::GetY(sNode* s)
{
	return s->y*nNodeSize + nNodeBorder;
}

float PathFinding::GetXFirst()
{
	return way->x*nNodeSize + nNodeBorder;
}

float PathFinding::GetYFirst()
{
	return way->y*nNodeSize + nNodeBorder;
}

void PathFinding::NextNode()
{


	if (wayNodes.empty())
	{
		way = NULL;
		return;
	}

	way = wayNodes.back();
	wayNodes.pop_back();

	/*
	way = wayNodes.at(nodeNumber);

	if (nodeNumber >= maximumNodes)
		nodeNumber = maximumNodes;
	else
		nodeNumber++;
	*/
}


bool PathFinding::OnUserCreate()
{

	std::cout << "\nPath Finding Initiating: " << std::endl;

	std::cout << "Enemy Movment Performance hit fix" << std::endl;

	std::cout << "AStar Frame Calculations performance hit fix" << std::endl;

	std::cout << "Set fixed time for astar frame calculations" << std::endl;

	// Create a 2D array of nodes - this is for convenience of rendering and construction
	// and is not required for the algorithm to work - the nodes could be placed anywhere
	// in any space, in multiple dimensions...
	nodes = new sNode[nMapWidth * nMapHeight];
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y * nMapWidth + x].x = x; // ...because we give each node its own coordinates
			nodes[y * nMapWidth + x].y = y;
			nodes[y * nMapWidth + x].bObstacle = false;
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;
		}

	// Create connections - in this case nodes are on a regular grid
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			if (y>0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
			if (y<nMapHeight - 1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
			if (x>0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
			if (x<nMapWidth - 1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

			// We can also connect diagonally
			/*if (y>0 && x>0)
			nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
			if (y<nMapHeight-1 && x>0)
			nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
			if (y>0 && x<nMapWidth-1)
			nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
			if (y<nMapHeight - 1 && x<nMapWidth-1)
			nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
			*/
		}

	// Manually positio the start and end markers so they are not nullptr
	// nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
	// nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth - 2];

	// Enemy position node
	int px = (((int)round(app->enemy->GetX() + app->enemy->GetSize() / 2)) - nNodeBorder) / nNodeSize;
	int py = (((int)round(app->enemy->GetY() + app->enemy->GetSize() / 2)) - nNodeBorder) / nNodeSize;

	nodeStart = &nodes[py * nMapWidth + px];

	// Player position node
	px = (((int)round(app->player->GetX() + app->player->GetSize()/2)) - nNodeBorder) / nNodeSize;
	py = (((int)round(app->player->GetY() + app->player->GetSize()/2)) - nNodeBorder) / nNodeSize;

	nodeEnd = &nodes[py * nMapWidth + px];

	Solve_AStar();

	std::cout << "Path Initiated " << std::endl;

	return true;
}

bool PathFinding::Solve_AStar()
{
	nodeNumber = 0;
	wayNodes.clear();
	maximumNodes = 0;

	// Reset Navigation Graph - default all node states
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y*nMapWidth + x].bVisited = false;
			nodes[y*nMapWidth + x].fGlobalGoal = INFINITY;
			nodes[y*nMapWidth + x].fLocalGoal = INFINITY;
			nodes[y*nMapWidth + x].parent = nullptr;	// No parents
		}

	auto distance = [](sNode* a, sNode* b) // For convenience
	{
		return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
	{
		return distance(a, b);
	};

	// Setup starting conditions
	sNode *nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	// Add start node to not tested list - this will ensure it gets tested.
	// As the algorithm progresses, newly discovered nodes get added to this
	// list, and will themselves be tested later
	std::list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	// if the not tested list contains nodes, there may be better paths
	// which have not yet been explored. However, we will also stop 
	// searching when we reach the target - there may well be better
	// paths but this one will do - it wont be the longest.
	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
	{
		// Sort Untested nodes by global goal, so lowest is first
		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

		// Front of listNotTestedNodes is potentially the lowest distance node. Our
		// list may also contain nodes that have been visited, so ditch these...
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		// ...or abort because there are no valid nodes left to test
		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true; // We only explore a node once


									  // Check each of this node's neighbours...
		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{
			// ... and only if the neighbour is not visited and is 
			// not an obstacle, add it to NotTested List
			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
				listNotTestedNodes.push_back(nodeNeighbour);

			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			// If choosing to path through this node is a lower distance than what 
			// the neighbour currently has set, update the neighbour to use this node
			// as the path source, and set its distance scores as necessary
			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
			}
		}
	}

	return true;
}

bool PathFinding::OnUserUpdate(float fElapsedTime)
{

	// Use integer division to nicely get cursor position in node space
	int nSelectedNodeX = app->GetMouseX() / nNodeSize;
	int nSelectedNodeY = app->GetMouseY() / nNodeSize;

	if (app->GetMouse(0).bReleased) // Use mouse to draw maze, shift and ctrl to place start and end
	{
		if (nSelectedNodeX >= 0 && nSelectedNodeX < nMapWidth)
			if (nSelectedNodeY >= 0 && nSelectedNodeY < nMapHeight)
			{
				//if (app->GetKey(olc::SHIFT).bHeld)
					//nodeStart = &nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX];
				//else if (app->GetKey(olc::CTRL).bHeld)
					//nodeEnd = &nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX];
				//else
				nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle = !nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle;

				Solve_AStar(); // Solve in "real-time" gives a nice effect
			}
	}

	if (app->player->IsMoving())
	{
		int xx = (((int)round(app->player->GetX() + app->player->GetSize()/2)) - nNodeBorder) / nNodeSize;
		int yy = (((int)round(app->player->GetY() + app->player->GetSize()/2)) - nNodeBorder) / nNodeSize;

		nodeEnd = &nodes[yy * nMapWidth + xx];
		Solve_AStar();
	}

	if (app->enemy->IsMoving())
	{
		// Enemy position node
		int xx = (((int)round(app->enemy->GetX() + app->enemy->GetSize() / 2)) - nNodeBorder) / nNodeSize;
		int yy = (((int)round(app->enemy->GetY() + app->enemy->GetSize() / 2)) - nNodeBorder) / nNodeSize;

		nodeStart = &nodes[yy * nMapWidth + xx];

		Solve_AStar();
	}
	
	// Reset Screen to black to draw on it
	app->FillRect(0, 0, app->ScreenWidth(), app->ScreenHeight(), olc::BLACK);

	#if DEBUG

	// Draw Connections First - lines from this nodes position to its
	// connected neighbour node positions
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			for (auto n : nodes[y*nMapWidth + x].vecNeighbours)
			{
				app->DrawLine(x*nNodeSize + nNodeBorder + nNodeDrawSize/2, y*nNodeSize + nNodeBorder + nNodeDrawSize / 2,
					n->x*nNodeSize + nNodeBorder + nNodeDrawSize / 2, n->y*nNodeSize + nNodeBorder + nNodeDrawSize / 2, olc::DARK_BLUE);
			}
		}

	// Draw Nodes on top
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{

			app->FillRect(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder,
				nNodeDrawSize, nNodeDrawSize, nodes[y * nMapWidth + x].bObstacle ? olc::WHITE : olc::DARK_BLUE);
			/*DrawLine(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder,
			(x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder,
			nodes[y * nMapWidth + x].bObstacle ? olc::WHITE : olc::BLUE);*/

			if (nodes[y * nMapWidth + x].bVisited)
				app->FillRect(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, nNodeDrawSize, nNodeDrawSize, olc::MAGENTA);
			//DrawLine(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder, olc::BLUE);

			if (&nodes[y * nMapWidth + x] == nodeStart)
				app->FillRect(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, nNodeDrawSize, nNodeDrawSize, olc::GREEN);
			//DrawLine(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder, olc::GREEN);

			if (&nodes[y * nMapWidth + x] == nodeEnd)
				app->FillRect(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, nNodeDrawSize, nNodeDrawSize, olc::RED);
			//DrawLine(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder, olc::RED);

		}

	#endif


	if (wayNodes.empty())
	{
		// Draw Path by starting ath the end, and following the parent node trail
		// back to the start - the start node will not have a parent path to follow
		if (nodeEnd != nullptr)
		{
			sNode *p = nodeEnd;
			while (p->parent != nullptr)
			{
				maximumNodes++;

				wayNodes.push_back(p);

				app->DrawLine(p->x*nNodeSize + nNodeBorder + nNodeDrawSize / 2, p->y*nNodeSize + nNodeBorder + nNodeDrawSize / 2,
					p->parent->x*nNodeSize + nNodeBorder + nNodeDrawSize / 2, p->parent->y*nNodeSize + nNodeBorder + nNodeDrawSize / 2, olc::YELLOW);

				// Set next node to this node's parent
				p = p->parent;
			}
		}

	}

	else
	{
		for each (sNode* p in wayNodes)
		{
			app->DrawLine(p->x*nNodeSize + nNodeBorder + nNodeDrawSize / 2, p->y*nNodeSize + nNodeBorder + nNodeDrawSize / 2,
				p->parent->x*nNodeSize + nNodeBorder + nNodeDrawSize / 2, p->parent->y*nNodeSize + nNodeBorder + nNodeDrawSize / 2, olc::YELLOW);
		}
	}

	return true;
}


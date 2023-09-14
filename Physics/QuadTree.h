#pragma once

#include <stdio.h>
#include "Box.h"
#include <vector>
#include <inttypes.h>

#define QUADTREE_SIZE 4


/// <summary>
/// Class <c>QuadTree</c> Used to create the Quad Tree structure for Collision Detection.
/// </summary>
class QuadTree
{
public:
	QuadTree(int x, int y, int w, int h);
	~QuadTree();
	int w, h, x, y;
	Box boxes[QUADTREE_SIZE];
	QuadTree* q1 = nullptr;
	QuadTree* q2 = nullptr;
	QuadTree* q3 = nullptr;
	QuadTree* q4 = nullptr;
	void addBox(Box toAdd, int a = 1);
	int removeBox(Box* toRemove, int* ret);
	//void findBox(Box* toFind, int* ret);
	void detectCollision(Box* toDectectWith, void (*func) (Box*, Box*));
	void detectAllCollisions(void (*func) (Box*, Box*));
	int hasSplit = 0;
	int	BoxMap = 0;
private:
	//int numBoxes = 0;
};

int findQuad(int bx, int by, int bw, int bh, int qx, int qy, int qw, int qh);
int checkColl(Box primary, Box secondary);
void printbin(int bin);
extern std::vector<Box> v;

struct findReturn {
	QuadTree* prevTree;
	QuadTree* presTree;
	int quad;
	int boxNum;
};


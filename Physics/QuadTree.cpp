#include "QuadTree.h"

std::vector<Box> v;

QuadTree::QuadTree(int x, int y, int w, int h) {
	this->h = h;
	this->w = w;
	this->x = x;
	this->y = y;
}

QuadTree::~QuadTree() {

}

void QuadTree::addBox(Box toAdd, int a) {
	if (a == 1) {
		printf("adding to vector...\n");
		v.push_back(toAdd);
	}
	if (BoxMap != (~((~0) << QUADTREE_SIZE))) {
		for (int i = 0; i < QUADTREE_SIZE; i++) {
			if (!((1 << i) & BoxMap)) {
				boxes[i] = toAdd;
				BoxMap |= 1 << i;
				break;
			}
		}
	}
	else {
		int q = findQuad(toAdd.x, toAdd.y, toAdd.w, toAdd.h, x, y, w, h);
		if (q & 0b0001) {
			if (q & 0b1000) {
				if (!(hasSplit & 0b1000)) {
					q4 = new QuadTree((x + (w / 2)), y, w / 2, h / 2);
					hasSplit |= 0b1000;
				}
				q4->addBox(toAdd, 0);
				//printf("q4");
			}
			if (q & 0b0100) {
				if (!(hasSplit & 0b0001)) {
					q1 = new QuadTree((x + (w / 2)), (y + (h / 2)), w / 2, h / 2);
					hasSplit |= 0b0001;
				}
				q1->addBox(toAdd, 0);
				//printf("q1");
			}
		}
		if (q & 0b0010) {
			if (q & 0b1000) {
				if (!(hasSplit & 0b0100)) {
					q3 = new QuadTree(x, y, w / 2, h / 2);
					hasSplit |= 0b0100;
				}
				q3->addBox(toAdd, 0);
				//printf("q3");
			}
			if (q & 0b0100) {
				if (!(hasSplit & 0b0010)) {
					q2 = new QuadTree(x, (y + (h / 2)), w / 2, h / 2);
					hasSplit |= 0b0010;
				}
				q2->addBox(toAdd, 0);
				//printf("q2");
			}
		}
	}
}

/// <summary>
/// Used to remove a box which was added to the Quad Tree
/// </summary>
/// <param name="toRemove"> The pointer to the box that needs to be removed </param>
/// <param name="ret"> Used to return if a box was found or not. should be initialized with 0*/</param>
/// <returns></returns>
int QuadTree::removeBox(Box* toRemove, int* ret) {
	int el = 0;
	//printf("Searching boxes...\n");
	//printf("BoxMap: "); printbin(BoxMap);
	for (int i = 0; i < QUADTREE_SIZE; i++) {
		if (BoxMap & (1 << i)) {
			if (boxes[i].addr == toRemove) {
				//printf("found box!\n");
				Box temp;
				boxes[i] = temp;
				BoxMap &= ~(1 << i);
				el = 1;
				*ret = 1;
				break;
			}
		}
	}
	//printf("Recurse into?: %d\n", ! bool(el));
	if (el == 0) {
		int q = findQuad(toRemove->x, toRemove->y, toRemove->w, toRemove->h, x, y, w, h);
		//printf("hasSplit: "); printbin(hasSplit);
		int el1 = 0;
		if ((q & 0b0001) and (el1 == 0)) {
			if ((q & 0b1000) and (el1 == 0)) {
				if (!(hasSplit & 0b1000)) {
					*ret = 0;
					el1 = 1;
				}
				else {
					if (q4->removeBox(toRemove, ret)) {
						delete q4;
						q4 = nullptr;
						hasSplit &= 0b0111;
						//printf("quad deleted\n");
					}
				}
				//printf("q4");
			}
			if ((q & 0b0100) and (el1 == 0)) {
				if (!(hasSplit & 0b0001)) {
					*ret = 0;
					el1 = 1;
				}
				else {
					if (q1->removeBox(toRemove, ret)) {
						delete q1;
						q1 = nullptr;
						hasSplit &= 0b1110;
						//printf("quad deleted\n");
					}
				}
				//printf("q1");
			}
		}
		if ((q & 0b0010) and (el1 == 0)) {
			if ((q & 0b1000) and (el1 == 0)) {
				if (!(hasSplit & 0b0100)) {
					*ret = 0;
					el1 = 1;
				}
				else {
					if (q3->removeBox(toRemove, ret)) {
						delete q3;
						q3 = nullptr;
						hasSplit &= 0b1011;
						//printf("quad deleted\n");
					}
				}
				//printf("q3");
			}
			if ((q & 0b0100) and (el1 == 0)) {
				if (!(hasSplit & 0b0010)) {
					*ret = 0;
					el1 = 1;
				}
				else {
					if (q2->removeBox(toRemove, ret)) {
						delete q2;
						q2 = nullptr;
						hasSplit &= 0b1101;
						//printf("quad deleted\n");
					}
				}
				//printf("q2");
			}
		}
		if (q & 0b0000) {
			*ret = 0;
		}
	}
	if (BoxMap == 0b0000) {
		if (!(q1 or q2 or q3 or q4)) {
			return 1;
		}
	}
	return 0;
}


void QuadTree::detectCollision(Box* toDetectWith, void (*func) (Box*, Box*)) {
	int el = 0;
	//printf("Searching boxes...\n");
	//printf("BoxMap: "); printbin(BoxMap);
	for (int i = 0; i < QUADTREE_SIZE; i++) {
		if (BoxMap & (1 << i)) {
			if (toDetectWith->addr == boxes[i].addr) {
				continue;
			}
 			if (checkColl(*toDetectWith, boxes[i])) {
				printf("collision detected...\n");
				func(toDetectWith, boxes + i);
			}
		}
	}
	//printf("Recurse into?: %d\n", ! bool(el));
	if (el == 0) {
		int q = findQuad(toDetectWith->x, toDetectWith->y, toDetectWith->w, toDetectWith->h, x, y, w, h);
		//printf("hasSplit: "); printbin(hasSplit);
		int el1 = 0;
		if ((q & 0b0001) and (el1 == 0)) {
			if ((q & 0b1000) and (el1 == 0)) {
				if (!(hasSplit & 0b1000)) {
					el1 = 1;
				}
				else {
					q4->detectCollision(toDetectWith, func);
				}
				//printf("q4");
			}
			if ((q & 0b0100) and (el1 == 0)) {
				if (!(hasSplit & 0b0001)) {
					el1 = 1;
				}
				else {
					q1->detectCollision(toDetectWith, func);
				}
				//printf("q1");
			}
		}
		if ((q & 0b0010) and (el1 == 0)) {
			if ((q & 0b1000) and (el1 == 0)) {
				if (!(hasSplit & 0b0100)) {
					el1 = 1;
				}
				else {
					q3->detectCollision(toDetectWith, func);
				}
				//printf("q3");
			}
			if ((q & 0b0100) and (el1 == 0)) {
				if (!(hasSplit & 0b0010)) {
					el1 = 1;
				}
				else {
					q2->detectCollision(toDetectWith, func);
				}
				//printf("q2");
			}
		}
		if (q & 0b0000) {
		}
	}
}

void QuadTree::detectAllCollisions(void(*func)(Box*, Box*))
{
	printf("detecting collisions...\n");
	for (int i = 0; i < v.size(); i++) {
		detectCollision(v.data() + i, func);
		int ret = 0;
		removeBox((v.data() + i)->addr, &ret);
		if (ret == 0) {
			printf("box not detected...%I64u\n", v.size());
		}
		if (ret == 1) {
			printf("box deleted...%I64u\n", v.size());
		}
	}
	printf("done detecting...\n");
	printf("adding box...\n");
	for (int i = 0; i < v.size(); i++) {
		printf("adding...%I64u\n", v.size());
		addBox(v[i], 0);
	}
	printf("done adding...%I64u\n", v.size());
}


int checkColl(Box primary, Box secondary) {
	return !(((primary.x + primary.w >= secondary.x) and (primary.y + primary.h >= secondary.y) and (primary.x >= secondary.x) and (primary.y >= secondary.y)) or
		((secondary.x + secondary.w >= primary.x) and (secondary.y + secondary.h >= primary.y) and (secondary.x >= primary.x) and (secondary.y >= primary.y)));
	//return 0;
}



int findQuad(int bx, int by, int bw, int bh, int qx, int qy, int qw, int qh) {
	int ret = 0;
	if ((bx + bw) >= (qx + (qw / 2))) {
		ret |= 0b0001;
	}
	if (bx <= (qx + (qw / 2))) {
		ret |= 0b0010;
	}
	if ((by + bh) >= (qy + (qh / 2))) {
		ret |= 0b0100;
	}
	if (by <= (qy + (qh / 2))) {
		ret |= 0b1000;
	}
	if ((bx > (qx + qw)) or (by > (qy + qh))) {
		ret = 0b0000;
	}
	if (((bx + bw) < qx) or ((by + bh) < qy)) {
		ret = 0b0000;
	}
	return ret;
}

void printbin(int bin) {
	for (int i = 0; i < 32; i++) {
		if (bin & (1 << (31 - i))) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf("\n");
}
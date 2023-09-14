#include "Box.h"

Box::Box(int x, int y, int w, int h, int uid) {
	this->h = h;
	this->w = w;
	this->x = x;
	this->y = y;
	this->uid = uid;
	this->addr = this;
}

Box::Box() {
	this->h = 0;
	this->w = 0;
	this->x = 0;
	this->y = 0;
	this->uid = 0;
	this->addr = nullptr;
}

Box::~Box() {

}


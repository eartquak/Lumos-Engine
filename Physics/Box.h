#pragma once
class Box
{
public:
	Box(int x, int y, int w, int h, int uid);
	Box();
	~Box();
	int h, w, x, y;
	int uid;
	Box* addr;
};



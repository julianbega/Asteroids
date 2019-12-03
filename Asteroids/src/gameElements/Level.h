#ifndef LEVEL_H
#define LEVEL_H
#include "zones/Zone.h"
class Level
{
private:
	Zone* map1;
public:
	Level();
	~Level();
	void update(Vector2 playerPos, Vector2 lastPosition);
	void draw();

};
#endif



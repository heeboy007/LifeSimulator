#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include"Tile.h"

struct Total
{
	int pro;
	int con1;
	int con2;
};

class MapLoader : Random
{
public:
	
	MapLoader();
	
	void deleteBuffers();
	sf::Image* makeDrawableImage();
	Total totalQuery();
	void updateEntireMap();
	static MapLoader* getInstance();
	
	static sf::Image* s_image;
	
private:
	
	Tile* grid[640][640] = {{0}};
	Total total;
	static bool created;
	static MapLoader* mapinstance;
	
	void updateProducer(int x, int y, Tile* tile, int seed);
	void updateConsumer1(int x, int y, Tile* tile, int seed);
	void updateConsumer2(int x, int y, Tile* tile, int seed);
	
};

#endif // MAP_LOADER_H

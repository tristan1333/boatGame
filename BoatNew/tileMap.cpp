#include "tileMap.h"
#include "tiles.h"
#include "vectors.h"
#include <iostream>
#include <fstream>
#include "LuaContext.hpp"
#include <string>
#define ARB_X 50
#define ARB_Y 50
tilemap::tilemap()
{
	
	tiles = new tile**[ARB_X];//Arbitrary preset number
	for(int x = 0; x <= ARB_X; x++)
	{
		tiles[x] = new tile*[ARB_Y];
		for(int y = 0; y <= ARB_Y;y++)
		{
			tiles[x][y] = new tile(new Vec2(x, y),1,1);
		}
	}
	w = ARB_X;
	h = ARB_Y;
}
tilemap::tilemap(int w, int h)
{
	this->w = w;
	this->h = h;
}

tilemap::tilemap(std::string fil)
{
	std::ifstream file;
	std::string line;
	file.open("MAP.vmf");
	getline(file, line);
	this->w = std::stoi(line);
	getline(file, line);
	this->h = std::stoi(line);
	tiles = new tile**[w];
	for (int x = 0; x <= w; x++)
	{
		tiles[x] = new tile*[h];
		for (int y = 0; y <= h; y++)
		{
			tiles[x][y] = new tile(new Vec2(x, y), 1, 1);
		}
	}
	std::cout << tiles[50][50]->type->id;
	//^^^^^^^ INITIATE THE TILE ARRAY WITH W AND H ^^^^^^^
	while (getline(file, line))
	{
		if (line == "ENDTILES")
		{
			break;
		}
		int x = std::stoi(line);
		getline(file, line);
		int y = std::stoi(line);
		getline(file, line);
		std::string typ = line;
		tiles[x][y]->type->id = typ;
	}
	file.close();
	this->w = w;
	this->h = h;
}
void savTileMap(tilemap* mp)
{
	//set_pieces.clear();
	std::ofstream file;
	file.open("MAP.vmf");
	std::string line;
	file << mp->w << "\n";
	file << mp->h;
	for (int x = 0; x <= mp->w; x++)
	{
		for (int y = 0; y <= mp->h; y++)
		{
			file << "\n";
			file << x;
			file << "\n";
			file << y;
			file << "\n";
			file << mp->tiles[x][y]->type->id.c_str();
		}
	}
	file << "ENDTILES";
	file.close();
}
void init_lua_map(tilemap* mp, LuaContext* L)
{
	std::cout << "map:create(" + std::to_string(mp->w +1) + ", " + std::to_string(mp->h+1) + ")";
	L->executeCode("map:create(" + std::to_string(mp->w +1) + ", " + std::to_string(mp->h+1) + ")");
	for (int x = 0; x <= mp->w; x++)
	{
		for (int y = 0; y <= mp->h; y++)
		{
		//	std::string exCod = "map:setTile(" + std::to_string((x + 1)) + ", " + std::to_string(y + 1) + ", " + "'" + mp->tiles[x][y]->type->id + "')";
		//	std::cout << exCod;
			L->executeCode("map:setTile(" + std::to_string((x)) + ", " + std::to_string(y) + ", " + "'" + mp->tiles[x][y]->type->id + "')");
		}
	}
}

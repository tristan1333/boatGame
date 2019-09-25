#include "events.h"
#include "LuaContext.hpp"
#include "tileMap.h"
#include "tiles.h"
#include <iostream>
eventHandler::eventHandler()
{

}

void eventHandler::handle(LuaContext* L, tilemap * mp)
{
	int size = L->readVariable<int>("tileUpdates", "size");
	//	if (size == 0)
	//	{
	//		return;
		//}

	for (int i = 1; i <= size; i++)
	{
		std::cout << "OHH";
		int x = L->readVariable<int>("tileUpdates", "events", i, "x");
		int y = L->readVariable<int>("tileUpdates", "events", i, "y");
		std::cout << L->readVariable<std::string>("map", "tiles", x + 1, y);
		std::string typ = L->readVariable<std::string>("tileUpdates", "events", i, "tile");
		//std::cout << x << y;
		mp->tiles[x][y]->type->id = typ;
	}
	size = L->readVariable<int>("printUpdates", "size");
	for (int i = 1; i <= size; i++)
	{
		std::cout << L->readVariable<std::string>("printUpdates", "events", i, "text");
	}
	L->executeCode("printUpdates:finish()");
	L->executeCode("tileUpdates:finish()");
}
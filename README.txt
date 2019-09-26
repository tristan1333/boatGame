----------------------------------------------------------
----------------------------------------------------------
STEP 1
--
Program will initiate SDL
This requires 0 file setup
---------------------------------------------------------
---------------------------------------------------------
STEP 2
--
Program will attempt to initialise lua

	**********
	STEP 1
	**********
	Program opens "Scripts/Tiles/tile.lua"
	THIS SETUPS LUA TO LOAD TILES AND MAKES THE REGISTRY!!

	**********
	STEP 2
	**********
	MOVE to load_lua_files
	this will open loadLua.blf
	loadLua.blf loads the reference to the tile reference script
	this is Scripts/Tiles/loadTile.blf
	
	**********
	STEP 3
	**********
	LoadTile.blf opens every single tile file and loads them into lua
	
	**********
	SUMMARY
	**********
	loadLua.blf -> loads loadTiles.blf
	loadTiles.blf -> loads and executes lua files for tiles

--------------------------------------------------------------
---------------------------------------------------------------
STEP 3
--
There is no step 3 currently !
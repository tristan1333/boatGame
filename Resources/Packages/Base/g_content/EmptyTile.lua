emptyTile = tile:create()
emptyTile.id = "emptyTile"
emptyTile.tex = "Resources/Base/Tiles/EmptyTile.png"
tiles:register(emptyTile)
caveFloor = tile:create()
caveFloor.id = "caveFloor"
caveFloor.tex = "Resources/Base/Tiles/caveFloor.png"
function caveFloor:onEnter(x, y, lx, ly, dir)
    --	prnt(map:getTile(x+1,y))
    --	map:changeTile(x+1, y+1, map:getTile(x, y))
end

tiles:register(caveFloor)
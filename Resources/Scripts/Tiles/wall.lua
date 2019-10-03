wallTile = tile:create()
wallTile.id = "wallTile"
wallTile.tex = "Resources/Base/Tiles/caveWall.png"
right = 0
down = 1
left = 2
up = 3
function wallTile:onEnter(x, y, lx, ly, dir) --lx/ly = player absolute floats, x/y = tile coords
    if dir == right then --left
        player.x = x - (player.w + 0.001)
    end
    if dir == left then --right
        player.x = x + 1.0001
    end
    if dir == up then --bottom
        player.y = y + 1.0001
    end
    if dir == down then --top
        player.y = y - (player.h + 0.001)
    end
end

tiles:register(wallTile)

wallTileTwo = tile:create(wallTile)
wallTileTwo.id = "walltwo"
wallTileTwo.tex = "Resources/Base/Tiles/wall.png"

function wallTileTwo:onEnter(x, y, lx, ly, dir)
    wallTileTwo.parent:onEnter(x, y, lx, ly, dir)
    map:changeTile(x + 1, y, "caveFloor")
end

function wallTileTwo:onClick(x,y)
	if player:inRange(x,y) then
	map:changeTile(x+1,y,"walltwo")
	map:changeTile(x-1,y,"walltwo")
	map:changeTile(x-1,y-1,"walltwo")
	map:changeTile(x-1,y+1,"walltwo")
	map:changeTile(x+1,y-1,"walltwo")
	map:changeTile(x+1,y+1,"walltwo")
	map:changeTile(x,y,"caveFloor")
	end
end

tiles:register(wallTileTwo)
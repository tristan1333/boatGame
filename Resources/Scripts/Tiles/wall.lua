wallTile = tile:create()
wallTile.id = "wallTile"
wallTile.tex = "Resources/Base/Tiles/caveWall.png"
right = 0
down = 1
left = 2
up = 3
function wallTile:onEnter(x, y, dir) --lx/ly = player absolute floats, x/y = tile coords
    if dir == right then --left
        player.x = x - 0.53
    end
    if dir == left then --right
        player.x = x + 1.03
    end
    if dir == up then --bottom
        player.y = y + 1.03
    end
    if dir == down then --top
        player.y = y - 0.53
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

tiles:register(wallTileTwo)
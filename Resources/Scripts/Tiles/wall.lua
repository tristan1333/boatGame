wallTile = tile:create()
wallTile.id = "wallTile"
wallTile.tex = "Resources/Base/Tiles/caveWall.png"
right = 0
down = 1
left = 2
up = 3
function wallTile:onEnter(x, y, lx, ly, dir) --lx/ly = player absolute floats, x/y = tile coords
    if dir == right then
        player.x = player.x - ((lx - x) + 0.01)
    end
    if dir == left then
        player.x = player.x + (1 - (lx - x) + 0.01)
    end
    if dir == up then
        player.y = player.y + (1 - (ly - y) + 0.01)
    end
    if dir == down then
        player.y = player.y - ((ly - y) + 0.01)
    end
    --[[if lx > x and player.x < x then
        player.x = player.x - ((lx - x) * 2)
        return
    elseif lx > x and player.x + player.w > x then
        player.x = player.x + ((lx - x) - (player.w*2))
        return
    else if ly > y then
        --player.y = y + 1 + 0.01
        return
    else if ly < y then
        --player:setPos(player.x, y + 1.01)
    end--]]
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
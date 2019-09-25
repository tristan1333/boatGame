map = {w, h}

map.tiles = {}

function map:create(w, h)
	for x=1,w do
		map.tiles[x] = {}
		for y = 1,h do
			map.tiles[x][y] = 0
		end
	end
end

function map:changeTile(x,y, nTile)
	map.tiles[x+1][y+1] = nTile
	tileUpdates:Add(x,y,nTile)
end
function map:setTile(x,y, nTile)
	map.tiles[x+1][y+1] = nTile
end

function map:getTile(x,y)
	return map.tiles[x+1][y+1]
end
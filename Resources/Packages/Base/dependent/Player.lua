player = { x = 0, y = 0, w = .5, h = .5 , reach = 1}
function player:applyx(mv)
    player.x = player.x + mv
end

function player:applyy(mv)
    player.y = mv + player.y
end

function player:setPos(xx, yy)
    player.x = xx
    player.y = yy
end

function player:inRange(x,y)
	local rx = player.x + (player.w/2)
	local ry = player.y + (player.h/2)
	if x < rx + player.reach and x > rx - player.reach and y < ry + player.reach and y > ry - player.reach then
		return true
	end
	return false
end
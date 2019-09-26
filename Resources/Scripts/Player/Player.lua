player = { x = 0, y = 0, w = .5, h = .5 }
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
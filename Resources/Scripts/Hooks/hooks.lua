hooks = {}

tileUpdates = { size = 0 }
tileUpdates.events = {}
function tileUpdates:Add(tx, ty, ttile)
    local evnt = { x = tx, y = ty, tile = ttile }
    table.insert(tileUpdates.events, evnt)
    tileUpdates.size = tileUpdates.size + 1
    --tileUpdates.events.insert(evnt)
    --WE ARE TRYING TO ADD
    --TILE UPDATES SO C++ CAN UPDATE LUA UPDATES
end

printUpdates = { size = 0 }
printUpdates.events = {}

function printUpdates:prnt(txt)
    local evnt = { text = txt }
    table.insert(printUpdates.events, evnt)
    printUpdates.size = printUpdates.size + 1
end

function prnt(txt)
    printUpdates:prnt(txt)
end

function printUpdates:finish()
    printUpdates.events = {}
    printUpdates.size = 0
end

function tileUpdates:finish()
    tileUpdates.events = {}
    tileUpdates.size = 0
end

clickUpdates = { size = 0 }
clickUpdates.events = {}

function clickUpdates:Add(cx, cy)
    local evnt = { x = cx, y = cy }
    table.insert(clickUpdates.events, evnt)
    clickUpdates.size = clickUpdates.size + 1
end

function clickUpdates:Handle()
    for o in clickUpdates.events do
        tiles[map:getTile(math.floor(o.x), math.floor(o.y))]:onClick()
    end
end
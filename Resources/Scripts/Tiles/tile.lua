tile = { id = "tile", tex = "Resources/Base/Tiles/space.png", parent = "tile" }
tiles = {}
tiles.reg = {}

function tiles:register(o)
    if self.reg[o.id] ~= nil then
        print(o.reg.id, " already has been registered inside tiles")
        return
    end
    tiles.reg[o.id] = o
    return
end

function tiles:containedTileKeys()
    keys = {}
    local c = 1
    for k, v in pairs(self.reg) do
        keys[c] = v
        c = c + 1
    end
    return keys
end

function tile:change()
    self.id = "itchanged!"
    return
end

function tile:onEnter(x, y, lx, ly)
end

function tile:onClick(x,y)
end

function tile:create(p)
    local o = {}
    if p ~= nil then
        setmetatable(o, p)

        --p.__index = p
        for k, v in pairs(p) do
            o[k] = v
        end
        o.parent = p
        return o
    end
    setmetatable(o, self)
    self.__index = self
    for k, v in pairs(self) do
        o[k] = v
    end

    return o
end

--[[function tile:create(p)
	local o = tile:create()
	o.parent = p
	return o
end]]

function tile:super()
    return parent
end

tiles:register(tile) --You need to define something, then register it to tiles. 
--Reference as tiles["tile"]
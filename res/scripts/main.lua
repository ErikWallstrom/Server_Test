--[[print('Lua initialized')
engine.window = { 
	title = 'Test Window',
	width = 800,
	height = 600,
	fps = 60
}

local player = require('player')

engine:add_entity(
	player:new(
		engine.window.width / 2, 
		engine.window.height / 2
	)
)

engine:add_entity(
	player:new(
		math.random(0, engine.window.width), 
		math.random(0, engine.window.height)
	)
)]]

player = {
    name = 'Dude',
    x = 6.2,
    y = 8.8,
    w = 90,
    h = 123,
    dead = false,
    inventory = {
        'sword',
        'armor'
    },
    
    start = function()
        
    end
}

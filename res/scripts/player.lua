local player = {
	new = function(self, x, y)
		object = {}
		object.name = 'player'
		object.x = x or 0.0
		object.y = y or 0.0
		object.w = 50
		object.h = 50
		
		for k, v in pairs(self) do
			object[k] = v;
		end
		
		return object
	end,
	
	start = function(self)
		print('start')
	end,
	
	update = function(self)
		print('update')
	end,
	
	graphics_component = {
		file = '../../res/images/TP_1.0_SpriteSheet.png',
		visible = true;
		rotation = 0.0,
		width = 11.0,
		height = 18.0,
		
		animations = {
			test1 = {
				delay = 1000,
				{ 1, 1 },
				{ 1, 2 }
			},
			
			test2 = {
				delay = 1000,
				{ 2, 1 },
				{ 2, 2 }
			}
		}
	},
	
	keyboard_component = {
		key_down = function(self, key)
			print('key_down')
			print(self)
		end,
		
		key_pressed = function(self, key)
			print('key_pressed')
		end,
		
		key_up = function(self, key)
			print('key_up')
		end,
		
		key_released = function(self, key)
			print('key_released')
		end
	},
	
	mouse_component = {
		left_click = function(self, x, y)
			print('left_click')
		end,
		
		right_click = function(self, x, y)
			print('right_click')
		end,
		
		left_down = function(self, x, y)
			print('left_down')
		end,
		
		right_down = function(self, x, y)
			print('right_down')
		end,
		
		left_up = function(self, x, y)
			print('left_up')
		end,
		
		right_up = function(self, x, y)
			print('right_up')
		end
	}
}

return player
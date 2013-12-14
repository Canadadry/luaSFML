require "class"
require "engine/entity"
require "engine/body"
require "engine/physic"
require "sfmlobject/spriteview"
require "sfmlobject/keypad"


Ship = class(Entity:new())

function Ship:init(x,y)
 
 self.body = Body:new(self)
 self.body.x = 400
 self.body.y = 300
 self.body.angle = 180
 self.body.radius = 10
 
 self.physic = Physic:new(self)
 self.physic.drag = 0.9
 
 self.gamepad = KeyPad:new(self)
 self.gamepad.power = 2
 
 
 
 self.view = SpriteView:new(self,"ship.png")
 
 
end
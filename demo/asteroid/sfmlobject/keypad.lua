require "engine/gamepad"
require "SFML"

KeyPad = class(GamePad:new())


function KeyPad:init(entity,speed,power)
    self.entity = entity
    self.rotate = "none"
    self.move = "none"
    self.speed = speed or 10
    self.power = power or 10
end


function KeyPad:update()
    if     self.rotate == "left"  then self.entity.body.angle = self.entity.body.angle - self.speed 
    elseif self.rotate == "right" then self.entity.body.angle = self.entity.body.angle + self.speed 
    end
    
    if     self.move == "forward"  then self.entity.physic:thrust( self.power)
    elseif self.move == "backward" then self.entity.physic:thrust(-self.power) 
    end
    
    print(" rotate " .. self.rotate .. " move ".. self.move)
end

function KeyPad:handleEvent(event)

    if    (event:type() == sfEventType.KeyPressed  and event:key():code() == sfKey.Left  and self.rotate == "none") 
    then  self.rotate = "left" 
    elseif(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Left  and self.rotate == "left") 
    then  self.rotate = "none"
    elseif(event:type() == sfEventType.KeyPressed  and event:key():code() == sfKey.Right and self.rotate == "none") 
    then  self.rotate = "right"
    elseif(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Right and self.rotate == "right") 
    then  self.rotate = "none" 
    
    elseif(event:type() == sfEventType.KeyPressed  and event:key():code() == sfKey.Up   and self.move == "none") 
    then  self.move = "forward" 
    elseif(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Up    and self.move == "forward"  ) 
    then  self.move = "none"
    elseif(event:type() == sfEventType.KeyPressed  and event:key():code() == sfKey.Down  and self.move == "none") 
    then  self.move = "backward"
    elseif(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Down  and self.move == "backward") 
    then  self.move = "none" end
  
end

require "class"
local signal = require "signal"

Entity = class({})

function Entity:init()
    self.onCreated   = signal.new()
    self.onDestroyed = signal.new()
end 

function Entity:handleEvent(event)
    if(self.gamepad) then self.gamepad:handleEvent(event) end
end 


function Entity:update()
    if(self.gamepad) then self.gamepad:update() end
    if(self.physic)  then self.physic:update() end
    if(self.view)    then self.view:update() end
end 

function Entity:destroyed()
    self.onDestroyed.dispatch(self)
end 

function Entity:render()
    if(self.view) then self.view:render() end
end 

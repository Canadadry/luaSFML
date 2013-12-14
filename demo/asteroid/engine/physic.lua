require "class"

Physic = class({drag=1,velocityX=0,velocityY=0})

function Physic:init(entity)
    self.entity = entity
end

function Physic:update()
    self.entity.body.x = self.entity.body.x + self.velocityX;
    self.entity.body.y = self.entity.body.y + self.velocityY;
    
    self.velocityX = self.velocityX * self.drag;
    self.velocityY = self.velocityY * self.drag;
end

function Physic:thrust(power)
    self.velocityX = self.velocityX + math.sin(math.pi-math.rad(self.entity.body.angle)) * power
    self.velocityY = self.velocityY + math.cos(math.pi-math.rad(self.entity.body.angle)) * power
end
require "class"

Body = class({x=0,y=0,angle=0,radius=0})

function Body:init(entity)
    self.entity = entity
end

function Body:testCollision(entity)
    local dx = self.x - entity.body.x;
    local dy = self.y - entity.body.y;
    
    return ((dx * dx) + (dy * dy)) <= (self.radius + otherEntity.body.radius)
end


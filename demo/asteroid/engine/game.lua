require "class"
local signal = require "signal"


Game = class({isPaused=false, entities= {}})

function Game:loop()
    if not self.isPaused then 
        self:forEachEntities("handleEvent")
        self:forEachEntities("update")
    end
        self:forEachEntities("render")
end

function Game:forEachEntities(func, ...)
        local entity = next(self.entities);
    while entity do
        entity[func](entity,...)
        entity = next(self.entities,entity)
    end
end 

function Game:addEntity(entity)
    self.entities[entity] = entity;
end


require "class"
local signal = require "signal"

Health = class({hits=0})

function Health:init(entity)
    self.entity = entity
    self.died = signal.new()
    self.hurt = signal.new()
end

function Health:hit(damage)
    self.hits = self.hits - damage;
    self.hurt.dispatch(self);
    if self.hits < 0 then
        self.died.dispatch(self);
    end
end
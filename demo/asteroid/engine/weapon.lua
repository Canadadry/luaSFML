require "class"

Weapon = class({ammo=0})

function Weapon:init(entity)
    self.entity = entity
end

function Weapon:fire()
    self.ammo = self.ammo - 1;
end
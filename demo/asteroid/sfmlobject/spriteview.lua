require "engine/view"
require "SFML"

SpriteView = class(View:new())

function SpriteView:init(entity,sprite)
    self.entity = entity
    self.texture =  sfTexture.new()
    self.texture:loadFromFile("assets/"..sprite)
    self.sprite = sfSprite.new(self.texture)
    self.sprite:setOrigin(self.texture:getSize()/2)
end

function SpriteView:update()
    self.sprite:setPosition(self.entity.body.x,self.entity.body.y)
    self.sprite:setRotation(self.entity.body.angle)
end

function SpriteView:render()
    window:draw(self.sprite)
end

require "class"

View = class({})

function View:init(entity)
    self.entity = entity
end

function View:update()
    print("updating entity ".. tostring(self));
end



function View:render()
    print("rendering entity ".. tostring(self));
end


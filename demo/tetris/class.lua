function class(cls)
--    local cls = {}
    cls.__index = cls
	cls.new = function (c, ...)
        local instance = setmetatable({}, cls)
		if instance.init then
			instance:init(...)
        end
        return instance
	end
	return cls
end

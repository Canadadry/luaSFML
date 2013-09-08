--require "SFML"
require "class"

Timer = class{clock = nil, loop = false, duration = 1.0,object =nil, trigerFunction = nil,playing = false} 

function Timer:init(func,object)
    self.trigerFunction = func
    self.object= object
    self.clock = sfClock.new()
end


function Timer:update()
    if  not self.playing then return end
    if  self.clock:getElapsedTime():asSeconds() > self.duration then 
        self.clock:restart()
        self.trigerFunction(self.object)
        self.playing = self.loop
    end
end

function Timer:start(duration, loop)
    self.duration  =  duration or self.duration
    self.loop  =  loop or self.repeate
    self.playing = true
    self.clock:restart()
end

function Timer:stop()
    self.playing = false;
end

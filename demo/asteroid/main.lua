require "SFML"
require "engine/game"
require "game/ship"

print("use enum press "..  sfEventType.KeyPressed.. " release " .. sfEventType.KeyReleased .. " left " .. sfKey.Left .. " right "..  sfKey.Right .. " up "..sfKey.Up .. " down ".. sfKey.Down) 

math.randomseed(os.time())

window = sfRenderWindow.new(sfVideoMode.new(800,600,32),"Asteroid",sfWindowStyle.Default);
window:setFramerateLimit(30)
window:setKeyRepeatEnabled(false)

game = Game.new();
ship = Ship:new();
game:addEntity(ship)

clearColor = sfColor.new(0,0,0);

event = sfEvent.new();
while window:isOpen() do
    i = 0;
    while window:pollEvent(event) do
        if(event:type() == sfEventType.Closed) then window:close(); 
        elseif(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Escape ) then window:close(); 
        elseif(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Q and event:key():system() == true ) then window:close(); 
        else game:forEachEntities("handleEvent",event)
        end
    end
    window:clear(clearColor);

    game:forEachEntities("update")
    game:forEachEntities("render")
    window:display();
end


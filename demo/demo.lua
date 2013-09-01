math.randomseed(os.time())

window = sfRenderWindow.new(sfVideoMode.new(640,480,32),"Test",sfWindowStyle.Default);
window:setFramerateLimit(30)


circle = sfRectangleShape.new(sfVector2f.new(30,60));

clearColor = sfColor.new(math.random(256)-1,math.random(256)-1,math.random(256)-1);

event = sfEvent.new();
while window:isOpen() do
    i = 0;
    while window:pollEvent(event) do
    	if(event:type() == sfEventType.Closed) then window:close(); end
    	if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Escape ) then window:close(); end
    	if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Q and event:key():system() == true ) then window:close(); end
    end
    window:clear(clearColor);
    window:draw(circle);
    window:display();
end


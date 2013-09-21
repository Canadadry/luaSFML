

math.randomseed(os.time())

window = sfRenderWindow.new(sfVideoMode.new(640,480,32),"Test",sfWindowStyle.Default);
window:setFramerateLimit(30)


circle = sfeSGItem.new();
circle:move(50,50);
circle:setWidth(100);
circle:setHeight(100);

child1 = sfeSGItem.new(circle);
child1:setWidth(50);
child1:setHeight(50);


clearColor = sfColor.new(math.random(256)-1,math.random(256)-1,math.random(256)-1);

event = sfEvent.new();
while window:isOpen() do
    i = 0;
    while window:pollEvent(event) do
    	if(event:type() == sfEventType.Closed) then window:close(); end
    	if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Escape ) then window:close(); end
    	if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Q and event:key():system() == true ) then window:close(); end
    end

	circle:rotate(1);
	child1:rotate(-2);

    window:clear(clearColor);
	window:draw(circle);
    window:display();
end


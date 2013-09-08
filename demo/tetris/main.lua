require "game"
--require "SFML"
require "timer"

math.randomseed(os.time())


tileSize = 53
zoom= 1

Game.tileChanged = function (x,y,id)
	tilemap:setIDForTile(id,x-1,y-1)
end

Game.stateChanged = function (newState)
	print("state "..newState)
end

window = sfRenderWindow.new(sfVideoMode.new(10*tileSize*zoom,16*tileSize*zoom,32),"Tetris",sfWindowStyle.Titlebar + sfWindowStyle.Close  );
window:setFramerateLimit(30)
window:setKeyRepeatEnabled(false)

texture =  sfTexture.new();
texture:loadFromFile("tetris_tiles-53.png");
texture:setSmooth(true);

tilemap = sfeTileMap.new();
tilemap:setSize(10,16)--game.mapWidth,game.mapHeight);
tilemap:setTexture(texture);
tilemap:setTileSize(tileSize,tileSize);
tilemap:scale(zoom,zoom)

game = Game:new();
clearColor = sfColor.new(0,0,0);
stepTimer = Timer:new(Game.step,game);
stepTimer:start(1,true);

event = sfEvent.new();
while window:isOpen() do
	i = 0;
	while window:pollEvent(event) do
		if(event:type() == sfEventType.Closed) then window:close(); end
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Escape ) then window:close(); end
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Q and event:key():system() == true ) then window:close(); end	
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Left ) then game:moveLeft(); end	
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Right) then game:moveRight(); end	
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Space) then game:rotateRight(); end	
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Down)  then game:step(); end	
	end
	stepTimer:update();
	window:clear(clearColor);
	window:draw(tilemap);
	window:display();
end


require "game"
require "SFML"

math.randomseed(os.time())

startBuffer = sfSoundBuffer.new();
startBuffer:loadFromFile("./sound/start.ogg")
looseBuffer = sfSoundBuffer.new();
looseBuffer:loadFromFile("./sound/loose.ogg")
nothingBuffer = sfSoundBuffer.new();
nothingBuffer:loadFromFile("./sound/nothing.ogg")
winBuffer = sfSoundBuffer.new();
winBuffer:loadFromFile("./sound/win.ogg")
sound = sfSound.new()

function playBuffer(buf)
    sound:stop()
    sound:setBuffer(buf);
    sound:play()
end

playBuffer(startBuffer)

gameParam = {w=15,h=15,m=30}
tileSize = 20
zoom= 1.5
Game.tileChanged = function (x,y,id)
	tilemap:setIDForTile(id,x-1,y-1)
end


Game.stateChanged = function (newState)
    if newState == "win" then playBuffer(winBuffer) end
    if newState == "loose" then playBuffer(looseBuffer) end
    if newState == "playing" then playBuffer(startBuffer) end
end


window = sfRenderWindow.new(sfVideoMode.new(gameParam.w*tileSize*zoom,gameParam.h*tileSize*zoom,32),"Minesweeper",sfWindowStyle.Titlebar + sfWindowStyle.Close  );
window:setFramerateLimit(30)

texture =  sfTexture.new();
texture:loadFromFile("minesweeper.png");
texture:setSmooth(true);

tilemap = sfeTileMap.new();
tilemap:setSize(gameParam.w,gameParam.h);
tilemap:setTexture(texture);
tilemap:setTileSize(tileSize,tileSize);
tilemap:scale(zoom,zoom)

game = Game:new(gameParam.w,gameParam.h,gameParam.m);


--window:setSize(game.mapWidth*tileSize,game.mapHeight*tileSize)
--window:create(sfVideoMode.new(game.mapWidth*tileSize*zoom,game.mapHeight*tileSize*zoom,32),"Minesweeper",sfWindowStyle.Titlebar + sfWindowStyle.Close  )
clearColor = sfColor.new(math.random(256)-1,math.random(256)-1,math.random(256)-1);

event = sfEvent.new();
while window:isOpen() do
	i = 0;
	while window:pollEvent(event) do
		if(event:type() == sfEventType.Closed) then window:close(); end
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Escape ) then window:close(); end
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Q and event:key():system() == true ) then window:close(); end
		if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Space ) then game:restart(); end
		if(event:type() == sfEventType.MouseButtonPressed) then
			if game.state == "playing" then		
    			clickPos = sfMouse.getPositionRelativeto(window);
    			if(event:mouseButton():button() == sfMouseButton.Left) then
    				if game:reveal(math.floor(clickPos:x()/tileSize/zoom)+1,math.floor(clickPos:y()/tileSize/zoom)+1) then if game.state == "playing" then playBuffer(nothingBuffer) end end
    			else
    				game:flag(math.floor(clickPos:x()/tileSize/zoom)+1,math.floor(clickPos:y()/tileSize/zoom)+1)
    				playBuffer(nothingBuffer)
    			end
			end
		end
	end
	window:clear(clearColor);
	window:draw(tilemap);
	window:display();
end


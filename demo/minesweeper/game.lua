require "class"
Game = class({ map, mapWidth, mapHeight, flagLeft, mineFound, mine, state ,tileChanged})

local TileDescription  = { redFlag = 0, blueFlag = 1, mine = 2, redMine = 3, failMine = 4 , water = 5, empty = 6}
local Tile = class({model_mineAround= 0, model_discovered= false, model_flaged=false})

local function shuffleTab(a)
	local j = 0;
	local valI = nil
	local valJ = nil
	local l = table.getn(a)-1;
	while (l > -1) do
		j = 1+math.floor(math.random() * l);
		valI = a[l];
		valJ = a[j];
		a[l] = valJ;
		a[j] = valI;
		l = l - 1;
	end
	return a;
end


function Game:restart()
    self:init(self.mapWidth, self.mapHeight ,self.mine)
end 

function Game:init(w,h,m)
	self.mapWidth = w
	self.mapHeight = h
	self.flagLeft = m
	self.mineFound = 0
	self.mine = m
	self.state = "playing"
	self.tileChanged = nil

	self.map = {}
	for x=1,self.mapWidth do
		self.map[x] = {}
		for y=1,self.mapHeight do
			self.map[x][y] = Tile:new()
		end
	end

	local place = {}
	for i=0,self.mapWidth*self.mapHeight do
		place[i]=i
	end
	shuffleTab(place);
	for i=1,self.mine do
		local x= place[i]%self.mapWidth+1;
		local y= math.floor(place[i]/self.mapWidth)+1;
		self:placeMine(x,y)
	end

	self:allTileChanged()
end

function Game:inBound(x,y)
	return (x>=1 and y>=1 and x<=self.mapWidth and y<=self.mapHeight)
end

function Game:placeMine(x,y)
	if(self:inBound(x,y)) then

		if(self.map[x][y].model_mineAround == 9) then
			return false
		end
		self.map[x][y].model_mineAround=9;
		self:neighbourMinePlaced(x-1,y-1);
		self:neighbourMinePlaced(x  ,y-1);
		self:neighbourMinePlaced(x+1,y-1);
		self:neighbourMinePlaced(x-1,y  );
		self:neighbourMinePlaced(x+1,y  );
		self:neighbourMinePlaced(x-1,y+1);
		self:neighbourMinePlaced(x  ,y+1);
		self:neighbourMinePlaced(x+1,y+1);
		return true
	end
	return false
end

function Game:neighbourMinePlaced(x,y)
	if(self:inBound(x,y)) then
		if self.map[x][y].model_mineAround == 9 then
			return
		end

		self.map[x][y].model_mineAround = self.map[x][y].model_mineAround+1

	end

end

function Game:flag(x,y)
	local ret = false
	if(self:inBound(x,y)) then
		local gameBox = self.map[x][y]
		if(	gameBox.model_discovered == false ) then
			if(self.flagLeft == 0 and gameBox.model_flaged == false) then
					return ret
			end
			ret = true
			if gameBox.model_flaged then
				self.flagLeft = self.flagLeft+1
			else
				self.flagLeft = self.flagLeft-1
			end

			gameBox.model_flaged = not gameBox.model_flaged;

			if(gameBox.model_mineAround == 9) then

				if gameBox.model_flaged then
					self.mineFound = self.mineFound+1
				else
					self.mineFound = self.mineFound-1
				end

				if(self.mineFound == self.mine) then
					self.state = "win"
					game:allTileChanged()
				end
			end

			if(self.tileChanged) then self.tileChanged(x,y,game:tileFromModel(self.map[x][y])); end
		end
	end
end


function Game:reveal(x,y)
	local ret = false
	if(self:inBound(x,y)) then

		local gameBox = self.map[x][y]
		if 	gameBox.model_discovered == false  then
			if gameBox.model_flaged then return ret end
			gameBox.model_discovered = true
			ret = true

			if(gameBox.model_mineAround == 9) then
				gameBox.model_discovered = true
				self.state = "loose"
				game:allTileChanged()
			elseif(gameBox.model_mineAround == 0) then
				self:revealAround(x,y);
			end

			if(self.tileChanged) then self.tileChanged(x,y,game:tileFromModel(self.map[x][y])); end
		end
	end

	return ret;
end

function Game:revealAround(x,y)
	if(self:inBound(x,y)) then
		self:reveal(x-1,y-1);
		self:reveal(x  ,y-1);
		self:reveal(x+1,y-1);
		self:reveal(x-1,y  );
		self:reveal(x+1,y  );
		self:reveal(x-1,y+1);
		self:reveal(x  ,y+1);
		self:reveal(x+1,y+1);
	end
end

function Game:allTileChanged()
	if(self.tileChanged) then
		for x=1,self.mapWidth do
			for y=1,self.mapHeight do
				self.tileChanged(x,y,self:tileFromModel(self.map[x][y]));
			end
		end
	end
	if(self.stateChanged) then self.stateChanged(self.state); end
end

function Game:tileFromModel(model)
	local id = model.model_mineAround

	if self.state == "playing" then

		if model.model_discovered then
			return id+TileDescription.empty
		elseif model.model_flaged then
			return TileDescription.redFlag
		else
			return TileDescription.water
		end

	else
		if not model.model_flaged then
			if id == 0 then
				return TileDescription.empty
			elseif id == 9 then
				if model.model_discovered then
					return  TileDescription.redMine
				else
					return TileDescription.mine
				end
			else
				return id+TileDescription.empty
			end
		elseif id == 9 then
			return TileDescription.redFlag
		else
			return TileDescription.failMine
		end
	end
end

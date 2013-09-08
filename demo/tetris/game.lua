require "class"

Game = class{map = {}, state="stop" , w =10, h =16, currentTetrimino = nil};


function deepcopy(orig)
    local orig_type = type(orig)
    local copy
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in next, orig, nil do
            copy[deepcopy(orig_key)] = deepcopy(orig_value)
        end
        setmetatable(copy, deepcopy(getmetatable(orig)))
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

function transpose(tab)
    local copy = {}
    h = table.getn(tab[1])
    w = table.getn(tab)
    
    for x=1,h do
		copy[x] = {}
		for y=1,w do
			copy[x][y] = tab[y][h-x+1]
		end
	end
    return copy
end

function tprint (tbl, indent)
  if not indent then indent = 0 end
  for k, v in pairs(tbl) do
    formatting = string.rep("  ", indent) .. k .. ": "
    if type(v) == "table" then
      print(formatting)
      tprint(v, indent+1)
    else
      print(formatting .. v)
    end
  end
end

local tetriminoList = { -- I
                        {{1},
                         {1},
                         {1},
                         {1}},
                        -- J
                        {{0,1},
                         {0,1},
                         {1,1}},
                        -- L
                        {{1,0},
                         {1,0},
                         {1,1}},  
                        -- O
                        {{1,1},
                         {1,1}}, 
                        -- S
                        {{0,1,1},
                         {1,1,0}},
                        -- Z
                        {{1,1,0},
                         {0,1,1}},
                        -- T
                        {{0,1,0},
                         {1,1,1}},
                    }

local tetriminoCount = 7                    


local Tetrimino = class{map = nil ,w=2,h=2, id = 1, col = 0, row = 0}

function Tetrimino:init()
    self.id = math.random(tetriminoCount)
    self.map = deepcopy(tetriminoList[self.id])
    self.h = table.getn(self.map[1])
    self.w = table.getn(self.map)
    
end 

function Game:init()
    for x=1,self.w do
		self.map[x] = {}
		for y=1,self.h do
			self.map[x][y] = 0
			self:onTileChanged(x,y,0);
		end
	end
	self:newTetrimino() 
	self.state="play"
	

end

function Game:newTetrimino()
	self.currentTetrimino = Tetrimino:new()
	self.currentTetrimino.col=4
	self:drawTetrimino()
end

function Game:clearDrawTetrimino()
    local tetrimino=self.currentTetrimino
    for x=1,tetrimino.w do
		for y=1,tetrimino.h do
			if tetrimino.map[x][y] == 1 then self:onTileChanged(x+tetrimino.col,y+tetrimino.row,0) end
		end
	end
end

function Game:drawTetrimino()
    local tetrimino=self.currentTetrimino
    for x=1,tetrimino.w do
		for y=1,tetrimino.h do
			if tetrimino.map[x][y] == 1 then self:onTileChanged(x+tetrimino.col,y+tetrimino.row,tetrimino.id) end
		end
	end
end

function Game:step()
    if self.state ~= "play" then return end
    self.currentTetrimino.row = self.currentTetrimino.row+1; 
    if self:checkCollision() == "free"  then
        self.currentTetrimino.row = self.currentTetrimino.row-1; 
        self:clearDrawTetrimino()
        self.currentTetrimino.row = self.currentTetrimino.row+1; 
        self:drawTetrimino()
    else
        self.currentTetrimino.row = self.currentTetrimino.row-1; 
        game:placeTetrimino() 
        if self:checkCollision() ~= "free"  then
            self.state = "stop";
        else 
            self:checkLine()
        end
        
    end
end

function Game:checkLine()

    local completedOnce = false
    for y=1,self.h do
        local completed = true
		for x=1,self.w do
        	if self.map[x][y] == 0 then completed=false end
		end
		if completed then
		   self:removeLine(y)
		   completedOnce = true
		end
	end
	
	if completedOnce then self:allTileChanged() end
end

function Game:removeLine(line)
		for x=1,self.w do
        	table.remove(self.map[x],line)
        	table.insert(self.map[x],1,0) 
		end
end

function Game:placeTetrimino()
    local tetrimino=self.currentTetrimino
    for x=1,tetrimino.w do
		for y=1,tetrimino.h do
        	if tetrimino.map[x][y] == 1 then self.map[x+tetrimino.col][y+tetrimino.row] =  tetrimino.id end
		end
	end
	self:newTetrimino()
end

function Game:checkCollision()
    local tetrimino=self.currentTetrimino
    for x=1,tetrimino.w do
		for y=1,tetrimino.h do
		    if self:validPos(x+tetrimino.col,y+tetrimino.row) then
       			if tetrimino.map[x][y] == 1 and self.map[x+tetrimino.col][y+tetrimino.row] > 0 then return "collide" end
       		else
       			return "out"
       		end
		end
	end
	return "free"
end

function Game:rotateLeft()
    self:rotateRight()
end

function Game:rotateRight()
    if self.state ~= "play" then return end

    self:clearDrawTetrimino()
    
    local tetrimino=self.currentTetrimino
    tetrimino.map = transpose(tetrimino.map)
    tetrimino.w = table.getn(tetrimino.map)
    tetrimino.h = table.getn(tetrimino.map[1])
    
    local inc = -1
    if(tetrimino.col < self.w/2) then inc = 1 end

    while self:checkCollision() == "out" do 
        tetrimino.col = tetrimino.col+inc; 
    end
    
    while self:checkCollision() == "collide" do 
        tetrimino.col = tetrimino.row-1; 
    end
        
    self:drawTetrimino()
        
end

function Game:moveLeft()  
    if self.state ~= "play" then return end

    self.currentTetrimino.col = self.currentTetrimino.col-1; 
    if self:checkCollision() == "free" then
        self.currentTetrimino.col = self.currentTetrimino.col+1; 
        self:clearDrawTetrimino()
        self.currentTetrimino.col = self.currentTetrimino.col-1; 
        self:drawTetrimino()
    else        
        self.currentTetrimino.col = self.currentTetrimino.col+1; 
    end
end

function Game:moveRight()
    if self.state ~= "play" then return end

    self.currentTetrimino.col = self.currentTetrimino.col+1; 
    if self:checkCollision() == "free"  then
        self.currentTetrimino.col = self.currentTetrimino.col-1; 
        self:clearDrawTetrimino()
        self.currentTetrimino.col = self.currentTetrimino.col+1; 
        self:drawTetrimino()    
     else        
        self.currentTetrimino.col = self.currentTetrimino.col-1; 
    end
end

function Game:validPos(x,y)
    if self.map[x]    == nil then return false end
    if self.map[x][y] == nil then return false end
    return true
end

function Game:allTileChanged()
	if(self.tileChanged) then
		for x=1,self.w do
			for y=1,self.h do
				self.tileChanged(x,y,self.map[x][y]);
			end
		end
	end
end

function Game:onTileChanged(x,y,id)
	if(self.tileChanged) then
	  self.tileChanged(x,y,id);
    end
end
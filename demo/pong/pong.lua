math.randomseed(os.time())

-- Define some constants
pi = 3.14156535
gameWidth = 800;
gameHeight = 600;
paddleSize = sfVector2f.new(25, 100);
ballRadius = 10;
colorWhite = sfColor.new(255, 255, 255)
colorBlack = sfColor.new(  0,   0,   0)
colorLeft  = sfColor.new(100, 100, 200)
colorRight = sfColor.new(200, 100, 100)

-- Create the window of the application
window = sfRenderWindow.new(sfVideoMode.new(gameWidth, gameHeight,32), "SFML Lua Pong",sfWindowStyle.Default);
window:setVerticalSyncEnabled(true);


-- Create the left paddle
leftPaddle = sfRectangleShape.new(paddleSize - sfVector2f.new(3, 3));
leftPaddle:setOutlineThickness(3);
leftPaddle:setOutlineColor(colorBlack);
leftPaddle:setFillColor(colorLeft);
leftPaddle:setOrigin(paddleSize / 2);

-- Create the right paddle
rightPaddle = sfRectangleShape.new(paddleSize - sfVector2f.new(3, 3));
rightPaddle:setOutlineThickness(3);
rightPaddle:setOutlineColor(colorBlack);
rightPaddle:setFillColor(colorRight);
rightPaddle:setOrigin(paddleSize / 2);

-- Create the ball
ball = sfCircleShape.new(ballRadius - 3);
ball:setOutlineThickness(3);
ball:setOutlineColor(colorBlack);
ball:setFillColor(colorWhite);
ball:setOrigin(ballRadius/2,ballRadius/2);

-- Load the text font
font = sfFont.new() ;
font:loadFromFile("sansation.ttf")

-- Initialize the pause message
pauseMessage = sfText.new("",font,40);
pauseMessage:setPosition(170, 150);
pauseMessage:setColor(colorWhite);
pauseMessage:setString("Welcome to SFML pong!\nPress space to start the game");

-- Define the paddles properties
AITimer           = sfClock.new();
AITime            = sfTime.seconds(0.1);
paddleSpeed       = 400;
rightPaddleSpeed  = 0;
ballSpeed         = 400;
ballAngle         = 0

clock = sfClock.new()
isPlaying = false;
event = sfEvent.new()

while window:isOpen() do
    -- Handle events
    while window:pollEvent(event) do
	if(event:type() == sfEventType.Closed) then window:close(); break; end
	if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Escape ) then window:close();  break; end
	if(event:type() == sfEventType.KeyReleased and event:key():code() == sfKey.Q and event:key():system() == true ) then window:close();  break; end


	-- Space key pressed: play
	 if(event:type() == sfEventType.KeyPressed and event:key():code() == sfKey.Space ) then
	    if  not isPlaying then
		-- (re)start the game
		isPlaying = true;
		clock:restart();

		-- Reset the position of the paddles and ball
		leftPaddle:setPosition(10 + paddleSize:x() / 2, gameHeight / 2);
		rightPaddle:setPosition(gameWidth - 10 - paddleSize:x() / 2, gameHeight / 2);
		ball:setPosition(gameWidth / 2, gameHeight / 2)

		-- Reset the ball angle
		repeat
		    -- Make sure the ball initial angle is not too much vertical
		    ballAngle = math.rad(math.random(360));

		until (math.abs(math.cos(ballAngle)) > 0.7);
	    end
	end
    end

    if isPlaying then
	deltaTime = clock:restart():asSeconds();

	-- Move the player's paddle
	if sfKeyboard.isKeyPressed(sfKey.Up) and (leftPaddle:getPosition():y() - paddleSize:y() / 2 > 5) then
	    leftPaddle:move(0, -paddleSpeed * deltaTime);
	end
	if sfKeyboard.isKeyPressed(sfKey.Down) and (leftPaddle:getPosition():y() + paddleSize:y() / 2 < gameHeight - 5) then
	    leftPaddle:move(0, paddleSpeed * deltaTime)
	end

	-- Move the computer's paddle
	if (((rightPaddleSpeed < 0 ) and (rightPaddle:getPosition():y() - paddleSize:y() / 2 > 5)) or
	    ((rightPaddleSpeed > 0) and (rightPaddle:getPosition():y() + paddleSize:y() / 2 < gameHeight - 5))) then

	    rightPaddle:move(0, rightPaddleSpeed * deltaTime)
	end

	-- Update the computer's paddle direction according to the ball position
	if (AITimer:getElapsedTime() > AITime) then
	    AITimer:restart()
	    if (ball:getPosition():y() + ballRadius > rightPaddle:getPosition():y() + paddleSize:y() / 2) then
		rightPaddleSpeed = paddleSpeed;
	    elseif (ball:getPosition():y() - ballRadius < rightPaddle:getPosition():y() - paddleSize:y() / 2) then
		rightPaddleSpeed = -paddleSpeed;
	    else
		rightPaddleSpeed = 0 ;
	    end
	end

	-- Move the ball
	factor = ballSpeed * deltaTime;
	ball:move(math.cos(ballAngle) * factor , math.sin(ballAngle) * factor)

	-- Check collisions between the ball and the screen
	if (ball:getPosition():x() - ballRadius < 0) then

	    isPlaying = false;
	    pauseMessage:setString("You lost !\nPress space to restart or\nescape to exit");
	end
	if (ball:getPosition():x() + ballRadius > gameWidth) then
	    isPlaying = false
	    pauseMessage:setString("You won !\nPress space to restart or\nescape to exit");
	end
	if (ball:getPosition():y() - ballRadius < 0) then
	    ballAngle = -ballAngle;
	    ball:setPosition(ball:getPosition():x(), ballRadius + 0.1)
	end
	if (ball:getPosition():y() + ballRadius > gameHeight) then
	    ballAngle = -ballAngle;
	    ball:setPosition(ball:getPosition():x(), gameHeight - ballRadius - 0.1)
	end

	-- Check the collisions between the ball and the paddles
	-- Left Paddle
	if (ball:getPosition():x() - ballRadius <  leftPaddle:getPosition():x() + paddleSize:x() / 2   and
	    ball:getPosition():x() - ballRadius >  leftPaddle:getPosition():x()                      and
	    ball:getPosition():y() + ballRadius >= leftPaddle:getPosition():y() - paddleSize:y() / 2   and
	    ball:getPosition():y() - ballRadius <= leftPaddle:getPosition():y() + paddleSize:y() / 2)  then
	    if (ball:getPosition():y() > leftPaddle:getPosition():y()) then
		ballAngle = pi - ballAngle + math.rad(math.random(20));
	    else
		ballAngle = pi - ballAngle - math.rad(math.random(20));
	    end
	    ball:setPosition(leftPaddle:getPosition():x() + ballRadius + paddleSize:x() / 2 + 0.1, ball:getPosition():y())
	end

	-- Right Paddle
	if (ball:getPosition():x() + ballRadius >  rightPaddle:getPosition():x() - paddleSize:x() / 2 and
	    ball:getPosition():x() + ballRadius <  rightPaddle:getPosition():x()                      and
	    ball:getPosition():y() + ballRadius >= rightPaddle:getPosition():y() - paddleSize:y() / 2 and
	    ball:getPosition():y() - ballRadius <= rightPaddle:getPosition():y() + paddleSize:y() / 2) then

	    if (ball:getPosition():y() > rightPaddle:getPosition():y()) then
		ballAngle = pi - ballAngle --+ (std::rand() % 20) * pi / 180;
	    else
		ballAngle = pi - ballAngle --- (std::rand() % 20) * pi / 180;
	    end
	    ball:setPosition(rightPaddle:getPosition():x() - ballRadius - paddleSize:x() / 2 - 0.1, ball:getPosition():y())
	end
    end

    -- Clear the window
    window:clear(colorBlack);

    if (isPlaying) then
	-- Draw the paddles and the ball
	window:draw(leftPaddle);
	window:draw(rightPaddle);
	window:draw(ball);
    else
	-- Draw the pause message
	window:draw(pauseMessage);
    end
    -- Display things on screen
    window:display()
end


#require "ws2812.class.nut:2.0.1"

function rand()
{
	return 1.0 * math.rand() / RAND_MAX;
}

function randRange(min, max)
{
	return rand() * (max - min) + min;
}

function changeState()
{
	server.log("change");
	for (local i = 0 ; i < 60 ; ++i) 
	{
		local red = randRange(5, 50)
		local green;
		local blue;
		if (red < 10)
		{
			green = 0;
			blue = 0;
		}
		else
		{
			green = randRange(0, 5);
			blue = randRange(0, 5);
		}
		local color = [red, green, blue];
		pixels.set(i, color);
	}
	pixels.draw();
	imp.wakeup(3.0, changeState)
}

server.log("start");
 
spi <- hardware.spi257;
spi.configure(MSB_FIRST, 7500);
pixels <- WS2812(spi, 60);

server.log("ready");

changeState();

//pixels.set(0, [20, 0, 0]);
//pixels.set(1, [0, 20, 0]);
//pixels.fill([20, 2, 2], 0, 59)


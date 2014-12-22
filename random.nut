// XmasChain

// http://electricimp.com/docs/examples/pwm-led/
// http://electricimp.com/docs/api/hardware/pin/configure/#toc_11

function rand()
{
    return 1.0 * math.rand() / RAND_MAX;
}

function setVolume(led, volume)
{
    led.write(volume);
}

function setRandVolume(led, max)
{
    local volume = max * rand();
    server.log(format("max value = %f, random = %f", max, volume));
    setVolume(led, volume);
}

server.log("start initialization");

ledWhite <- hardware.pin7;
ledBlueLeft <- hardware.pin8;
ledBlueRight <- hardware.pin9

frequency <- 400;
period <- 1.0 / frequency;

ledWhite.configure(PWM_OUT, period, 0.0);
ledBlueLeft.configure(PWM_OUT, period, 0.0);
ledBlueRight.configure(PWM_OUT, period, 0.0);

function run()
{
    setRandVolume(ledBlueLeft, 10 / 256.0);
    setRandVolume(ledBlueRight, 10 / 256.0)
    setRandVolume(ledWhite, 50 / 256.0)
    imp.wakeup(10, run);
}

server.log("initialization done");
run()


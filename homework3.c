#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 1;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.
    unsigned char buttonStatus = UNPRESSED;
    bool completeDebounce = false;

    //These will turn the LEDs off because the previous programming
    //in the microboard was messing up the LEDs for this program.
    turnOff_LaunchpadLED2Red();
    turnOff_LaunchpadLED2Green();
    turnOff_LaunchpadLED2Blue();
    turnOff_BoosterpackLEDRed();
    turnOff_BoosterpackLEDGreen();
    turnOff_BoosterpackLEDBlue();

    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);


    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if(timer0Expired())
        {
            if(count0 >= MAX_COUNT)
            {
                count0 = 0;
            }
            else
            {
                count0++;
            }
        }



        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if(timer1Expired())
        {
            buttonStatus = checkStatus_BoosterpackS1();
        }


        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        completeDebounce = fsmBoosterpackButtonS1(buttonStatus);


        // TODO: If a completed, debounced button press has occurred, increment count1.
        if(completeDebounce)
        {
            if(count1 >= MAX_COUNT)
            {
                count1 = 0;
            }
            else
            {
                count1++;
            }
        }


    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    if(count == OFF)
    {
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
    }
    else if(count == RED)
    {
        turnOn_LaunchpadLED2Red();
    }
    else if(count == GREEN)
    {
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
    }
    else if(count == YELLOW)
    {
        turnOn_LaunchpadLED2Red();
    }
    else if(count == BLUE)
    {
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
    }
    else if(count == MAGENTA)
    {
        turnOn_LaunchpadLED2Red();
    }
    else if(count == CYAN)
    {
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
    }
    else if(count == WHITE)
    {
        turnOn_LaunchpadLED2Red();
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    if(count == OFF)
    {
        turnOff_BoosterpackLEDRed();
        turnOff_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDBlue();
    }
    else if(count == RED)
    {
        turnOn_BoosterpackLEDRed();
    }
    else if(count == GREEN)
    {
        turnOff_BoosterpackLEDRed();
        turnOn_BoosterpackLEDGreen();
    }
    else if(count == YELLOW)
    {
        turnOn_BoosterpackLEDRed();
    }
    else if(count == BLUE)
    {
        turnOff_BoosterpackLEDRed();
        turnOff_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDBlue();
    }
    else if(count == MAGENTA)
    {
        turnOn_BoosterpackLEDRed();
    }
    else if(count == CYAN)
    {
        turnOff_BoosterpackLEDRed();
        turnOn_BoosterpackLEDGreen();
    }
    else if(count == WHITE)
    {
        turnOn_BoosterpackLEDRed();
    }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    bool pressed = false;
    static char action = UNPRESSED;

    switch(action)
    {
        case UNPRESSED:
            if(buttonhistory == PRESSED)
            {
                action = PRESSED;
            }
            break;
        case PRESSED:
            if(buttonhistory != PRESSED)
            {
                pressed = true;
                action = UNPRESSED;
            }
            break;
    }

    return pressed;
}

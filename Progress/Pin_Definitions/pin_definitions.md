# Intro
The goal of this example is to showcase how GPIO pin functions can be defined through arduino code and through register configuration.

In this example, pin D12 and D11 are connected to a pushbuttons leading to GND.

## Basic
We can start with a basic arduino sketch.

We will need to configure D12 to have an internal pullup resistor to prevent the pin from floating when it is not connected to GND through the pushbutton.
In this configuration, the state of the pin will be inverse to the state of the button (pressed = 0, released = 1)

@@include|basic/basic.ino|all|//||C|

The above example allows us to push the button to activate the board's built-in LED.

STM32duino's `pinMode()` function does a few things:
1. Get the pin's GPIO port X and pin number N (PX_N)
2. Enable GPIO port X's clock
3. Set the GPIO port speed
4. For certain MCU families, handle alternative pin functions
5. Appropriately modify the port's pin mode register
6. Appropriately modify the port's pullup register

And does so every time the function is called.

However, things like enabling the port's clock/setting it's speed only have to be done once. 
So, if we wished to simplify compiled code, we could omit calling `pinMode()` and instead configure pins from ports which we have already enabled through their registers.

Pins D12 and D11 translate to PB_4 and PB_5 respectively. So we can avoid reconfiguring port B once it's already been enabled:

@@include|basic_morepins/basic_morepins.ino|all|//||C|

The above example will alternatively get PB_4 and PB_5's state and write it to the LED.
# **Infrared Tripwire Wiring**

## Receiver  
Battery -> JST 2.0 connector(on ESP32)  
**Receiver**  
3V3 -> VS1838B VCC  
GND -> VS1838B GND  
VS1838B OUT -> GPIO 4 (beam detect: HIGH = broken, LOW = beam present)  

**LEDS, button**  
GPIO 16 -> 100Ω -> Green LED → GND  
GPIO 17 -> 100Ω -> Red LED → GND  
GPIO 18 -> Button leg A -> Button leg B → GND  

## Transmitter  
Battery -> JST 2.0 connector(on ESP32)  
**Transmitter**  
VCC  ->  ESP32 3.3V  
GND  ->  ESP32 GND  
DAT  ->  ESP32 GPIO 5  

**LED, button**  
GPIO 16 -> 100Ω → Green LED (status)  
GPIO 18 -> Button → GND  

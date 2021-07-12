Bluetooth Communiation(HC-05) Test

 Hardware Required:

 1, Arduino Mega 2560 Board
 2, Bluetooth Module (HC-05)
 3, 5v to 3.3v Level Shifter
 

Connection:

HC-05    ->      Level Shifter       ->  Arduino Mega Board

TX      ->        LV1 | HV1         ->     RX2
RX      ->        LV2 | HV2         ->     TX2
Vcc     ->            HV            ->     5V
GND     ->            GND           ->     GND
                      LV            ->     3.3V  

Note: 

    USART0: Terminal Console 
    USART2: BLE Communiation
    
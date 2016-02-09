/*
    Example for CupDrone
    Modified by Baram 2015. 8.22

    BOARD_LED0_PIN
    BOARD_LED1_PIN

    BOARD_PWM_M0 
    BOARD_PWM_M1
    BOARD_PWM_M2
    BOARD_PWM_M3    
*/



#define LED_PIN BOARD_LED0_PIN




bool blinkState = false;

void setup() 
{

    HwI2C.begin();
    
    SerialUSB.begin();

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);

    pinMode( BOARD_PWM_M0, PWM );
    pinMode( BOARD_PWM_M1, PWM );
    pinMode( BOARD_PWM_M2, PWM );
    pinMode( BOARD_PWM_M3, PWM );
}


void loop() 
{
	analogWrite( BOARD_PWM_M0, 1000 );
	analogWrite( BOARD_PWM_M1, 0 );
	analogWrite( BOARD_PWM_M2, 0 );
	analogWrite( BOARD_PWM_M3, 0 );


    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}


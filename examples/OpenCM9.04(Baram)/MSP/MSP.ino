/*
    Example for CupDrone
    Modified by Baram 2015. 8.22
*/
#include "MSP_Cmd.h"
#include "MSP.h"



MSP		Remote;


void setup() 
{
	SerialUSB.begin();
	Remote.begin(2);
}


void loop() 
{
	if( Remote.update() == true )
	{		
		SerialUSB.print( Remote.Get_Roll() ); 		SerialUSB.print( "\t" );
		SerialUSB.print( Remote.Get_Pitch() ); 		SerialUSB.print( "\t" );
		SerialUSB.print( Remote.Get_Yaw() ); 		SerialUSB.print( "\t" );
		SerialUSB.print( Remote.Get_Throtle() ); 	SerialUSB.print( "\t" );
		SerialUSB.println(" ");

	}
}

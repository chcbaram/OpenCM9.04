//----------------------------------------------------------------------------
//    프로그램명 	: 
//
//    만든이     	: Cho Han Cheol 
//
//    날  짜     : 
//    
//    최종 수정  	: 
//
//    MPU_Type	: 
//
//    파일명     	: MSP_Cmd.ino
//----------------------------------------------------------------------------




#include <Arduino.h> 

#include "MSP.h"











/*---------------------------------------------------------------------------
     TITLE   : MSP_Cmd
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
MSP::MSP()
{
	Cmd 	   = 0x00;
	ArmMode    = false;
	CmdRoll    = 0;
	CmdPitch   = 0;
	CmdYaw     = 0;;
	CmdThrotle = 0;
}





/*---------------------------------------------------------------------------
     TITLE   : begin
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void MSP::begin( uint8_t uart_num )
{
	MspCmd.begin( uart_num );	
}





/*---------------------------------------------------------------------------
     TITLE   : update
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
bool MSP::update( void )
{
    bool Ready_Cmd = false;


    Ready_Cmd = MspCmd.update();


    //-- 명령어 처리 
    //
    if( Ready_Cmd == true )
    {
        pCmd  = MspCmd.Get_CmdPtr();
        pResp = MspCmd.Get_RespPtr();
        
        switch( pCmd->Cmd )
        {
            case MSP_SET_RAW_RC_TINY:
    			CmdRoll     = 1000 + pCmd->Data[0] * 4 - 1500;
    			CmdPitch    = 1000 + pCmd->Data[1] * 4 - 1500;
    			CmdYaw      = 1000 + pCmd->Data[2] * 4 - 1500;
    			CmdThrotle  = 1000 + pCmd->Data[3] * 4 - 1000;
                break;

            case MSP_ARM:
                ArmMode = true;
                break;

            case MSP_DISARM:
                ArmMode = false;
                break;

            default:
                pResp->Cmd       = pCmd->Cmd;
                pResp->ErrorCode = 0x00;
                pResp->Length    = 0;
                MspCmd.SendResp( pResp );
                break;
        }
        
        Cmd = pCmd->Cmd;
    }

    if( ArmMode == false )
    {
    	CmdRoll     = 0;
    	CmdPitch    = 0;
    	CmdYaw      = 0;
    	CmdThrotle  = 0;
    }

	return Ready_Cmd;
}

/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/


#include "HardwareI2C.h"

#include "timer.h"
#include "util.h"
#include "rcc.h"

#include "wirish.h"
#include "boards.h"


HardwareI2C HwI2C(2);



HardwareI2C::HardwareI2C(uint32 i2c_num) 
{
    switch (i2c_num) 
    {
    case 1:
        this->i2c_d = I2C1;
        break;
    case 2:
        this->i2c_d = I2C2;
        break;
    default:
        ASSERT(0);
    }
}

void HardwareI2C::begin(void)
{
    i2c_master_enable( this->i2c_d, I2C_FAST_MODE );
}



int32 HardwareI2C::read(uint8 DevAddr, uint8 RegAddr, uint8 *data, uint32 length) 
{
    int32 ret;
    i2c_msg msgs[1]; 
 

    msgs[0].addr    = DevAddr;
    msgs[0].reg_addr = RegAddr;
    msgs[0].flags   = 0; 
    msgs[0].length  = 0; 
    msgs[0].data    = data;
    i2c_master_xfer(this->i2c_d, msgs, 1, 0);
  
    msgs[0].addr    = DevAddr;
    msgs[0].flags   = I2C_MSG_READ; 
    msgs[0].length  = length; 
    msgs[0].data    = data;
    ret = i2c_master_xfer(this->i2c_d, msgs, 1, 0);

    if( ret < 0 ) return 1;
    else          return 0;    
}


int32 HardwareI2C::write(uint8 DevAddr, uint8 RegAddr, uint8 *data, uint32 length) 
{
    int32 ret;
    i2c_msg msgs[1]; 


    msgs[0].addr        = DevAddr;
    msgs[0].reg_addr    = RegAddr;
    msgs[0].flags       = 0;
    msgs[0].length      = length;
    msgs[0].data        = data;
    ret = i2c_master_xfer(this->i2c_d, msgs, 1,0);

    if( ret < 0 ) return 1;
    else          return 0;
}



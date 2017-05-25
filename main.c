/*
 * File:   main.c
 * Author: Daniel Cambron
 *
 * Created on June 8, 2016, 6:56 PM
 * 
 *  Lexcelon Batlab V1.0 Measurement Processor Firmware
 *  Copyright (C) 2017 Daniel Cambron <daniel.cambron@lexcelon.com>
 *  Copyright (C) 2017 Lexcelon, LLC
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "hal.h"

bool flag_restart = false;

void main(void) 
{
    uint32_t i;
    
    SYSTEM_Initialize();
    
    app_initialize();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    for(i=0;i<400000;i++); //give the system time to initialize the measurements over the interrupts
    //if you don't do this, then the status flags will erroneously be thrown on startup
    
    while(1)
    {
        if(PORTEbits.RE3 == 0 || flag_restart == true)
        {
            asm("reset");
        }
        if(get_uart_packet())    // if a message was received.
        {
            handle_uart_packet();// reacts to packet and forms response
            send_uart_packet();
        }
        
        send_psu();              // get update of External PSU status
        
        for(i=0;i<4;i++)         // service each cell
        {
            set_flags(i);        // use inputs to decide what the next state will be
            send_streams(i);     // sends a stream packet if we're scheduled for that
            set_relays(i);       // set the outputs for the next state
            set_currents(i);
            set_fan(i);
        } //END FOR
    } //END WHILE(1)
} //END MAIN


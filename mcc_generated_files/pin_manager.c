/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC18F24K40
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */   
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

    /**
    TRISx registers
    */    
    TRISA = 0x0F;
    TRISB = 0x0F;
    TRISC = 0xD0;
     TRISCbits.TRISC7=1; /* RX on RC7 is an input */
    TRISCbits.TRISC6=0; /* TX on RC6 is an output */
    

    /**
    ANSELx registers
    */   
    ANSELC = 0x00;
    ANSELB = 0x0F;
    ANSELA = 0x0F;

    /**
    WPUx registers
    */ 
    WPUE = 0x08;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */   
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    


   
    
    
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    SSP1DATPPSbits.SSP1DATPPS = 0x14;   //RC4->MSSP1:SDI1;
    RXPPSbits.RXPPS = 0x17;   //RC7->EUSART:RX;
    RA4PPS = 0x07;   //RA4->PWM3:PWM3;
    RC3PPS = 0x0D;   //RC3->MSSP1:SCK1;
    RB5PPS = 0x06;   //RB5->CCP2:CCP2;
    RC1PPS = 0x08;   //RC1->PWM4:PWM4;
    RC2PPS = 0x05;   //RC2->CCP1:CCP1;
    RC5PPS = 0x0E;   //RC5->MSSP1:SDO1;
    RC6PPS = 0x09;   //RC6->EUSART:TX;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
    
        RLY0_SetLow();
    RLY0_SetDigitalOutput();
    RLY1_SetLow();
    RLY1_SetDigitalOutput();
    RLY2_SetLow();
    RLY2_SetDigitalOutput();
    RLY3_SetLow();
    RLY3_SetDigitalOutput();
    
    ISET0_SetLow();
    ISET0_SetDigitalOutput();
    ISET1_SetLow();
    ISET1_SetDigitalOutput();
    ISET2_SetLow();
    ISET2_SetDigitalOutput();
    ISET3_SetLow();
    ISET3_SetDigitalOutput();
    
    SS_SetDigitalOutput();
    SS_SetLow();
    SS_SetHigh();
    
    LED_ERR_SetDigitalOutput();
    LED_ERR_SetLow();
    LED_STATUS_SetDigitalOutput();
    LED_STATUS_SetLow();
}       

void PIN_MANAGER_IOC(void)
{   

}

/**
 End of File
*/
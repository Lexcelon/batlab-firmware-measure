/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC18F23K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RLY1 aliases
#define ISET2_TRIS               TRISA4
#define ISET2_LAT                LATA4
#define ISET2_PORT               RA4
#define ISET2_SetHigh()    do { LATA4 = 1; } while(0)
#define ISET2_SetLow()   do { LATA4 = 0; } while(0)
#define ISET2_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define ISET2_GetValue()         PORTAbits.RA4
#define ISET2_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define ISET2_SetDigitalOutput()   do { TRISA4 = 0; } while(0)



// get/set RLY2 aliases
#define RLY2_TRIS               TRISA5
#define RLY2_LAT                LATA5
#define RLY2_PORT               RA5
#define RLY2_ANS                ANSA5
#define RLY2_SetHigh()    do { LATA5 = 1; } while(0)
#define RLY2_SetLow()   do { LATA5 = 0; } while(0)
#define RLY2_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define RLY2_GetValue()         PORTAbits.RA5
#define RLY2_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define RLY2_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define RLY2_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define RLY2_SetDigitalMode()   do { ANSA5 = 0; } while(0)


// get/set ISET3 aliases
#define RLY0_TRIS               TRISA6
#define RLY0_LAT                LATA6
#define RLY0_PORT               RA6
#define RLY0_SetHigh()    do { LATA6 = 1; } while(0)
#define RLY0_SetLow()   do { LATA6 = 0; } while(0)
#define RLY0_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define RLY0_GetValue()         PORTAbits.RA6
#define RLY0_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define RLY0_SetDigitalOutput()   do { TRISA6 = 0; } while(0)



// get/set ISET2 aliases
#define SS_TRIS               TRISA7
#define SS_LAT                LATA7
#define SS_PORT               RA7
#define SS_SetHigh()    do { LATA7 = 1; } while(0)
#define SS_SetLow()   do { LATA7 = 0; } while(0)
#define SS_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define SS_GetValue()         PORTAbits.RA7
#define SS_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define SS_SetDigitalOutput()   do { TRISA7 = 0; } while(0)




// get/set RLY3 aliases
#define RLY3_TRIS               TRISB4
#define RLY3_LAT                LATB4
#define RLY3_PORT               RB4
#define RLY3_WPU                WPUB4
#define RLY3_ANS                ANSB4
#define RLY3_SetHigh()    do { LATB4 = 1; } while(0)
#define RLY3_SetLow()   do { LATB4 = 0; } while(0)
#define RLY3_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define RLY3_GetValue()         PORTBbits.RB4
#define RLY3_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define RLY3_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define RLY3_SetPullup()    do { WPUB4 = 1; } while(0)
#define RLY3_ResetPullup()   do { WPUB4 = 0; } while(0)
#define RLY3_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define RLY3_SetDigitalMode()   do { ANSB4 = 0; } while(0)


// get/set SS aliases
#define ISET3_TRIS               TRISB5
#define ISET3_LAT                LATB5
#define ISET3_PORT               RB5
#define ISET3_WPU                WPUB5
#define ISET3_ANS                ANSB5
#define ISET3_SetHigh()    do { LATB5 = 1; } while(0)
#define ISET3_SetLow()   do { LATB5 = 0; } while(0)
#define ISET3_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define ISET3_GetValue()         PORTBbits.RB5
#define ISET3_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define ISET3_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define ISET3_SetPullup()    do { WPUB5 = 1; } while(0)
#define ISET3_ResetPullup()   do { WPUB5 = 0; } while(0)
#define ISET3_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define ISET3_SetDigitalMode()   do { ANSB5 = 0; } while(0)


// get/set LED1 aliases
#define LED1_TRIS               TRISB6
#define LED1_LAT                LATB6
#define LED1_PORT               RB6
#define LED1_WPU                WPUB6
#define LED1_SetHigh()    do { LATB6 = 1; } while(0)
#define LED1_SetLow()   do { LATB6 = 0; } while(0)
#define LED1_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define LED1_GetValue()         PORTBbits.RB6
#define LED1_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define LED1_SetPullup()    do { WPUB6 = 1; } while(0)
#define LED1_ResetPullup()   do { WPUB6 = 0; } while(0)


// get/set LED2 aliases
#define LED2_TRIS               TRISB7
#define LED2_LAT                LATB7
#define LED2_PORT               RB7
#define LED2_WPU                WPUB7
#define LED2_SetHigh()    do { LATB7 = 1; } while(0)
#define LED2_SetLow()   do { LATB7 = 0; } while(0)
#define LED2_Toggle()   do { LATB7 = ~LATB7; } while(0)
#define LED2_GetValue()         PORTBbits.RB7
#define LED2_SetDigitalInput()    do { TRISB7 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISB7 = 0; } while(0)

#define LED2_SetPullup()    do { WPUB7 = 1; } while(0)
#define LED2_ResetPullup()   do { WPUB7 = 0; } while(0)


// get/set ISET1 aliases
#define RLY1_TRIS               TRISC0
#define RLY1_LAT                LATC0
#define RLY1_PORT               RC0
#define RLY1_SetHigh()    do { LATC0 = 1; } while(0)
#define RLY1_SetLow()   do { LATC0 = 0; } while(0)
#define RLY1_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define RLY1_GetValue()         PORTCbits.RC0
#define RLY1_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define RLY1_SetDigitalOutput()   do { TRISC0 = 0; } while(0)



// get/set ISET0 aliases
#define ISET1_TRIS               TRISC1
#define ISET1_LAT                LATC1
#define ISET1_PORT               RC1
#define ISET1_SetHigh()    do { LATC1 = 1; } while(0)
#define ISET1_SetLow()   do { LATC1 = 0; } while(0)
#define ISET1_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define ISET1_GetValue()         PORTCbits.RC1
#define ISET1_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define ISET1_SetDigitalOutput()   do { TRISC1 = 0; } while(0)



// get/set RLY0 aliases
#define ISET0_TRIS               TRISC2
#define ISET0_LAT                LATC2
#define ISET0_PORT               RC2
#define ISET0_ANS                ANSC2
#define ISET0_SetHigh()    do { LATC2 = 1; } while(0)
#define ISET0_SetLow()   do { LATC2 = 0; } while(0)
#define ISET0_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define ISET0_GetValue()         PORTCbits.RC2
#define ISET0_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define ISET0_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define ISET0_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define ISET0_SetDigitalMode()   do { ANSC2 = 0; } while(0)




/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);


#endif // PIN_MANAGER_H
/**
 End of File
*/
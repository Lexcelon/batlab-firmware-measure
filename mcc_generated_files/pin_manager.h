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
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC18F24K40
        Version           :  1.01
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

// get/set ISENSE2 aliases
#define ISENSE2_TRIS               TRISAbits.TRISA0
#define ISENSE2_LAT                LATAbits.LATA0
#define ISENSE2_PORT               PORTAbits.RA0
#define ISENSE2_WPU                WPUAbits.WPUA0
#define ISENSE2_OD                ODCONAbits.ODCA0
#define ISENSE2_ANS                ANSELAbits.ANSELA0
#define ISENSE2_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ISENSE2_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ISENSE2_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ISENSE2_GetValue()           PORTAbits.RA0
#define ISENSE2_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ISENSE2_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ISENSE2_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define ISENSE2_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define ISENSE2_SetPushPull()    do { ODCONAbits.ODCA0 = 1; } while(0)
#define ISENSE2_SetOpenDrain()   do { ODCONAbits.ODCA0 = 0; } while(0)
#define ISENSE2_SetAnalogMode()  do { ANSELAbits.ANSELA0 = 1; } while(0)
#define ISENSE2_SetDigitalMode() do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set ISENSE3 aliases
#define ISENSE3_TRIS               TRISAbits.TRISA1
#define ISENSE3_LAT                LATAbits.LATA1
#define ISENSE3_PORT               PORTAbits.RA1
#define ISENSE3_WPU                WPUAbits.WPUA1
#define ISENSE3_OD                ODCONAbits.ODCA1
#define ISENSE3_ANS                ANSELAbits.ANSELA1
#define ISENSE3_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ISENSE3_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ISENSE3_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ISENSE3_GetValue()           PORTAbits.RA1
#define ISENSE3_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ISENSE3_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ISENSE3_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define ISENSE3_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define ISENSE3_SetPushPull()    do { ODCONAbits.ODCA1 = 1; } while(0)
#define ISENSE3_SetOpenDrain()   do { ODCONAbits.ODCA1 = 0; } while(0)
#define ISENSE3_SetAnalogMode()  do { ANSELAbits.ANSELA1 = 1; } while(0)
#define ISENSE3_SetDigitalMode() do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set ISENSE1 aliases
#define ISENSE1_TRIS               TRISAbits.TRISA2
#define ISENSE1_LAT                LATAbits.LATA2
#define ISENSE1_PORT               PORTAbits.RA2
#define ISENSE1_WPU                WPUAbits.WPUA2
#define ISENSE1_OD                ODCONAbits.ODCA2
#define ISENSE1_ANS                ANSELAbits.ANSELA2
#define ISENSE1_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ISENSE1_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ISENSE1_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ISENSE1_GetValue()           PORTAbits.RA2
#define ISENSE1_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ISENSE1_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ISENSE1_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define ISENSE1_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define ISENSE1_SetPushPull()    do { ODCONAbits.ODCA2 = 1; } while(0)
#define ISENSE1_SetOpenDrain()   do { ODCONAbits.ODCA2 = 0; } while(0)
#define ISENSE1_SetAnalogMode()  do { ANSELAbits.ANSELA2 = 1; } while(0)
#define ISENSE1_SetDigitalMode() do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set ISENSE0 aliases
#define ISENSE0_TRIS               TRISAbits.TRISA3
#define ISENSE0_LAT                LATAbits.LATA3
#define ISENSE0_PORT               PORTAbits.RA3
#define ISENSE0_WPU                WPUAbits.WPUA3
#define ISENSE0_OD                ODCONAbits.ODCA3
#define ISENSE0_ANS                ANSELAbits.ANSELA3
#define ISENSE0_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define ISENSE0_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define ISENSE0_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define ISENSE0_GetValue()           PORTAbits.RA3
#define ISENSE0_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define ISENSE0_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define ISENSE0_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define ISENSE0_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)
#define ISENSE0_SetPushPull()    do { ODCONAbits.ODCA3 = 1; } while(0)
#define ISENSE0_SetOpenDrain()   do { ODCONAbits.ODCA3 = 0; } while(0)
#define ISENSE0_SetAnalogMode()  do { ANSELAbits.ANSELA3 = 1; } while(0)
#define ISENSE0_SetDigitalMode() do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()    do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()   do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()   do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()         PORTAbits.RA4
#define RA4_SetDigitalInput()   do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()  do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()     do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()   do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode() do { ANSELAbits.ANSELA4 = 1; } while(0)
#define RA4_SetDigitalMode()do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RLY2 aliases
#define RLY2_TRIS               TRISAbits.TRISA5
#define RLY2_LAT                LATAbits.LATA5
#define RLY2_PORT               PORTAbits.RA5
#define RLY2_WPU                WPUAbits.WPUA5
#define RLY2_OD                ODCONAbits.ODCA5
#define RLY2_ANS                ANSELAbits.ANSELA5
#define RLY2_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RLY2_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RLY2_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RLY2_GetValue()           PORTAbits.RA5
#define RLY2_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RLY2_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RLY2_SetPullup()      do { WPUAbits.WPUA5 = 1; } while(0)
#define RLY2_ResetPullup()    do { WPUAbits.WPUA5 = 0; } while(0)
#define RLY2_SetPushPull()    do { ODCONAbits.ODCA5 = 1; } while(0)
#define RLY2_SetOpenDrain()   do { ODCONAbits.ODCA5 = 0; } while(0)
#define RLY2_SetAnalogMode()  do { ANSELAbits.ANSELA5 = 1; } while(0)
#define RLY2_SetDigitalMode() do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RLY0 aliases
#define RLY0_TRIS               TRISAbits.TRISA6
#define RLY0_LAT                LATAbits.LATA6
#define RLY0_PORT               PORTAbits.RA6
#define RLY0_WPU                WPUAbits.WPUA6
#define RLY0_OD                ODCONAbits.ODCA6
#define RLY0_ANS                ANSELAbits.ANSELA6
#define RLY0_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define RLY0_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define RLY0_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define RLY0_GetValue()           PORTAbits.RA6
#define RLY0_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define RLY0_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define RLY0_SetPullup()      do { WPUAbits.WPUA6 = 1; } while(0)
#define RLY0_ResetPullup()    do { WPUAbits.WPUA6 = 0; } while(0)
#define RLY0_SetPushPull()    do { ODCONAbits.ODCA6 = 1; } while(0)
#define RLY0_SetOpenDrain()   do { ODCONAbits.ODCA6 = 0; } while(0)
#define RLY0_SetAnalogMode()  do { ANSELAbits.ANSELA6 = 1; } while(0)
#define RLY0_SetDigitalMode() do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set SPI_SS aliases
#define SPI_SS_TRIS               TRISAbits.TRISA7
#define SPI_SS_LAT                LATAbits.LATA7
#define SPI_SS_PORT               PORTAbits.RA7
#define SPI_SS_WPU                WPUAbits.WPUA7
#define SPI_SS_OD                ODCONAbits.ODCA7
#define SPI_SS_ANS                ANSELAbits.ANSELA7
#define SPI_SS_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define SPI_SS_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define SPI_SS_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define SPI_SS_GetValue()           PORTAbits.RA7
#define SPI_SS_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define SPI_SS_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define SPI_SS_SetPullup()      do { WPUAbits.WPUA7 = 1; } while(0)
#define SPI_SS_ResetPullup()    do { WPUAbits.WPUA7 = 0; } while(0)
#define SPI_SS_SetPushPull()    do { ODCONAbits.ODCA7 = 1; } while(0)
#define SPI_SS_SetOpenDrain()   do { ODCONAbits.ODCA7 = 0; } while(0)
#define SPI_SS_SetAnalogMode()  do { ANSELAbits.ANSELA7 = 1; } while(0)
#define SPI_SS_SetDigitalMode() do { ANSELAbits.ANSELA7 = 0; } while(0)

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


// get/set TEMP3 aliases
#define TEMP3_TRIS               TRISBbits.TRISB0
#define TEMP3_LAT                LATBbits.LATB0
#define TEMP3_PORT               PORTBbits.RB0
#define TEMP3_WPU                WPUBbits.WPUB0
#define TEMP3_OD                ODCONBbits.ODCB0
#define TEMP3_ANS                ANSELBbits.ANSELB0
#define TEMP3_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define TEMP3_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define TEMP3_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define TEMP3_GetValue()           PORTBbits.RB0
#define TEMP3_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define TEMP3_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define TEMP3_SetPullup()      do { WPUBbits.WPUB0 = 1; } while(0)
#define TEMP3_ResetPullup()    do { WPUBbits.WPUB0 = 0; } while(0)
#define TEMP3_SetPushPull()    do { ODCONBbits.ODCB0 = 1; } while(0)
#define TEMP3_SetOpenDrain()   do { ODCONBbits.ODCB0 = 0; } while(0)
#define TEMP3_SetAnalogMode()  do { ANSELBbits.ANSELB0 = 1; } while(0)
#define TEMP3_SetDigitalMode() do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set TEMP2 aliases
#define TEMP2_TRIS               TRISBbits.TRISB1
#define TEMP2_LAT                LATBbits.LATB1
#define TEMP2_PORT               PORTBbits.RB1
#define TEMP2_WPU                WPUBbits.WPUB1
#define TEMP2_OD                ODCONBbits.ODCB1
#define TEMP2_ANS                ANSELBbits.ANSELB1
#define TEMP2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define TEMP2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define TEMP2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define TEMP2_GetValue()           PORTBbits.RB1
#define TEMP2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define TEMP2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define TEMP2_SetPullup()      do { WPUBbits.WPUB1 = 1; } while(0)
#define TEMP2_ResetPullup()    do { WPUBbits.WPUB1 = 0; } while(0)
#define TEMP2_SetPushPull()    do { ODCONBbits.ODCB1 = 1; } while(0)
#define TEMP2_SetOpenDrain()   do { ODCONBbits.ODCB1 = 0; } while(0)
#define TEMP2_SetAnalogMode()  do { ANSELBbits.ANSELB1 = 1; } while(0)
#define TEMP2_SetDigitalMode() do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set TEMP1 aliases
#define TEMP1_TRIS               TRISBbits.TRISB2
#define TEMP1_LAT                LATBbits.LATB2
#define TEMP1_PORT               PORTBbits.RB2
#define TEMP1_WPU                WPUBbits.WPUB2
#define TEMP1_OD                ODCONBbits.ODCB2
#define TEMP1_ANS                ANSELBbits.ANSELB2
#define TEMP1_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define TEMP1_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define TEMP1_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define TEMP1_GetValue()           PORTBbits.RB2
#define TEMP1_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define TEMP1_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define TEMP1_SetPullup()      do { WPUBbits.WPUB2 = 1; } while(0)
#define TEMP1_ResetPullup()    do { WPUBbits.WPUB2 = 0; } while(0)
#define TEMP1_SetPushPull()    do { ODCONBbits.ODCB2 = 1; } while(0)
#define TEMP1_SetOpenDrain()   do { ODCONBbits.ODCB2 = 0; } while(0)
#define TEMP1_SetAnalogMode()  do { ANSELBbits.ANSELB2 = 1; } while(0)
#define TEMP1_SetDigitalMode() do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set TEMP0 aliases
#define TEMP0_TRIS               TRISBbits.TRISB3
#define TEMP0_LAT                LATBbits.LATB3
#define TEMP0_PORT               PORTBbits.RB3
#define TEMP0_WPU                WPUBbits.WPUB3
#define TEMP0_OD                ODCONBbits.ODCB3
#define TEMP0_ANS                ANSELBbits.ANSELB3
#define TEMP0_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define TEMP0_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define TEMP0_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define TEMP0_GetValue()           PORTBbits.RB3
#define TEMP0_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define TEMP0_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define TEMP0_SetPullup()      do { WPUBbits.WPUB3 = 1; } while(0)
#define TEMP0_ResetPullup()    do { WPUBbits.WPUB3 = 0; } while(0)
#define TEMP0_SetPushPull()    do { ODCONBbits.ODCB3 = 1; } while(0)
#define TEMP0_SetOpenDrain()   do { ODCONBbits.ODCB3 = 0; } while(0)
#define TEMP0_SetAnalogMode()  do { ANSELBbits.ANSELB3 = 1; } while(0)
#define TEMP0_SetDigitalMode() do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RLY3 aliases
#define RLY3_TRIS               TRISBbits.TRISB4
#define RLY3_LAT                LATBbits.LATB4
#define RLY3_PORT               PORTBbits.RB4
#define RLY3_WPU                WPUBbits.WPUB4
#define RLY3_OD                ODCONBbits.ODCB4
#define RLY3_ANS                ANSELBbits.ANSELB4
#define RLY3_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RLY3_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RLY3_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RLY3_GetValue()           PORTBbits.RB4
#define RLY3_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RLY3_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RLY3_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define RLY3_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define RLY3_SetPushPull()    do { ODCONBbits.ODCB4 = 1; } while(0)
#define RLY3_SetOpenDrain()   do { ODCONBbits.ODCB4 = 0; } while(0)
#define RLY3_SetAnalogMode()  do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RLY3_SetDigitalMode() do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()    do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()   do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()   do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()         PORTBbits.RB5
#define RB5_SetDigitalInput()   do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()  do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()     do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()   do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode() do { ANSELBbits.ANSELB5 = 1; } while(0)
#define RB5_SetDigitalMode()do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set LED1 aliases
#define LED_ERR_TRIS               TRISBbits.TRISB6
#define LED_ERR_LAT                LATBbits.LATB6
#define LED_ERR_PORT               PORTBbits.RB6
#define LED_ERR_WPU                WPUBbits.WPUB6
#define LED_ERR_OD                ODCONBbits.ODCB6
#define LED_ERR_ANS                ANSELBbits.ANSELB6
#define LED_ERR_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define LED_ERR_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define LED_ERR_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define LED_ERR_GetValue()           PORTBbits.RB6
#define LED_ERR_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define LED_ERR_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define LED_ERR_SetPullup()      do { WPUBbits.WPUB6 = 1; } while(0)
#define LED_ERR_ResetPullup()    do { WPUBbits.WPUB6 = 0; } while(0)
#define LED_ERR_SetPushPull()    do { ODCONBbits.ODCB6 = 1; } while(0)
#define LED_ERR_SetOpenDrain()   do { ODCONBbits.ODCB6 = 0; } while(0)
#define LED_ERR_SetAnalogMode()  do { ANSELBbits.ANSELB6 = 1; } while(0)
#define LED_ERR_SetDigitalMode() do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set LED1 aliases
#define LED_MSG_TRIS               TRISBbits.TRISB6
#define LED_MSG_LAT                LATBbits.LATB6
#define LED_MSG_PORT               PORTBbits.RB6
#define LED_MSG_WPU                WPUBbits.WPUB6
#define LED_MSG_OD                ODCONBbits.ODCB6
#define LED_MSG_ANS                ANSELBbits.ANSELB6
#define LED_MSG_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define LED_MSG_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define LED_MSG_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define LED_MSG_GetValue()           PORTBbits.RB6
#define LED_MSG_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define LED_MSG_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define LED_MSG_SetPullup()      do { WPUBbits.WPUB6 = 1; } while(0)
#define LED_MSG_ResetPullup()    do { WPUBbits.WPUB6 = 0; } while(0)
#define LED_MSG_SetPushPull()    do { ODCONBbits.ODCB6 = 1; } while(0)
#define LED_MSG_SetOpenDrain()   do { ODCONBbits.ODCB6 = 0; } while(0)
#define LED_MSG_SetAnalogMode()  do { ANSELBbits.ANSELB6 = 1; } while(0)
#define LED_MSG_SetDigitalMode() do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set LED2 aliases
#define LED_STATUS_TRIS               TRISBbits.TRISB7
#define LED_STATUS_LAT                LATBbits.LATB7
#define LED_STATUS_PORT               PORTBbits.RB7
#define LED_STATUS_WPU                WPUBbits.WPUB7
#define LED_STATUS_OD                ODCONBbits.ODCB7
#define LED_STATUS_ANS                ANSELBbits.ANSELB7
#define LED_STATUS_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define LED_STATUS_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define LED_STATUS_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define LED_STATUS_GetValue()           PORTBbits.RB7
#define LED_STATUS_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define LED_STATUS_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define LED_STATUS_SetPullup()      do { WPUBbits.WPUB7 = 1; } while(0)
#define LED_STATUS_ResetPullup()    do { WPUBbits.WPUB7 = 0; } while(0)
#define LED_STATUS_SetPushPull()    do { ODCONBbits.ODCB7 = 1; } while(0)
#define LED_STATUS_SetOpenDrain()   do { ODCONBbits.ODCB7 = 0; } while(0)
#define LED_STATUS_SetAnalogMode()  do { ANSELBbits.ANSELB7 = 1; } while(0)
#define LED_STATUS_SetDigitalMode() do { ANSELBbits.ANSELB7 = 0; } while(0)

#define FAN1_TRIS               TRISBbits.TRISB7
#define FAN1_LAT                LATBbits.LATB7
#define FAN1_PORT               PORTBbits.RB7
#define FAN1_WPU                WPUBbits.WPUB7
#define FAN1_OD                ODCONBbits.ODCB7
#define FAN1_ANS                ANSELBbits.ANSELB7
#define FAN1_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define FAN1_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define FAN1_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define FAN1_GetValue()           PORTBbits.RB7
#define FAN1_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define FAN1_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define FAN1_SetPullup()      do { WPUBbits.WPUB7 = 1; } while(0)
#define FAN1_ResetPullup()    do { WPUBbits.WPUB7 = 0; } while(0)
#define FAN1_SetPushPull()    do { ODCONBbits.ODCB7 = 1; } while(0)
#define FAN1_SetOpenDrain()   do { ODCONBbits.ODCB7 = 0; } while(0)
#define FAN1_SetAnalogMode()  do { ANSELBbits.ANSELB7 = 1; } while(0)
#define FAN1_SetDigitalMode() do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RLY1 aliases
#define RLY1_TRIS               TRISCbits.TRISC0
#define RLY1_LAT                LATCbits.LATC0
#define RLY1_PORT               PORTCbits.RC0
#define RLY1_WPU                WPUCbits.WPUC0
#define RLY1_OD                ODCONCbits.ODCC0
#define RLY1_ANS                ANSELCbits.ANSELC0
#define RLY1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RLY1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RLY1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RLY1_GetValue()           PORTCbits.RC0
#define RLY1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RLY1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RLY1_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define RLY1_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define RLY1_SetPushPull()    do { ODCONCbits.ODCC0 = 1; } while(0)
#define RLY1_SetOpenDrain()   do { ODCONCbits.ODCC0 = 0; } while(0)
#define RLY1_SetAnalogMode()  do { ANSELCbits.ANSELC0 = 1; } while(0)
#define RLY1_SetDigitalMode() do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 procedures
#define RC1_SetHigh()    do { LATCbits.LATC1 = 1; } while(0)
#define RC1_SetLow()   do { LATCbits.LATC1 = 0; } while(0)
#define RC1_Toggle()   do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RC1_GetValue()         PORTCbits.RC1
#define RC1_SetDigitalInput()   do { TRISCbits.TRISC1 = 1; } while(0)
#define RC1_SetDigitalOutput()  do { TRISCbits.TRISC1 = 0; } while(0)
#define RC1_SetPullup()     do { WPUCbits.WPUC1 = 1; } while(0)
#define RC1_ResetPullup()   do { WPUCbits.WPUC1 = 0; } while(0)
#define RC1_SetAnalogMode() do { ANSELCbits.ANSELC1 = 1; } while(0)
#define RC1_SetDigitalMode()do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()    do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()   do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()   do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()         PORTCbits.RC2
#define RC2_SetDigitalInput()   do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()  do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()     do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()   do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode() do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RC2_SetDigitalMode()do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()    do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()   do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()   do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()         PORTCbits.RC3
#define RC3_SetDigitalInput()   do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()  do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()     do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()   do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode() do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()    do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()   do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()   do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()         PORTCbits.RC4
#define RC4_SetDigitalInput()   do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()  do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()     do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()   do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode() do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()    do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()   do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()   do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()         PORTCbits.RC5
#define RC5_SetDigitalInput()   do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()  do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()     do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()   do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode() do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()     do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()   do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()     do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()   do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode() do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()do { ANSELCbits.ANSELC7 = 0; } while(0)

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
/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
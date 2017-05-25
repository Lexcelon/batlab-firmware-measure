/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC18F24K40
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// CONFIG1L
#pragma config FEXTOSC = OFF    // ->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_64MHZ    // ->HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1

// CONFIG1H
#pragma config CLKOUTEN = OFF    // ->CLKOUT function is disabled
#pragma config CSWEN = ON    // ->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE = INTMCLR //was EXT   // ->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR 
#pragma config PWRTE = OFF    // Power-up Timer Enable bit->Power up timer disabled
#pragma config LPBOREN = OFF    // ->ULPBOR disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled , SBOREN bit is ignored

// CONFIG2H
#pragma config BORV = VBOR_2P45    // Brown Out Reset Voltage selection bits->Brown-out Reset Voltage (VBOR) set to 2.45V
#pragma config ZCD = OFF    // ZCD Disable bit->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config DEBUG = OFF    // Debugger Enable bit->Background debugger disabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Extended Instruction Set and Indexed Addressing Mode disabled

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31    // ->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4L
#pragma config WRT0 = OFF    // Write Protection Block 0->Block 0 (000800-001FFFh) not write-protected
#pragma config WRT1 = OFF    // Write Protection Block 1->Block 1 (002000-003FFFh) not write-protected

// CONFIG4H
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-30000Bh) not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config SCANE = ON    // ->Scanner module is available for use, SCANMD bit can control the module
#pragma config LVP = OFF    // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP = OFF    // UserNVM Program Memory Code Protection bit->UserNVM code protection disabled
#pragma config CPD = OFF    // DataNVM Memory Code Protection bit->DataNVM code protection disabled

// CONFIG6L
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks

// CONFIG6H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    
    INTERRUPT_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    SPI1_Initialize();
    FVR_Initialize();
    PWM1_Initialize();
    PWM2_Initialize();
    ADCC_Initialize();
    PWM4_Initialize();
    PWM3_Initialize();
    //TMR0_Initialize();
    TMR2_Initialize();
    EUSART_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 64_MHz; 
    OSCFRQ = 0x08;
    // TUN 0; 
    OSCTUNE = 0x00;
    // Set the secondary oscillator
    
}

void TMR0_Initialize(void)
{
    //T0CON = 0b10000101; //' 64 prescale of fosc/4' = 250000 Hz
    T0CON0 = 0b10010000;
    T0CON1 = 0b01000110;

    PIE0bits.TMR0IE = 1;
    PIR0bits.TMR0IF = 0;
    
    //@ 250000 Hz, 25000 ticks takes 0.1 sec. so if we set the timer to 0xFFFF - 25000
    // it should go off every 0.1 sec
    TMR0 = 0x9E57; 
}

void TMR2_Initialize(void)
{
    // T2CS FOSC/4; 
    T2CLKCON = 0x01;
    // T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized; 
    T2HLT = 0x00;
    // T2RSEL PWM3_out; 
    T2RST = 0x06;
    // PR2 255; 
    T2PR = 159;
        //PR2 = 153;//159; //0xFF--> 62.7 kHz, 159 --> 100 kHz and 160 max duty cycle //TIMER 2 counts up to this 
    // TMR2 0; 
    T2TMR = 0x00;
     //T2CON = 0x4C; //start timer 2 with 10:1 postscaler
    T2CON = 0x89;
    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR2IF = 0;
    // Enabling TMR2 interrupt.
    PIE4bits.TMR2IE = 1;  
}

/*
void TMR4_Initialize(void)
{
    // T2CS FOSC/4; 
    T4CLKCON = 0x01;
    // T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized; 
    T4HLT = 0x00;
    // T2RSEL PWM3_out; 
    T4RST = 0x06;
    // PR2 255; 
    T4PR = 153;
        //PR2 = 153;//159; //0xFF--> 62.7 kHz, 159 --> 100 kHz and 160 max duty cycle //TIMER 2 counts up to this 
    // TMR2 0; 
    T4TMR = 0x00;
     //T2CON = 0x4C; //start timer 2 with 10:1 postscaler
    T4CON = 0x89;
    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR4IF = 0;
    // Enabling TMR2 interrupt.
    PIE4bits.TMR4IE = 1;  
}*/




        
/**
 End of File
*/

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
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC18F23K22
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
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

// CONFIG1H
#pragma config FOSC = INTIO67    // Oscillator Selection bits->Internal oscillator block
#pragma config PLLCFG = OFF    // 4X PLL Enable->Oscillator used directly
#pragma config PRICLKEN = ON    // Primary clock enable bit->Primary clock enabled
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF    // Internal/External Oscillator Switchover bit->Oscillator Switchover mode disabled

// CONFIG2L
#pragma config PWRTEN = OFF    // Power-up Timer Enable bit->Power up timer disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 190    // Brown Out Reset Voltage bits->VBOR set to 1.90 V nominal

// CONFIG2H
#pragma config WDTEN = OFF    // Watchdog Timer Enable bits->Watch dog timer is always disabled. SWDTEN has no effect.
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits->1:32768

// CONFIG3H
#pragma config CCP2MX = PORTC1    // CCP2 MUX bit->CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = ON    // PORTB A/D Enable bit->PORTB<5:0> pins are configured as analog input channels on Reset
#pragma config CCP3MX = PORTB5    // P3A/CCP3 Mux bit->P3A/CCP3 input/output is multiplexed with RB5
#pragma config HFOFST = ON    // HFINTOSC Fast Start-up->HFINTOSC output and ready status are not delayed by the oscillator stable status
#pragma config T3CMX = PORTC0    // Timer3 Clock input mux bit->T3CKI is on RC0
#pragma config P2BMX = PORTB5    // ECCP2 B output mux bit->P2B is on RB5
#pragma config MCLRE = EXTMCLR    // MCLR Pin Enable bit->MCLR pin enabled, RE3 input pin disabled

// CONFIG4L
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config LVP = ON    // Single-Supply ICSP Enable bit->Single-Supply ICSP enabled if MCLRE is also 1
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config DEBUG = OFF    // Background Debug->Disabled

// CONFIG5L
#pragma config CP0 = OFF    // Code Protection Block 0->Block 0 (000200-000FFFh) not code-protected
#pragma config CP1 = OFF    // Code Protection Block 1->Block 1 (001000-001FFFh) not code-protected

// CONFIG5H
#pragma config CPB = OFF    // Boot Block Code Protection bit->Boot block (000000-0001FFh) not code-protected
#pragma config CPD = OFF    // Data EEPROM Code Protection bit->Data EEPROM not code-protected

// CONFIG6L
#pragma config WRT0 = OFF    // Write Protection Block 0->Block 0 (000200-000FFFh) not write-protected
#pragma config WRT1 = OFF    // Write Protection Block 1->Block 1 (001000-001FFFh) not write-protected

// CONFIG6H
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-3000FFh) not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block (000000-0001FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected

// CONFIG7L
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000200-000FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (001000-001FFFh) not protected from table reads executed in other blocks

// CONFIG7H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0001FFh) not protected from table reads executed in other blocks

#include "mcc.h"

const uint8_t SINETABLE[100] =
{
    /*
    50,53,56,59,62,65,68,71,74,77,
    79,82,84,86,89,90,92,94,95,96,
    98,98,99,100,100,100,100,100,99,98,
    98,96,95,94,92,90,89,86,84,82,
    79,77,74,71,68,65,62,59,56,53,
    50,47,44,41,38,35,32,29,26,23,
    21,18,16,14,11,10,8,6,5,4,
    2,2,1,0,0,0,0,0,1,2,
    2,4,5,6,8,10,11,14,16,18,
    21,23,26,29,32,35,38,41,44,47
     */
    
    //full range pwm sinewave ---> goes between 0 and 5 Amps
        80,85,90,95,100,105,109,114,119,123,
    127,131,135,138,142,145,148,150,152,154,
    156,157,159,159,160,160,160,159,159,157,
    156,154,152,150,148,145,142,138,135,131,
    127,123,119,114,109,105,100,95,90,85,
    80,75,70,65,60,55,51,46,41,37,
    33,29,25,22,18,15,12,10,8,6,
    4,3,1,1,0,0,0,1,1,3,
    4,6,8,10,12,15,18,22,25,29,
    33,37,41,46,51,55,60,65,70,75
};

uint8_t sine_mode[4] = {0};
uint8_t sine_freq = 1;
uint8_t sine_mag = 0;
uint8_t sine_offset = 0;
uint16_t system_timer = 0;

void SYSTEM_Initialize(void)
{
    
    INTERRUPT_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    SPI1_Initialize();
    FVR_Initialize();
    ADC_Initialize();
    EUSART1_Initialize();
    TIMER0_Initialize();
    CCP_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; IRCF 16MHz_HFINTOSC/4; IDLEN disabled; 
    OSCCON = 0x70;
    // PRISD enabled; SOSCGO disabled; MFIOSEL disabled; 
    OSCCON2 = 0x04;
    // INTSRC disabled; PLLEN enabled; TUN 0; 
    OSCTUNE = 0x40;
    // Set the secondary oscillator
    
}

void TIMER0_Initialize(void)
{
    T0CON = 0b10000101; //' 64 prescale of fosc/4' = 250000 Hz
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    
    //@ 250000 Hz, 25000 ticks takes 0.1 sec. so if we set the timer to 0xFFFF - 25000
    // it should go off every 0.1 sec
    TMR0 = 0x9E57;
    
}
void TIMER0_ISR(void)
{
   TMR0 = 0x9E57; 
   system_timer++;
}

void TIMER2_ISR(void) //10 khz
{
    static uint8_t sine_counter = 0;
    sine_counter += sine_freq; // sine_freq is integer multiple of 100 Hz
    if(sine_counter > 99)
    {
        sine_counter = 0;
    }
    if(sine_mode[0])
    {
        SetDuty0((SINETABLE[sine_counter] >> sine_mag) + sine_offset);
    }
    if(sine_mode[1])
    {
        SetDuty1((SINETABLE[sine_counter] >> sine_mag) + sine_offset);
    }
    if(sine_mode[2])
    {
        SetDuty2((SINETABLE[sine_counter] >> sine_mag) + sine_offset);
    }
    if(sine_mode[3])
    {
        SetDuty3((SINETABLE[sine_counter] >> sine_mag) + sine_offset);
    }
}

void CCP_Initialize(void)
{
    ISET0_SetDigitalInput();
    ISET1_SetDigitalInput();
    ISET2_SetDigitalInput();
    ISET3_SetDigitalInput();
    
    CCPTMRS0 = 0x00; //ALL CCPS use TIMER 2
    CCPTMRS1 = 0x00; //ALL CCPS use TIMER 2
    PR2 = 153;//159; //0xFF--> 62.7 kHz, 159 --> 100 kHz and 160 max duty cycle //TIMER 2 counts up to this 
    CCP1CON = 0x0C; // PWM mode, 2 LSB duty cycle 0
    CCP2CON = 0x0C; // PWM mode
    CCP3CON = 0x0C; // PWM mode
    CCP5CON = 0x0C; // PWM mode
    CCPR1L = 0x00; // 8 msb DUTY CYCLE 0
    CCPR2L = 0x00;
    CCPR3L = 0x00;
    CCPR5L = 0x00;
    
    T2CON = 0x4C; //start timer 2 with 10:1 postscaler
    
    TMR2IE = 1;
    TMR2IF = 0;
    
    ISET0_SetDigitalOutput();
    ISET1_SetDigitalOutput();
    ISET2_SetDigitalOutput();
    ISET3_SetDigitalOutput();
       
}

void SetDuty0(uint8_t duty)
{
    CCPR1L = duty;
    //CCP2CON = (duty)? 0x3F:0x0F;
}

void SetDuty1(uint8_t duty)
{
    CCPR2L = duty;
    //CCP1CON = (duty)? 0x3F:0x0F;
}

void SetDuty2(uint8_t duty)
{
    CCPR5L = duty;
    //CCP3CON = (duty)? 0x3F:0x0F;
}

void SetDuty3(uint8_t duty)
{
    CCPR3L = duty;
    //CCP5CON = (duty & 0x03)<< 4;
}

void SetDuty(uint8_t cell, uint8_t duty)
{
    if(duty)
    {
        LED1_SetHigh();
    }
    else
    {
        LED1_SetLow();
    }
    switch(cell)
    {
        case 0: SetDuty0(duty); break;
        case 1: SetDuty1(duty); break;
        case 2: SetDuty2(duty); break;
        case 3: SetDuty3(duty); break;
    }
}

void SPI1_Initialize(void)
{
    // Set the SPI1 module to the options selected in the User Interface
    
    // SMP Middle; CKE Idle to Active; 
    SSP1STAT = 0x00;
    
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/64; SSPOV no_overflow; 
    SSP1CON1 = 0x22;
    
    // SSP1ADD 0; 
    SSP1ADD = 0x00;
}

uint8_t SPI1_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
    SSP1CON1bits.WCOL = 0;

    SSP1BUF = data;

    while(!SSP1STATbits.BF);

    return (SSP1BUF);
}


/**
 End of File
*/

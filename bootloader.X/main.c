/*
 * File:   main.c
 * Author: Daniel Cambron
 *
 * Created on May 16, 2017, 11:37 PM
 * 
 *  Lexcelon Batlab V1.0 Bootloader Firmware
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

// CONFIG1L
#pragma config FEXTOSC = OFF    // ->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_64MHZ    // ->HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1

// CONFIG1H
#pragma config CLKOUTEN = OFF    // ->CLKOUT function is disabled
#pragma config CSWEN = ON    // ->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE = INTMCLR //was EXTMCLR   // ->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR 
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
#pragma config LVP = OFF   // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP = OFF    // UserNVM Program Memory Code Protection bit->UserNVM code protection disabled
#pragma config CPD = OFF    // DataNVM Memory Code Protection bit->DataNVM code protection disabled

// CONFIG6L
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks

// CONFIG6H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks


#define PROG_START           0x0400
#define CHECKSUM_ADDR        0x3FFF

#define BOOTLOAD_FLAG_ADDR   0xFF
#define BOOTLOAD_FLAG_APP    0x00

#define BOOTLOADER_NAMESPACE 0x05
#define REG_REBOOT    0x00
#define REG_ADDR_PTR  0x01
#define REG_PROG_DATA 0x02
#define WREG_REBOOT    0x80
#define WREG_ADDR_PTR  0x81
#define WREG_PROG_DATA 0x82
#define PACKET_START_BYTE    0xAA

#asm
PSECT intcode
    goto PROG_START+0x0008
PSECT intcodelo
    goto PROG_START+0x0018
#endasm
        
void FLASH_WriteByteNoErase(unsigned int addr,unsigned char data);
unsigned char FLASH_ReadByte(unsigned int addr);
void FLASH_EraseChip(void);
unsigned char DATAEE_ReadByte(unsigned char bAdd);
void DATAEE_WriteByte(unsigned char bAdd, unsigned char bData);
void uart_tx(unsigned char value);
unsigned char uart_rx();
void initialize(void);
void send_packet(unsigned char addr,unsigned char datal,unsigned char datah);
unsigned char validate(void);

void main(void) 
{
    unsigned long j = 0;
    while(j<400000){j++;}
    initialize();
    if(DATAEE_ReadByte(BOOTLOAD_FLAG_ADDR) || PORTEbits.RE3 == 0 || !validate())
    {
        unsigned int MEMaddr = PROG_START;
        unsigned char erase_flag = 0;
        DATAEE_WriteByte(BOOTLOAD_FLAG_ADDR,BOOTLOAD_FLAG_APP); //if we have a good image and we haven't 
                                                                //explicitly been told to bootload
                                                                //then we should boot to application
        while(1)
        {
            unsigned char addr;
            unsigned char write;
            unsigned char datal;
            unsigned char datah;
            while(uart_rx() != PACKET_START_BYTE); //get a start byte
            if(uart_rx() == BOOTLOADER_NAMESPACE)
            {
                write = uart_rx(); //get the register
                addr = write & 0x7F;
                write &= 0x80;
                datal = uart_rx(); //low byte data
                datah = uart_rx(); //high byte data
                if(write)
                {
                    if(addr == REG_REBOOT)
                    {
                        if(validate())
                        {
                            DATAEE_WriteByte(BOOTLOAD_FLAG_ADDR,BOOTLOAD_FLAG_APP);
                            send_packet(WREG_REBOOT,0x00,0x00);//success packet
                            asm("goto " ___mkstr(PROG_START));
                        }
                        else
                        {
                            send_packet(WREG_REBOOT,0x01,0x01);//fail packet 
                        }
                    }
                    else if (addr == REG_ADDR_PTR)
                    {
                        unsigned char success = 0x00;
                        MEMaddr = datal + (datah << 8);
                        if(MEMaddr < PROG_START){MEMaddr = PROG_START;success=0x01;} //protect bootloader code
                        send_packet(WREG_ADDR_PTR,success,success);//success packet
                    }
                    else if (addr == REG_PROG_DATA)
                    {
                        if(!erase_flag)
                        {
                            FLASH_EraseChip();
                            erase_flag = 1;
                        }
                        FLASH_WriteByteNoErase(MEMaddr,datal);
                        send_packet(WREG_PROG_DATA,0x00,0x00);//success packet                           
                    }
                    else
                    {
                        send_packet(WREG_PROG_DATA,0x01,0x01);//fail packet
                    }
                }
                else //read
                {
                    if (addr == REG_ADDR_PTR)
                    {
                        datal = MEMaddr & 0x00FF;
                        datah = MEMaddr >> 8;
                        send_packet(addr,datal,datah);//success packet
                    }
                    else if (addr == REG_PROG_DATA)
                    {
                        datal = FLASH_ReadByte(MEMaddr);
                        send_packet(addr,datal,0x00);//success packet
                    }
                    else
                    {
                        send_packet(addr,0x01,0x01);//fail packet
                    }
                }
            }
        } //end while(1))
    }
    //else, go to the regularly scheduled programming
    asm("goto " ___mkstr(PROG_START));
}
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void initialize(void)
{
    //OSCILLATOR
    OSCCON1 = 0x60; 
    OSCCON3 = 0x00; // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCEN = 0x00; // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCFRQ = 0x08; // HFFRQ 64_MHz; 
    OSCTUNE = 0x00; // TUN 0; 
    //EUSART
    BAUD1CON = 0x08; // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled;
    RC1STA = 0x90; // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    TX1STA = 0x24; // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    SP1BRGL = 0x8A;  // Baud Rate = 115200; SP1BRGL 138; 
    SP1BRGH = 0x00; // Baud Rate = 115200; SP1BRGH 0; 
    //PIN STATES
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    
 
    TRISA = 0x0F;
    TRISB = 0x0F;
    TRISC = 0x90;
    
    ANSELC = 0x00;
    ANSELB = 0x0F;
    ANSELA = 0x0F;

    WPUE = 0x08;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    
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
}

unsigned char validate(void)
{
    unsigned int i;
    unsigned char cs = 0;
    for(i=PROG_START;i<(unsigned int)CHECKSUM_ADDR;i++)
    {
        cs += FLASH_ReadByte(i);
    }
    return (cs == FLASH_ReadByte(CHECKSUM_ADDR));
}

void send_packet(unsigned char addr,unsigned char datal,unsigned char datah)
{
    uart_tx(PACKET_START_BYTE);
    uart_tx(BOOTLOADER_NAMESPACE);
    uart_tx(addr);
    uart_tx(datal);
    uart_tx(datah);
}

/* write data on flash memory */
void FLASH_WriteByteNoErase(unsigned int addr,unsigned char data)
{
    TBLPTRU = 0x00;
    TBLPTRH = (unsigned char)((addr & 0xFF00)>> 8);
    TBLPTRL = (unsigned char)(addr & 0x00FF);
    TABLAT = data;  // Load data byte
    asm("TBLWT");
    NVMCON1bits.NVMREG = 2;
    NVMCON1bits.WREN = 1;
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;  // Start program
    NVMCON1bits.WREN = 0; // Disable writes to memory
}

unsigned char FLASH_ReadByte(unsigned int addr)
{
	NVMCON1bits.NVMREG = 2;
    TBLPTRU = 0x00;
    TBLPTRH = (unsigned char)((addr & 0xFF00)>> 8);
    TBLPTRL = (unsigned char)(addr & 0x00FF);
    asm("TBLRD");
    return (TABLAT);
}

void FLASH_EraseChip(void)
{
    unsigned int baseAddr = 0x0400; //don't erase the bootloader
    TBLPTRU = 0x00;
    while(baseAddr < 0x4000) //0x4000 flash size, eraseable in 64 byte chunks
    {
        TBLPTRH = (unsigned char)((baseAddr & 0xFF00)>> 8);
        TBLPTRL = (unsigned char)(baseAddr & 0x00FF);
        baseAddr += 64;
        NVMCON1bits.NVMREG = 2;
        NVMCON1bits.WREN = 1;
        NVMCON1bits.FREE = 1;
        NVMCON2 = 0x55;
        NVMCON2 = 0xAA;
        NVMCON1bits.WR = 1;
    }
}

void DATAEE_WriteByte(unsigned char bAdd, unsigned char bData)
{
    NVMADRL = (bAdd & 0xFF);
    NVMDAT = bData;
    NVMCON1bits.NVMREG = 0;
    NVMCON1bits.WREN = 1;
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    // Wait for write to complete
    while (NVMCON1bits.WR)
    {
    }

    NVMCON1bits.WREN = 0;
}

unsigned char DATAEE_ReadByte(unsigned char bAdd)
{
    NVMADRL = bAdd;
    NVMCON1bits.NVMREG = 0;
    NVMCON1bits.RD = 1;
    NOP();  // NOPs may be required for latency at high frequencies
    NOP();

    return (NVMDAT);
}

void uart_tx(unsigned char value) 
{
    TX1REG = value;
    while (!TX1STAbits.TRMT);
}

unsigned char uart_rx() 
{
    if (RC1STAbits.OERR) {
        /* overrun error, reset CREN */
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }

    while (!PIR3bits.RCIF);
    return RC1REG;
}
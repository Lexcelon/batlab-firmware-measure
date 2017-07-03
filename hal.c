#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "hal.h"

#define FIRMWARE_VER 2

volatile uint16_t cellregs[4][CELLREGS_SIZE] = {0};
volatile uint16_t unitregs[UNITREGS_SIZE] = {0};
volatile uint16_t commregs[COMMREGS_SIZE] = {0};
packet p,q; //incoming,outgoing

volatile uint32_t CHARGE[4] = {0}; //this is separate from the regfile so we don't have to copy it in the ISR
volatile uint8_t SINE_COUNTER = 0;
bool initialized = false;
extern bool flag_restart;

uint8_t SINETABLE[256] = //if mapped directly to duty, this goes from 0 to 4 amps.
{
0,0,0,1,1,1,2,2,
3,4,4,5,6,7,8,9,11,12,
13,15,16,18,20,21,23,25,27,29,
31,33,35,37,39,42,44,46,49,51,
54,56,59,62,64,67,70,73,76,79,
81,84,87,90,93,96,99,103,106,109,
112,115,118,121,124,128,128,131,134,137,140,143,146,149,152,156,
159,162,165,168,171,174,176,179,182,185,
188,191,193,196,199,201,204,206,209,211,
213,216,218,220,222,224,226,228,230,232,
234,235,237,239,240,242,243,244,246,247,
248,249,250,251,251,252,253,253,254,254,
254,255,255,255,255,255,255,255,254,254,
253,253,252,252,251,250,249,248,247,246,
245,244,242,241,239,238,236,235,233,231,
229,227,225,223,221,219,217,215,212,210,
207,205,202,200,197,195,192,189,186,184,
181,178,175,172,169,166,163,160,157,154,
151,148,145,142,138,135,132,129,126,123,
120,117,113,110,107,104,101,98,95,92,
89,86,83,80,77,74,71,69,66,63,
60,58,55,53,50,48,45,43,40,38,
36,34,32,30,28,26,24,22,20,19,
17,16,14,13,11,10,9,8,7,6,
5,4,3,3,2,2,1,1,0,0,
0,0
};

//******************************************************************************
//* app_initialize
//******************************************************************************
void app_initialize(void)
{
    uint32_t i;
    uint8_t temp[2];
    
    //Initialize unit namespace
    temp[0] = DATAEE_ReadByte(EEP_SERIAL_NUM); //load in serial number
    temp[1] = DATAEE_ReadByte(EEP_SERIAL_NUM+1);
    memcpy_2(&(unitregs[REG_SERIAL_NUM]),&(temp[0]));
    
    temp[0] = DATAEE_ReadByte(EEP_DEVICE_ID); //load in device ID
    temp[1] = DATAEE_ReadByte(EEP_DEVICE_ID+1);
    memcpy_2(&(unitregs[REG_DEVICE_ID]),&(temp[0]));
    
    unitregs[REG_FIRMWARE_VER] = FIRMWARE_VER;
    unitregs[REG_VCC] = 0x0000;
    unitregs[REG_SINE_FREQ] = 1; //39.0625 Hz
    unitregs[REG_SYSTEM_TIMER] = 0;
    unitregs[REG_SETTINGS] = 0x0000;
    unitregs[REG_SINE_OFFSET] = 16; //minimum at 0.125 amp.
    unitregs[REG_SINE_MAGDIV] = 2; //0= 2 Amp pp.  1 = 1 Amp pp; 2 = 0.5 amp pp; 3 = 0.25 amp pp
    unitregs[REG_LOCK] = LOCK_UNLOCKED;
    
    temp[0] = DATAEE_ReadByte(EEP_VOLT_CH_CALIB_OFF);
    temp[1] = DATAEE_ReadByte(EEP_VOLT_CH_CALIB_OFF+1);
    memcpy_2(&(unitregs[REG_VOLT_CH_CALIB_OFF]),&(temp[0]));
        
    temp[0] = DATAEE_ReadByte(EEP_VOLT_CH_CALIB_SCA);
    temp[1] = DATAEE_ReadByte(EEP_VOLT_CH_CALIB_SCA+1);
    memcpy_2(&(unitregs[REG_VOLT_CH_CALIB_SCA]),&(temp[0]));
    
    temp[0] = DATAEE_ReadByte(EEP_VOLT_DC_CALIB_OFF);
    temp[1] = DATAEE_ReadByte(EEP_VOLT_DC_CALIB_OFF+1);
    memcpy_2(&(unitregs[REG_VOLT_DC_CALIB_OFF]),&(temp[0]));
        
    temp[0] = DATAEE_ReadByte(EEP_VOLT_DC_CALIB_SCA);
    temp[1] = DATAEE_ReadByte(EEP_VOLT_DC_CALIB_SCA+1);
    memcpy_2(&(unitregs[REG_VOLT_DC_CALIB_SCA]),&(temp[0]));
    
    
    //initialize COMMS namespace
    commregs[REG_LED0] = LED_OFF;
    commregs[REG_LED1] = LED_OFF;
    commregs[REG_LED2] = LED_OFF;
    commregs[REG_LED3] = LED_OFF;
    commregs[REG_PSU ] = LED_OFF;

    //initialize CELL namespace
    for(i=0;i<4;i++)
    {
        temp[0] = DATAEE_ReadByte(EEP_CURRENT_CALIB_OFF+2*i);
        temp[1] = DATAEE_ReadByte(EEP_CURRENT_CALIB_OFF+2*i+1);
        memcpy_2(&(cellregs[i][REG_CURRENT_CALIB_OFF]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_CURRENT_CALIB_SCA+2*i);
        temp[1] = DATAEE_ReadByte(EEP_CURRENT_CALIB_SCA+2*i+1);
        memcpy_2(&(cellregs[i][REG_CURRENT_CALIB_SCA]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_TEMP_CALIB_R+2*i);
        temp[1] = DATAEE_ReadByte(EEP_TEMP_CALIB_R+2*i+1);
        memcpy_2(&(cellregs[i][REG_TEMP_CALIB_R]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_TEMP_CALIB_B+2*i);
        temp[1] = DATAEE_ReadByte(EEP_TEMP_CALIB_B+2*i+1);
        memcpy_2(&(cellregs[i][REG_TEMP_CALIB_B]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_CURRENT_CALIB_PP+2*i);
        temp[1] = DATAEE_ReadByte(EEP_CURRENT_CALIB_PP+2*i+1);
        memcpy_2(&(cellregs[i][REG_CURRENT_CALIB_PP]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_VOLTAGE_CALIB_PP+2*i);
        temp[1] = DATAEE_ReadByte(EEP_VOLTAGE_CALIB_PP+2*i+1);
        memcpy_2(&(cellregs[i][REG_VOLTAGE_CALIB_PP]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_CURR_CALIB_PP_OFF+2*i);
        temp[1] = DATAEE_ReadByte(EEP_CURR_CALIB_PP_OFF+2*i+1);
        memcpy_2(&(cellregs[i][REG_CURR_CALIB_PP_OFF]),&(temp[0]));
        
        temp[0] = DATAEE_ReadByte(EEP_VOLT_CALIB_PP_OFF+2*i);
        temp[1] = DATAEE_ReadByte(EEP_VOLT_CALIB_PP_OFF+2*i+1);
        memcpy_2(&(cellregs[i][REG_VOLT_CALIB_PP_OFF]),&(temp[0]));
        
        cellregs[i][REG_MODE              ] = MODE_NO_CELL;
        cellregs[i][REG_ERROR             ] = 0x0000;
        cellregs[i][REG_STATUS            ] = 0x0000;
        cellregs[i][REG_CURRENT_SETPOINT  ] = 256;  //2A  @5.0V ref out of 640 5V->5A
        cellregs[i][REG_REPORT_INTERVAL   ] = 0;    //set it off initially; 10= 0.1 sec
        cellregs[i][REG_TEMPERATURE       ] = 25093;//int16
        cellregs[i][REG_CURRENT           ] = 31999;//int16
        cellregs[i][REG_VOLTAGE           ] = 20390;//int16
        cellregs[i][REG_CHARGEL           ] = 0x0000;//low16 of int32
        cellregs[i][REG_CHARGEH           ] = 0x0000;//high16 of int32
        cellregs[i][REG_VOLTAGE_LIMIT_CHG ] = 30584; //4.2V @4.5V ref int16
        cellregs[i][REG_VOLTAGE_LIMIT_DCHG] = 20389; //2.8V @4.5V ref int16
        cellregs[i][REG_CURRENT_LIMIT_CHG ] = 32000; //4A   @4.096V ref = 4.096A int16    20mOhms * gain 50 = 3V->3A
        cellregs[i][REG_CURRENT_LIMIT_DCHG] = 32000; //4A   @4.096V ref = 4.096A int16    20mOhms * gain 50 = 3V->3A
        cellregs[i][REG_TEMP_LIMIT_CHG    ] = 25092; //45 deg C units ???? @5.0A int16
        cellregs[i][REG_TEMP_LIMIT_DCHG   ] = 20825;//65 deg C units ???? @5.0V int16
        
        
    }
    initialized = true;
}
//******************************************************************************
//* check_for_uart_packet - reads buffer for uart packet - returns length or 0
//******************************************************************************
uint8_t check_for_uart_packet()
{  
    //search through the buffer until we find a packet
    while(EUSART_Peek() != PACKET_START_BYTE )
    {
        if(eusartRxCount < USB_RX_PACKET_LEN) 
        {
            return 0; //full packet not in buffer
        } 
        getch();
    }
    if(eusartRxCount < USB_RX_PACKET_LEN) 
    {
        return 0; //full packet not in buffer
    }
    return USB_RX_PACKET_LEN;
}
//******************************************************************************
//* get_uart_packet - read found packet into buffer - return length or 0 if none
//******************************************************************************
uint8_t get_uart_packet()
{
    uint8_t i;
    p.len = check_for_uart_packet(); //returns 0 if no packet
    for(i=0;i<p.len;i++)
    {
        p.payload[i] = getch();
    }
    return p.len;
}
//******************************************************************************
//* handle_uart_packet - do what the packet says to do
//******************************************************************************
void handle_uart_packet()
{
    uint8_t cell,addr,master_write;
    cell = (p.payload[1] & 0x03);
    addr = (p.payload[2] & 0x7F);
    master_write = (p.payload[2] & 0x80);
    
    q.len = USB_RX_PACKET_LEN;
    q.payload[0] = p.payload[0];
    q.payload[1] = p.payload[1];
    q.payload[2] = p.payload[2];
    q.payload[3] = 0x01; //failed write
    q.payload[4] = 0x01; //failed write
    
    if(p.payload[1] == NAMESPACE_COMMS) //update of LED state from COMMS
    {
        if(master_write) //writing a value to the comms pic means this was an ack message
        {
            q.len = 0; //don't send anything because this packet was a response
        }
        else            //this is the results of a read
        {
            if(addr < COMMREGS_SIZE)
            {
                memcpy_2(&(commregs[addr]),&(p.payload[3]));
            }
            q.len = 0; //don't send anything because this packet was a response
        }
    }
    else if(p.payload[1] == NAMESPACE_UNIT)
    {
        if(master_write) //pc writing to a unit register
        {
            if(addr == REG_SERIAL_NUM && (unitregs[REG_SERIAL_NUM] == 0xFFFF || unitregs[REG_SETTINGS] & SET_DEBUG ) )
            {
                DATAEE_WriteByte(EEP_SERIAL_NUM,p.payload[3]); //serial number only writable once
                DATAEE_WriteByte(EEP_SERIAL_NUM+1,p.payload[4]);
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if(addr == REG_DEVICE_ID && (unitregs[REG_DEVICE_ID] == 0xFFFF || unitregs[REG_SETTINGS] & SET_DEBUG) )
            {
                DATAEE_WriteByte(EEP_DEVICE_ID,p.payload[3]); //serial number only writable once
                DATAEE_WriteByte(EEP_DEVICE_ID+1,p.payload[4]);
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if (addr == REG_SINE_FREQ)
            {
                SINE_COUNTER = 0;
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00; 
            }
            else if (addr == REG_BOOTLOAD)
            {
                DATAEE_WriteByte(EEP_BOOTLOAD_ADDR,0xFE);
                flag_restart = 1;
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if(addr == REG_VOLT_CH_CALIB_OFF)
            {
                DATAEE_WriteByte(EEP_VOLT_CH_CALIB_OFF,p.payload[3]);
                DATAEE_WriteByte(EEP_VOLT_CH_CALIB_OFF+1,p.payload[4]);
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if(addr == REG_VOLT_CH_CALIB_SCA)
            {
                DATAEE_WriteByte(EEP_VOLT_CH_CALIB_SCA,p.payload[3]);
                DATAEE_WriteByte(EEP_VOLT_CH_CALIB_SCA+1,p.payload[4]);
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if(addr == REG_VOLT_DC_CALIB_OFF)
            {
                DATAEE_WriteByte(EEP_VOLT_DC_CALIB_OFF,p.payload[3]);
                DATAEE_WriteByte(EEP_VOLT_DC_CALIB_OFF+1,p.payload[4]);
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if(addr == REG_VOLT_DC_CALIB_SCA)
            {
                DATAEE_WriteByte(EEP_VOLT_DC_CALIB_SCA,p.payload[3]);
                DATAEE_WriteByte(EEP_VOLT_DC_CALIB_SCA+1,p.payload[4]);
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
            else if (addr == REG_SETTINGS || addr == REG_SINE_OFFSET || addr == REG_SINE_MAGDIV || addr == REG_LED_MESSAGE || addr == REG_LOCK)
            {
                memcpy_2(&(unitregs[addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00; 
            }
        }
        else //pc reading from a register
        {
            if(addr < UNITREGS_SIZE)
            {
                INTERRUPT_GlobalInterruptDisable();
                memcpy_2(&(q.payload[3]),&(unitregs[addr])); 
                INTERRUPT_GlobalInterruptEnable();
            }
        }
    }
    else if(p.payload[1] <= NAMESPACE_CELL3 ) 
    {
        if(master_write)//PC write to reg
        {
            if(addr == REG_CURRENT_CALIB_OFF)
            {
                DATAEE_WriteByte(EEP_CURRENT_CALIB_OFF+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_CURRENT_CALIB_OFF+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_CURRENT_CALIB_SCA)
            {
                DATAEE_WriteByte(EEP_CURRENT_CALIB_SCA+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_CURRENT_CALIB_SCA+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_TEMP_CALIB_R)
            {
                DATAEE_WriteByte(EEP_TEMP_CALIB_R+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_TEMP_CALIB_R+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_TEMP_CALIB_B)
            {
                DATAEE_WriteByte(EEP_TEMP_CALIB_B+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_TEMP_CALIB_B+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_CURRENT_CALIB_PP)
            {
                DATAEE_WriteByte(EEP_CURRENT_CALIB_PP+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_CURRENT_CALIB_PP+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_VOLTAGE_CALIB_PP)
            {
                DATAEE_WriteByte(EEP_VOLTAGE_CALIB_PP+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_VOLTAGE_CALIB_PP+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_CURR_CALIB_PP_OFF)
            {
                DATAEE_WriteByte(EEP_CURR_CALIB_PP_OFF+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_CURR_CALIB_PP_OFF+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_VOLT_CALIB_PP_OFF)
            {
                DATAEE_WriteByte(EEP_VOLT_CALIB_PP_OFF+2*cell,p.payload[3]);
                DATAEE_WriteByte(EEP_VOLT_CALIB_PP_OFF+2*cell+1,p.payload[4]);
            }
            else if(addr == REG_CHARGEH || addr == REG_CHARGEL)
            {
                CHARGE[cell] = 0;
            }
            if(addr < CELLREGS_SIZE)
            {
                memcpy_2(&(cellregs[cell][addr]),&(p.payload[3]));
                q.payload[3] = 0x00;
                q.payload[4] = 0x00;
            }
        } 
        else //PC read register
        {
            if(addr < CELLREGS_SIZE)
            {
                INTERRUPT_GlobalInterruptDisable();
                memcpy_2(&(q.payload[3]),&(cellregs[cell][addr]));
                INTERRUPT_GlobalInterruptEnable();
            }
        }
    }
}
//******************************************************************************
//* create_led_packet
//******************************************************************************
void create_led_packet(uint8_t cell,uint16_t state)
{
    q.len = USB_RX_PACKET_LEN;
    q.payload[0] = PACKET_START_BYTE;
    q.payload[1] = NAMESPACE_COMMS;
    switch(cell)
    {
        case 0: q.payload[2] = REG_LED0 | 0x80; break;
        case 1: q.payload[2] = REG_LED1 | 0x80; break;
        case 2: q.payload[2] = REG_LED2 | 0x80; break;
        case 3: q.payload[2] = REG_LED3 | 0x80; break;
    }
    memcpy_2(&(q.payload[3]),&state);
}
//******************************************************************************
//* create_psu_packet - requests to receive the state of the external PSU
//******************************************************************************
void create_psu_packet()
{
    q.len = USB_RX_PACKET_LEN;
    q.payload[0] = PACKET_START_BYTE;
    q.payload[1] = NAMESPACE_COMMS;
    q.payload[2] = REG_PSU;
    q.payload[3] = 0x00;
    q.payload[4] = 0x00;
}
//******************************************************************************
//* create_stream_packet
//******************************************************************************
void create_stream_packet(uint8_t celladdr)
{
    q.len = STREAM_PACKET_LEN;
    q.payload[0] = STREAM_PACKET_START_BYTE;
    q.payload[1] = celladdr;
    q.payload[2] = 0x00;
    
    INTERRUPT_GlobalInterruptDisable();
    memcpy_2(&(q.payload[3]),&(cellregs[celladdr][REG_MODE]));
    memcpy_2(&(q.payload[5]),&(cellregs[celladdr][REG_STATUS]));
    memcpy_2(&(q.payload[7]),&(cellregs[celladdr][REG_TEMPERATURE]));
    memcpy_2(&(q.payload[9]),&(cellregs[celladdr][REG_CURRENT]));
    memcpy_2(&(q.payload[11]),&(cellregs[celladdr][REG_VOLTAGE]));
    INTERRUPT_GlobalInterruptEnable();
}
//******************************************************************************
//* send_uart_packet
//******************************************************************************
void send_uart_packet()
{
    uint8_t i;
    for(i=0;i<q.len;i++)
    {
        putch(q.payload[i]);
    }
}

//******************************************************************************
//* set_flags - use available information to compute new status flags
//*                    READS and WRITES status
//******************************************************************************            
void set_flags(uint8_t i)        //use inputs to decide what the next state will be
{
    static uint16_t error;
    static uint16_t mode;
    static uint16_t status;
    static int16_t voltage;
    static int16_t current;
    static uint16_t temperature;
    
    error = cellregs[i][REG_ERROR];
    mode = cellregs[i][REG_MODE];
    status = cellregs[i][REG_STATUS];
    
    INTERRUPT_GlobalInterruptDisable();     //The measurements are taken on interrupts, so make sure they don't change while being read.
        voltage = cellregs[i][REG_VOLTAGE];
        current = cellregs[i][REG_CURRENT];
        temperature = cellregs[i][REG_TEMPERATURE];
        cellregs[i][REG_CHARGEL] = CHARGE[i] & 0xFFFF;
        cellregs[i][REG_CHARGEH] = CHARGE[i] >> 16;
    INTERRUPT_GlobalInterruptEnable();
    
    // perform safety and status checks and update the status variable 
    status = ( (voltage > -BACKWARDS_VOLTAGE && voltage < NC_VOLTAGE) || voltage > 32700) ? status | STAT_NO_CELL : status & ~STAT_NO_CELL;
    status = (voltage < -BACKWARDS_VOLTAGE) ? status | STAT_BACKWARDS : status & ~STAT_BACKWARDS;
    status = (voltage > (int16_t)cellregs[i][REG_VOLTAGE_LIMIT_CHG] ) ? status | STAT_VOLTAGE_LIMIT_CHG : status & ~STAT_VOLTAGE_LIMIT_CHG;
    status = (voltage < (int16_t)cellregs[i][REG_VOLTAGE_LIMIT_DCHG]) ? status | STAT_VOLTAGE_LIMIT_DCHG : status & ~STAT_VOLTAGE_LIMIT_DCHG;
    status = (current > (int16_t)cellregs[i][REG_CURRENT_LIMIT_CHG]) ? status | STAT_CURRENT_LIMIT_CHG : status & ~STAT_CURRENT_LIMIT_CHG;
    status = (current > (int16_t)cellregs[i][REG_CURRENT_LIMIT_DCHG]) ? status | STAT_CURRENT_LIMIT_DCHG : status & ~STAT_CURRENT_LIMIT_DCHG;
    //note that the temperature adc variable has an inverse exp relationship with real Temperature, hence the '<' comparisons
    status = (temperature < cellregs[i][REG_TEMP_LIMIT_CHG]) ? status | STAT_TEMP_LIMIT_CHG : status & ~STAT_TEMP_LIMIT_CHG;
    status = (temperature < cellregs[i][REG_TEMP_LIMIT_DCHG]) ? status | STAT_TEMP_LIMIT_DCHG : status & ~STAT_TEMP_LIMIT_DCHG;
    status = (!commregs[REG_PSU]) ? status | STAT_NO_PSU : status & ~STAT_NO_PSU;
    status = (unitregs[REG_SERIAL_NUM] == 0xFFFF || unitregs[REG_DEVICE_ID] == 0xFFFF) ? status | STAT_NOT_INITIALIZED : status & ~STAT_NOT_INITIALIZED;
    status = (unitregs[REG_VOLT_CH_CALIB_SCA] == 0xFFFF || cellregs[i][REG_CURRENT_CALIB_SCA] == 0xFFFF) ? status | STAT_NOT_CALIBRATED : status & ~STAT_NOT_CALIBRATED;

    //state machine for cell MODE
    switch(mode)
    {
        case MODE_NO_CELL: 
            if(!(status & STAT_NO_CELL)) {mode = MODE_IDLE;}
            if((status & STAT_BACKWARDS)) {mode = MODE_BACKWARDS;}
            LED_CMD(i,LED_OFF);
            break;
        case MODE_BACKWARDS: 
            if(!(status & STAT_BACKWARDS)) {mode = MODE_IDLE;}
            LED_CMD(i,LED_FLASH_FAST);
            break;
        case MODE_IDLE: 
            if(status & STAT_NO_CELL) {mode = MODE_NO_CELL;}
            if(status & STAT_BACKWARDS) {mode = MODE_BACKWARDS;} //backwards is the second if so it trumps no cell
            error = 0; //errors do not persist in IDLE state.
            LED_CMD(i,LED_BLIP);
            break;
        case MODE_CHARGE:
            LED_CMD(i,LED_RAMP_UP);
            if(unitregs[REG_SETTINGS] & SET_SAFETY_DISABLE){break;}
            if(status & STAT_VOLTAGE_LIMIT_CHG) {mode = MODE_STOPPED; error |= ERR_VOLTAGE_LIMIT_CHG;}
            if(status & STAT_VOLTAGE_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_VOLTAGE_LIMIT_DCHG;}
            if(status & STAT_CURRENT_LIMIT_CHG) {mode = MODE_STOPPED; error |= ERR_CURRENT_LIMIT_CHG;}
            if(status & STAT_TEMP_LIMIT_CHG) {mode = MODE_STOPPED; error |= ERR_TEMP_LIMIT_CHG;}
            if(status & STAT_NO_PSU) {mode = MODE_STOPPED; error |= ERR_NO_PSU;}
            break;
        case MODE_IMPEDANCE:
            LED_CMD(i,LED_SINE);
            if(unitregs[REG_SETTINGS] & SET_SAFETY_DISABLE){break;}
            if(status & STAT_VOLTAGE_LIMIT_CHG) {mode = MODE_STOPPED; error |= ERR_VOLTAGE_LIMIT_CHG;}
            if(status & STAT_VOLTAGE_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_VOLTAGE_LIMIT_DCHG;}
            if(status & STAT_CURRENT_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_CURRENT_LIMIT_DCHG;}
            if(status & STAT_TEMP_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_TEMP_LIMIT_DCHG;}
            break;
        case MODE_DISCHARGE:
            LED_CMD(i,LED_RAMP_DOWN);
            if(unitregs[REG_SETTINGS] & SET_SAFETY_DISABLE){break;}
            if(status & STAT_VOLTAGE_LIMIT_CHG) {mode = MODE_STOPPED; error |= ERR_VOLTAGE_LIMIT_CHG;}
            if(status & STAT_VOLTAGE_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_VOLTAGE_LIMIT_DCHG;}
            if(status & STAT_CURRENT_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_CURRENT_LIMIT_DCHG;}
            if(status & STAT_TEMP_LIMIT_DCHG) {mode = MODE_STOPPED; error |= ERR_TEMP_LIMIT_DCHG;}
            break;
        case MODE_STOPPED:
            LED_CMD(i,LED_ON);
            break;
    }
    
    //control the Message LED if not in debug mode.
    if(!(unitregs[REG_SETTINGS] & SET_DEBUG))
    {
        if( (status & (STAT_NOT_CALIBRATED | STAT_NOT_INITIALIZED)) )
        {
            SET_LED_MSG(LED_FLASH_FAST);
        }
        else
        {
            SET_LED_MSG(unitregs[REG_LED_MESSAGE]);
        }
    }

    cellregs[i][REG_ERROR] = error;
    cellregs[i][REG_MODE] = mode;
    cellregs[i][REG_STATUS] = status;
}   
//******************************************************************************
//* send_streams - sends a stream packet if we're scheduled for that
//******************************************************************************
void send_streams(uint8_t i)
{
    uint16_t timer;
    
    INTERRUPT_GlobalInterruptDisable();
    timer = unitregs[REG_SYSTEM_TIMER];
    INTERRUPT_GlobalInterruptEnable();
    if(cellregs[i][REG_REPORT_INTERVAL] == 0){return;}
    
    static uint16_t last_msg[4] = {0};
    if(timer - last_msg[i] > cellregs[i][REG_REPORT_INTERVAL])
    {
        last_msg[i] = timer;
        create_stream_packet(i);
        send_uart_packet();
    }
}
//******************************************************************************
//* send_psu - requests update of the PSU infor if it has been longer than 1 sec
//******************************************************************************
void send_psu()
{
    static uint16_t last_msg = 0;
    uint16_t timer;
    
    INTERRUPT_GlobalInterruptDisable();
    timer = unitregs[REG_SYSTEM_TIMER];
    INTERRUPT_GlobalInterruptEnable();
    
    if(timer - last_msg > 10)
    {
        last_msg = timer;
        create_psu_packet();
        send_uart_packet();
    }
}
//******************************************************************************
//* set_relays - uses status and mode information to control direction relays
//******************************************************************************
void set_relays(uint8_t i)       //set the outputs for the next state
{
    if(cellregs[i][REG_MODE] == MODE_CHARGE)
    {
        switch(i)
        {
            case 0: RLY0_SetHigh(); break;
            case 1: RLY1_SetHigh(); break;
            case 2: RLY2_SetHigh(); break;
            case 3: RLY3_SetHigh(); break;
        } 
    }
    else
    {
        switch(i)
        {
            case 0: RLY0_SetLow(); break;
            case 1: RLY1_SetLow(); break;
            case 2: RLY2_SetLow(); break;
            case 3: RLY3_SetLow(); break;
        }   
    }
}
//******************************************************************************
//* set_currents - uses status and mode information to control current output
//*                 only reads status and mode
//******************************************************************************
void set_currents(uint8_t i)
{
    uint16_t mode = cellregs[i][REG_MODE];

    if(mode == MODE_CHARGE || mode == MODE_DISCHARGE)
    {
        SetDuty(i,cellregs[i][REG_CURRENT_SETPOINT]);
    }
    else if (mode == MODE_IMPEDANCE)
    {
        //do Nothing here because current is set in the 10khz ISR.
    }
    else //no current should be flowing
    {
       SetDuty(i,0); //override current setpoint and stop current flow  
    }
}
//******************************************************************************
//* set_fan - uses status and mode information to control fan
//******************************************************************************
void set_fan(uint8_t i)       //set the outputs for the next state
{
    static uint16_t fan_flag = 0;
    uint16_t mode = cellregs[i][REG_MODE];
    uint16_t status = cellregs[i][REG_STATUS];
    static uint16_t fan_on_timer = 0;
    static uint8_t flag_startup = 1;
    uint16_t timer;
    
    INTERRUPT_GlobalInterruptDisable();
    timer = unitregs[REG_SYSTEM_TIMER];
    INTERRUPT_GlobalInterruptEnable();

    if(i==0)
    {
        fan_flag = 0;
    }
    
    if(mode == MODE_CHARGE || mode == MODE_DISCHARGE || mode == MODE_IMPEDANCE)
    {
        fan_flag++;
        fan_on_timer = timer;
        flag_startup = 0;
    }
    if(status & STAT_TEMP_LIMIT_CHG || status & STAT_TEMP_LIMIT_DCHG){fan_flag++;}
    if(timer - fan_on_timer > 1200UL || flag_startup) //greater than 2 minutes have past since fan needed
    {
       fan_on_timer = timer - 1201UL; //keep the expire time at 2 minutes so it doesn't roll over
    }
    else
    {
        fan_flag++; //fan has not expired yet 
    }
        
    if(i == 3)
    {
        if(fan_flag)
        {
            FAN1_SetHigh();
        }
        else        
        {
            FAN1_SetLow();
        }
    }
}
//******************************************************************************
//* Hardware level helper functions
//******************************************************************************
void LED_CMD(uint8_t led,uint16_t state)
{
    static uint16_t last_msg[4] = {0};
    uint16_t timer;
    
    INTERRUPT_GlobalInterruptDisable();
    timer = unitregs[REG_SYSTEM_TIMER];
    INTERRUPT_GlobalInterruptEnable();
    //only send the message if the LED is wrong or if it has been more than 2 seconds since the last update
    
    if( commregs[led] != state || timer - last_msg[led] > 20 )
    {
        last_msg[led] = timer;
        create_led_packet(led,state);
        send_uart_packet();
        commregs[led] = state;
    } 
    
}
//******************************************************************************
//* SET_LED_MSG - control the onboard message LED
//******************************************************************************
void SET_LED_MSG(uint16_t state)
{
    static uint16_t last_msg = 0;
    uint16_t timer;
    
    INTERRUPT_GlobalInterruptDisable();
    timer = unitregs[REG_SYSTEM_TIMER];
    INTERRUPT_GlobalInterruptEnable();
    if(state == LED_FLASH_FAST)
    {
        if(timer - last_msg > 8)
        {
            last_msg = timer;
            LED_MSG_SetHigh();  
        }
        else if(timer - last_msg > 4)
        {
            LED_MSG_SetLow();
        }
    }
    else if (state == LED_FLASH_SLOW)
    {
        if(timer - last_msg > 16)
        {
            last_msg = timer;
            LED_MSG_SetHigh();  
        }
        else if(timer - last_msg > 8)
        {
            LED_MSG_SetLow();
        }
    }
    else if (state == LED_ON)
    {
        LED_MSG_SetLow();
    }
    else
    {
        LED_MSG_SetHigh();
    }
}

void ADC_VDD(void)
{
    ADREF = 0x00;
    //ADACQ = 0x20; //32 us aquisition time
    while(!FVR_IsOutputReady());
}

void ADC_FVR(void)
{
    ADREF = 0x03;
    //ADACQ = 0x03; //3 us aquisition time
    while(!FVR_IsOutputReady());
}

void memcpy_2(void *dest,void *src)
{
    char *csrc = (char*)src;
    char *cdest = (char*)dest;
    cdest[0] = csrc[0];
    cdest[1] = csrc[1];
}

uint16_t ADC_Get15BitOversample(adcc_channel_t channel)
{
    uint8_t i;
    uint16_t result=0;
    ADPCH = channel;    
    for(i=0;i<32;i++) //15 us per loop --> almost 1 ms total
    {
        // Start the conversion
        ADCON0bits.ADGO = 1;
        // Wait for the conversion to finish
        while (ADCON0bits.ADGO);
        // Conversion finished, return the result
        result += ((ADRESH << 8) + ADRESL);
    }
    return result;
}

uint16_t ADC_Get10BitSample(adcc_channel_t channel)
{
    ADPCH = channel;    
    // Start the conversion
    ADCON0bits.ADGO = 1;
    // Wait for the conversion to finish
    while (ADCON0bits.ADGO);
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

uint16_t ADC_Get10BitCurrent(uint8_t cell)
{
    static adcc_channel_t channel[4] = {ISENSE0,ISENSE1,ISENSE2,ISENSE3};
    ADPCH = channel[cell];    
    // Start the conversion
    ADCON0bits.ADGO = 1;
    // Wait for the conversion to finish
    while (ADCON0bits.ADGO);
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

uint16_t ADC_Get12BitCurrent(uint8_t cell)
{
    static adcc_channel_t channel[4] = {ISENSE0,ISENSE1,ISENSE2,ISENSE3};
    uint16_t sum = 0;
    ADPCH = channel[cell];    
    
    ADCON0bits.ADGO = 1; // Start the conversion
    while (ADCON0bits.ADGO); // Wait for the conversion to finish
    sum += ((ADRESH << 8) + ADRESL);
    
    ADCON0bits.ADGO = 1; // Start the conversion
    while (ADCON0bits.ADGO); // Wait for the conversion to finish
    sum += ((ADRESH << 8) + ADRESL);
    
    ADCON0bits.ADGO = 1; // Start the conversion
    while (ADCON0bits.ADGO); // Wait for the conversion to finish
    sum += ((ADRESH << 8) + ADRESL);
    
    ADCON0bits.ADGO = 1; // Start the conversion
    while (ADCON0bits.ADGO); // Wait for the conversion to finish
    sum += ((ADRESH << 8) + ADRESL);
    
    // Conversion finished, return the result
    return sum;
}

int16_t SPI_Get12BitSample(uint8_t cell) //50 us
{
    union bytes             //cs must see a falling edge first
    {                       // send 0x08 | i for first byte
        uint8_t byte[2];    //discard result
        int16_t voltage;   //then send 0x00
    } result;               // result & 0x1F is high byte

    SS_SetLow();            //spi mode 0,0
    result.byte[1] = SPI1_Exchange8bit(0x08 | cell);
    result.byte[1] = SPI1_Exchange8bit(0x00) & 0x1F;
    result.byte[0] = SPI1_Exchange8bit(0x00);
    if(result.byte[1] & 0x10)
    {
        result.byte[1] |= 0xF0; //sign extend to 16 bit number
    }
    SS_SetHigh();
    return result.voltage;
}

void SetDuty(uint8_t cell, uint16_t duty) //duty should be 15 bit unsigned
{
    static int8_t compensation[4] = {0};
    static uint16_t cprev[4] = {0};
    uint16_t current;
    
    INTERRUPT_GlobalInterruptDisable();
    current = cellregs[cell][REG_CURRENT];
    INTERRUPT_GlobalInterruptEnable();
    //duty Cycle is out of 640 if PR2 = 159
    //640 = 5V = 10A
    //     VCC
    //duty/640 * 5V = 2.048V * reg / 2**15
    //duty * 5 * 2**15 / (640 * 2.048 ) = reg
    if(duty > 0)
    {
        if(unitregs[REG_SETTINGS] & SET_TRIM_OUTPUT)
        {
            if( current != cprev[cell] )
            {
                cellregs[cell][REG_COMPENSATION] = compensation[cell];
                if( (current << 1) > ((duty + 1) * 125)  )
                {  //If we are trying to send less than actual, then send less
                    --compensation[cell];
                }
                else if ((current << 1) < ((duty ) * 125)  )
                {
                    ++compensation[cell];   
                }
                cprev[cell] = current; 
            }
            duty = (int16_t)duty + compensation[cell]; //if we aren't too far off the mark, duty stays the same
        } 
        else if(unitregs[REG_SETTINGS] & SET_VCC_COMPENSATION)
        {
            uint32_t temp;
            INTERRUPT_GlobalInterruptDisable();
            temp = (uint32_t)((unitregs[REG_VCC] + 16) >> 5) * (uint32_t)duty * 625UL;
            INTERRUPT_GlobalInterruptEnable();
            duty = (temp + (262144UL)) >> 19;
        }
        if(duty > 900) {duty = 0;}
        if(duty > 640) {duty = 640;}
    }
    cellregs[cell][REG_DUTY] = duty;
    switch(cell)
    { 
        case 0: PWM1_LoadDutyValue(duty); break;
        case 1: PWM4_LoadDutyValue(duty); break;
        case 2: PWM3_LoadDutyValue(duty); break;
        case 3: PWM2_LoadDutyValue(duty); break;
    }
}

void TMR0_ISR(void) //10 Hz
{
    //TMR0 Unused
}

void TMR2_ISR(void) //10 khz
{
    static uint16_t ctr = 0;
    if(initialized == false){return;}
    if(unitregs[REG_SETTINGS] & SET_DEBUG){LED_MSG_SetLow();}
    if(ctr == 999){unitregs[REG_SYSTEM_TIMER]++;ctr = 0;} //10Hz system timer
    else {ctr++;}
    SINE_COUNTER+=unitregs[REG_SINE_FREQ];
    
    if(cellregs[0][REG_MODE]==MODE_IMPEDANCE){PWM1_LoadDutyValue(  unitregs[REG_SINE_OFFSET] + (SINETABLE[SINE_COUNTER] >> unitregs[REG_SINE_MAGDIV]) );}
    if(cellregs[1][REG_MODE]==MODE_IMPEDANCE){PWM4_LoadDutyValue(  unitregs[REG_SINE_OFFSET] + (SINETABLE[SINE_COUNTER] >> unitregs[REG_SINE_MAGDIV]) );}
    if(cellregs[2][REG_MODE]==MODE_IMPEDANCE){PWM3_LoadDutyValue(  unitregs[REG_SINE_OFFSET] + (SINETABLE[SINE_COUNTER] >> unitregs[REG_SINE_MAGDIV]) );}
    if(cellregs[3][REG_MODE]==MODE_IMPEDANCE){PWM2_LoadDutyValue(  unitregs[REG_SINE_OFFSET] + (SINETABLE[SINE_COUNTER] >> unitregs[REG_SINE_MAGDIV]) );}
    
    measurement_handler();
    if(unitregs[REG_SETTINGS] & SET_DEBUG){LED_MSG_SetHigh();}
    
}

void measurement_handler()
{
    static uint16_t cmax[4] = {0};
    static uint16_t cmin[4] = {0};
    static uint32_t csum[4] = {0};
    static uint16_t vmax[4] = {0};
    static uint16_t vmin[4] = {0};
    static int32_t  vsum[4] = {0};
    static uint32_t tsum[4] = {0};
    static uint32_t vccsum = 0;
    
    static uint16_t ctr = 1;
    static uint8_t  timeslice = 0;
    
    static uint16_t current;
    static int16_t  voltage;
    
    if(timeslice < 4)
    {
        current = ADC_Get10BitCurrent(timeslice);                              //get the measurements 70 us
        voltage = SPI_Get12BitSample(timeslice); 
        current += ADC_Get10BitCurrent(timeslice);
        csum[timeslice] += current;
        vsum[timeslice] += voltage;
        //c2sum[timeslice] += (uint32_t)current * current;
        //v2sum[timeslice] += ((int32_t)voltage * voltage) >> 2;
        if(ctr > 128) //give the ADC time to settle into its slice
        {
            if(current > cmax[timeslice]){cmax[timeslice] = current;}
            if(current < cmin[timeslice]){cmin[timeslice] = current;}
            if(voltage > vmax[timeslice]){vmax[timeslice] = voltage;}
            if(voltage < vmin[timeslice]){vmin[timeslice] = voltage;}
        }
    }
    else if (timeslice == 4)
    {  
        //temperature measurement
        tsum[0] += ADC_Get10BitSample(TEMP0);
        tsum[1] += ADC_Get10BitSample(TEMP1);
        tsum[2] += ADC_Get10BitSample(TEMP2);
        tsum[3] += ADC_Get10BitSample(TEMP3);
    }
    else
    {
        //VCC measurement
        vccsum  += ADC_Get10BitSample(channel_FVR);
    }
    
    if(ctr >= 1024) //9.765625 Hz IPP VPP update
    {
        ctr = 0;
        if(timeslice < 4)
        { 
            if(!unitregs[REG_LOCK])
            {
                cellregs[timeslice][REG_CURRENT] = ((csum[timeslice] << 8) / cellregs[timeslice][REG_CURRENT_CALIB_SCA])  - (int16_t)cellregs[timeslice][REG_CURRENT_CALIB_OFF]; // (value / 1024) * 32 is the same as value >> 5 (registers expect 15 bit measurements))
                if((int16_t)cellregs[timeslice][REG_CURRENT] < 128) {cellregs[timeslice][REG_CURRENT] = 0;} //no negative current allowed. And tiny currents are due to the offset not being appropriate for 0 Amp measurement
                if(cellregs[timeslice][REG_MODE] == MODE_CHARGE)
                {
                    cellregs[timeslice][REG_VOLTAGE] = ((vsum[timeslice] << 7) / unitregs[REG_VOLT_CH_CALIB_SCA])  - (int16_t)unitregs[REG_VOLT_CH_CALIB_OFF]; // (value / 1024) *  8 is the same as value >> 7 (registers expect 15 bit measurements))
                }
                else
                {
                    cellregs[timeslice][REG_VOLTAGE] = ((vsum[timeslice] << 7) / unitregs[REG_VOLT_DC_CALIB_SCA])  - (int16_t)unitregs[REG_VOLT_DC_CALIB_OFF]; // (value / 1024) *  8 is the same as value >> 7 (registers expect 15 bit measurements))
                }
                if(cellregs[timeslice][REG_VOLTAGE] & 0x8000 && cellregs[timeslice][REG_VOLTAGE] < 0x8E38  ) {cellregs[timeslice][REG_VOLTAGE] = 0x7FFF;} //only small negative voltages allowed.
                cellregs[timeslice][REG_CURRENT_PP] = ((  (uint32_t)(cmax[timeslice] - cmin[timeslice]) << 18U) / cellregs[timeslice][REG_CURRENT_CALIB_PP]) - (int16_t)cellregs[timeslice][REG_CURR_CALIB_PP_OFF];  //<< 5; //scale this 10 bit value into a 15 bit value
                cellregs[timeslice][REG_VOLTAGE_PP] = ((  (uint32_t)(vmax[timeslice] - vmin[timeslice]) << 17U) / cellregs[timeslice][REG_VOLTAGE_CALIB_PP]) - (int16_t)cellregs[timeslice][REG_VOLT_CALIB_PP_OFF];  //<< 3; //scale this 12 bit value into a 15 bit value
            }
            cmax[timeslice] = 0;
            cmin[timeslice] = 0xFFFF;
            vmax[timeslice] = 0x0000;
            vmin[timeslice] = 0x7FFF;
            CHARGE[timeslice] += cellregs[timeslice][REG_CURRENT];
            csum[timeslice] = 0;
            vsum[timeslice] = 0;
            if(timeslice==3) {ADC_VDD();} //set the reference up for temperature measurement
            timeslice++;
        }
        else if (timeslice == 4)    //temperature and VCC update
        {
            if(!unitregs[REG_LOCK])
            {
                cellregs[0][REG_TEMPERATURE] = (tsum[0] >> 5); // (value / 1024) * 32 is the same as value >> 5 (registers expect 15 bit measurements))
                cellregs[1][REG_TEMPERATURE] = (tsum[1] >> 5); // (value / 1024) * 32 is the same as value >> 5 (registers expect 15 bit measurements))
                cellregs[2][REG_TEMPERATURE] = (tsum[2] >> 5); // (value / 1024) * 32 is the same as value >> 5 (registers expect 15 bit measurements))
                cellregs[3][REG_TEMPERATURE] = (tsum[3] >> 5); // (value / 1024) * 32 is the same as value >> 5 (registers expect 15 bit measurements))   
            }
            tsum[0] = 0;
            tsum[1] = 0;
            tsum[2] = 0;
            tsum[3] = 0;   
            ADCLK = 0x3F; //slow the clock down a bit for vcc measurement 
            timeslice++;
        }
        else if (timeslice == 5)
        {
            if(!unitregs[REG_LOCK])
            {
                unitregs[REG_VCC] = vccsum >> 5; // (value / 1024) * 32 is the same as value >> 5 (registers expect 15 bit measurements))
            }
            vccsum  = 0;
            ADCLK = 0x1F;
            ADC_FVR();    //set it back up for current measurement
            timeslice = 0; //break is over. time to get back to work
            
        }
    }
    ctr++; //10khz ctr   
}


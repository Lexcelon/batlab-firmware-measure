#include <xc.h>
#include "mcc_generated_files/mcc.h"

#ifndef HAL_H
#define HAL_H
//******************************************************************************
//* NAMESPACE DEFINITIONS - Byte 2 of Command/Response Packet
//******************************************************************************
#define NAMESPACE_CELL0      0x00
#define NAMESPACE_CELL1      0x01
#define NAMESPACE_CELL2      0x02
#define NAMESPACE_CELL3      0x03
#define NAMESPACE_UNIT       0x04
#define NAMESPACE_BOOTLOADER 0x05
#define NAMESPACE_COMMS      0xFF
//******************************************************************************
//* CELL REGISTER MAP (Cells 0-3) cellregs[cell][reg]
//******************************************************************************
#define REG_MODE               0x00
#define REG_ERROR              0x01
#define REG_STATUS             0x02
#define REG_CURRENT_SETPOINT   0x03
#define REG_REPORT_INTERVAL    0x04

#define REG_TEMPERATURE        0x05
#define REG_CURRENT            0x06
#define REG_VOLTAGE            0x07
#define REG_CHARGEL            0x08
#define REG_CHARGEH            0x09 

#define REG_VOLTAGE_LIMIT_CHG  0x0A
#define REG_VOLTAGE_LIMIT_DCHG 0x0B
#define REG_CURRENT_LIMIT_CHG  0x0C
#define REG_CURRENT_LIMIT_DCHG 0x0D
#define REG_TEMP_LIMIT_CHG     0x0E
#define REG_TEMP_LIMIT_DCHG    0x0F

#define REG_DUTY               0x10
#define REG_COMPENSATION       0x11
#define REG_CURRENT_PP         0x12
#define REG_VOLTAGE_PP         0x13

#define REG_CURRENT_CALIB_OFF  0x14 //also mapped to EEPROM
#define REG_CURRENT_CALIB_SCA  0x15 //also mapped to EEPROM
#define REG_TEMP_CALIB_R       0x16 //also mapped to EEPROM
#define REG_TEMP_CALIB_B       0x17 //also mapped to EEPROM
#define REG_CURRENT_CALIB_PP   0x18 //also mapped to EEPROM
#define REG_VOLTAGE_CALIB_PP   0x19 //also mapped to EEPROM
#define REG_CURR_CALIB_PP_OFF  0x1A //also mapped to EEPROM
#define REG_VOLT_CALIB_PP_OFF  0x1B //also mapped to EEPROM
#define REG_CURR_LOWV_SCA      0x1C //also mapped to EEPROM
#define REG_CURR_LOWV_OFF      0x1D //also mapped to EEPROM
#define REG_CURR_LOWV_OFF_SCA  0x1E //also mapped to EEPROM

#define CELLREGS_SIZE          0x1F



//******************************************************************************
//* UNIT REGISTER MAP (addr 4) unitregs
//******************************************************************************
#define REG_SERIAL_NUM         0x00 //read only -- also mapped to eeprom
#define REG_DEVICE_ID          0x01 //read only -- also mapped to eeprom
#define REG_FIRMWARE_VER       0x02 //read only
#define REG_VCC                0x03
#define REG_SINE_FREQ          0x04 //frequency used for impedance calculation. 
#define REG_SYSTEM_TIMER       0x05
#define REG_SETTINGS           0x06
#define REG_SINE_OFFSET        0x07
#define REG_SINE_MAGDIV        0x08
#define REG_LED_MESSAGE        0x09
#define REG_BOOTLOAD           0x0A
#define REG_VOLT_CH_CALIB_OFF  0x0B //also mapped to EEPROM
#define REG_VOLT_CH_CALIB_SCA  0x0C //also mapped to EEPROM
#define REG_VOLT_DC_CALIB_OFF  0x0D //also mapped to EEPROM
#define REG_VOLT_DC_CALIB_SCA  0x0E //also mapped to EEPROM
#define REG_LOCK               0x0F
#define REG_ZERO_AMP_THRESH    0x10 //also mapped to EEPROM
#define REG_WATCHDOG_TIMER     0x11 

#define UNITREGS_SIZE          0x12

//******************************************************************************
//* COMMS REGISTER MAP (addr FF) commregs
//******************************************************************************
#define REG_LED0               0x00 //we rely on these 4 being equivalent 
#define REG_LED1               0x01 //to cell index. this speeds things 
#define REG_LED2               0x02 //up quite a bit
#define REG_LED3               0x03
#define REG_PSU                0x04
#define REG_PSU_VOLTAGE        0x05
#define REG_PSU_CUTOFF_LOW     0x06
#define REG_PSU_CUTOFF_HIGH    0x07
#define REG_PSU_CUTOFF_HYST    0x08

#define COMMREGS_SIZE          0x09
//******************************************************************************
//* EEPROM MEMORY MAP
//******************************************************************************
#define EEP_SERIAL_NUM         0x00 //2 bytes
#define EEP_CURRENT_CALIB_OFF  0x02 //8 bytes
#define EEP_CURRENT_CALIB_SCA  0x0A //8 bytes
#define EEP_TEMP_CALIB_R       0x12 //8 bytes
#define EEP_TEMP_CALIB_B       0x1A //8 bytes
#define EEP_CURRENT_CALIB_PP   0x22 //8 bytes
#define EEP_VOLTAGE_CALIB_PP   0x2A //8 bytes
#define EEP_DEVICE_ID          0x32 //2 bytes
#define EEP_VOLT_CH_CALIB_OFF  0x34 //2 bytes
#define EEP_VOLT_CH_CALIB_SCA  0x36 //2 bytes
#define EEP_VOLT_DC_CALIB_OFF  0x38 //2 bytes
#define EEP_VOLT_DC_CALIB_SCA  0x3A //2 bytes
#define EEP_CURR_CALIB_PP_OFF  0x3C //8 bytes
#define EEP_VOLT_CALIB_PP_OFF  0x44 //8 bytes
#define EEP_ZERO_AMP_THRESH    0x4C //2 bytes
#define EEP_CURR_LOWV_SCA      0x4E //8 bytes
#define EEP_CURR_LOWV_OFF      0x56 //8 bytes
#define EEP_CURR_LOWV_OFF_SCA  0x5E //8 bytes
#define EEP_BOOTLOAD_ADDR      0xFF
//******************************************************************************
//* Register Specific Codes and Flags
//******************************************************************************
#define MODE_NO_CELL           0x0000
#define MODE_BACKWARDS         0x0001
#define MODE_IDLE              0x0002
#define MODE_CHARGE            0x0003
#define MODE_DISCHARGE         0x0004
#define MODE_IMPEDANCE         0x0005
#define MODE_STOPPED           0x0006
#define MODE_CV_CHARGE         0x0007
#define MODE_CV_DISCHARGE      0x0008

#define ERR_VOLTAGE_LIMIT_CHG  0x0001
#define ERR_VOLTAGE_LIMIT_DCHG 0x0002
#define ERR_CURRENT_LIMIT_CHG  0x0004
#define ERR_CURRENT_LIMIT_DCHG 0x0008
#define ERR_TEMP_LIMIT_CHG     0x0010
#define ERR_TEMP_LIMIT_DCHG    0x0020
#define ERR_BACKWARDS          0x0040
#define ERR_NO_CELL            0x0080
#define ERR_NO_PSU             0x0100
#define ERR_HW_CURRENT_LIMIT   0x0200
#define ERR_LOW_VCC            0x0800

#define STAT_VOLTAGE_LIMIT_CHG  0x0001
#define STAT_VOLTAGE_LIMIT_DCHG 0x0002
#define STAT_CURRENT_LIMIT_CHG  0x0004
#define STAT_CURRENT_LIMIT_DCHG 0x0008
#define STAT_TEMP_LIMIT_CHG     0x0010
#define STAT_TEMP_LIMIT_DCHG    0x0020
#define STAT_BACKWARDS          0x0040
#define STAT_NO_CELL            0x0080
#define STAT_NO_PSU             0x0100
#define STAT_NOT_INITIALIZED    0x0200
#define STAT_NOT_CALIBRATED     0x0400
#define STAT_LOW_VCC            0x0800

#define SET_TRIM_OUTPUT        0x0001
#define SET_VCC_COMPENSATION   0x0002
#define SET_WATCHDOG           0x0004
#define SET_NO_PSU_DCHG_ENABLE 0x0008
#define SET_CH0_HI_RES_MODE    0x0010
#define SET_CH1_HI_RES_MODE    0x0020
#define SET_CH2_HI_RES_MODE    0x0040
#define SET_CH3_HI_RES_MODE    0x0080
#define SET_CV_DISCHARGE       0x0100
#define SET_SAFETY_DISABLE     0x4000
#define SET_DEBUG              0x8000

#define LED_OFF                0x0000 
#define LED_BLIP               0x0001
#define LED_FLASH_SLOW         0x0002
#define LED_FLASH_FAST         0x0003
#define LED_ON                 0x0004
#define LED_PWM                0x0005 //High byte used for PWM setpoint
#define LED_RAMP_UP            0x0006
#define LED_RAMP_DOWN          0x0007
#define LED_SINE               0x0008

#define LOCK_LOCKED            0x0001
#define LOCK_UNLOCKED          0x0000
//******************************************************************************
//* APPLICATION DEFINES
//******************************************************************************
#define PACKET_START_BYTE 0xAA
#define STREAM_PACKET_START_BYTE 0xAF
#define USB_RX_PACKET_LEN 5
#define STREAM_PACKET_LEN 13
#define MAX_PACKET_LENGTH 15

#define MAXTOL 10
#define NC_VOLTAGE 13107 //1.8 Volts
#define BACKWARDS_VOLTAGE 73 //0.01 Volts
#define MIN_VCC 31581 //4.25 Volts

typedef struct packets
{
    uint8_t len;
    uint8_t payload[MAX_PACKET_LENGTH];
} packet;

//initialization
void app_initialize(void);

//communication functions
uint8_t check_for_uart_packet();
uint8_t get_uart_packet();
void handle_uart_packet();
void create_led_packet(uint8_t cell,uint16_t state);
void create_stream_packet(uint8_t celladdr);
void create_psu_packet();
void send_uart_packet();
void process_command(uint16_t cmd);

//get measurements
void measurement_handler();
    
//set outputs
void set_flags(uint8_t i);        //use inputs to decide what the next state will be         
void send_streams(uint8_t i);      //sends a stream packet if we're scheduled for that
void set_relays(uint8_t i);       //set the outputs for the next state
void set_currents(uint8_t i);
void set_fan(uint8_t i);
void send_psu();

//Hardware Level
void LED_CMD(uint8_t led,uint16_t state);
void SET_LED_MSG(uint16_t state);
void ADC_VDD(void);
void ADC_FVR(void);
void memcpy_2(void *dest,void *src);
uint16_t ADC_Get15BitOversample(adcc_channel_t channel);
uint16_t ADC_Get10BitSample(adcc_channel_t channel);
uint16_t ADC_Get10BitCurrent(uint8_t cell);
uint16_t ADC_Get12BitCurrent(uint8_t cell);
int16_t SPI_Get12BitSample(uint8_t cell);
void TMR0_ISR(void);
void TMR2_ISR(void);
void SetDuty(uint8_t cell, uint16_t duty);


#endif
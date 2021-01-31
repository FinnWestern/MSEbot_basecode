
//MSE 2202 
//Western Engineering base code
//2020 05 13 E J Porter


/*
  esp32                                             MSE-DuinoV2
  pins         description                        Brd Jumpers /Labels                                                                      User (Fill in chart with user PIN usage) 
  1             3v3                               PWR 3V3                                                                                  3V3
  2             gnd                               GND                                                                                      GND
  3             GPIO15/AD2_3/T3/SD_CMD/           D15 (has connections in both 5V and 3V areas)                    
  4             GPIO2/AD2_2/T2/SD_D0              D2(has connections in both 5V and 3V areas)  /INDICATORLED ( On ESP32 board
  5             GPIO4/AD2_0/T0/SD_D1              D4(has connections in both 5V and 3V areas)  
  6             GPIO16/RX2                        Slide Switch S1b
  7             GPIO17/TX2                        Slide Switch S2b
  8             GPIO5                             D5 (has connections in both 5V and 3V areas)  
  9             GPIO18                            D18 (has connections in both 5V and 3V areas)  
  10            GPIO19/CTS0                       D19 (has connections in both 5V and 3V areas)  
  11            GPIO21                            D21/I2C_DA  
  12            GPIO3/RX0                         RX0
  13            GPIO1//TX0                        TX0
  14            GPIO22/RTS1                       D22/I2C_CLK
  15            GPIO23                            D23 (has connections in both 5V and 3V areas)  
  16            EN                                JP4 (Labeled - RST) for reseting ESP32
  17            GPI36/VP/AD1_0                    AD0                   
  18            GPI39/VN/AD1_3/                   AD3
  19            GPI34/AD1_6/                      AD6
  20            GPI35/AD1_7                       Potentiometer R2 / AD7
  21            GPIO32/AD1_4/T9                   Potentiometer R1 / AD4
  22            GPIO33/AD1_5/T8                   IMon/D33  monitor board current
  23            GPIO25/AD2_8/DAC1                 SK6812 Smart LEDs / D25
  24            GPIO26/A2_9/DAC2                  Push Button PB2
  25            GPIO27/AD2_7/T7                   Push Button PB1
  26            GPOP14/AD2_6/T6/SD_CLK            Slide Switch S2a
  27            GPIO12/AD2_5/T5/SD_D2/            D12(has connections in both 5V and 3V areas)  
  28            GPIO13/AD2_4/T4/SD_D3/            Slide Switch S1a
  29            GND                               GND                                                                                  GND
  30            VIN                               PWR 5V t 7V                                                                          PWR 5V to 7V

*/



#include "0_Core_Zero.h"


//pins
#define MOTORLEFTa 14
#define MOTORLEFTb 4
#define MOTORRIGHTa 5
#define MOTORRIGHTb 18


#include <esp_task_wdt.h>

#include <Math.h>
#include "Motion.h";
#include "MyWEBserver.h"
#include "BreakPoint.h"
#include "WDT.h";

void loopWEBServerButtonresponce(void);


const int CR1_ciMainTimer =  1000;

unsigned char CR1_ucMainTimerCaseCore1;

uint32_t CR1_u32Now;
uint32_t CR1_u32Last;
uint32_t CR1_u32Temp;
uint32_t CR1_u32Avg;


unsigned long CR1_ulMainTimerPrevious;
unsigned long CR1_ulMainTimerNow;

unsigned long CR1_ulMotorTimerPrevious;
unsigned long CR1_ulMotorTimerNow;

void setup() {
  Serial.begin(115200);
 
  
  Core_ZEROInit();

  WDT_EnableFastWatchDogCore1();
   WDT_ResetCore1();
   WDT_vfFastWDTWarningCore1[0] = 0;
   WDT_vfFastWDTWarningCore1[1] = 0;
   WDT_vfFastWDTWarningCore1[2] = 0;
   WDT_vfFastWDTWarningCore1[3] = 0;
   WDT_ResetCore1();
   WDT_vfFastWDTWarningCore1[4] = 0;
   WDT_vfFastWDTWarningCore1[5] = 0;
   WDT_vfFastWDTWarningCore1[6] = 0;
   WDT_vfFastWDTWarningCore1[7] = 0;
   WDT_ResetCore1();
   WDT_vfFastWDTWarningCore1[8] = 0;
   WDT_vfFastWDTWarningCore1[9] = 0;
   WDT_ResetCore1(); 

   setupMotion();
}
void loop()
{

  //WSVR_BreakPoint(1);
 
 
 
 CR1_ulMainTimerNow = micros();
 if(CR1_ulMainTimerNow - CR1_ulMainTimerPrevious >= CR1_ciMainTimer)
 {
   WDT_ResetCore1(); 
   WDT_ucCaseIndexCore0 = CR0_ucMainTimerCaseCore0;
   
   CR1_ulMainTimerPrevious = CR1_ulMainTimerNow;
 
  switch(CR1_ucMainTimerCaseCore1)  //full switch run through is 1mS
  {
    //###############################################################################
    case 0: 
    {
      CR1_ulMotorTimerNow = millis();
      if(CR1_ulMotorTimerNow - CR1_ulMotorTimerPrevious >= 5000)   
      {   
       CR1_ulMotorTimerPrevious = CR1_ulMotorTimerNow;
       switch(ucMotorStateIndex)
       {
        case 0:
        {
          ucMotorStateIndex = 1;
          ucMotorState = 0;
          move(0);
          break;
        }
         case 1:
        {
          ucMotorStateIndex = 2;
          ucMotorState = 0;
          move(0);
          break;
        }
         case 2:
        {
          ucMotorStateIndex = 3;
          ucMotorState = 1;
          move(0);
          break;
        }
         case 3:
        {
          ucMotorStateIndex = 4;
          ucMotorState = 0;
          move(0);
          break;
        }
         case 4:
        {
          ucMotorStateIndex = 5;
          ucMotorState = 2;
          move(0);
          break;
        }
         case 5:
        {
          ucMotorStateIndex = 6;
          ucMotorState = 0;
          move(0);
          break;
        }
         case 6:
        {
          ucMotorStateIndex = 7;
          ucMotorState = 3;
          move(0);
          break;
        }
         case 7:
        {
          ucMotorStateIndex = 8;
          ucMotorState = 0;
          move(0);
          break;
        }
         case 8:
        {
          ucMotorStateIndex = 0;
          ucMotorState = 4;
          move(0);
          break;
        }
         
       }
      }
      CR1_ucMainTimerCaseCore1 = 1;
      
      break;
    }
    //###############################################################################
    case 1: 
    {
   
    
      CR1_ucMainTimerCaseCore1 = 2;
    
      break;
    }
    //###############################################################################
    case 2: 
    {
      
   
      CR1_ucMainTimerCaseCore1 = 3;
      break;
    }
    //###############################################################################
    case 3: 
    {
      
      
      CR1_ucMainTimerCaseCore1 = 4;
      break;
    }
    //###############################################################################
    case 4:   
    {
    
      CR1_ucMainTimerCaseCore1 = 5;
      break;
    }
    //###############################################################################
    case 5: 
    {
   
      CR1_ucMainTimerCaseCore1 = 6;
      break;
    }
    //###############################################################################
    case 6: //LCD Display
    {
  
    
      CR1_ucMainTimerCaseCore1 = 7;
      break;
    }
    //###############################################################################
    case 7: 
    {
   
      CR1_ucMainTimerCaseCore1 = 8;
      break;
    }
    //###############################################################################
    case 8: 
    {
    
      CR1_ucMainTimerCaseCore1 = 9;
      break;
    }
    //###############################################################################
    case 9: 
    {
  
      CR1_ucMainTimerCaseCore1 = 0;
      break;
    }

  }
 }

}
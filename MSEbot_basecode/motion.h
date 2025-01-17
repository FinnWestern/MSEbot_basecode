/*
 Western Engineering base code
2020 05 13 E J Porter

 Dual Motor driver controller implement
  
 */

 #ifndef MOTION_H
  #define MOTION_H 1

//---------------------------------------------------------------------------

#define DEBUGPRINT
#define ACCELERATIONRATE 5;



unsigned char ucMotion_Direction;
unsigned char ucMotion_Speed;

const uint8_t cui8StartingSpeed = 140;

uint8_t ui8LeftWorkingSpeed = cui8StartingSpeed;
uint8_t ui8RightWorkingSpeed = cui8StartingSpeed;

unsigned char ucMotorState = 5;

double dManualSpeed;
double dForwardSpeed;
double dReverseSpeed;
double dLeftSpeed;
double dRightSpeed;

void setupMotion (void)
{
	
  dManualSpeed = 0;
  dForwardSpeed = 250;  // max 255; min ~150 before motor stall
  dReverseSpeed = 250;
  dLeftSpeed = 170;
  dRightSpeed = 170;
  
  //setup PWM for motors
  ledcAttachPin(ciMotorLeftA, 1); // assign Motors pins to channels
  ledcAttachPin(ciMotorLeftB, 2);
  ledcAttachPin(ciMotorRightA, 3);
  ledcAttachPin(ciMotorRightB, 4);

  // Initialize channels 
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 20000, 8); // 20mS PWM, 8-bit resolution
  ledcSetup(2, 20000, 8);
  ledcSetup(3, 20000, 8);
  ledcSetup(4, 20000, 8);
 	
   ucMotion_Direction = 0;
   ucMotion_Speed = 0;
}


void ResetSpeeds()
{
  ui8LeftWorkingSpeed = cui8StartingSpeed;
  ui8RightWorkingSpeed = cui8StartingSpeed;

  
}

void MoveTo(uint8_t ui8Direction, uint8_t ui8LeftSpeed, uint8_t ui8RightSpeed)
{
    int  iPrintOnce;
      
   
     switch(ui8Direction)
      {
      
      
        //forward
        case 1:
        {
            
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
          
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
          
          break;
        }
        //Left
        case 2:
        {
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(1,0);
          ledcWrite(2,ui8LeftWorkingSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
        
          break;
        }
        //Right
        case 3:
        {
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(3,0);
          ledcWrite(4,ui8RightWorkingSpeed);
       
          break;
        }
        //Reverse
        case 4:
        {
             
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(1,0);
          ledcWrite(2,ui8LeftWorkingSpeed);
          ledcWrite(3,0);
          ledcWrite(4,ui8RightWorkingSpeed);
       
          break;
        }
        case 5:   //left pivot
        {
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(1,255);
          ledcWrite(2,255);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
        
          break;
        }
        case 6:     //right pivot
        {
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(3,255);
          ledcWrite(4,255);
       
          break;
        }
     
        
      }
 }

void MoveToNoAcceleration(uint8_t ui8Direction, uint8_t ui8LeftSpeed, uint8_t ui8RightSpeed)
{
    int  iPrintOnce;
      
   
     switch(ui8Direction)
      {
      
      
        //forward
        case 1:
        {  
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightSpeed);
          
          break;
        }
        //Left
        case 2:
        {
          ledcWrite(1,0);
          ledcWrite(2,ui8LeftSpeed);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightSpeed);
        
          break;
        }
        //Right
        case 3:
        {
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftSpeed);
          ledcWrite(3,0);
          ledcWrite(4,ui8RightSpeed);
       
          break;
        }
        //Reverse
        case 4:
        {
          ledcWrite(1,0);
          ledcWrite(2,ui8LeftSpeed);
          ledcWrite(3,0);
          ledcWrite(4,ui8RightSpeed);
       
          break;
        }
        case 5:   //left pivot
        {
          if(ui8RightWorkingSpeed >= ui8RightSpeed)
          {
            ui8RightWorkingSpeed = ui8RightSpeed;
          }
          else
          {
            ui8RightWorkingSpeed = ui8RightWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(1,255);
          ledcWrite(2,255);
          ledcWrite(4,0);
          ledcWrite(3,ui8RightWorkingSpeed);
        
          break;
        }
        case 6:     //right pivot
        {
          if(ui8LeftWorkingSpeed >= ui8LeftSpeed)
          {
            ui8LeftWorkingSpeed = ui8LeftSpeed;
          }
          else
          {
          ui8LeftWorkingSpeed = ui8LeftWorkingSpeed + ACCELERATIONRATE;
          }
         
          ledcWrite(2,0);
          ledcWrite(1,ui8LeftWorkingSpeed);
          ledcWrite(3,255);
          ledcWrite(4,255);
       
          break;
        }
     
        
      }
 }

void move(uint8_t ui8Speed)
{
    int  iPrintOnce;
    ucMotorState = 5;

     switch(ucMotorState)
      {
        //Stop, coast mode
        case 0:
        {
          //if 0 is put in both INs motors will coast stop 
          ledcWrite(2,0);
          ledcWrite(1,0);
          ledcWrite(4,0);
          ledcWrite(3,0);
        //ucWorkingButtonState = 9;
      #ifdef DEBUGPRINT  
          if(iPrintOnce != 0)
           {
            iPrintOnce = 0;
            Serial.print(F("stop-coasting"));
            Serial.println(ui8Speed);
          }
      #endif    
          break;
        }
      
        //Forward
        case 1:
        {
          //ui8speed = dForwardSpeed;
          ledcWrite(2,0);
          ledcWrite(1,ui8Speed);
          ledcWrite(4,0);
          ledcWrite(3,ui8Speed);
          //ucWorkingButtonState = 9;
        #ifdef DEBUGPRINT  
          if(iPrintOnce != 1)
           {
            iPrintOnce = 1;
            Serial.print(F("Forward "));
            Serial.println(ui8Speed);
           }
         #endif   
          break;
        }
        //Left
        case 2:
        {
          ui8Speed = dLeftSpeed;
          ledcWrite(2,0);
          ledcWrite(1,ui8Speed);
          ledcWrite(3,0);
          ledcWrite(4,ui8Speed);
         //ucWorkingButtonState = 9;
         #ifdef DEBUGPRINT  
          if(iPrintOnce != 3)
           {
            iPrintOnce = 3;
            Serial.print(F("Left "));
            Serial.println(ui8Speed);
           }
         #endif 
          break;
        }
        //Right
        case 3:
        {
          ui8Speed = dRightSpeed;
          ledcWrite(1,0);
          ledcWrite(2,ui8Speed);
          ledcWrite(4,0);
          ledcWrite(3,ui8Speed);
          // ucWorkingButtonState = 9;
          #ifdef DEBUGPRINT  
          if(iPrintOnce != 4)
           {
            iPrintOnce = 4;
            Serial.print(F("Right "));
            Serial.println(ui8Speed);
           }
         #endif   
          break;
        }
        //Reverse
        case 4:
        {
          // ui8speed = dReverseSpeed;
          ledcWrite(1,0);
          ledcWrite(2,ui8Speed);
          ledcWrite(3,0);
          ledcWrite(4,ui8Speed);
         // ucWorkingButtonState = 9;
         #ifdef DEBUGPRINT  
          if(iPrintOnce != 2)
           {
            iPrintOnce = 2;
            Serial.print(F("Reverse "));
            Serial.println(ui8Speed);
           }
         #endif  
          break;
        }
        //Stop  braking mode
        case 5:
        {
          //if 255 is put in both INs brakes will be applied 
          ledcWrite(2,255);
          ledcWrite(1,255);
          ledcWrite(4,255);
          ledcWrite(3,255);
        //ucWorkingButtonState = 9;
      #ifdef DEBUGPRINT  
          if(iPrintOnce != 0)
           {
            iPrintOnce = 0;
            Serial.print(F("stop-braking"));
            Serial.println(ui8Speed);
          }
      #endif    
          break;
        }
      }
}
#endif

#include <Arduino.h>

const int BUTTON_PIN = 12;
const int LED_PIN = 4;

int buttonstate = HIGH;
int lastreading = HIGH;
int ledstate = LOW;

const unsigned long debounce_delay = 50;
unsigned long last_debouce_time;
 
const int PWM_CHANNEL = 1;
const int PWM_FREQ = 10000;
const int PWM_RESOLUTION = 6;
const int MAX_BRIGHTNESS = 63;

unsigned long previousblinkmillis = 0;
unsigned long currentblinkmillis;
const unsigned long blinkinterval = 500;

unsigned long previousfademillis = 0;
unsigned long currentfademillis;
const unsigned long fadeinterval = 50;
int fadedirection = 1;
int brightness = 0;

int mode = 0;

void setup(){
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);

  ledcWrite(PWM_CHANNEL, 0);
}


void loop()
{
  int reading = digitalRead(BUTTON_PIN);

  if( reading != lastreading)
  {
    last_debouce_time = millis();
  }

  if (millis()-last_debouce_time>debounce_delay)
  {
    if (reading != buttonstate)
    {
      buttonstate = reading;

      if(buttonstate == LOW)
      {
           mode++;
           if (mode >= 4){
            mode = 0;
           }
           Serial.print("Mode -");
           Serial.println(mode);
      }
    }
  }
    lastreading = reading;

  
    if (mode == 0)
    {
      ledcWrite(PWM_CHANNEL, 0);
    }

    else if (mode == 1)
    {
     ledcWrite(PWM_CHANNEL, 63);
    }

    else if (mode == 2)
    {
      currentblinkmillis = millis();

      if (currentblinkmillis - previousblinkmillis > blinkinterval)
      {
        previousblinkmillis = currentblinkmillis;
        ledstate = !ledstate;
        if (ledstate){
          ledcWrite(PWM_CHANNEL, MAX_BRIGHTNESS);
        }
        else
        {
          ledcWrite(PWM_CHANNEL, 0);
        }
      }
    }

    else if (mode ==3)
    {
      currentfademillis = millis();

      if (currentfademillis - previousfademillis > fadeinterval)
      {
        previousfademillis = currentfademillis;

        brightness += fadedirection;

        if (brightness >= MAX_BRIGHTNESS)
        {
          brightness = MAX_BRIGHTNESS;
          fadedirection = -1;
        }
        
        if (brightness <=0)
        {
          brightness = 0;
          fadedirection = 1;
        }
        ledcWrite(PWM_CHANNEL, brightness);
      }
    }
}
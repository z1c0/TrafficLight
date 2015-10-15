#define RED 0
#define YELLOW 1
#define GREEN 2

#define RED_PIN 2
#define YELLOW_PIN 7
#define GREEN_PIN 11
#define BUTTON_PIN 4

int current = GREEN;
int lights[3];
unsigned long waitTimes[3];
unsigned long lastSwitchTime = 0;
unsigned long lastPress = 0;
bool fromGreen = false;

void setup() 
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  lights[RED] = RED_PIN;
  lights[YELLOW] = YELLOW_PIN;
  lights[GREEN] = GREEN_PIN;
  waitTimes[RED] = 3000;
  waitTimes[YELLOW] = 1500;
  waitTimes[GREEN] = 4000;
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
}

void change()
{
  switch(current)
  {
    case RED:
      current = YELLOW;
      fromGreen = false;
      break;
      
    case YELLOW:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      if (fromGreen)
      {
        current = RED;
      }
      else
      {
        current = GREEN;
      }
      break;
      
    case GREEN:
      // flash
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(GREEN_PIN, LOW);
        delay(400);
        digitalWrite(GREEN_PIN, HIGH);
        delay(400);
      }
      digitalWrite(GREEN_PIN, LOW);
      current = YELLOW;
      fromGreen = true;
      break;
  }
}

bool buttonPress()
{
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastPress > 300)
  {
    lastPress = millis();
    return true;
  }
  return false;
}

void loop() 
{ 
  digitalWrite(lights[current], HIGH);
    
  if ((millis() - lastSwitchTime >= waitTimes[current]) || buttonPress())
  { 
    change();
    lastSwitchTime = millis();
    //delay(300);
  }
}


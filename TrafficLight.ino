#define STATE_RED 0
#define STATE_RED_YELLOW 1
#define STATE_GREEN 2
#define STATE_GREEN_BLINK 3
#define STATE_YELLOW 4
#define STATE_YELLOW_BLINK 5

#define RED_PIN 2
#define YELLOW_PIN 7
#define GREEN_PIN 11

#define YELLOW_PHASE 1500

int gState = STATE_RED;

void setup() 
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void wait(int millis)
{
  delay(millis);
}

void loop()
{
  switch(gState)
  {
    case STATE_RED:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      wait(6000);
      gState = STATE_RED_YELLOW;
      break;      

    case STATE_RED_YELLOW:
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      wait(YELLOW_PHASE);
      gState = STATE_GREEN;
      break;      

    case STATE_GREEN:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      wait(7500);
      gState = STATE_GREEN_BLINK;
      break;      
      
    case STATE_GREEN_BLINK:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      for (int i = 0; i < 4; i++)
      {
        digitalWrite(GREEN_PIN, LOW);
        wait(400);
        digitalWrite(GREEN_PIN, HIGH);
        wait(400);
      }
      gState = STATE_YELLOW;
      break;      

    case STATE_YELLOW:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      wait(YELLOW_PHASE);
      gState = (random(0, 10) == 5) ? STATE_YELLOW_BLINK : STATE_RED;
      break;      
      
    case STATE_YELLOW_BLINK:
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      for (int i = 0; i < 40; i++)
      {
        digitalWrite(YELLOW_PIN, LOW);
        wait(300);
        digitalWrite(YELLOW_PIN, HIGH);
        wait(300);
      }
      gState = STATE_RED;
      break;      
  }
}


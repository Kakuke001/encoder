#define A 2
#define B 3
#define LED 9
uint8_t x= 128; //delay time
static bool A_state= LOW;
static bool B_state= LOW;
uint16_t interrupt_start = 0;
uint16_t interrupt_end = 0;
int8_t val = 0; 
 void setup() { 
   pinMode (A,INPUT);
   pinMode (B,INPUT);
   digitalWrite(B,HIGH);
   digitalWrite(A,HIGH);
   Serial.begin (9600);
   pinMode(LED,OUTPUT);
   attachInterrupt(digitalPinToInterrupt(2), checkA, CHANGE);
   attachInterrupt(digitalPinToInterrupt(3), checkB, CHANGE);
 } 
void checkA()
{
  interrupt_end = millis();
  if (interrupt_end - interrupt_start > 25)
  {
    interrupt_start = millis();
    val+=1;
    compare();
  }
}

void checkB()
{
 interrupt_end = millis();
  if (interrupt_end - interrupt_start > 25)
   {
    val-=1;
    interrupt_start = millis();
    compare();
   }
}

void compare()
{
  Serial.print("val.....");
  Serial.println(val);
  if (val < 0)
    {
      x+=10;
      val+=1;
      A_state=B_state=LOW;
    }
   if (val > 0)
    {
      x-=10;
      val-=1;
      A_state=B_state=LOW;
    }
  if(x < 20)
  {
    x=20;
  }
  if(x>240)
  {
    x=240;
  }
}

 void loop()
 { 
  compare();
  
   digitalWrite(LED,HIGH);
   delay(x);
   digitalWrite(LED,LOW);
   delay(x);
   Serial.println(x);
 } 

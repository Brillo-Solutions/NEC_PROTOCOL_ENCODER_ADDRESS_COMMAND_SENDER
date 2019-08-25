#define irLed 2            
#define markLowBit 562     
#define spaceHighBit 1.6875      
unsigned long keyCode = 0x40BF08F7;  

void setup()
{
  pinMode(irLed, OUTPUT);
}

void irCarrierGen(unsigned int irPulseTime)
{
  for(int k = 0; k < (irPulseTime / 26); k++)
  {
    digitalWrite(irLed, HIGH);   
    delayMicroseconds(9);          
    digitalWrite(irLed, LOW);    
    delayMicroseconds(9);       
  }
}

void sendKeyCode(unsigned long keyCode)
{
  irCarrierGen(9000); 
  delayMicroseconds(4500);
  
  for (int k = 0; k < 32; k++)          
  {
    irCarrierGen(markLowBit);               
    if (keyCode & 0x80000000)            
      delay(spaceHighBit);
    else
      delayMicroseconds(markLowBit);
    keyCode <<= 1;                       
  }
  irCarrierGen(markLowBit);
}

void loop()
{
  sendKeyCode(keyCode);
  delay(2000);
}
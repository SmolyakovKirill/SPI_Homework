#include<SPI.h>
#define buttonpin 2
#define led_1 3
#define led_2 4
#define led_3 5
#define led_4 8
volatile boolean received;
volatile byte Slavereceived;
int buttonvalue;
int x;

void setup()
{
  Serial.begin(115200);                   // инициализируем последовательную связь со скоростью 115200
  
  pinMode(buttonpin,INPUT);               // устанавливаем пин в статус INPUT
  pinMode(led_1, OUTPUT);                 // устанавливаем пин в статус OUTPUT
  pinMode(led_2, OUTPUT);                 // устанавливаем пин в статус OUTPUT
  pinMode(led_3, OUTPUT);                 // устанавливаем пин в статус OUTPUT
  pinMode(led_4, OUTPUT);                 // устанавливаем пин в статус OUTPUT
  SPCR |= _BV(SPE);                       //переводим SPI в Slave Mode 
  received = false;
  SPI.attachInterrupt();                  //включаем прерывание для протокола SPI
  
}
ISR (SPI_STC_vect)                        //функция обработки прерывания 
{
  Slavereceived = SPDR;        
  received = true;                        
}
void loop()
{ 
  Serial.println(Slavereceived);          //В зависимости от значения включается светодиод
  if(received)                            
   {
      if (Slavereceived == 0x98) 
      {
        digitalWrite(led_1,HIGH);         
      }
      else
      {
        digitalWrite(led_1,LOW);          
      }
      if (Slavereceived == 0x45) 
      {
        digitalWrite(led_2,HIGH);         
      }
      else
      {
        digitalWrite(led_2,LOW);          
      }
      
      if (Slavereceived == 0x7A) 
      {
        digitalWrite(led_3,HIGH);         
      }
      else
      {
        digitalWrite(led_3,LOW);          
      }

      if (Slavereceived == 0xCD) 
      {
        digitalWrite(led_4,HIGH);         
      }
      else
      {
        digitalWrite(led_4,LOW);          
      } 
    }
}

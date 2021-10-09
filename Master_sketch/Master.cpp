#include<SPI.h>
#define buttonpin 2
int buttonvalue;
byte myData[4] = {0x98, 0x45, 0x7A, 0xCD};
byte Mastersend, Mastereceive; 

void setup (void)
{
    Serial.begin(115200);                   // инициализируем последовательную связь со скоростью 115200
    SPI.begin();                            // инициализируем связь по протоколу SPI
    SPI.setClockDivider(SPI_CLOCK_DIV8);    // установим делитель для связи по протоколу SPI
    digitalWrite(SS,HIGH);                  // подаем на контакт напряжение высокого уровня на контакт SS для того чтобы не было подключения к Slave
}

void loop(void)
{
    buttonvalue = digitalRead(buttonpin);   // считываем нажатие кнопки
    digitalWrite(SS, LOW);                  // подаем на контакт напряжение низкого уровня на контакт SS для связи со Slave
    if(buttonvalue == HIGH)                 // Если кнопка нажата отправляем значения из массива на Slave, в противном случае отправляем 0
    {
        for(int i = 0; i < 4; i++)
        {
            Mastersend = myData[i];
            Mastereceive = SPI.transfer(Mastersend);    
            delay(250);
        }
    }
    else
    {
      Mastersend = 0;
      Mastereceive = SPI.transfer(Mastersend);
    }
}
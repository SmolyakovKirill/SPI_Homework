#include<SPI.h>
#define buttonpin 2
int buttonvalue;
byte myData[4] = {0x98, 0x45, 0x7A, 0xCD};
byte Mastersend, Mastereceive; 

void setup (void)
{
    Serial.begin(115200);                   // �������������� ���������������� ����� �� ��������� 115200
    SPI.begin();                            // �������������� ����� �� ��������� SPI
    SPI.setClockDivider(SPI_CLOCK_DIV8);    // ��������� �������� ��� ����� �� ��������� SPI
    digitalWrite(SS,HIGH);                  // ������ �� ������� ���������� �������� ������ �� ������� SS ��� ���� ����� �� ���� ����������� � Slave
}

void loop(void)
{
    buttonvalue = digitalRead(buttonpin);   // ��������� ������� ������
    digitalWrite(SS, LOW);                  // ������ �� ������� ���������� ������� ������ �� ������� SS ��� ����� �� Slave
    if(buttonvalue == HIGH)                 // ���� ������ ������ ���������� �������� �� ������� �� Slave, � ��������� ������ ���������� 0
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
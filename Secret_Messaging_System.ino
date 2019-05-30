#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
#define TxD 3 
#define RxD 2
SoftwareSerial bluetoothSerial(TxD,RxD);
int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char c;
int iLineNumber = 1;                                    
int iCursor = 0;
int flag = 0, index = 0, j = 0,count = 0;
String data, code = "", encrypt = "", decrypt = "",toPrint;
void UpdateLCDDisplay();
void setup() 
{
  bluetoothSerial.begin(9600);
  lcd.begin(16,2);    
  Serial.begin(9600);
   lcd.print("'&' for encode");
 lcd.setCursor(0,1);  
 lcd.print("'%' for decode");
}

void loop() 
{

  while(bluetoothSerial.available()==0)
  {}
  char character;
  while(bluetoothSerial.available()>0)
  {
      character = bluetoothSerial.read();
      data = data + character;
     if (character == '&')
     {  
      bluetoothSerial.print("Received: ");
      data = data.substring(0,data.length()-2);
      Serial.println(data);
      for(int i=0; i<data.length(); i++)
      {
        char myChar = data.charAt(i);
        for(int i=7; i>=0; i--)
        {
           byte bytes = bitRead(myChar,i);
           code = code + (String)bytes;
           
        }
        code = code +" ";
      } 
      Serial.println(code);
      for(int x = 0; x<code.length(); x++)
      {
        char ch = code.charAt(x);
        if(ch == '0')
        {
           encrypt += "1";
        }
        else if(ch == '1')
        {
          encrypt += "0";
        }
        else
        {
          encrypt += " ";
        }        
      }
      Serial.println(encrypt);
      encrypt = encrypt + "|||";
      bluetoothSerial.println(encrypt);
      toPrint = encrypt;
      lcd.setCursor(0,0);
      lcd.print("Encrypted code");
      for(int u = 0;u<toPrint.length(); u++)
      {
        UpdateLCDDisplay();
        delay(1000);
      }
      data = "";
      code = "";
      encrypt = "";
    }
    if (character == '%')
    {  
      bluetoothSerial.print("Received: ");
      data = data.substring(0,data.length()-2)+" ";
      Serial.println(data);
      for(int x = 0; x<data.length(); x++)
      {
        char ch = data.charAt(x);
        if(ch == '0')
        {
           code += "1";
        }
        else if(ch == '1')
        {
          code += "0";
        }
        else
        {
          code += " ";
        }        
      }
      Serial.print(code);
      for(int i = index;i<code.length(); i++)
      {
        if(code.charAt(i)==' ')
        count+=1;
        i+=1;
      }
      Serial.print(count);
      int temp[count];
      for(int i = index;i<code.length(); i++)
      {
        if(code.charAt(i)==' ')
        {
          int index = i;
          temp[j] = (code.substring(0,i)).toInt();
        }
        code = code.substring(i+2);
        Serial.println(temp[j]);
        j += 1;
      }
      for(int i = 0; i < count ; i++)
      {
        decrypt[i] = (char)(temp[i],BIN);
        bluetoothSerial.print((char)(temp[i],BIN));
      }
      toPrint = decrypt;
      lcd.setCursor(0,0);
      lcd.print("Decrypted code");
      UpdateLCDDisplay();
    }
  }
}
void UpdateLCDDisplay()
{
  int itoPrint = toPrint.length();                                            
  if (iCursor == (itoPrint - 1) )                                             
  {
    iCursor = 0;
  }
  //lcd.clear();
  lcd.setCursor(0,iLineNumber);
  
  if(iCursor < itoPrint - 16)                                                  
  {
    for (int iChar = iCursor; iChar < iCursor + 16 ; iChar++)
    {
      lcd.print(toPrint[iChar]);
    }
  }
  else
  {
    for (int iChar = iCursor; iChar < (itoPrint - 1) ; iChar++)                
    {
      lcd.print(toPrint[iChar]);
    }
    for (int iChar = 0; iChar <= 16 - (itoPrint- iCursor); iChar++)           
    {
      lcd.print(toPrint[iChar]);   
    }
  }
  iCursor++;
}

  

//https://forum.arduino.cc/index.php?topic=176732.msg1312111#msg1312111

// LCD Scrolltext by 'jurs' for German Arduino Forum
// define the chars in one LED line
#define LEDLINE 16 


// Folgende zwei Zeilen Code für Sainsmart LCD Keypad Shield
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Sainsmart keypad LCD


// Folgende zwei Zeilen Code für I2C Display
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display


// define scrolling speed for two LED lines
const int ledScrollSpeed[2]={225,450};
// define scrolling direction for two LED lines (true means right-to-left scrolling)
const boolean ledScrollDir[2]={true,true};

char charAt(char *text, int pos)
// scrolling-logic coded here
{
  if (pos<LEDLINE) return ' '; // scroll in
  else if (pos>=LEDLINE && pos<LEDLINE+strlen(text))
    return text[pos-LEDLINE]; // scroll text
  else return ' ';  // scroll out

}


void task_text(char *text, byte line)
// scroll the LED lines
{
  char currenttext[LEDLINE+1];
  static unsigned long nextscroll[2];
  static int positionCounter[2];
  int i;
  if (millis()>nextscroll[line])
  {
    nextscroll[line]=millis()+ledScrollSpeed[line];

    for (i=0;i<LEDLINE;i++)
      currenttext[i]=charAt(text,positionCounter[line]+i);
    currenttext[LEDLINE]=0;   

    lcd.setCursor(0,line);
    lcd.print(currenttext);
    if (ledScrollDir[line])
    {
      positionCounter[line]++;
      if (positionCounter[line]==strlen(text)+LEDLINE) positionCounter[line]=0;
    } 
    else 
    {
      positionCounter[line]--;
      if (positionCounter[line]<0) positionCounter[line]=strlen(text)+LEDLINE-1;
    } 
  }
}


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
}

void loop() {
  // Scroll text in line number 0
   task_text("Hello wordl! dig dig dig dig and die, fucking bee",1);
  // Scroll text in line number 1
   //task_text("Zeile-2",1); 
}
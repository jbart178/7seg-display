#define aPin 1    //               A
#define bPin 2    //            ________
#define cPin 3    //          |          |
#define dPin 4    //       F  |          |  B
#define ePin 5    //          |          |
#define fPin 6     //         | ________ |
#define gPin 7   //                G
#define DP   0    //          |          |
#define D1   12     //         |          |
#define D2   11     //      E  |          |  C
#define D3   10    //          | ________ |
#define D4   9    //               D
#define D5   8


// Digit anode
// Segment cathode
const int seg[7] = {1, 2, 3, 4, 5, 6, 7};
const int dig[5] = {12, 11, 10, 9, 8};

int n = 26584;

byte num[5] = {B0000000, B0000000, B0000000, B0000000, B0000000};

void setup() {
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(DP,OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);

  digitalWrite(13, LOW);
  // Set digit pins to HIGH to ensure LEDs are off
  for (byte i=0; i < 5; i++) {
    digitalWrite(dig[i], LOW);
  }
}
void loop() {
  readSensors();
  refreshScreen();
}



void readSensors() {

  int d = 10000;
  for (int i = 0; i < 5; i++) {
    num[i] = pickNumber(((n % (d * 10)) - (n % d)) / d);
    d /= 10;
  }
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisDig = 0; thisDig < 5; thisDig++) {
    // take the digit pin (anode) high:
    digitalWrite(dig[thisDig], HIGH);
    // iterate over the digits (cathodes):
    for (int thisSeg = 0; thisSeg < 7; thisSeg++) {
      digitalWrite(seg[thisSeg], bitRead(num[thisDig], thisSeg));
    }
    // take the row pin low to turn off the whole digit:
    digitalWrite(dig[thisDig], LOW);
  }
}

byte pickNumber(int x){
   switch(x){
     case 1: return one(); 
     case 2: return two(); 
     case 3: return three(); 
     case 4: return four(); 
     case 5: return five(); 
     case 6: return six(); 
     case 7: return seven(); 
     case 8: return eight(); 
     case 9: return nine(); 
     default: return zero(); 
   }
}

byte clearLEDs()
{
  return ~B0000000;
}

byte one() //B, C set
{
  return ~B1001111;
}

byte two() //A, B, D, E, G set
{
  return ~B0010010;
}

byte three() //A, B, C, D, G set
{
  return ~B0000110;
}

byte four() //B, C, F, G set
{
  return ~B1001100;
}

byte five() //A, C, D, F, G set
{
  return ~B0100100;
}

byte six() //A, C, D, E, F, G set
{
  return ~B0100000;
}

byte seven() //A, B, C set
{
  return ~B0001111;
}

byte eight() //A, B, C, D, E, F, G set
{
  return ~B0000000;
}

byte nine() //A, B, C, D, F, G set
{
  return ~B0000100;
}

byte zero() //A, B, C, D, E, F set
{
  return ~B0000001;
}
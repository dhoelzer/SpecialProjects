/*
 * This sketch is POC code for testing the function of HM6116 2k SRAM chips.  The chip is wired to the arduino as below, 
 * except that A10 and CS (Chip Select) are tied to ground.
 * 
 * The serial output provides visual verification that the values are correct.  I've chosen to start at 0x5A since that
 * provides a nice set of alternating bits (01011010B) as a starting pattern.
 */

const int a0 = 0;
const int a1 = 1;
const int a2 = 2;
const int a3 = 3;
const int a4 = 4;
const int a5 = 5;
const int a6 = 6;
const int a7 = 7;
const int a8 = 8;
const int a9 = 9;
const int d0 = 10;
const int d1 = 11;
const int d2 = 12;
const int d3 = 13;
const int d4 = A0;
const int d5 = A1;
const int d6 = A2;
const int d7 = A3;
const int OE = A4;
const int WE = A5;
int x = 0x5a;

void setup() {
  Serial.begin(57600);
  Serial.println("Uno running");
  for(int x=0; x!=10; x++){ 
    pinMode(x, OUTPUT);
    Serial.print("Pin ");
    Serial.print(x);
    Serial.print(" configured as address line ");
    Serial.println(x);
  }
  pinMode(OE, OUTPUT);
  pinMode(WE, OUTPUT);
  digitalWrite(OE, HIGH);
  digitalWrite(WE, HIGH);
}

void loop() {

  Serial.print("Storing byte ");
  Serial.println(x);
  for(int address = 0; address!=1024; address++)
  {
    store(address, x);
  }
  Serial.println("Reading back");
  for(int address = 0; address!=1024; address++)
  {
    int result = retrieve(address);
    Serial.print(address);
    Serial.print(" -> ");
    Serial.println(result);
  }
  x = x+1;
}      

void store(int address, int value)
{
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  for(int x = 0; x != 10; x++)
  {
    digitalWrite(x, (address & 0x01 ? HIGH : LOW));
  }
  digitalWrite(d0, (value & 0x01 ? HIGH : LOW));
  digitalWrite(d1, (value & 0x02 ? HIGH : LOW));
  digitalWrite(d2, (value & 0x04 ? HIGH : LOW));
  digitalWrite(d3, (value & 0x08 ? HIGH : LOW));
  digitalWrite(d4, (value & 0x10 ? HIGH : LOW));
  digitalWrite(d5, (value & 0x20 ? HIGH : LOW));
  digitalWrite(d6, (value & 0x40 ? HIGH : LOW));
  digitalWrite(d7, (value & 0x80 ? HIGH : LOW));
  digitalWrite(WE, LOW);
  delay(1);
  digitalWrite(WE, HIGH);
}

int retrieve(int address)
{
  int result = 0;
  
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);
  for(int x = 0; x != 10; x++)
  {
    digitalWrite(x, (address & 0x01 ? HIGH : LOW));
  }
  digitalWrite(OE, LOW);
  delay(1);
  result = digitalRead(d0) | (digitalRead(d1) << 1) | (digitalRead(d2) << 2)| (digitalRead(d3) << 3)| (digitalRead(d4) << 4)| (digitalRead(d5) << 5)| (digitalRead(d6) << 6)| (digitalRead(d7) << 7);
  digitalWrite(OE, HIGH);
  return result;
}

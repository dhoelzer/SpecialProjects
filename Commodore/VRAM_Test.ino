/*
 * This sketch is for in in circuit tester of the video RAM on a Commodore PET-2001N.  Pin assignments
 * can be determined from the code below.
 * 
 * To use this sketch, remove the 2114/6114 SRAM chips from the PET motherboard.  Wire the D0-D7 jumpers as follows:
 * 
 * d0 -> UF8 pin 14
 * d1 -> UF8 pin 13
 * d2 -> UF8 pin 12
 * d3 -> UF8 pin 11
 * d4 -> UF7 pin 14
 * d5 -> UF7 pin 13
 * d6 -> UF7 pin 12
 * d7 -> UF7 pin 11
 * 
 * It is also important to connect a jumper from one of the ground pin sockets on the arduino to
 * pin 9 of either UF7 or UF8 to create a common ground between the two systems.
 * 
 * The sketch will automatically send incrementing bytes to the video RAM.
 */


const int d0 = 10;
const int d1 = 11;
const int d2 = 12;
const int d3 = 13;
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

void setup() {
  Serial.begin(57600);
  Serial.println("Commodore PET 2001 SRAM static character in circuit tester");
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  Serial.println();
}

void loop() {
  for(unsigned int nextChar = 0; nextChar < 256; nextChar++){
    setCharacter(nextChar);
    delay(500);
  }
}      

void setCharacter(char character){
  Serial.print("Current character value: ");
  Serial.println(character, HEX);
  store(character);
}

void store(char value)
{

  digitalWrite(d0, (value & 0x01 ? HIGH : LOW));
  digitalWrite(d1, (value & 0x02 ? HIGH : LOW));
  digitalWrite(d2, (value & 0x04 ? HIGH : LOW));
  digitalWrite(d3, (value & 0x08 ? HIGH : LOW));
  digitalWrite(d4, (value & 0x10 ? HIGH : LOW));
  digitalWrite(d5, (value & 0x20 ? HIGH : LOW));
  digitalWrite(d6, (value & 0x40 ? HIGH : LOW));
  digitalWrite(d7, (value & 0x80 ? HIGH : LOW));
}

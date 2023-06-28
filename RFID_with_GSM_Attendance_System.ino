#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <DS3231.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
SoftwareSerial sim(8, 9); 

String number = "+880XXXXXXXXXX"; // +880 is the country code

int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;


#define buzzerPin  A1
#define RST_PIN    A0
#define SDA_PIN    10

MFRC522 mfrc522(SDA_PIN, RST_PIN);
DS3231  rtc(SDA, SCL);

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);
  sim.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  rtc.begin();

  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("    WELCOME    ");
  lcd.setCursor(0, 1);
  lcd.print("TO OUR PROJECT");
  delay(4000);
  lcd.clear();
}

void loop() {
  RTC();
  rfid();
}

void RTC()
{
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
  
  lcd.setCursor(0, 0);
  lcd.print("Put Your Card to" );
  lcd.setCursor(0, 1);
  lcd.print("the Reader......");
  /* delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(rtc.getTimeStr());
    lcd.setCursor(0, 1);
    lcd.print("Date: ");
    lcd.print(rtc.getDateStr());
    delay(500);
    lcd.clear(); */
}

void rfid()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();


  if (content.substring(1) == "B4 25 85 1E" && state1 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Kamal    ");
    lcd.setCursor(7, 1);
    lcd.print("000001");
    info();
    SendKamal();
    state1 = 1;
  }
  else if (content.substring(1) == "B4 25 85 1E" && state1 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Kamal    ");
    lcd.setCursor(7, 1);
    lcd.print("000001");
    info();
    SendKamal();
    state1 = 0;
  }
  else if (content.substring(1) == "D1 5A E1 D5" && state2 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Jamal    ");
    lcd.setCursor(7, 1);
    lcd.print("000002");
    info();
    SendJamal();
    state2 = 1;
  }
  else if (content.substring(1) == "D1 5A E1 D5" && state2 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Jamal    ");
    lcd.setCursor(7, 1);
    lcd.print("000002");
    info();
    SendJamal();
    state2 = 0;
  }
  else if (content.substring(1) == "A1 6E B5 D4" && state3 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Azad    ");
    lcd.setCursor(7, 1);
    lcd.print("000003");
    info();
    SendAzad();
    state3 = 1;
  }
  else if (content.substring(1) == "A1 6E B5 D4" && state3 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Azad    ");
    lcd.setCursor(7, 1);
    lcd.print("000003");
    info();
    SendAzad();
    state3 = 0;
  }
  else if (content.substring(1) == "F1 72 62 D5" && state4 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Akib    ");
    lcd.setCursor(7, 1);
    lcd.print("000004");
    info();
    SendAkib();
    state4 = 1;
  }
  else if (content.substring(1) == "F1 72 62 D5" && state4 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Akib    ");
    lcd.setCursor(7, 1);
    lcd.print("000004");
    info();
    SendAkib();
    state4 = 0;
  }
  else if (content.substring(1) == "21 BD 21 D5" && state5 == 0) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Noman    ");
    lcd.setCursor(7, 1);
    lcd.print("000005");
    info();
    SendNoman();
    state5 = 1;
  }
  else if (content.substring(1) == "21 BD 21 D5" && state5 == 1) //change here the UID of the card/cards that you want to give access
  {
    beepON();
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Noman    ");
    lcd.setCursor(7, 1);
    lcd.print("000005");
    info();
    SendNoman();
    state5 = 0;
  }
  else   {
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ID : ");
    lcd.print("Unknown");
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    Serial.println(" Access denied");
    delay(1500);
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
  }
}

void smsSend()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  for (int x = 11; x < 16; x++)
  {
    lcd.setCursor(x, 0);
    lcd.print(".");
    delay(1000);
  }

}
void beepON()
{
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}
void info()
{
  lcd.setCursor(0, 0);
  lcd.print("Name : ");
  lcd.setCursor(0, 1);
  lcd.print("ID   : ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Authorized Access");
  delay(1000);
  lcd.clear();
}

void SendKamal()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state1 == 0) {
    const char kamal[] = "No: 000001 Soldier Kamal has joined from OP/CL/PL at ";
    sim.print(kamal);
  }
  else if (state1 == 1) {
    const char kamal[] = "No: 000001 Soldier Kamal has gone for OP/CL/PL at ";
    sim.print(kamal);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}

void SendJamal()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state2 == 0) {
    const char Jamal[] = "No: 000002 Soldier Jamal has joined from OP/CL/PL at ";
    sim.print(Jamal);
  }
  else if (state2 == 1) {
    const char Jamal[] = "No: 000002 Soldier Jamal has gone for OP/CL/PL at ";
    sim.print(Jamal);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}
void SendAzad()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state3 == 0) {
    const char Azad[] = "No: 000003 Soldier Azad has joined from OP/CL/PL at ";
    sim.print(Azad);
  }
  else if (state3 == 1) {
    const char Azad[] = "No: 000003 Soldier Azad has gone for OP/CL/PL at ";
    sim.print(Azad);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}
void SendAkib()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state4 == 0) {
    const char Akib[] = "No: 000004 Soldier Akib has joined from OP/CL/PL at ";
    sim.print(Akib);
  }
  else if (state4 == 1) {
    const char Akib[] = "No: 000004 Soldier Akib has gone for OP/CL/PL at ";
    sim.print(Akib);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}
void SendNoman()
{
  lcd.setCursor(0, 0);
  lcd.print("SMS Sending");
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  if (state5 == 0) {
    const char Noman[] = "No: 000005 Soldier Noman has joined from OP/CL/PL at ";
    sim.print(Noman);
  }
  else if (state5 == 1) {
    const char Noman[] = "No: 000005 Soldier Noman has gone for OP/CL/PL at ";
    sim.print(Noman);
  }
  sim.println(rtc.getTimeStr());
  delay(100);
  sim.println((char)26);
  smsSend();
}

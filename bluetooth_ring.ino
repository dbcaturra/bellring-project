#include <MillisTimer.h>
MillisTimer timer1;

#include <SoftwareSerial.h> 
SoftwareSerial BT(10,11); //10 RX, 11 TX.

char dato;
int led = 2;


String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
          }
      }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
  }
  

void turnOnBell(){
  digitalWrite(led,HIGH);
  delay(2500);
  digitalWrite(led,LOW);  
  }


void turnOffBell(){
    digitalWrite(led,LOW);  
  }

void bellTimer(int dp, int np){
  Serial.write("bellTimer...");
  }

// This is the function that is called when the timer expires.
void myTimerFunction(MillisTimer &mt)
{
  Serial.print("timer expire...");
  turnOnBell();
}


void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  //TIMER
  timer1.setInterval(7500);       // set timer to trigger every 1000 millis
  timer1.expiredHandler(myTimerFunction);   // call flash() function when timer runs out
  timer1.setRepeats(7);           // repeat forever if set to 0
  timer1.start();                 // start the timer when the sketch starts 
  }


void loop() {
  if(BT.available()){
    dato=BT.read(); 
    Serial.write(dato);
    //String datoS = String(dato);
    
    if (char(dato) == '1'){
        Serial.write("UNO");
        turnOnBell();
      }

    if (char(dato) == '0'){
        turnOffBell();
      }
    
    if(char(dato) == '2') {
        /*Serial.write("Config parser...");
        String np = getValue(datoS, ',', 0);
        String dp = getValue(datoS, ',', 1);
        String dd = getValue(datoS, ',', 2);
        int np_ = np.toInt();
        int dp_ = dp.toInt();
        int dd_ = dd.toInt();*/
        turnOnBell();
        bellTimer(5, 7);
      }

    timer1.run();
    if (!timer1.isRunning())
      {
        Serial.println("Timer finished!");
        for (;;);
      }
    //BT.end();
    //BT.begin(9600);
    }
  }

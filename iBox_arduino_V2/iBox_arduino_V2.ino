#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 
#include <Servo.h>

 //char report;
YunServer server;
Servo ServoPan;
Servo ServoTilt;

void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); 
}
 
void loop() {
  YunClient client = server.accept();
 
  if (client) {
    //String command = client.readString();
    String command = client.readStringUntil('/');
    command.trim();
    if (command == "temperature") {
      float val = float(int((analogRead(A0)*(-0.064)+54.5)*10))/10;
      client.print(val);client.print("°C");
    }
    else if (command == "humidite") {
      int val = analogRead(A1)*(0.154)-27.0;
      client.print(val);client.print("%");
    }
    if (command == "bouton") {
       int num_bouton;
       num_bouton=client.parseInt();
         if (num_bouton==2)
          {ServoPan.attach(2);ServoPan.write(ServoPan.read()+20);delay(1000);ServoPan.detach();}
         if (num_bouton==4)
          {ServoPan.attach(2);ServoPan.write(ServoPan.read()-20);delay(1000);ServoPan.detach();}
         if (num_bouton==1)
          {ServoTilt.attach(3);
            if (ServoTilt.read()>0) {ServoTilt.write(ServoTilt.read()-10);delay(1000);}
           ServoTilt.detach();}
         if (num_bouton==5)
          {ServoTilt.attach(3);
            if (ServoTilt.read()<90) {ServoTilt.write(ServoTilt.read()+10);delay(1000);}
           ServoTilt.detach();}
    }
    client.stop();
  }
 
  delay(50);
}


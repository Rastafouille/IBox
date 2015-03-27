#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 
 char report;
YunServer server;
 
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
      
      
    }
    client.stop();
  }
 
  delay(50);
}


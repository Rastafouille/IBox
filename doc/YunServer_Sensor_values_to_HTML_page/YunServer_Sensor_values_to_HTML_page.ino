#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 
 char report;
YunServer server;
 
void setup() {
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}
 
void loop() {
  YunClient client = server.accept();
 
  if (client) {
    String command = client.readString();
    command.trim();
    if (command == "temperature") {
      int val = analogRead(A0);
      client.print(val);
    }
    else if (command == "humidite") {
      int val = analogRead(A1);
      client.print(val);
    }
    client.stop();
  }
 
  delay(50);
}


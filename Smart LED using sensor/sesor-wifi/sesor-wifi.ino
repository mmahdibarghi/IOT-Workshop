#include <ESP8266WiFi.h>
int ledPin = D7; // choose pin for the LED
int inputPin = D2; // choose input pin for sensor 


int val = 0; // variable for reading the sensor status
int state=0;
int counter=0;

const char* ssid = "Barghi"; //wif name
const char* password = "**********";   //wifi password
 WiFiServer server(80);

void setup() 
{ 
   Serial.begin(115200);
   pinMode(ledPin, OUTPUT);
   pinMode(inputPin, INPUT);


// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 

  server.begin();
  Serial.println("Server started");
 

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}



void loop()
{ 

 WiFiClient client = server.available();
 client.flush();



   val = digitalRead(inputPin); // read input value 
   if (val == LOW && state==0)
   { 
      digitalWrite(ledPin, HIGH); // turn LED OFF
      state=1;
      delay(2000);
       
    
   } 
   else if (val == LOW && state==1) 
   { 
      digitalWrite(ledPin, HIGH);
      state=0;
      counter++;
      delay(2000);
   }
   else
   {
      digitalWrite(ledPin, LOW);
   }









  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println(" <title>Made in lobby</title>");
  client.println("</head>");
    client.println("<body>");

  
  if(state==1) {
    client.print("bah bah, saaaalaaaam!!");
    client.print(counter);
    counter++;
  } 
  else{
    client.print("khodahafezi :\"( ");
    client.print(counter);
    
  }
  
  client.println("<br><br>");
      client.println("</body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}

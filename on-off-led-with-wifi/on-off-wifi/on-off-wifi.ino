#include <ESP8266WiFi.h>
int ledPin = D7; // choose pin for the LED
int value = LOW; // variable for reading the pin status from WiFi
int state=0;
int counter=0;

const char* ssid = "Barghi";  //WiFi Name
const char* password = "*********"; //WiFi password
 WiFiServer server(80);

void setup() 
{ 
   Serial.begin(115200);
   pinMode(ledPin, OUTPUT); // declare LED as output 



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
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}



void loop()
{ 
  

 WiFiClient client = server.available();

  if(!client)
  {
    return;
  }

  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  client.flush();
  if(request.indexOf("/LED=ON") != -1)
  {
    digitalWrite(ledPin, HIGH);
    value= HIGH; 
  }
  else if(request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(ledPin,LOW);
    value= LOW;
    
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br />");  
  client.println("</html>");
 
  
}

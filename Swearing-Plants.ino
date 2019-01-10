/* SWEARING PLANTS MOISTURE SERVICE
 * Uses the NODEMCU to send email notifications letting you know that your
 * plants need to be watered. It checks moisture once an hour
 * 
 * ohh, and it's a bit vulgar with it's notification.
 * 
 */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266SMTP.h>

//DECLARATIONS
//***********************************************************************
//Network Information
//***********************************************************************
const char* ssid     = "SSID";
const char* password = "PASSWORD";
//***********************************************************************
//Email Information
//***********************************************************************
//Email address you want to send notifications to
const char* sendToEmail = "email@gmail.com";
//Email Address and password you want to send the email from
//I recommend making a Gmail Account dedicated to this. Make sure to 
//Change your privacy settings to allow access from Less secure sources 
const char* sentFromEmail ="email2@gmail.com";
const char* sentFromEmailPassword = "password";
//***********************************************************************
//API Information. Uses Fuck Off as a Service (foaas.com)
//***********************************************************************
const char* host = "foaas.com";
const char* from = "Basil";
const int httpPort = 80;

char* pathArray[] = {
  "/asshole/","/because/","/bucket/","/cool/","/diabetes/",
  "/everyone/","/everything/","/family/","/fascinating/", "/flying/",
  "/fyyff/","/give/","/greed/water/","/horse/","/immensity/","/cup/",
  "/life/","/looking/","/maybe/","/me/", "/mornin/","/no/","/pink/",
  "/question/","/ratsarse/","/retard/","/ridiculous/","/rtfm/", "/sake/",
  "/shit/","/single/","/thanks/","/that/","/this/","/too/","/tucker/",
  "/what/","/zayn/","/zero/"
};

//METHODS
//***********************************************************************
//Connection Code
//***********************************************************************
void connect(){
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//***********************************************************************
//Makes a call to the FOAAS API and returns a vulgar message
//***********************************************************************
String apiCall(){
  String message;
  
  //Connect to the API
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "API Connection Failed";
  }
   // This will send the request to the server
  client.print(String("GET ") + pathArray[random(sizeof(pathArray))] + from + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n"  + 
               "Accept: text/plain \r\n" +
               "Connection: close\r\n\r\n");             
  uint32_t timeout = millis();
    while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return "Client Timeout";
    }
  }

  while(client.available()){
    message = client.readStringUntil('\r');
  }
 return message;
}

//***********************************************************************
//Method to send an email notification. Based on Cosmic Boris' example
//***********************************************************************
void sendGmail(String message){
  uint32_t startTime = millis();
  
  SMTP.setEmail(sentFromEmail)
    .setPassword(sentFromEmailPassword)
    .Subject("Plant Information")
    .setFrom(from)
    .setForGmail();                 // simply sets port to 465 and setServer("smtp.gmail.com");           

  
    
  if(SMTP.Send(sendToEmail, "You forgot to water me! " + message)) {
    Serial.println(F("Message sent"));
  } else {
    Serial.print(F("Error sending message: "));
    Serial.println(SMTP.getError());
  } 
  
  Serial.println(millis() - startTime);
}

//***********************************************************************
//Main code
//***********************************************************************
void setup(){
  //Initialize Serial communications
  Serial.begin(115200);
  Serial.setTimeout(2000);
  while (!Serial) { }
  //Set pin A0 as input
  pinMode(A0,INPUT);
  //Set pin D2 as OUTPUT and turn on sensor
  pinMode(D2,OUTPUT);
  digitalWrite(D2,HIGH);
  //Connect to wifi
  connect();
  //Collect 10 Analog Data points and take an average
  int sum = 0;
  int temp =0;
  for(int i=0;i <10; i++){
    temp = analogRead(A0);
    sum += temp;
    delay(100);
  }
  int average = sum / 10;
  if(average > 512){
  
  //Make API call
  String message = apiCall();
  //Send mean email
  sendGmail(message);
  }
  //Deep Sleep for an hour
  ESP.deepSleep(3600e6); 
}


void loop() {

}


//ChanukaLiyanaarachchi Projects
//Esp Project Series
//Project 01 : ESP32-Battery-Telemetry

#include <WiFi.h>
#include <WebServer.h>

// ==========================================
// 1. ENTER YOUR WI-FI DETAILS HERE
// ==========================================
const char* ssid = "Your Wifi SSID"; 
const char* password = "Your Wifi Password";

WebServer server(80);

// The 10 safe pins we selected for the LED Bar Graph
int ledPins[] = {13, 27, 26, 25, 33, 32, 21, 22, 19, 18};
int numLeds = 10;

void setup() {
  Serial.begin(115200);

  // Set all 10 pins as outputs and turn them off initially
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected! ESP32 IP Address:");
  Serial.println(WiFi.localIP());

  // Tell the server to listen for "/battery" requests
  server.on("/battery", handleBatteryUpdate);

  server.begin();
}

void loop() {
  server.handleClient();
}

// This function runs whenever the phone sends data
void handleBatteryUpdate() {
  // Check if the phone included the "?level=" data
  if (server.hasArg("level")) {
    int batteryLevel = server.arg("level").toInt(); // Extract the number
    Serial.print("Phone battery updated to: ");
    Serial.print(batteryLevel);
    Serial.println("%");

    updateBarGraph(batteryLevel); // Change the LEDs
    
    server.send(200, "text/plain", "Battery Level Received!");
  } else {
    server.send(400, "text/plain", "Error: No battery level sent.");
  }
}

// The math to turn on the correct number of LEDs
void updateBarGraph(int percentage) {
  // Map the 0-100% battery level to our 0-10 LEDs
  int ledsToLight = map(percentage, 0, 100, 0, numLeds);

  for (int i = 0; i < numLeds; i++) {
    if (i < ledsToLight) {
      digitalWrite(ledPins[i], HIGH); // Turn ON
    } else {
      digitalWrite(ledPins[i], LOW);  // Turn OFF
    }
  }
}
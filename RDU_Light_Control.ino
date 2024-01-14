#include <ESP8266WiFi.h>

const char* ssid = "Redmi 9T";
const char* password = "03042002";

int ledPinRed = D0;     // GPIO0
int ledPinYellow = D1;  // GPIO1
int ledPinGreen = D2;   // GPIO2

WiFiServer server(80);

int currentMode = 0;
unsigned long modeStartTime = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);

  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYellow, LOW);
  digitalWrite(ledPinGreen, LOW);

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

void resetLEDs() {
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYellow, LOW);
  digitalWrite(ledPinGreen, LOW);
}

void mode1() {
  unsigned long elapsedTime = millis() - modeStartTime;

  if (elapsedTime < 2000) {
    resetLEDs();
    digitalWrite(ledPinGreen, HIGH);
  } else if (elapsedTime < 3000) {
    resetLEDs();
    digitalWrite(ledPinYellow, HIGH);
  } else if (elapsedTime < 5000) {
    resetLEDs();
    digitalWrite(ledPinRed, HIGH);
  } else {
    modeStartTime = millis();  // Reset the start time for the next cycle
  }
}

void mode2() {
  unsigned long elapsedTime = millis() - modeStartTime;

  if (elapsedTime < 4000) {
    resetLEDs();
    digitalWrite(ledPinGreen, HIGH);
  } else if (elapsedTime < 5000) {
    resetLEDs();
    digitalWrite(ledPinYellow, HIGH);
  } else if (elapsedTime < 9000) {
    resetLEDs();
    digitalWrite(ledPinRed, HIGH);
  } else {
    modeStartTime = millis();  // Reset the start time for the next cycle
  }
}

void mode3() {
  unsigned long elapsedTime = millis() - modeStartTime;

  if (elapsedTime < 8000) {
    resetLEDs();
    digitalWrite(ledPinGreen, HIGH);
  } else if (elapsedTime < 9000) {
    resetLEDs();
    digitalWrite(ledPinYellow, HIGH);
  } else if (elapsedTime < 17000) {
    resetLEDs();
    digitalWrite(ledPinRed, HIGH);
  } else {
    modeStartTime = millis();  // Reset the start time for the next cycle
  }
}


void mode4() {
  unsigned long elapsedTime = millis() - modeStartTime;

  if (elapsedTime % 1000 < 500) {
    resetLEDs();
    digitalWrite(ledPinYellow, HIGH);
  } else {
    resetLEDs();
  }
}

void handleRequest(WiFiClient client) {
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/favicon.ico") != -1) {
    // Ignore the request for favicon.ico
    return;
  }

  int mode = 0;
  if (request.indexOf("GET /?mode=1") != -1) {
    mode = 1;
  } else if (request.indexOf("GET /?mode=2") != -1) {
    mode = 2;
  } else if (request.indexOf("GET /?mode=3") != -1) {
    mode = 3;
  } else if (request.indexOf("GET /?mode=4") != -1) {
    mode = 4;
  }

  currentMode = mode;
  modeStartTime = millis();  // Reset the start time when the mode changes

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.println("<h1>ESP8266 LED Control</h1>");
  client.println("<form action='/' method='get'>");
  client.println("Mode 1: <input type='submit' name='mode' value='1'><br>");
  client.println("Mode 2: <input type='submit' name='mode' value='2'><br>");
  client.println("Mode 3: <input type='submit' name='mode' value='3'><br>");
  client.println("Mode 4: <input type='submit' name='mode' value='4'><br>");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    while (client.connected() && !client.available()) {
      delay(1);
    }
    handleRequest(client);
  }

  switch (currentMode) {
    case 1:
      mode1();
      break;
    case 2:
      mode2();
      break;
    case 3:
      mode3();
      break;
    case 4:
      mode4();
      break;
    default:
      break;
  }
}

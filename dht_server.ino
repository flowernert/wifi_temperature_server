//network related
#include <ESP8266WiFi.h>
#define SSID "your_ssid"
#define PASSWORD "your_wifi_password"

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
ESP8266WebServer server(80);

void putTemperature();//http put request handler
void json_to_resource_update(JsonObject& jsonBody);
void initTemperaturesResource();

#define ID_INSIDE 0
#define ID_SOUTH_SHADED 1
#define ID_SOUTH_SUN 2
#define ID_ATTIC 3

#define NO_DATA_RECEIVED -100

byte temperatures_resource[4] = {NO_DATA_RECEIVED};
uint32_t delayMS = 1000;

void setup() {
  Serial.begin(9600); 

  //Wifi setup and connection
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //http routes setup
  server.on("/", showTemperatures);
  server.on("/temperatures", HTTP_PUT, putTemperature);
  server.begin();

  // To identify the server's IP for the clients
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(delayMS);
  server.handleClient();
}

void showTemperatures() {
  server.send(200, "text/plain", 
              String("Temperature inside is ") + String(temperatures_resource[ID_INSIDE]) + String(" *C\n") +
              String("Temperature at south under shade is ") + String(temperatures_resource[ID_SOUTH_SHADED]) + String(" *C\n") +
              String("Temperature at south under sun is ") + String(temperatures_resource[ID_SOUTH_SUN]) + String(" *C\n") +
              String("Temperature in the attic is ") + String(temperatures_resource[ID_ATTIC]) + String(" *C\n") 
  );
}

void json_to_resource_update(JsonObject& jsonBody) {
    byte id = jsonBody["id"];
    byte value = jsonBody["value"];
    temperatures_resource[id] = value;

    Serial.println(id);
    Serial.println(value);
}

void putTemperature() {
  StaticJsonBuffer<200> jsonBuffer;
  String post_body = server.arg("plain");
  Serial.println("post body :");
  Serial.println(post_body);
  Serial.println(post_body.length());

  JsonObject& jsonBody = jsonBuffer.parseObject(post_body);

  Serial.print("HTTP Method: ");
  Serial.println(server.method());
  
  if (!jsonBody.success()) {
    Serial.println("error in parsing json body");
    server.send(400);
  }
  else {
    if (server.method() == HTTP_PUT) {
      int id = jsonBody["id"];
      if (id > 0 and id < 4) {
        json_to_resource_update(jsonBody);
        server.sendHeader("Location", "/temperatures/" + String(id));
        server.send(200);
      }
      else {
        server.send(404);
      }
    }
    else {
      server.send(400);
    }
  }
}


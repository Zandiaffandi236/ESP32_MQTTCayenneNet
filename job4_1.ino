//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include "CayenneMQTTESP32.h" // ganti tanda " dengan > jika program error
#include "DHT.h"

#define DHTPIN 15     // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// WiFi network info.
char ssid[] = "Galax";
char wifiPassword[] = "12345678";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "2fc92080-81b4-11ed-8d53-d7cd1025126a";
char password[] = "b933955043a28a7f2a902c804e8ff77e2c713266";
char clientID[] = "398de3d0-81b4-11ed-b193-d9789b2af62b";

unsigned long lastMillis = 0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  //  pinMode (D4, OUTPUT);
}
float h, t, f;
void loop() {
  Cayenne.loop();

  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}

CAYENNE_OUT(1)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Suhu %f C", 1, t);
  Cayenne.celsiusWrite(1, t);
}
CAYENNE_OUT(2)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Suhu %f F", 2, f);
  Cayenne.fahrenheitWrite(2, f);
}
CAYENNE_OUT(3)
{
  CAYENNE_LOG("Send data for Virtual Channel %d Hum %f ", 3, h);
  Cayenne.virtualWrite(3, h);
}

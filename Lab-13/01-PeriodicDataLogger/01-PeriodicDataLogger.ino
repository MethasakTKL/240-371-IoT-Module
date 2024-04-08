#include <DHT.h>

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);

  dht.begin();
  delay(500);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.println("");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // sleep 1 minute
  Serial.println("SEE YOU NEXT MINUTE");
  esp_sleep_enable_timer_wakeup(10 * 1000000);
  esp_deep_sleep_start();
}

void loop()
{
}

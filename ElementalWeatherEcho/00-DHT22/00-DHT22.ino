#include <DHT.h>

#define DHTPIN 16     // กำหนดหมายเลขพินของ DHT22
#define DHTTYPE DHT22 // ระบุรุ่นของ DHT (DHT11 หรือ DHT22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(2000); // รอให้ระบบเริ่มต้น
  dht.begin();
}

void loop() {
  delay(2000); // รอเวลา 2 วินาที ระหว่างการอ่านข้อมูล

  float humidity = dht.readHumidity();    // อ่านค่าความชื้น
  float temperature = dht.readTemperature(); // อ่านค่าอุณหภูมิ (เซลเซียส)

  // ตรวจสอบว่าอ่านข้อมูลได้สำเร็จหรือไม่
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // แสดงผลลัพธ์ทาง Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
}

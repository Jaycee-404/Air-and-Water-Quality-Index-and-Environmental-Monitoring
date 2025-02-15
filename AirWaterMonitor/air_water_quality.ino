#define BLYNK_TEMPLATE_ID "TMPLgwKssgggsnFXp"
#define BLYNK_DEVICE_NAME "Air & Water Quality Monitor"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"  // 🔴 Replace with your token

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// 🔹 WiFi Credentials
char ssid[] = "YOUR_WIFI_SSID";  // 🔴 Replace with your WiFi name
char pass[] = "YOUR_WIFI_PASSWORD";  // 🔴 Replace with your WiFi password

// 🔹 Define Sensors & LCD
#define DHTPIN 2         // DHT11 connected to D2 (NodeMCU)
#define DHTTYPE DHT11    // DHT11 Sensor
#define GAS_SENSOR A0    // Gas sensor pin
#define TURBIDITY_SENSOR A0  // Turbidity sensor (same pin for ESP8266)

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 🔹 Degree Symbol for LCD
typedef byte customChar[8];
customChar degree_symbol = {
    0b00111,
    0b00101,
    0b00111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

void sendSensorData() {
    // 🌡️ Read Temperature & Humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // 🌫️ Read Gas Sensor
    int gasValue = analogRead(GAS_SENSOR);

    // 💦 Read Turbidity Sensor
    int turbidityRaw = analogRead(TURBIDITY_SENSOR);
    if (turbidityRaw > 208) turbidityRaw = 208;
    int turbidity = map(turbidityRaw, 0, 208, 300, 0);

    // 🔹 Send Data to Blynk
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, gasValue);
    Blynk.virtualWrite(V3, turbidity);

    // 🔹 Debugging
    Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C  ");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.print("%  ");
    Serial.print("Gas: "); Serial.print(gasValue); Serial.print("  ");
    Serial.print("Turbidity: "); Serial.println(turbidity);
}

void setup() {
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    dht.begin();
    lcd.init();
    lcd.backlight();
    lcd.createChar(1, degree_symbol);

    // Initial LCD Message
    lcd.setCursor(2, 0);
    lcd.print("Air & Water");
    lcd.setCursor(2, 1);
    lcd.print("Monitoring");
    delay(2000);
    lcd.clear();

    // Set Timer for Sensor Data
    timer.setInterval(5000L, sendSensorData);
}

void loop() {
    Blynk.run();
    timer.run();

    // 🌡️ Read Temperature & Humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int gasValue = analogRead(GAS_SENSOR);
    int turbidityRaw = analogRead(TURBIDITY_SENSOR);
    if (turbidityRaw > 208) turbidityRaw = 208;
    int turbidity = map(turbidityRaw, 0, 208, 300, 0);

    // 🔹 Display on LCD
    lcd.setCursor(0, 0);
    lcd.print("Temp: "); lcd.print(temperature);
    lcd.setCursor(6, 0);
    lcd.write(1);  // Degree symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: "); lcd.print(humidity); lcd.print("%");
    delay(4000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Gas: "); lcd.print(gasValue);
    if (gasValue < 600) {
        lcd.setCursor(0, 1);
        lcd.print("Fresh Air");
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Bad Air!");
        Blynk.logEvent("pollution_alert", "Bad Air Detected!");
    }
    delay(4000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Turbidity: "); lcd.print(turbidity);
    lcd.setCursor(0, 1);
    if (turbidity < 10) lcd.print("Water Very Clean");
    else if (turbidity < 30) lcd.print("Water Normal");
    else lcd.print("Water Dirty!");
    delay(4000);
    lcd.clear();
}
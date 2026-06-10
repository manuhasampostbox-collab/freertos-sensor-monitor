#include <Arduino_FreeRTOS.h>
#include <Wire.h>

// ================================================
// FreeRTOS Multi-Task Sensor Monitor
// Tasks: SensorRead (Priority 2), UartLogger (Priority 1), Heartbeat (Priority 1)
// Protocols: I2C (Wire), UART (Serial)
// Platform: Arduino Mega (Wokwi simulation)
// ================================================

volatile float g_temperature = 0;
volatile float g_humidity = 0;
volatile bool g_data_ready = false;

// Simulate I2C sensor read
float simulateTemp() {
  static float t = 24.0;
  t += 0.3;
  if (t > 32.0) t = 24.0;
  return t;
}

float simulateHum() {
  static float h = 55.0;
  h += 0.5;
  if (h > 75.0) h = 55.0;
  return h;
}

// Task 1: Read sensor every 1 second (highest priority)
void taskSensorRead(void *pvParameters) {
  Serial.println("[TASK1] Sensor task started");
  for(;;) {
    g_temperature = simulateTemp();
    g_humidity = simulateHum();
    g_data_ready = true;
    Serial.print("[TASK1] Temp=");
    Serial.print(g_temperature);
    Serial.print("C Hum=");
    Serial.print(g_humidity);
    Serial.println("%");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task 2: Log data over UART
void taskUartLogger(void *pvParameters) {
  Serial.println("[TASK2] Logger started");
  int count = 0;
  for(;;) {
    if (g_data_ready) {
      g_data_ready = false;
      count++;
      Serial.print("[TASK2] LOG #");
      Serial.print(count);
      Serial.print(" Temp=");
      Serial.print(g_temperature);
      Serial.print("C Hum=");
      Serial.print(g_humidity);
      Serial.println("% STATUS=OK");
    }
    vTaskDelay(1100 / portTICK_PERIOD_MS);
  }
}

// Task 3: Heartbeat LED blink
void taskHeartbeat(void *pvParameters) {
  Serial.println("[TASK3] Heartbeat started");
  pinMode(LED_BUILTIN, OUTPUT);
  for(;;) {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(800 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("FreeRTOS Sensor Monitor");
  Serial.println("3 Tasks: SensorRead, UartLogger, Heartbeat");
  xTaskCreate(taskSensorRead, "SensorRead", 256, NULL, 2, NULL);
  xTaskCreate(taskUartLogger, "UartLogger", 256, NULL, 1, NULL);
  xTaskCreate(taskHeartbeat,  "Heartbeat",  128, NULL, 1, NULL);
}

void loop() {}

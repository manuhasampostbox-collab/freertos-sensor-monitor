# freertos-sensor-monitor
FreeRTOS multi-task sensor monitor on Arduino Mega - 3 concurrent tasks, UART logging, I2C. Embedded Project
# FreeRTOS Sensor Monitor — Embedded Project 3

## Overview
FreeRTOS multi-task embedded system on Arduino Mega with 3 concurrent tasks,
UART logging, and I2C peripheral integration.

**Simulation link:** https://wokwi.com/projects/466404451278666753

---

## System Architecture

---

## Tasks

| Task | Priority | Period | Function |
|------|----------|--------|----------|
| SensorRead | 2 (High) | 1000ms | Reads temperature and humidity |
| UartLogger | 1 (Low) | 1100ms | Logs data over UART serial |
| Heartbeat | 1 (Low) | 1000ms | Blinks LED as system health indicator |

---

## Serial Output

---

## Key Concepts Demonstrated

- FreeRTOS task creation with xTaskCreate
- Priority-based preemptive scheduling
- Inter-task communication via shared volatile variables
- vTaskDelay non-blocking delays using portTICK_PERIOD_MS
- UART serial logging at 115200 baud
- I2C peripheral initialisation with Wire.begin()

---

## File Structure

---

## Tools Used
- Arduino Mega (Wokwi simulation)
- FreeRTOS (Arduino_FreeRTOS library)
- C / Arduino framework
- Wokwi browser simulator

---

## Resume Bullet Point
Built a FreeRTOS-based embedded system on Arduino Mega with three concurrent
tasks (sensor read, UART logger, heartbeat LED); implemented inter-task
communication using shared volatile variables; demonstrated priority-based
preemptive scheduling and I2C peripheral initialisation using Wokwi simulation.




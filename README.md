# ESP32 Multi-Mode LED & Button Controller

An embedded firmware project built for the ESP32 using the Arduino framework. It demonstrates robust, non-blocking state machine design with hardware debouncing, PWM brightness control, blinking, and a smooth breathing effect toggled via a single pushbutton.

---

## Features

* **Non-Blocking Architecture:** Built entirely around `millis()` to ensure the main loop never blocks execution.
* **Hardware Debouncing:** Filters out pushbutton noise with a configurable 50ms delay.
* **PWM Brightness Control:** Utilizes LEDC PWM channels (10 kHz frequency, 6-bit resolution).
* **Multi-Mode State Machine:** Cycles through 4 distinct operating modes with each button press.

---

## Pinout Configuration

| Component | ESP32 GPIO Pin | Description |
| --- | --- | --- |
| **Pushbutton** | `GPIO 12` | Configured as `INPUT_PULLUP` (Active LOW) |
| **LED** | `GPIO 4` | PWM output channel for brightness and fading |

---

## Operating Modes

Pressing the pushbutton cycles through the following modes sequentially:

| Mode | State Name | Action / Behavior |
| --- | --- | --- |
| **0** | **Off** | LED is completely turned off (PWM = 0). |
| **1** | **Steady On** | LED is illuminated at maximum brightness (PWM = 63). |
| **2** | **Blinking** | LED blinks continuously at a 500ms interval. |
| **3** | **Breathing / Fading** | LED smoothly fades in and out with a 50ms step interval. |

---

## Code Structure & Technical Highlights

* **Debounce Logic:** Compares state changes and checks elapsed time using `millis()` against a `debounce_delay` of 50ms.
* **LEDC Configuration:** Uses ESP32 PWM peripheral controls (`ledcSetup`, `ledcAttachPin`, and `ledcWrite`) configured at 10 kHz with a 6-bit depth (`MAX_BRIGHTNESS = 63`).
* **State Tracking:** Uses independent non-blocking interval timers (`previousblinkmillis`, `previousfademillis`) to handle background timing without freezing button responsiveness.

---

## Getting Started

### Prerequisites

* [PlatformIO](https://platformio.org/) or [Arduino IDE](https://www.arduino.cc/) configured with the ESP32 board package.
* An ESP32 development board, a push button, and an LED with a current-limiting resistor.

### Compilation & Upload

1. Clone or download this repository.
2. Open the project in your preferred IDE.
3. Connect your ESP32 board via USB and upload the firmware.

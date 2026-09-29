/****************************************************
       LASER BEAM SECURITY GRID
       ESP8266 + 2 Laser + 2 LDR + Buzzer + Blynk
****************************************************/

// ================= BLYNK DETAILS =================

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Laser Beam Security Grid"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

// ================= WIFI DETAILS ==================

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ================= LIBRARIES =====================

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ================= PIN CONNECTIONS ===============

// Laser 1  -> D1
// Laser 2  -> D2
// LDR 1 DO -> D5
// LDR 2 DO -> D6
// Buzzer   -> D7

#define LASER1 D1
#define LASER2 D2

#define LDR1 D5
#define LDR2 D6

#define BUZZER D7

#define LED LED_BUILTIN

// =================================================

BlynkTimer timer;

bool oldAlarm = false;

int alertCount = 0;

unsigned long lastAlert = 0;

const unsigned long alertDelay = 10000;


// =================================================
// SETUP
// =================================================

void setup()
{
  Serial.begin(115200);

  // Laser pins
  pinMode(LASER1, OUTPUT);
  pinMode(LASER2, OUTPUT);

  // LDR pins
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // Built-in LED
  pinMode(LED, OUTPUT);

  // Initial condition
  digitalWrite(LASER1, HIGH);
  digitalWrite(LASER2, HIGH);

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, HIGH);

  Serial.println();
  Serial.println("================================");
  Serial.println(" LASER BEAM SECURITY GRID");
  Serial.println("================================");

  // Connect Wi-Fi + Blynk
  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  // Check sensors every 100 milliseconds
  timer.setInterval(
    100L,
    checkSecurity
  );

  Serial.println("SYSTEM READY");
}


// =================================================
// SECURITY CHECK
// =================================================

void checkSecurity()
{
  int sensor1 = digitalRead(LDR1);
  int sensor2 = digitalRead(LDR2);

  /*
     Beam present  = HIGH
     Beam broken   = LOW

     If your LDR works opposite,
     change LOW below to HIGH.
  */

  bool zone1Alarm = (sensor1 == LOW);
  bool zone2Alarm = (sensor2 == LOW);

  bool alarm = zone1Alarm || zone2Alarm;


  // =================================================
  // NORMAL CONDITION
  // =================================================

  if (!alarm)
  {
    digitalWrite(BUZZER, LOW);

    // Built-in LED OFF
    digitalWrite(LED, HIGH);

    // Blynk
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
  }


  // =================================================
  // INTRUSION CONDITION
  // =================================================

  else
  {
    // Buzzer ON
    digitalWrite(BUZZER, HIGH);

    // Built-in LED ON
    digitalWrite(LED, LOW);

    // Overall alarm
    Blynk.virtualWrite(V0, 1);

    // Zone 1
    Blynk.virtualWrite(
      V1,
      zone1Alarm ? 1 : 0
    );

    // Zone 2
    Blynk.virtualWrite(
      V2,
      zone2Alarm ? 1 : 0
    );


    // Send notification only once
    // when alarm starts

    if (!oldAlarm)
    {
      alertCount++;

      Blynk.virtualWrite(
        V3,
        alertCount
      );

      if (millis() - lastAlert > alertDelay)
      {
        if (zone1Alarm && zone2Alarm)
        {
          Blynk.logEvent(
            "laser_alert",
            "Intrusion detected in Zone 1 and Zone 2"
          );
        }

        else if (zone1Alarm)
        {
          Blynk.logEvent(
            "laser_alert",
            "Intrusion detected in Zone 1"
          );
        }

        else
        {
          Blynk.logEvent(
            "laser_alert",
            "Intrusion detected in Zone 2"
          );
        }

        lastAlert = millis();
      }
    }
  }


  // Save current alarm state
  oldAlarm = alarm;


  // =================================================
  // SERIAL MONITOR
  // =================================================

  Serial.print("Zone 1: ");

  if (zone1Alarm)
    Serial.print("INTRUSION");
  else
    Serial.print("NORMAL");

  Serial.print(" | Zone 2: ");

  if (zone2Alarm)
    Serial.print("INTRUSION");
  else
    Serial.print("NORMAL");

  Serial.print(" | Alerts: ");
  Serial.println(alertCount);
}


// =================================================
// LOOP
// =================================================

void loop()
{
  Blynk.run();

  timer.run();
}

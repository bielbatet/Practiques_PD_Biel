#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>

#define RST_PIN 9
#define SS_RFID 15
#define SS_SD 10

MFRC522 mfrc522(SS_RFID, RST_PIN);
File logFile;
int lecturaCount = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Inici SPI compartit
  SPI.begin(12, 13, 11, 10); // SCK, MISO, MOSI, CS dummy

  // Inicialitzem SD
  Serial.println("📦 Iniciant SD...");
  if (!SD.begin(SS_SD)) {
    Serial.println("❌ No s'ha pogut inicialitzar la SD.");
    return;
  }
  Serial.println("✅ SD inicialitzada!");

  // Inicialitzem RFID
  mfrc522.PCD_Init();
  Serial.println("📡 Lector RFID llest.");

  Serial.println("\nApropa una targeta per registrar UID...");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lecturaCount++;

    // Llegim UID
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
      uid += String(mfrc522.uid.uidByte[i], HEX);
    }

    // Simulem hora (exemple bàsic)
    String hora = "2025-03-24 18:42:00";

    // Obrim fitxer
    logFile = SD.open("/lecturas.log", FILE_APPEND);
    if (logFile) {
      logFile.print(hora);
      logFile.print(" - UID: ");
      logFile.println(uid);
      logFile.close();

      Serial.println("✅ Lectura registrada:");
      Serial.print("  🕒 ");
      Serial.println(hora);
      Serial.print("  🆔 UID: ");
      Serial.println(uid);
    } else {
      Serial.println("❌ Error obrint el fitxer .log");
    }

    mfrc522.PICC_HaltA();
    delay(1000); // Petita pausa per evitar lectures duplicades
  }
}


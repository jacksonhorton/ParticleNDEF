
#include <Wire.h>
#include <PN532_I2C.h>
#include <ParticlePN532.h>
#include <NfcAdapter.h>

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup()
{
    Log.info("NDEF Writer");
    nfc.begin();
}

void loop()
{
    Log.info("\nPlace a formatted Mifare Classic or Ultralight NFC tag on the reader.");
    if (nfc.tagPresent())
    {
        NdefMessage message = NdefMessage();
        message.addUriRecord("http://particle.io");

        bool success = nfc.write(message);
        if (success)
        {
            Log.info("Success. Try reading this tag with your phone.");
        }
        else
        {
            Log.warn("Write failed.");
        }
    }
    delay(5000);
}
// Erases a NFC tag by writing an empty NDEF message
#include <Wire.h>
#include <PN532_I2C.h>
#include <ParticlePN532.h>
#include <NfcAdapter.h>

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup(void)
{
    Log.info("NFC Tag Eraser");
    nfc.begin();
}

void loop(void)
{
    Log.info("\nPlace a tag on the NFC reader to erase.");

    if (nfc.tagPresent())
    {

        bool success = nfc.erase();
        if (success)
        {
            Log.info("\nSuccess, tag contains an empty record.");
        }
        else
        {
            Log.warn("\nUnable to erase tag.");
        }
    }
    delay(5000);
}

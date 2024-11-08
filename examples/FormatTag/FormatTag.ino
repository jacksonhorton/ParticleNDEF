// Formats a Mifare Classic tags as an NDEF tag
// This will fail if the tag is already formatted NDEF
// nfc.clean will turn a NDEF formatted Mifare Classic tag back to the Mifare Classic format
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
    Log.info("NDEF Formatter");
    nfc.begin();
}

void loop(void)
{

    Log.info("\nPlace an unformatted Mifare Classic tag on the reader.");
    if (nfc.tagPresent())
    {

        bool success = nfc.format();
        if (success)
        {
            Log.info("\nSuccess, tag formatted as NDEF.");
        }
        else
        {
            Log.warn("\nFormat failed.");
        }
    }
    delay(5000);
}

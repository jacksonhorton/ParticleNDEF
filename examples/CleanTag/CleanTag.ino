// Clean resets a tag back to factory-like state
// For Mifare Classic, tag is zero'd and reformatted as Mifare Classic
// For Mifare Ultralight, tags is zero'd and left empty
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
    Log.info("NFC Tag Cleaner");
    nfc.begin();
}

void loop(void)
{

    Log.info("\nPlace a tag on the NFC reader to clean.");

    if (nfc.tagPresent())
    {

        bool success = nfc.clean();
        if (success)
        {
            Log.info("\nSuccess, tag restored to factory state.");
        }
        else
        {
            Log.warn("\nError, unable to clean tag.");
        }
    }
    delay(5000);
}

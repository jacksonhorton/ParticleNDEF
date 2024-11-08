
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
    Log.info("NDEF Reader");
    nfc.begin();
}

void loop(void)
{
    Log.info("\nScan a NFC tag");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        tag.print();
    }
    delay(5000);
}

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
        Log.info(String(tag.getType()));
        Log.info("UID: %s", String(tag.getUidString()));

        if (tag.hasNdefMessage()) // every tag won't have a message
        {

            NdefMessage message = tag.getNdefMessage();
            Log.info("\nThis NFC Tag contains an NDEF Message with %d NDEF Record(s).", message.getRecordCount());

            // cycle through the records, printing some info from each
            int recordCount = message.getRecordCount();
            for (int i = 0; i < recordCount; i++)
            {
                Log.info("NDEF Record %d:", i + 1);
                NdefRecord record = message.getRecord(i);
                // NdefRecord record = message[i]; // alternate syntax

                Log.info("\tTNF: %s", record.getTnf());
                Log.info("\tType: %s", record.getType()); // will be "" for TNF_EMPTY

                // The TNF and Type should be used to determine how your application processes the payload
                // There's no generic processing for the payload, it's returned as a byte[]
                int payloadLength = record.getPayloadLength();
                byte payload[payloadLength];
                record.getPayload(payload);

                PrintHexChar(payload, payloadLength);

                // Force the data into a String (might work depending on the content)
                // Real code should use smarter processing
                String payloadAsString = "";
                for (int c = 0; c < payloadLength; c++)
                {
                    payloadAsString += (char)payload[c];
                }
                Log.info("\tPayload (string:) %s", payloadAsString);

                // id is probably blank and will return ""
                String uid = record.getId();
                if (uid != "")
                {
                    Log.info("\tID: %s", String(uid));
                }
            }
        }
    }
    delay(3000);
}

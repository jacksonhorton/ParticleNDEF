# NDEF Library for Particle

Read and Write NDEF messages on NFC Tags with Particle.

NFC Data Exchange Format (NDEF) is a common data format that operates across all NFC devices, regardless of the underlying tag or device technology.

### Supports
Reading from Mifare Classic Tags with 4 byte UIDs.
Writing to Mifare Classic Tags with 4 byte UIDs.
Reading from Mifare Ultralight tags.
Writing to Mifare Ultralight tags.

## Dependencies
The [`ParticlePN532`](https://github.com/jacksonhorton/ParticlePN532) Particle library.


## Getting Started

To use the Ndef library in your code, include the following in your sketch:
```
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
```

### NfcAdapter

The user interacts with the NfcAdapter to read and write NFC tags using the NFC shield.

Read a message from a tag
```
if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    tag.print();
}
```
Write a message to a tag
```
if (nfc.tagPresent()) {
    NdefMessage message = NdefMessage();
    message.addTextRecord("Hello, Arduino!");
    success = nfc.write(message);
}
```
Erase a tag. Tags are erased by writing an empty NDEF message. Tags are not zeroed out the old data may still be read off a tag using an application like [NXP's TagInfo](https://play.google.com/store/apps/details?id=com.nxp.taginfolite&hl=en).
```
if (nfc.tagPresent()) {
    success = nfc.erase();
}
```

Format a Mifare Classic tag as NDEF.
```
if (nfc.tagPresent()) {
    success = nfc.format();
}
```

Clean a tag. Cleaning resets a tag back to a factory-like state. For Mifare Classic, tag is zeroed and reformatted as Mifare Classic (non-NDEF). For Mifare Ultralight, the tag is zeroed and left empty.
```
if (nfc.tagPresent()) {
    success = nfc.clean();
}
```

## License

[BSD License](https://github.com/jacksonhorton/ParticleNdef/blob/master/LICENSE) (c) 2024, Jackson Horton (c) 2013-2014, Don Coleman
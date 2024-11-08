#ifndef MifareUltralight_h
#define MifareUltralight_h

#include <ParticlePN532.h>
#include <NfcTag.h>
#include <ParticleNDEF.h>

class MifareUltralight
{
    public:
        MifareUltralight(ParticlePN532& nfcShield);
        ~MifareUltralight();
        NfcTag read(byte *uid, unsigned int uidLength);
        boolean write(NdefMessage& ndefMessage, byte *uid, unsigned int uidLength);
        boolean clean();
    private:
        ParticlePN532* nfc;
        unsigned int tagCapacity;
        unsigned int messageLength;
        unsigned int bufferSize;
        unsigned int ndefStartIndex;
        boolean isUnformatted();
        void readCapabilityContainer();
        void findNdefMessage();
        void calculateBufferSize();
};

#endif

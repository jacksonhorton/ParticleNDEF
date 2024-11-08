#include "ParticleNDEF.h"

#ifdef NDEF_LOGGING
// Borrowed from Adafruit_NFCShield_I2C
void PrintHex(const byte *data, const long numBytes)
{
  String hexString = "";
  for (int32_t szPos = 0; szPos < numBytes; szPos++)
  {
    hexString += "0x";
    // Append leading 0 for small values
    if (data[szPos] <= 0xF)
      hexString += "0";
    hexString += String(data[szPos] & 0xff, HEX);
    if ((numBytes > 1) && (szPos != numBytes - 1))
    {
      hexString += " ";
    }
  }

  Log.info("\t\tHEX:\t%s", hexString.c_str());
}

void PrintChar(const byte *data, const long numBytes)
{
  String charString = "";

  for (int32_t szPos = 0; szPos < numBytes; szPos++)
  {
    if (data[szPos] <= 0x1F)
      charString += ".";
    else
      charString += (char)data[szPos];
  }

  Log.info("\t\tCHAR:\t%s", hexString.c_str());
}

// Borrowed from Adafruit_NFCShield_I2C
void PrintHexChar(const byte *data, const long numBytes)
{
  PrintHex(data, numBytes);
  PrintChar(data, numBytes);
}

// Note if buffer % blockSize != 0, last block will not be written
void DumpHex(const byte *data, const long numBytes, const unsigned int blockSize)
{
  int i;
  for (i = 0; i < (numBytes / blockSize); i++)
  {
      PrintHexChar(data, blockSize);
      data += blockSize;
  }
}
#endif

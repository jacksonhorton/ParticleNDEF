#ifndef Ndef_h
#define Ndef_h

// To save memory and stop serial output comment out the next line
#define NDEF_LOGGING

/* NOTE: To use the ParticleNDEF library in your code, don't include ParticleNDEF.h
   See README.md for details on which files to include in your sketch.
*/

#include <Particle.h>

#ifdef NDEF_LOGGING
void PrintHex(const byte *data, const long numBytes);
void PrintHexChar(const byte *data, const long numBytes);
void DumpHex(const byte *data, const long numBytes, const int blockSize);
#endif

#endif

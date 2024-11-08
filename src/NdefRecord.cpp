#include "NdefRecord.h"

NdefRecord::NdefRecord()
{
    //Serial.println("NdefRecord Constructor 1");
    _tnf = 0;
    _typeLength = 0;
    _payloadLength = 0;
    _idLength = 0;
    _type = (byte *)NULL;
    _payload = (byte *)NULL;
    _id = (byte *)NULL;
}

NdefRecord::NdefRecord(const NdefRecord& rhs)
{
    //Log.info("NdefRecord Constructor 2 (copy)");

    _tnf = rhs._tnf;
    _typeLength = rhs._typeLength;
    _payloadLength = rhs._payloadLength;
    _idLength = rhs._idLength;
    _type = (byte *)NULL;
    _payload = (byte *)NULL;
    _id = (byte *)NULL;

    if (_typeLength)
    {
        _type = (byte*)malloc(_typeLength);
        memcpy(_type, rhs._type, _typeLength);
    }

    if (_payloadLength)
    {
        _payload = (byte*)malloc(_payloadLength);
        memcpy(_payload, rhs._payload, _payloadLength);
    }

    if (_idLength)
    {
        _id = (byte*)malloc(_idLength);
        memcpy(_id, rhs._id, _idLength);
    }

}

// TODO NdefRecord::NdefRecord(tnf, type, payload, id)

NdefRecord::~NdefRecord()
{
    //Log.info("NdefRecord Destructor");
    if (_typeLength)
    {
        free(_type);
    }

    if (_payloadLength)
    {
        free(_payload);
    }

    if (_idLength)
    {
        free(_id);
    }
}

NdefRecord& NdefRecord::operator=(const NdefRecord& rhs)
{
    //Log.info("NdefRecord ASSIGN");

    if (this != &rhs)
    {
        // free existing
        if (_typeLength)
        {
            free(_type);
        }

        if (_payloadLength)
        {
            free(_payload);
        }

        if (_idLength)
        {
            free(_id);
        }

        _tnf = rhs._tnf;
        _typeLength = rhs._typeLength;
        _payloadLength = rhs._payloadLength;
        _idLength = rhs._idLength;

        if (_typeLength)
        {
            _type = (byte*)malloc(_typeLength);
            memcpy(_type, rhs._type, _typeLength);
        }

        if (_payloadLength)
        {
            _payload = (byte*)malloc(_payloadLength);
            memcpy(_payload, rhs._payload, _payloadLength);
        }

        if (_idLength)
        {
            _id = (byte*)malloc(_idLength);
            memcpy(_id, rhs._id, _idLength);
        }
    }
    return *this;
}

// size of records in bytes
int NdefRecord::getEncodedSize()
{
    int size = 2; // tnf + typeLength
    if (_payloadLength > 0xFF)
    {
        size += 4;
    }
    else
    {
        size += 1;
    }

    if (_idLength)
    {
        size += 1;
    }

    size += (_typeLength + _payloadLength + _idLength);

    return size;
}

void NdefRecord::encode(byte *data, bool firstRecord, bool lastRecord)
{
    // assert data > getEncodedSize()

    uint8_t* data_ptr = &data[0];

    *data_ptr = getTnfByte(firstRecord, lastRecord);
    data_ptr += 1;

    *data_ptr = _typeLength;
    data_ptr += 1;

    if (_payloadLength <= 0xFF) {  // short record
        *data_ptr = _payloadLength;
        data_ptr += 1;
    } else { // long format
        // 4 bytes but we store length as an int
        data_ptr[0] = 0x0; // (_payloadLength >> 24) & 0xFF;
        data_ptr[1] = 0x0; // (_payloadLength >> 16) & 0xFF;
        data_ptr[2] = (_payloadLength >> 8) & 0xFF;
        data_ptr[3] = _payloadLength & 0xFF;
        data_ptr += 4;
    }

    if (_idLength)
    {
        *data_ptr = _idLength;
        data_ptr += 1;
    }

    //Serial.println(2);
    memcpy(data_ptr, _type, _typeLength);
    data_ptr += _typeLength;

    if (_idLength)
    {
        memcpy(data_ptr, _id, _idLength);
        data_ptr += _idLength;
    }
    
    memcpy(data_ptr, _payload, _payloadLength);
    data_ptr += _payloadLength;
}

byte NdefRecord::getTnfByte(bool firstRecord, bool lastRecord)
{
    int value = _tnf;

    if (firstRecord) { // mb
        value = value | 0x80;
    }

    if (lastRecord) { //
        value = value | 0x40;
    }

    // chunked flag is always false for now
    // if (cf) {
    //     value = value | 0x20;
    // }

    if (_payloadLength <= 0xFF) {
        value = value | 0x10;
    }

    if (_idLength) {
        value = value | 0x8;
    }

    return value;
}

byte NdefRecord::getTnf()
{
    return _tnf;
}

void NdefRecord::setTnf(byte tnf)
{
    _tnf = tnf;
}

unsigned int NdefRecord::getTypeLength()
{
    return _typeLength;
}

int NdefRecord::getPayloadLength()
{
    return _payloadLength;
}

unsigned int NdefRecord::getIdLength()
{
    return _idLength;
}

String NdefRecord::getType()
{
    char type[_typeLength + 1];
    memcpy(type, _type, _typeLength);
    type[_typeLength] = '\0'; // null terminate
    return String(type);
}

// this assumes the caller created type correctly
void NdefRecord::getType(uint8_t* type)
{
    memcpy(type, _type, _typeLength);
}

void NdefRecord::setType(const byte * type, const unsigned int numBytes)
{
    if(_typeLength)
    {
        free(_type);
    }

    _type = (uint8_t*)malloc(numBytes);
    memcpy(_type, type, numBytes);
    _typeLength = numBytes;
}

// assumes the caller sized payload properly
void NdefRecord::getPayload(byte *payload)
{
    memcpy(payload, _payload, _payloadLength);
}

void NdefRecord::setPayload(const byte * payload, const int numBytes)
{
    if (_payloadLength)
    {
        free(_payload);
    }

    _payload = (byte*)malloc(numBytes);
    memcpy(_payload, payload, numBytes);
    _payloadLength = numBytes;
}

String NdefRecord::getId()
{
    char id[_idLength + 1];
    memcpy(id, _id, _idLength);
    id[_idLength] = '\0'; // null terminate
    return String(id);
}

void NdefRecord::getId(byte *id)
{
    memcpy(id, _id, _idLength);
}

void NdefRecord::setId(const byte * id, const unsigned int numBytes)
{
    if (_idLength)
    {
        free(_id);
    }

    _id = (byte*)malloc(numBytes);
    memcpy(_id, id, numBytes);
    _idLength = numBytes;
}
#ifdef NDEF_LOGGING

void NdefRecord::print()
{
    String tnfString = "";
    switch (_tnf) {
    case TNF_EMPTY:
        tnfString = "Empty";
        break;
    case TNF_WELL_KNOWN:
        tnfString = "Well Known";
        break;
    case TNF_MIME_MEDIA:
        tnfString = "Mime Media";
        break;
    case TNF_ABSOLUTE_URI:
        tnfString = "Absolute URI";
        break;
    case TNF_EXTERNAL_TYPE:
        tnfString = "External";
        break;
    case TNF_UNKNOWN:
        tnfString = "Unknown";
        break;
    case TNF_UNCHANGED:
        tnfString = "Unchanged";
        break;
    case TNF_RESERVED:
        tnfString = "Reserved";
        break;
    default:
        tnfString = "";
    }

    Log.info("\tNDEF Record");
    Log.info("\t\tTNF 0x%x %s", _tnf, tnfString);
    Log.info("\t\tType Length 0x%x %d", _typeLength, _typeLength);
    Log.info("\t\tPayload Length 0x%x %d", _payloadLength, _payloadLength);

    if (_idLength)
    {
        Log.info("\t\tId Length 0x%x", _idLength);
    }

    Log.info("\t\tType:");
    PrintHexChar(_type, _typeLength); // Assuming PrintHexChar is updated to use Particle logging

    // TODO chunk large payloads so this is readable
    Log.info("\t\tPayload:");
    PrintHexChar(_payload, _payloadLength); // Assuming PrintHexChar is updated to use Particle logging

    if (_idLength)
    {
        Log.info("\t\tId:");
        PrintHexChar(_id, _idLength); // Assuming PrintHexChar is updated to use Particle logging
    }

    Log.info("\t\tRecord is %d bytes", getEncodedSize());
}
#endif

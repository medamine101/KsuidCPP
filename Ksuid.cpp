#include <iostream>
#include <ctime>

using byte = unsigned char;
// using namespace std;

class Ksuid
{
private:
    const int EncodedSize = 27;
    

    // Static constants
    static const int TimestampSize = 4;
    static const int PayloadSize = 16;

    unsigned int getCurrentTime();

    //DateTime variable
    tm EpochDateTime = {20, 53, 16, 13, 05, 2014 - 1900, 0, 0, 0};

    byte *_payload;
    unsigned int _timestamp;

public:
    
    
    static const unsigned int Epoch = 1400000000;

    //Constructors
    Ksuid(/* args */);
    Ksuid(byte *payload);
    Ksuid(byte *payload, unsigned int timestamp);

    ~Ksuid();

    //Static Functions
    static unsigned int GetTimestamp(tm dateTime);
    static Ksuid Generate();
    static Ksuid FromString(std::string encoded);
    static Ksuid *FromByteArray(byte *bytes);

    //Non Static Functions
    byte *ToByteArray();
    std::string ToString();
    byte *getPayload();
    unsigned int getTimestamp();
    unsigned int getUnixTimestamp();
};

Ksuid::Ksuid()
{

    _payload = new byte[PayloadSize];

    //Generate random byte array
    for (int i = 0; i < PayloadSize; i++)
    {
        _payload[i] = rand() % 256;
    }

    //Get current time in seconds
    _timestamp = this->getCurrentTime();
}

Ksuid::Ksuid(byte *payload)
{

    _payload = new byte[PayloadSize];

    //Copy payload
    memcpy(_payload, payload, PayloadSize);

    //Get current time in seconds

    _timestamp = this->getCurrentTime();
}

Ksuid::Ksuid(byte *payload, unsigned int timestamp)
{

    _payload = new byte[PayloadSize];

    //Copy payload
    memcpy(_payload, payload, PayloadSize);

    //Copy timestamp
    _timestamp = timestamp;
}

Ksuid::~Ksuid()
{

    //Delete payload
    delete[] _payload;
}

//Get current time as timestamp
unsigned int Ksuid::getCurrentTime()
{

    //Get current time in seconds
    time_t currentTime = time(NULL);
    unsigned int timestamp = (unsigned int)currentTime - Epoch;

    return timestamp;
}

//Convert tm struct to seconds
unsigned int Ksuid::GetTimestamp(tm dateTime)
{

    unsigned int seconds = 0;

    seconds += dateTime.tm_sec;
    seconds += dateTime.tm_min * 60;
    seconds += dateTime.tm_hour * 60 * 60;
    seconds += dateTime.tm_mday * 60 * 60 * 24;
    seconds += dateTime.tm_mon * 60 * 60 * 24 * 30;
    seconds += dateTime.tm_year * 60 * 60 * 24 * 30 * 12;

    return seconds - Epoch;
}

//Generate new Ksuid with no args
Ksuid Ksuid::Generate()
{
    return Ksuid();
}

Ksuid Ksuid::FromString(std::string encoded)
{
    
    


}

Ksuid *Ksuid::FromByteArray(byte *bytes)
{
    //TODO: Implement

    byte *timestamp = new byte[TimestampSize];

    //Copy bytes into timestamp
    memcpy(timestamp, bytes, TimestampSize);


    //Create buffer
    byte *buffer = new byte[PayloadSize];

    memcpy(buffer, bytes + TimestampSize, PayloadSize);

    return new Ksuid(buffer, *(unsigned int *)timestamp);

    //

}

byte *Ksuid::ToByteArray()
{
    //TODO: Implement
}

std::string Ksuid::ToString()
{
    //TODO: Implement
}

byte *Ksuid::getPayload()
{
    return _payload;
}

unsigned int Ksuid::getTimestamp()
{
    return _timestamp;
}

unsigned int Ksuid::getUnixTimestamp()
{
    return _timestamp + Epoch;
}

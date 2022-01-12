#include <string>
#include <iostream>
#include <sstream>
#include "base_x.hh"

using namespace std;

const int EPOCH = 1400000000;
const int PAYLOAD_BYTES = 16;

const int TIMESTAMP_BYTES = 4;
const int TOTAL_BYTES = TIMESTAMP_BYTES + PAYLOAD_BYTES;
const int PAD_TO_LENGTH = 27;
//Comparator should be here

//Needed since Builder appears later in the file
// class Builder;
class Ksuid;

class Builder
{
private:
    

public:

    int timestamp;
    byte payload[PAYLOAD_BYTES];
    byte ksuidBytes[TOTAL_BYTES];

    Builder(/* args */);
    ~Builder();

    Builder withTimeStamp(const int);
    Builder withPayload(const byte *);
    Builder withKsuidBytes(const byte*);
    Builder withKsuidString(const string);
    Ksuid build();
};

class Ksuid
{
private:
    
    int timestamp;
    byte payload[PAYLOAD_BYTES];
    byte ksuidBytes[TOTAL_BYTES];

public:

    
   


    Ksuid(Builder);
    static Builder newBuilder();
    byte *asBytes();
    string asString();
    string asRaw();
    //Functions for instant, get time in default and provided timezone
    int getTimestamp();
    byte *getPayload();
    string toInspectString();
    ~Ksuid();
};

Ksuid::Ksuid(Builder builder)
{
    //Check if byte array is empty

    bool isEmpty = false;
    for (int i = 0; i < TOTAL_BYTES; i++)
    {
        if (to_integer<int>(builder.ksuidBytes[i]) != 0)
        {
            isEmpty = true;
        }
    }


    if (!isEmpty)
    {
        //Sanity check here line 40 from og java code


        memcpy(ksuidBytes, builder.ksuidBytes, TOTAL_BYTES);

        //Copy the timestamp from the ksuidBytes
        memcpy(&timestamp, ksuidBytes, TIMESTAMP_BYTES);

        //Copy the payload from the ksuidBytes
        memcpy(payload, ksuidBytes + TIMESTAMP_BYTES, PAYLOAD_BYTES);

    }
    else
    {
        //Sanity check here from like 49 in og java code

        timestamp = builder.timestamp;
        
        //Copy the payload from the builder
        memcpy(payload, builder.payload, PAYLOAD_BYTES);

        //Copy timestamp and payload into ksuidBytes
        memcpy(ksuidBytes, &timestamp, TIMESTAMP_BYTES);
        memcpy(ksuidBytes + TIMESTAMP_BYTES, payload, PAYLOAD_BYTES);




    }
}

/**
 * Create KSUID Builder
 *
 * @return Builder
 */
Builder Ksuid::newBuilder()
{
    return Builder();
}

/**
 * Get pointer to KSUID byte array
 *
 * @return std::byte array pointer
 */
byte *Ksuid::asBytes()
{
    return ksuidBytes;
}

/**
 * Get KSUID as string
 *
 * @return std::string
 */
string Ksuid::asString()
{
    auto encoded = Base62::base62().encode((char *)ksuidBytes, (size_t) TOTAL_BYTES);

    return encoded;
}

/**
 * Get KSUID as hex encoded string
 *
 * @return std::string
 */
string Ksuid::asRaw()
{

    //Return hex string
    return Base16::base16().encode((char *)ksuidBytes, (size_t) TOTAL_BYTES);
    
}

int Ksuid::getTimestamp()
{
    return timestamp;
}

byte *Ksuid::getPayload()
{
    return payload;
}

string Ksuid::toInspectString()
{
    stringstream ss;
    
    ss << "REPRESENTATION: " << asString() << " " << asRaw() << "String: " << getTimestamp() << "Raw: " << getPayload();

    return ss.str();
}

Ksuid::~Ksuid()
{
}

// class Builder
// {
// private:
    

// public:

//     int timestamp;
//     byte payload[PAYLOAD_BYTES];
//     byte ksuidBytes[TOTAL_BYTES];

//     Builder(/* args */);
//     ~Builder();

//     Builder withTimeStamp(const int);
//     Builder withPayload(const byte *);
//     Builder withKsuidBytes(const byte*);
//     Builder withKsuidString(const string);
//     Ksuid build();
// };

Builder::Builder(/* args */)
{
}

Builder::~Builder()
{
}

Builder Builder::withTimeStamp(const int timestamp)
{
    this->timestamp = timestamp;
    return *this;
}

Builder Builder::withPayload(const byte* payload)
{

    //Copy payload to new byte array
    memcpy(this->payload, payload, PAYLOAD_BYTES);
    return *this;
}

Builder Builder::withKsuidBytes(const byte* ksuidBytes)
{
    //Copy ksuidBytes to new byte array
    memcpy(this->ksuidBytes, ksuidBytes, TOTAL_BYTES);
    return *this;
}

Builder Builder::withKsuidString(const string ksuidString)
{
    //Get Base62 decoded
    string decoded = Base62::base62().decode(ksuidString);

    //convert string to byte array
    memcpy(this->ksuidBytes, decoded.c_str(), TOTAL_BYTES);

    //Convert string to byte array
    return *this;
}

Ksuid Builder::build()
{
    return Ksuid(*this);

}
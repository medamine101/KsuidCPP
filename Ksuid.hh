#include <string>
#include <iostream>
#include <sstream>
#include "base_62.hh"
#include <vector>

using namespace std;

const int EPOCH = 1400000000;
const int PAYLOAD_BYTES = 16;

const int TIMESTAMP_BYTES = 4;
const int TOTAL_BYTES = TIMESTAMP_BYTES + PAYLOAD_BYTES;
const int PAD_TO_LENGTH = 27;

// TODO: Add Comparator

/*************************
 * KSUID and Builder Class
 *************************/

class Ksuid;

class Builder
{
public:
    int timestamp;
    vector<byte> payload;
    vector<byte> ksuidBytes;

    Builder();
    ~Builder();

    Builder withTimeStamp(const int);
    Builder withPayload(vector<byte>);
    Builder withKsuidBytes(vector<byte>);
    Builder withKsuidString(const string);
    Ksuid build();
};

class Ksuid
{
private:
    int timestamp;
    vector<byte> payload;
    vector<byte> ksuidBytes;

public:
    Ksuid(Builder);
    static Builder newBuilder();
    static Ksuid newKsuid();
    vector<byte> asBytes();
    string asString();
    string asRaw();
    // Functions for instant, get time in default and provided timezone
    int getTimestamp();
    string getPayload();
    string toInspectString();
    ~Ksuid();
};

/*************************
 * KSUID Functions
 *************************/

Ksuid::Ksuid(Builder builder)
{
    // Check if byte array is not empty
    if (!builder.ksuidBytes.empty())
    {
        // Ensure that the byte array is the correct length
        if (builder.ksuidBytes.size() != TOTAL_BYTES)
        {
            throw std::invalid_argument("Ksuid byte array is not the expected length of " + to_string(TOTAL_BYTES) + " bytes");
        }

        ksuidBytes = builder.ksuidBytes;

        //  Copy the timestamp
        timestamp = (int)ksuidBytes[0] << 24 | (int)ksuidBytes[1] << 16 | (int)ksuidBytes[2] << 8 | (int)ksuidBytes[3];

        // Copy the payload
        payload = vector<byte>(ksuidBytes.begin() + TIMESTAMP_BYTES, ksuidBytes.end());
    }
    else
    {
        // Ensure that payload is the correct length
        if (builder.payload.size() != PAYLOAD_BYTES)
        {
            throw std::invalid_argument("Payload byte array is not the expected length of " + to_string(PAYLOAD_BYTES) + " bytes");
        }

        timestamp = builder.timestamp;

        // Copy the payload from the builder
        payload = builder.payload;

        // Copy timestamp and payload into ksuidBytes
        ksuidBytes = vector<byte>(TOTAL_BYTES);
        ksuidBytes[0] = ((byte *)(&timestamp))[3];
        ksuidBytes[1] = ((byte *)(&timestamp))[2];
        ksuidBytes[2] = ((byte *)(&timestamp))[1];
        ksuidBytes[3] = ((byte *)(&timestamp))[0];

        for (int i = 0; i < PAYLOAD_BYTES; i++)
        {
            ksuidBytes[i + TIMESTAMP_BYTES] = payload[i];
        }
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
 * Create KSUID using current time and random payload
 *
 * @return Ksuid
 */
Ksuid Ksuid::newKsuid()
{

    //Generate timestamp in seconds
    int timestamp = (int)time(NULL) - EPOCH;

    vector<byte> payload(PAYLOAD_BYTES);

    // Generate random payload
    arc4random_buf(&payload.data()[0], PAYLOAD_BYTES);

    return newBuilder().withTimeStamp(timestamp).withPayload(payload).build();
}

/**
 * Get pointer to KSUID byte array
 *
 * @return std::byte array pointer
 */
vector<byte> Ksuid::asBytes()
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
    return Base62::base62().encode((char *)ksuidBytes.data(), TOTAL_BYTES);
}

/**
 * Get KSUID as hex encoded string
 *
 * @return std::string
 */
string Ksuid::asRaw()
{

    // Return hex string capitalized

    stringstream ss;

    for (int i = 0; i < TOTAL_BYTES; i++)
    {
        ss << hex << (int)ksuidBytes[i];
    }

    return ss.str();
}

int Ksuid::getTimestamp()
{
    return timestamp;
}

string Ksuid::getPayload()
{

    /// Convert payload to string
    stringstream ss;
    for (int i = 0; i < PAYLOAD_BYTES; i++)
    {
        ss << hex << (int)payload[i];
    }

    string payloadString = ss.str();

    return payloadString;
}

string Ksuid::toInspectString()
{
    stringstream ss;

    // Convert payload to string
    string payloadString = "";
    for (int i = 0; i < PAYLOAD_BYTES; i++)
    {
        payloadString += (char)payload[i];
    }

    ss << "REPRESENTATION: " << asString() << " " << asRaw() << "String: " << getTimestamp() << "Raw: " << payloadString;

    return ss.str();
}

Ksuid::~Ksuid()
{
}

/*************************
 * Builder Functions
 *************************/

Builder::Builder()
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

Builder Builder::withPayload(vector<byte> payload)
{
    this->payload = payload;
    return *this;
}

Builder Builder::withKsuidBytes(vector<byte> ksuidBytes)
{
    this->ksuidBytes = ksuidBytes;
    return *this;
}

Builder Builder::withKsuidString(const string ksuidString)
{
    string decoded = Base62::base62().decode(ksuidString);
    ksuidBytes = vector<byte>(TOTAL_BYTES);

    // get size difference between decoded and ksuidBytes
    int sizeDiff = TOTAL_BYTES - decoded.size();

    // Loop thorugh decodedCString and copy to ksuidBytes
    for (int i = decoded.size() - 1; i >= 0; i--)
        ksuidBytes[i + sizeDiff] = (byte)decoded[i];

    return *this;
}

Ksuid Builder::build()
{
    return Ksuid(*this);
}
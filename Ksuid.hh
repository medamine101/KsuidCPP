#include <string>
#include <iostream>
#include <sstream>
#include "base_x.hh"
#include <vector>

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
    // byte payload[PAYLOAD_BYTES];
    vector<byte> payload;
    // byte ksuidBytes[TOTAL_BYTES];
    vector<byte> ksuidBytes;

    Builder(/* args */);
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
    vector<byte> asBytes();
    string asString();
    string asRaw();
    //Functions for instant, get time in default and provided timezone
    int getTimestamp();
    string getPayload();
    string toInspectString();
    ~Ksuid();
};

Ksuid::Ksuid(Builder builder)
{
    //Check if byte array is not empty
    if (!builder.ksuidBytes.empty())
    {
        // Ensure that the byte array is the correct length
        if (builder.ksuidBytes.size() != TOTAL_BYTES)
        {
            throw std::invalid_argument("Ksuid byte array is not the expected length of " + to_string(TOTAL_BYTES) + " bytes");
        }

        ksuidBytes = builder.ksuidBytes;


        //FIXME: This is a hack to get the timestamp from the byte array, not known if this is correct
        // Copy the timestamp
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
        
        //Copy the payload from the builder
        payload = builder.payload;


        //FIXME: This is a hack to create ksuidBytes from the timestamp and payload, not known if this is correct
        //Copy timestamp and payload into ksuidBytes
        ksuidBytes = vector<byte>(TOTAL_BYTES);
        // // ksuidBytes[0] = (byte)((timestamp >> 24) & 0xFF);
        ksuidBytes[0] = ((byte*)(&timestamp))[3];
        // // ksuidBytes[1] = (byte)((timestamp >> 16) & 0xFF);
        ksuidBytes[1] = ((byte*)(&timestamp))[2];
        // // ksuidBytes[2] = (byte)((timestamp >> 8) & 0xFF);
        ksuidBytes[2] = ((byte*)(&timestamp))[1];
        // // ksuidBytes[3] = (byte)(timestamp & 0xFF);
        ksuidBytes[3] = ((byte*)(&timestamp))[0];

        for (int i = 0; i < PAYLOAD_BYTES; i++)
        {
            ksuidBytes[i + TIMESTAMP_BYTES] = payload[i];
        }

        //print vector
        for (int i = 0; i < TOTAL_BYTES; i++)
        {
            cout << (int)ksuidBytes[i] << " ";
        }
        cout << endl;




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
    return Base62::base62().encode((char*) ksuidBytes.data(), TOTAL_BYTES);
}

/**
 * Get KSUID as hex encoded string
 *
 * @return std::string
 */
string Ksuid::asRaw()
{

    //Return hex string

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

    ///Convert payload to string
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

    //Convert payload to string
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

Builder Builder::withPayload(vector<byte> payload)
{

    //Copy payload to builder's payload
    this->payload = payload;

    return *this;
}

Builder Builder::withKsuidBytes(vector<byte> ksuidBytes)
{
    //Copy ksuidBytes
    this->ksuidBytes = ksuidBytes;
    
    return *this;
}

Builder Builder::withKsuidString(const string ksuidString)
{
    //Get Base62 decoded
    string decoded = Base62::base62().decode(ksuidString);

    //Loop thorugh decodedCString and copy to ksuidBytes
    for (int i = 0; i < decoded.length(); i++)
    {
        ksuidBytes[i] = (byte) decoded[i];
    }

    return *this;
}

Ksuid Builder::build()
{
    return Ksuid(*this);

}
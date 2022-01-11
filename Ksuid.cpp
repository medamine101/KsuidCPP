#include <string>

using namespace std;

const int EPOCH = 1400000000;
const int PAYLOAD_BYTES = 16;

const int TIMESTAMP_BYTES = 4;
const int TOTAL_BYTES = TIMESTAMP_BYTES + PAYLOAD_BYTES;
const int PAD_TO_LENGTH = 27;
//Comparator should be here


class KSUID
{
private:
    
    int timestamp;
    byte *payload;
    byte * ksuidBytes;

public:

    
   


    KSUID(/* args */);
    ~KSUID();
};

KSUID::KSUID(/* args */)
{
}

KSUID::~KSUID()
{
}



#include <iostream>
#include <string>
#include "Ksuid.hh"
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Testing KSUID" << endl;

    // cout << "Enter string as payload: ";

    // string payload;

    // // cin >> payload;

    // // cout << "Enter timestamp: ";

    // int timestamp = 100;
    int timestamp = 150215977;

    // // cin >> timestamp;

    // int payloadArray[] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10 };

    int payloadArray[] = {124, 76, 43, -110, 116, -6, \
    -91, 45, 0, -125, -127, 109, 28, 24, 28, -17 };

    // vector<byte> payload;

    // for(int i = 0; i < 16; i++)
    // {
    //     payload.push_back( (byte) payloadArray[i]);
    // }



    // Builder ksuidBuilder = Ksuid::newBuilder();

    // // ksuidBuilder = ksuidBuilder.withTimeStamp(timestamp);
    // // ksuidBuilder = ksuidBuilder.withPayload(payload);
    // ksuidBuilder = ksuidBuilder.withKsuidString("1HCpXwx2EK9oYluWbacgeCnFcLf");

    // Ksuid ksuid = ksuidBuilder.build();
    
    // cout << "KSUID Payload: " << ksuid.getPayload() << endl;
    // cout << "KSUID Timestamp: " << ksuid.getTimestamp() << endl;
    // cout << "KSUID as String: " << ksuid.asString() << endl;
    // cout << "KSUID as Raw: " << ksuid.asRaw() << endl;

    Ksuid ksuid = Ksuid::newKsuid();

    cout << "KSUID Payload: " << ksuid.getPayload() << endl;
    cout << "KSUID Timestamp: " << ksuid.getTimestamp() << endl;
    cout << "KSUID as String: " << ksuid.asString() << endl;
    cout << "KSUID as Raw: " << ksuid.asRaw() << endl;

    return 0;
}
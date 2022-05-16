#include <iostream>
#include <string>
#include "Ksuid.hh"
#include <vector>
#include <unistd.h>

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

    int payloadArray[] = {124, 76, 43, -110, 116, -6,
    -91, 45, 0, -125, -127, 109, 1, 24, 28, -17 };

    //create vector of bytes from array
    vector<byte> payloadVector;

    for (int i = 0; i < sizeof(payloadArray) / sizeof(payloadArray[0]); i++)
    {
        payloadVector.push_back((byte)payloadArray[i]);
    }

    // Ksuid k1 = Ksuid::newKsuid();
    Ksuid k1 = Ksuid::newBuilder()
        // .withTimeStamp(timestamp)
        .withPayload(payloadVector)
        .build();


    // sleep(2);

    // Ksuid k2 = Ksuid::newKsuid();
    // Ksuid k2 = Ksuid::newBuilder()
    //     // .withTimeStamp(timestamp)
    //     .withPayload(payloadVector)
    //     .build();

    // Ksuid k3 = Ksuid::newKsuid();


    // bool check = k1 != k2;
    // cout << "k2: " << k2.asString() << endl;
    // cout << "k2 timestamp: " << k2.getTimestamp() << endl;
    // cout << check << endl;
    cout << k1.toInspectString() << endl;
    cout << k1.toLogString() << endl;


    return 0;
}
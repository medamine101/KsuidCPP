#include <iostream>
#include <string>
#include "Ksuid.hh"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Testing KSUID" << endl;

    cout << "Enter string as payload: ";

    string payload;

    cin >> payload;

    cout << "Enter timestamp: ";

    int timestamp;

    cin >> timestamp;

    //Convert to byte array
    byte *testBytes = (byte *) payload.c_str();

    Builder ksuidBuilder = Ksuid::newBuilder();

    ksuidBuilder = ksuidBuilder.withTimeStamp(timestamp);
    ksuidBuilder = ksuidBuilder.withPayload(testBytes);

    Ksuid ksuid = ksuidBuilder.build();
    
    cout << "KSUID: " << ksuid.asString() << endl;

    return 0;
}
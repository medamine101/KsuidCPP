#include <iostream>
#include <string>
#include "Ksuid.hh"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Testing KSUID" << endl;

    string test = "Hello World";

    //Convert to byte array
    byte *testBytes = (byte *) test.c_str();

    Builder ksuidBuilder = Ksuid::newBuilder();

    ksuidBuilder = ksuidBuilder.withTimeStamp(123456789);
    ksuidBuilder = ksuidBuilder.withPayload(testBytes);

    Ksuid ksuid = ksuidBuilder.build();
    
    cout << "KSUID: " << ksuid.asString() << endl;

    return 0;
}
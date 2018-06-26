// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct tri{
    char bytes[36];
};

int main(void){
    //setup serial port connection to the arduino
    HANDLE handler = CreateFileA(static_cast<LPCSTR>("COM2"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handler == INVALID_HANDLE_VALUE){
        cout <<"COM2 busy probably!\n";
    }
    else {
        DCB dcbSerialParameters = {0};
        dcbSerialParameters.BaudRate = CBR_9600;
        dcbSerialParameters.ByteSize = 8;
        dcbSerialParameters.StopBits = ONESTOPBIT;
        dcbSerialParameters.Parity = NOPARITY;
        dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;
        PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);

        //filename of the STL file
        cout << "Type in STL file name: ";
        string file_name;
        cin >> file_name;

        //open STL file
        ifstream STL_file;
        STL_file.open(file_name);

        //STL header data
        char header[80] = "";
        char nTris[4];
        unsigned long n_tris;

        //read STL header
        if (STL_file) {
            STL_file.read(header, 80);
            cout << "header: " << header << "\n";
            STL_file.read(nTris, 4);
            n_tris = *((unsigned long *) nTris);
            cout << "number of tris: " << n_tris << endl;
        } else {
            cout << "ERROR!\n";
        }

        //vector of tris; ( 9 floats / 36 chars )
        vector<tri> tris;

        //read tris
        for (int i = 0; i < n_tris; i++) {
            char stl_tri[50];
            if (STL_file) {
                STL_file.read(stl_tri, 50);
                tri t;
                for (int j = 0; j < 36; j++) {
                    t.bytes[j] = stl_tri[j + 12];
                }
                tris.push_back(t);
                cout << "Read try: " << i << "\n";
            } else {
                cout << "ERROR!\n";
            }
        }
        STL_file.close();

        DWORD bytesSend;
        bool hasWritten = WriteFile(handler, (LPCVOID) &n_tris, 4, &bytesSend, NULL);
        if (hasWritten) {
            cout << "Sending: " << n_tris << " tris\n";
        }
        for (int i = 0; i < tris.size(); ++i) {
            hasWritten = WriteFile(handler, (LPCVOID) &tris[i], 36, &bytesSend, NULL);
            if (hasWritten) {
                cout << "Send tri: " << i << "\n";
            }
        }
    }
}
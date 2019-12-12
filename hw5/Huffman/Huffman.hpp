#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef unsigned char byte;

struct IInputStream {
    virtual bool Read(byte& value) = 0;
};

struct IOutputStream {
    virtual void Write(byte value) = 0;
};

class CInputStream : public IInputStream {
public:
    CInputStream(const vector<byte>& _body) : index(0), body(_body) {}
    virtual bool Read(byte& value) {
        if (index >= body.size()) {
            return false;
        }
        value = body[index++];
        return true;
    }

private:
    unsigned int index;
    const vector<unsigned char>& body;
};


class COutputStream : public IOutputStream {
public:
    COutputStream(vector<byte>& _body) : body(_body) {
        body.clear();
    }
    virtual void Write(byte value) {
        body.push_back(value);
    }

private:
    vector<byte>& body;
};

void fillInputs(vector< vector<byte> >& inputs);

bool isEqual(const vector<byte>& v1, const vector<byte>& v2);

int calculateSize(const vector< vector<byte> >& array);

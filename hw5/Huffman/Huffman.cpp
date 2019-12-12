#include "Huffman.hpp"


void fillInputs(vector< vector<byte> >& inputs) {
    inputs.clear();

    string currentFileName;
    while (getline( cin, currentFileName )) {
        if (currentFileName.empty()) {
            continue;
        }

        // Есть еще один файл, который следует закодировать
        inputs.push_back(vector<byte>());

        ifstream file;
        try {
          file.open(currentFileName.c_str(), ifstream::in);
        }
        catch (std::ifstream::failure e) {
          std::cerr << "Exception opening file: " << std::strerror(errno) << "\n";
        }
        byte value;

        while (file >> value) {
            (*inputs.rbegin()).push_back(value);
        }
        break;
    }
}

bool isEqual(const vector<byte>& v1, const vector<byte>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for( unsigned int i = 0; i < v1.size(); i++ ) {
        if( v1[i] != v2[i] ) {
            return false;
        }
    }
    
    return true;
}

int calculateSize(const vector< vector<byte> >& array) {
    int result = 0;
    for ( unsigned int i  = 0; i < array.size(); i++ ) {
        const vector<byte>& data = array[i];
        result += data.size();
    }
    return result;
}


// resize.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"
#include "Image.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream fin;
    ofstream fout;

    string file = argv[1];
    string fileOut = argv[2];

    fin.open(file);
    if (!fin.is_open()) {
        cout << "Error opening file: " << file << endl;
        return 1;
    }

    if (argc == 5 || argc == 4) {
        Image *img = new Image;
        ofstream fout(fileOut);

        if (argc == 5) {
            int width = atoi(argv[3]);
            int height = atoi(argv[4]);
            Image_init(img, fin);
            seam_carve(img, width, height);
        }

        else if (argc == 4) {
            int width = atoi(argv[3]);
            int height = Image_height(img);
            Image_init(img, fin);
            seam_carve(img, width, height);
        }

        Image_print(img, fout);
        delete img;
    }
    else {
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    }
    return 0;
}

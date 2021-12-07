//#include <Magick++.h>
#include <ImageMagick-6/Magick++.h>

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

#include <vector>

using namespace std;
using namespace Magick;

int loadImage(string path);

pair<size_t, int> analyzerImage();

string *labelsFile();

int creatPath(string path);

int creatLink(string file, string link);

int removeFile(string path);

int main(int argc, char *argv[]) {
    if (argc > 1) {

        // Creating a directory
        if (mkdir("/tmp/t2/", 0777) == -1) {
            cerr << "Error :  " << strerror(errno) << endl;
        } else {
            cout << "Diretórios /tmp/t2/ criado" << endl;
        }

        string link(argv[1]);
        cout << "link: " << link << endl;

        string file(argv[2]);
        cout << "file: " << file << endl;

        string *labels = new string[1003];
        labels = labelsFile();

        string path = link.substr(0, link.find_last_of("/\\"));
        cout << "path: " << path << endl;

        string filename = file.substr(file.find_last_of("/\\") + 1);
        cout << "filename: " << filename << endl;

        int status_img = loadImage(file);
        if (status_img == 0) {
            pair<size_t, int> tmp = analyzerImage();

            cout << "Image: " << " : "
                 << labels[tmp.first] << " : "
                 << tmp.second << endl;

            creatPath(link + '/' + labels[tmp.first]);
            creatLink(file, link + '/' + labels[tmp.first] + '/' + filename);
        }

        removeFile("/tmp/t2/out.csv");
        removeFile("/tmp/t2/input.png");

        if (rmdir("/tmp/t2/")) {
            cerr << "Error :  " << strerror(errno) << endl;
        } else {
            cout << "Diretórios /tmp/t2/ deletado" << endl;
        }
        return 0;
    } else {
        return -1;
    }
}

int removeFile(string path) {
    int result = remove(path.c_str());
    if (result != 0) {
        cerr << "Error :  " << strerror(errno) << endl;
    }
    return result;
}

int creatPath(string path) {
    cout << "creatPath: " << path << endl;
    int result = mkdir(path.c_str(), 0777);
    if (result == -1) {
        cerr << "Error :  " << strerror(errno) << endl;
    }
    return 0;
}

int creatLink(string file, string link) {
    //cout << endl << "ln -s '" + file + "' '" + link + ".link'" << endl << endl;
    string ln("ln -s '" + file + "' '" + link + ".link'");
    return system(ln.c_str());
}

string *labelsFile() {
    string *result = new string[1003];

    ifstream filereader("./ImageNetLabels.pt-br.txt");

    if (!filereader.is_open()) {
        cout << "error is open file out" << endl;
    } else {
        string tmp;
        size_t index = 0;
        while (getline(filereader, tmp)) {
            pair<size_t, string> pair_tmp;
            result[index] = tmp;
            index++;
        }
        filereader.close();
    }

    return result;
}

int loadImage(string path) {
    Image image;
    try {
        // Read a file into image object
        image.read(path);

        image.resize(Geometry("331x331"));
        image.type(TrueColorType);
        image.extent(Geometry("331x331"), Color(0, 0, 0), CenterGravity);
        //image.frame(Geometry("331x331"));
        //image.backgroundColor(Color(0, 0, 0));

        // Write the image to a file
        image.write("/tmp/t2/input.png");

        return 0;
    }
    catch (Exception &error_) {
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }
}

pair<size_t, int> analyzerImage() {
    system("python3 ./ia.py");

    pair<size_t, int> result;
    result.first = 0;
    result.second = -1;
    ifstream filereader("/tmp/t2/out.csv");

    if (!filereader.is_open()) {
        cout << "error is open file out" << endl;
    } else {
        string tmp;
        size_t index = 0;
        while (getline(filereader, tmp)) {
            int tmpInt = atoi(tmp.c_str());
            if (result.second < tmpInt) {
                result.first = index;
                result.second = tmpInt;
            }
            index++;
        }
        filereader.close();
    }
    return result;
}

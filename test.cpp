#include <iostream>
#include <string>
#include <sys/stat.h>
#include <errno.h>
#include <linux/limits.h>


using namespace std;

int make_dir(int size, char c) {
    string newDirectory(size, c);
    string directoryName = "dir1/dir2/dir3/" + newDirectory;

    for (size_t i = 0; i < directoryName.size(); i++) {
        if (i != 0 &&
                (directoryName[i] == '/' || i == directoryName.size() - 1)) {
            if (directoryName[i] == '/') {
                directoryName[i] = '\0';
            }

            int errorCode =
                mkdir(directoryName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
            if (errorCode != 0 && errno != EEXIST) {
                cout << "Error code: " << errorCode << endl;
                cout << "Error no: " << errno << endl;
                cout << "Too long no: " << ENAMETOOLONG << endl;
                cout << "Directory name: " << directoryName.c_str()
                    << endl << endl;
            }
            directoryName[i] = '/';
        }
    }
}

int main() {
    cout << "Path max size: " << PATH_MAX << endl;
    cout << "Name max size: " << NAME_MAX << endl << endl;

    make_dir(143, 'a');
    make_dir(144, 'b');
    make_dir(255, 'c');
}


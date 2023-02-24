#include <iostream>
#include <queue>
#include <vector>
#include "ReadBufferFromFile.h"
#include <iostream>

using namespace std;
using namespace IO;
int main() {
    ReadBufferFromFile file("/home/yh/code/test.txt");
    while(!file.eof())
    {
	    cout<<file.position();
        break;
    }
    return 0;
}

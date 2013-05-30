#include "src/file.h"

int main(int argc, char *argv[])
{
    File file("text.txt",1);
    cout<<file.readString();
    cin.get();
    file.close();

    return 0;
}

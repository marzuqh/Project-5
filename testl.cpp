#include <iostream>
#include "dlist.h"

using namespace std;

int main()
{
    Dlist<int> ilist;
    int *ip = new int(3);
    ilist.insertFront(ip);

    ip = ilist.removeFront();
    cout << *ip << endl;

    delete ip;

    return 0;
}

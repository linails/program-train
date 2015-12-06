#include <iostream>
#include "object_c.h"
#include "sqlite3.h"

using std::cout;
using std::endl;

int main(void)
{
    sqlite3 *db = NULL;
    sqlite3_open("first.db",&db);
    cout << "hello world ..." <<endl;
    sqlite3_close(db);
    return 0;
}


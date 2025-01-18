#include <iostream>
#include "dsa_map.hpp"
using namespace std;

map<int, int>*
create_map()
{
    map<int, int> *m = new map<int, int>();
    return m;
}

void
destroy_map(map<int, int> *m)
{
    delete m;
}

int
insert_map(map<int, int> *m, int k, int v)
{
    m->insert({k, v});
    return 0;
}

int delete_map(map<int, int> *m, int k)
{
    m->erase(k);
    return 0;
}

void
print_map(map<int, int> *m)
{
    map<int, int>::iterator itr;
    for (itr = m->begin(); itr != m->end(); ++itr) {
        cout << "\t" << itr->first << "-" << itr->second;
    }
}

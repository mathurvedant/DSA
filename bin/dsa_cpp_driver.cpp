/*
 * Copyright (c) 2025 Vedant Mathur
 *
 * DSA CPP driver program.
 */

#include <iostream>
#include <dsa_map.hpp>
using namespace std;

void
test_map()
{
    cout << "\n\tTesting Map";
    map<int, int> *m = create_map();

    cout << "\n\tInserting into Map";
    for (int i = 1, j = 11; i < 10; i++, j++) {
        insert_map(m, i, j);
    }

    cout <<"\n\t\tMap After Insert:";
    print_map(m);

    cout << "\n\tDeleting From Map";
    for (int i = 1; i < 10; i+=2) {
        delete_map(m, i);
    }

    cout <<"\n\t\tMap After Delete:";
    print_map(m);

    destroy_map(m);
}

int main(void)
{
    cout << "Welcome to DSA CPP Driver Program!";

    test_map();

    cout << "\n";

    return 0;
}


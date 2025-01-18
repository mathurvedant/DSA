#include <map>

std::map<int, int>* create_map();
void destroy_map(std::map<int, int> *m);

int insert_map(std::map<int, int> *m, int k, int v);
int delete_map(std::map<int, int> *m, int k);
void print_map(std::map<int, int> *m);

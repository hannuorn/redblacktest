#include <iostream>
#include <map>
#include <chrono>

#include "RBTree.cpp"

using namespace std;


int main()
{
    int n = 1 * 1000 * 1000;

    cout << "RB_Tree vs. std::map\n";
    cout << "Adding and removing " << n << " nodes\n\n";

    auto rb_start = chrono::high_resolution_clock::now();
    cout << "RB_Tree... ";
    RB_Tree<int, int> rb;
    for (int i = 0; i < n; i++) {
        rb.add(i, i);
    }
    for (int i = 0; i < n; i++) {
        rb.remove(i);
    }
    auto rb_finish = chrono::high_resolution_clock::now();
    chrono::duration<double> rb_elapsed = rb_finish - rb_start;
    cout << "elapsed time: " << rb_elapsed.count() << " seconds.\n\n";

    auto map_start = chrono::high_resolution_clock::now();
    cout << "std::map...";
    std::map<int, int> cppmap;
    for (int i = 0; i < n; i++) {
        cppmap[i] = i;
    }
    for (int i = 0; i < n; i++) {
        cppmap.erase(i);
    }
    auto map_finish = chrono::high_resolution_clock::now();
    chrono::duration<double> map_elapsed = map_finish - map_start;
    cout << "elapsed time: " << map_elapsed.count() << " seconds.\n\n";
}

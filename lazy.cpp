//
// Created by davew on 4/1/22.
//

// Lazy evaluation self-test and demo. Not actually needed for using the system in lazy.h/lazy.t
//  Run the self-test with
//   clang++ -std=c++2a -D LAZY_TEST_MAIN=1 lazy.cpp -o lazy-test && ./lazy-test
//
#include "lazy.h"
#if defined LAZY_TEST_MAIN && LAZY_TEST_MAIN
#define verbose 1
#define explode 1
int main() {
	lazy_test();
}
#else
#define verbose 0
#define explode 0
#endif


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// return n, very slowly if some options are chosen
enum slowness { quick, exponential, infinite };
int lazy_test_slowness(int n, slowness how_slow)
{
#if verbose
    cout << "in lazy_test_slowness(" << n << ", " << how_slow << ")" << endl;
#endif
    if (n<=0) return n;
    
    if (how_slow == quick) {
	const lazy<int> i = lazy<int>([=]() { return lazy_test_slowness(n-1, how_slow); });
	const lazy<int> j = lazy<int>([=]() { return lazy_test_slowness(n+1, how_slow); });  // would diverge
	return 2*i.get() - i.get() + 1; // since i=j=n-1, this is just n
    } else if (how_slow == exponential) {
        // substitute in the definition of i ... this produces two recursive calls :-(
        return 2*lazy_test_slowness(n-1, how_slow)-lazy_test_slowness(n-1, how_slow) + 1; // since i=j=n-1, this is just n
    } else if (how_slow == infinite) {
        int i = lazy_test_slowness(n-1, how_slow);
        int j = lazy_test_slowness(n+1, how_slow);  //  diverges
        return 2*i - (j-2) + 1;
    } else {
        throw "unhandled case :-(";
    }
}

bool lazy_test()
{
    // for loop notation from https://stackoverflow.com/questions/12702561/iterate-through-a-c-vector-using-a-for-loop
    // vector initialization from https://stackoverflow.com/questions/2236197/what-is-the-easiest-way-to-initialize-a-stdvector-with-hardcoded-elements
    bool ok=true;
    std::vector<slowness> choices=
#if explode
	{ quick, exponential, infinite };
#else
	{ quick, exponential };
#endif
    for (slowness slow: choices)     // all speed options
	for (int n=3; n<=9; n+=3) {  // three sample sizes
#if verbose
	    cout << "\n\n   *** calling lazy_test_slowness(" << n << ", " << slow << ")" << endl;
#endif
	    if (lazy_test_slowness(n, slow) != n) {
		cerr << "lazy_test in lazy.cpp: inconsistency found for n=" << n << " and approach/version=" << slow << endl;
		ok=false;
	    }
	}
    return ok;
}


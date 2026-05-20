#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
    vector<long long> sizes = {100, 1000, 100000, 10000000, 100000000};

    cout << "Experimental analysis: std::sort on descending array\n";
    cout << "n\t\t\tTime (seconds)\n";
    cout << "----------------------------------------\n";

    for (long long n : sizes) {
        try {
            vector<int> arr(n);
            for (long long i = 0; i < n; i++) {
                arr[i] = n - i; // descending order — sort does real work
            }

            clock_t start = clock();
            sort(arr.begin(), arr.end());
            clock_t end = clock();

            double sec = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            cout << left << setw(12) << n << fixed << setprecision(6) << sec << " s\n";
        } catch (const bad_alloc&) {
            cout << n << "\t\t\t(skipped — not enough memory)\n";
        }
    }

    return 0;
}

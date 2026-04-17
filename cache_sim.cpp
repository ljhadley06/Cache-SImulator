#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Line {
    bool valid;
    int tag;
};

int main(int argc, char* argv[]) {
    // Expected usage:
    // ./cache_sim <num_entries> <associativity> <input_file>
    if (argc != 4) {
        cerr << "Usage: " << argv[0]
             << " <num_entries> <associativity> <input_file>\n";
        return 1;
    }

    int num_entries;
    int associativity;

    try {
        num_entries = stoi(argv[1]);
        associativity = stoi(argv[2]);
    } catch (...) {
        cerr << "Error: num_entries and associativity must be integers.\n";
        return 1;
    }

    if (num_entries <= 0 || associativity <= 0) {
        cerr << "Error: num_entries and associativity must be positive.\n";
        return 1;
    }

    if (num_entries % associativity != 0) {
        cerr << "Error: associativity must evenly divide num_entries.\n";
        return 1;
    }

    string input_file = argv[3];
    int num_sets = num_entries / associativity;

    ifstream inFile(input_file);
    if (!inFile) {
        cerr << "Error: could not open input file: " << input_file << "\n";
        return 1;
    }

    ofstream outFile("cache_sim_output");
    if (!outFile) {
        cerr << "Error: could not create output file cache_sim_output\n";
        return 1;
    }

    // cache[set][line]
    vector<vector<Line>> cache(
        num_sets,
        vector<Line>(associativity, {false, -1})
    );

    // Simple replacement pointer per set (round-robin / FIFO style)
    vector<int> next_replace(num_sets, 0);

    int address;

    while (inFile >> address) {
        int index = address % num_sets;
        int tag = address / num_sets;

        bool hit = false;

        // Check for hit in the target set
        for (int i = 0; i < associativity; i++) {
            if (cache[index][i].valid && cache[index][i].tag == tag) {
                hit = true;
                break;
            }
        }

        if (hit) {
            outFile << address << " : HIT\n";
        } else {
            outFile << address << " : MISS\n";

            bool placed = false;

            // First try to place in an invalid line
            for (int i = 0; i < associativity; i++) {
                if (!cache[index][i].valid) {
                    cache[index][i].valid = true;
                    cache[index][i].tag = tag;
                    placed = true;
                    break;
                }
            }

            // If set is full, replace using round-robin/FIFO-style replacement
            if (!placed) {
                int replace_line = next_replace[index];
                cache[index][replace_line].valid = true;
                cache[index][replace_line].tag = tag;

                next_replace[index] =
                    (next_replace[index] + 1) % associativity;
            }
        }
    }

    inFile.close();
    outFile.close();

    return 0;
}

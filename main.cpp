#include <iostream>
#include <string>

#include "input_reader.h"
#include "stat_reader.h"

using namespace std;

int main() {
    TransportCatalogue catalogue;

    InputReader input_reader = InputReader::ReadBaseRequests(cin);
    input_reader.ApplyCommands(catalogue);

    StatsReader stats_reader;
    stats_reader.ParseStatsRequests(cin);
    stats_reader.PrintStatistics(catalogue, cout);

    int stat_request_count;
    cin >> stat_request_count >> ws;
    for (int i = 0; i < stat_request_count; ++i) {
        string line;
        getline(cin, line);
        ParseAndPrintStat(catalogue, line, cout);
    }
}

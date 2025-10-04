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
}

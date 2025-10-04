#pragma once

#include <iosfwd>
#include <string_view>
#include <vector>

#include "transport_catalogue.h"


class StatsReader {
public:
    void ParseStatsRequests(std::istream& input);
    void PrintStatistics(const TransportCatalogue& catalogue, std::ostream& output);
private:
    std::vector<std::string> requests; //< I dont like this temp buf
};

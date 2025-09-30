#include "stat_reader.h"
#include "transport_catalogue.h"
#include <string>
#include <iostream>
#include <iomanip>

void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request,
                       std::ostream& output) {
    if (request.find("Bus") == 0) {
        std::string bus_name = std::string(request.substr(4));
        
        auto bus_stats = tansport_catalogue.GetBusStats(bus_name);
        
        output << "Bus " << bus_name << ": ";
        if (bus_stats) {
            output << bus_stats->stops_count << " stops on route, "
                   << bus_stats->stops_count_unique << " unique stops, "
                   << std::setprecision(6) << bus_stats->route_length << " route length";
        } else {
            output << "not found";
        }
        output << std::endl;
    }    
}
#include "stat_reader.h"
#include "transport_catalogue.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <map>

static void PrintBusStats(std::string_view name, const std::optional<TransportCatalogue::BusStats> stats, std::ostream& output) {
    output << "Bus " << name << ": ";
    if (!stats) {
        output << "not found";
    } else {
        output << stats->stops_count << " stops on route, "
               << stats->stops_count_unique << " unique stops, "
               << std::setprecision(6) << stats->route_length << " route length";
    }
    output << std::endl;    
}

static void PrintStopStats(std::string_view name, const std::optional<TransportCatalogue::StopStats> stats, std::ostream& output) {   
    output << "Stop " << name << ": ";
    if (!stats) {
        output << "not found";
    } else if (stats->buses.empty()) {
        output << "no buses";
    } else {
        output << "buses";
        for (const auto& bus_name : stats->buses) {
            output << " " << bus_name;
        }
    }
    output << std::endl;
}

void ParseAndPrintStat(const TransportCatalogue& catalogue, std::string_view request,
                       std::ostream& output) {
    if (request.find("Bus") == 0) {
        auto bus_name = std::string(request.substr(4));
        auto bus_stats = catalogue.GetBusStats(bus_name);
        PrintBusStats(std::move(bus_name), bus_stats, output);
    } else if (request.find("Stop") == 0) {
        auto stop_name = std::string(request.substr(5));
        auto stop_stats = catalogue.GetStopStats(stop_name);
        PrintStopStats(std::move(stop_name), stop_stats, output);
    }
}
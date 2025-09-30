#include "transport_catalogue.h"
#include <unordered_set>
#include "geo.h"

void TransportCatalogue::AddStop(Stop stop) {
    stops_.push_back(stop);
    /* Обновляем контейнер для поиска остановок */
    const Stop *added_stop = &stops_.back();
    stop_name_to_stop[added_stop->name] = added_stop;
}

void TransportCatalogue::AddBus(Bus bus) {
    buses_.push_back({bus.name, bus.stops});
    /* Обновляем контейнер для поиска маршрутов */
    const Bus *added_bus = &buses_.back();
    bus_name_to_bus[added_bus->name] = added_bus;
}

const Stop *TransportCatalogue::FindStop(std::string_view name) const {
    auto it = stop_name_to_stop.find(name);
    if (it != stop_name_to_stop.end()) {
        return it->second;
    }

    return nullptr;
}

const Bus *TransportCatalogue::FindBus(std::string_view name) const {
    auto it = bus_name_to_bus.find(name);
    if (it != bus_name_to_bus.end()) {
        return it->second;
    }

    return nullptr;
}


double TransportCatalogue::ComputeRouteLength(const Bus& bus) const {
    double total_length = 0.0;
    
    for (size_t i = 0; i < bus.stops.size() - 1; ++i) {
        const Stop* stop1 = bus.stops[i];
        const Stop* stop2 = bus.stops[i + 1];
        total_length += ComputeDistance(
            {stop1->coordinates.lat, stop1->coordinates.lng},
            {stop2->coordinates.lat, stop2->coordinates.lng}
        );
    }
    
    return total_length;
}

std::optional<TransportCatalogue::BusStats> TransportCatalogue::GetBusStats(std::string_view name) const {
    const Bus* bus = FindBus(name);
    if (!bus) {
        return std::nullopt;
    }
    
    BusStats stats;
    
    stats.stops_count = bus->stops.size();
    
    std::unordered_set<const Stop*> unique(bus->stops.begin(), bus->stops.end());
    stats.stops_count_unique = unique.size();
    
    stats.route_length = ComputeRouteLength(*bus);
    
    return stats;
}
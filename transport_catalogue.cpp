#include "transport_catalogue.h"
#include <unordered_set>
#include "geo.h"


void TransportCatalogue::AddStop(transport_catalogue::Stop stop) {
    stops_.push_back(std::move(stop));
    /* Обновляем контейнер для поиска остановок */
    const transport_catalogue::Stop *added_stop = &stops_.back();
    stop_name_to_stop_[added_stop->name] = added_stop;

    /* Создаем пустой set под автобусы */
    stop_name_to_buses_[added_stop->name];
}

void TransportCatalogue::AddBus(transport_catalogue::Bus bus) {
    buses_.push_back({bus.name, bus.stops});
    
    /* Обновляем контейнеры для поиска */
    // маршрутов по собственному имени
    const transport_catalogue::Bus *added_bus = &buses_.back();
    bus_name_to_bus_[added_bus->name] = added_bus;
    
    // маршрутов по имени остановки
    std::string_view bus_name = bus.name;
    for (const transport_catalogue::Stop *stop : added_bus->stops) {
        stop_name_to_buses_[stop->name].insert(std::move(std::string(bus_name)));
    }
}

const transport_catalogue::Stop *TransportCatalogue::FindStop(std::string_view name) const {
    auto it = stop_name_to_stop_.find(name);
    if (it != stop_name_to_stop_.end()) {
        return it->second;
    }

    return nullptr;
}

const transport_catalogue::Bus *TransportCatalogue::FindBus(std::string_view name) const {
    auto it = bus_name_to_bus_.find(name);
    if (it != bus_name_to_bus_.end()) {
        return it->second;
    }

    return nullptr;
}

std::optional<TransportCatalogue::StopStats> TransportCatalogue::GetStopStats(std::string_view name) const {
    const transport_catalogue::Stop *stop = FindStop(name);
    if (stop == nullptr) {
        return std::nullopt;
    }

    StopStats stats;

    auto it = stop_name_to_buses_.find(name);
    if (it != stop_name_to_buses_.end()) {
        stats.buses = it->second;
    }

    return stats;
}

std::optional<TransportCatalogue::BusStats> TransportCatalogue::GetBusStats(std::string_view name) const {
    const transport_catalogue::Bus* bus = FindBus(name);
    if (bus == nullptr) {
        return std::nullopt;
    }
    
    BusStats stats;
    
    stats.stops_count = bus->stops.size();
    
    std::unordered_set<const transport_catalogue::Stop*> unique(bus->stops.begin(), bus->stops.end());
    stats.stops_count_unique = unique.size();
    
    stats.route_length = ComputeRouteLength(*bus);
    
    return stats;
}

double TransportCatalogue::ComputeRouteLength(const transport_catalogue::Bus& bus) const {
    double total_length = 0.0;
    
    for (size_t i = 0; i < bus.stops.size() - 1; ++i) {
        const transport_catalogue::Stop* stop1 = bus.stops[i];
        const transport_catalogue::Stop* stop2 = bus.stops[i + 1];
        total_length += ComputeDistance(
            {stop1->coordinates.lat, stop1->coordinates.lng},
            {stop2->coordinates.lat, stop2->coordinates.lng}
        );
    }
    
    return total_length;
}
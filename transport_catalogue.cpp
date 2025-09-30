#include "transport_catalogue.h"

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
#pragma once

#include <string>
#include <deque>
#include <unordered_map>
#include <vector>
#include <optional>
#include "geo.h"
#include <set>

namespace transport_catalogue {

struct Stop {
	std::string name;
	Coordinates coordinates;
};

struct Bus {
	std::string name;
	std::vector<const Stop *> stops;
};

}

class TransportCatalogue {
public:
	void AddStop(transport_catalogue::Stop stop);
	void AddBus(transport_catalogue::Bus bus);

	const transport_catalogue::Stop *FindStop(std::string_view name) const;
	const transport_catalogue::Bus *FindBus(std::string_view name) const;

	struct StopStats {
		std::set<std::string> buses;
	};

	std::optional<TransportCatalogue::StopStats> GetStopStats(std::string_view name) const;

	struct BusStats {
		size_t stops_count;
		size_t stops_count_unique;
		double route_length;
	};

	std::optional<TransportCatalogue::BusStats> GetBusStats(std::string_view name) const;

private:
	std::deque<transport_catalogue::Stop> stops_;
	std::deque<transport_catalogue::Bus> buses_;
	/* Контейнеры для поиска */
	std::unordered_map<std::string_view, const transport_catalogue::Stop *> stop_name_to_stop_;
	std::unordered_map<std::string_view, const transport_catalogue::Bus *> bus_name_to_bus_;
	std::unordered_map<std::string_view, std::set<std::string>> stop_name_to_buses_;

	double ComputeRouteLength(const transport_catalogue::Bus& bus) const;
};
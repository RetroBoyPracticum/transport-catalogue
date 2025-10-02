#pragma once

#include <string>
#include <deque>
#include <unordered_map>
#include <vector>
#include <optional>
#include "geo.h"
#include <set>

struct Stop {
	std::string name;
	Coordinates coordinates;
};

struct Bus {
	std::string name;
	std::vector<const Stop *> stops;
};

class TransportCatalogue {
public:
	void AddStop(Stop stop);
	void AddBus(Bus bus);

	const Stop *FindStop(std::string_view name) const;
	const Bus *FindBus(std::string_view name) const;

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
	std::deque<Stop> stops_;
	std::deque<Bus> buses_;
	/* Контейнеры для поиска */
	std::unordered_map<std::string_view, const Stop *> stop_name_to_stop_;
	std::unordered_map<std::string_view, const Bus *> bus_name_to_bus_;

	std::unordered_map<std::string_view, std::set<std::string>> stop_to_buses_;

	double ComputeRouteLength(const Bus& bus) const;
};
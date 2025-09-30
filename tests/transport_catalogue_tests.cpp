#include <gtest/gtest.h>
#include "transport_catalogue.h"
#include <vector>


class TransportCatalogueClass : public ::testing::Test {
    void SetUp() {
        catalogue = TransportCatalogue();
    }

public:
    TransportCatalogue catalogue;
};


TEST_F(TransportCatalogueClass, StopAddAndFind_Single) {
    Stop stop = {"stop1", {11.111111, 22.222222}};

    catalogue.AddStop(stop);

    const Stop *found = catalogue.FindStop(stop.name);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->name, stop.name);
    EXPECT_NEAR(found->coordinates.lat, stop.coordinates.lat, 0.000001);
    EXPECT_NEAR(found->coordinates.lng, stop.coordinates.lng, 0.000001);
}

TEST_F(TransportCatalogueClass, BusAddAndFind_Single) {
    const Stop stop1 = {"stop1", {11.111111, 22.222222}};
    const Stop stop2 = {"stop2", {33.333333, 44.444444}};
    const Stop stop3 = {"stop3", {55.555555, 66.666666}};

    const std::vector<const Stop *> stops = {
        &stop1, &stop2, &stop3,
    };
    const Bus bus = {"bus1", stops};
    catalogue.AddBus(bus);

    const Bus *found = catalogue.FindBus(bus.name);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->name, bus.name);
    EXPECT_EQ(found->stops, stops);
}
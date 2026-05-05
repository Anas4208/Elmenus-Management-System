#ifndef FILEOPS_H
#define FILEOPS_H

#include "Order.h"
#include "DeliveryDriver.h"
#include <vector>

void saveCompletedOrders(const std::vector<Order*>& orders);
void saveDriverStats(const std::vector<DeliveryDriver*>& drivers);

#endif // FILEOPS_H

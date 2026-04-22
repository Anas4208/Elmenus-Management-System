#!/bin/bash

echo "Testing DeliveryDriver completely..."

{
# Register a driver first
echo "2"
echo "D001"
echo "Bob Driver"
echo "5551234567"
echo "Van"

# Test driver display
echo "9"
echo "D001"

# Register a customer for orders
echo "1"
echo "C001"
echo "John Customer"
echo "1234567890"
echo "123 Main St"

# Create order to test driver earnings
echo "3"
echo "ORD001"
echo "C001"

# Add items to order
echo "4"
echo "ORD001"
echo "Pizza"
echo "50"
echo "2"

# Assign driver (tests assignDriver)
echo "5"
echo "ORD001"
echo "D001"

# Update to delivered (tests completeDelivery and commission)
echo "6"
echo "ORD001"
echo "3"

# Create another order to test multiple deliveries
echo "3"
echo "ORD002"
echo "C001"

echo "4"
echo "ORD002"
echo "Burger"
echo "30"
echo "1"

echo "5"
echo "ORD002"
echo "D001"

echo "6"
echo "ORD002"
echo "3"

# Display driver info again to see updated earnings and deliveries
echo "9"
echo "D001"

# Test statistics
echo "11"

# Exit
echo "17"
} | ./main

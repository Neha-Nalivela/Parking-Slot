# 🚗 Parking Management System in C

A **console-based Parking Management System** developed in **C** using fundamental data structures such as **arrays, linked lists, circular queues, and hash tables**.

The system manages vehicle parking, available parking slots, waiting vehicles, vehicle removal, parking duration, and parking fines.

## 📌 Project Overview

The Parking Management System is designed to simulate the basic operations of a parking lot.

It allows users to:

* Park a vehicle in an available slot
* Add vehicles to a waiting queue when all slots are occupied
* Remove a parked vehicle
* Automatically assign a freed slot to the next waiting vehicle
* Display currently parked vehicles
* Calculate parking duration and fine
* Search vehicles efficiently using a hash table

The project demonstrates how multiple **Data Structures and Algorithms (DSA)** concepts can be combined to solve a real-world problem.

---

## ✨ Features

### 1. Park Vehicle

* Searches for the first available parking slot.
* Assigns the vehicle to that slot.
* Records the vehicle's entry time.
* Stores the vehicle information in a linked list.
* Stores vehicle information in a hash table for faster lookup.

### 2. Waiting Queue

If all parking slots are occupied:

* The vehicle is added to a **circular waiting queue**.
* Vehicles are processed according to **FIFO (First In, First Out)** order.
* When a parking slot becomes available, the first vehicle in the queue is automatically parked.

### 3. Remove Vehicle

When a vehicle leaves:

* The vehicle is searched using its vehicle number.
* Its parking slot is marked as available.
* The vehicle is removed from the linked list.
* Parking duration is calculated.
* A parking fine is calculated.
* The next vehicle in the waiting queue is automatically parked.

### 4. Display Parked Vehicles

Displays:

* Vehicle number
* Parking slot number

### 5. Parking Fine Calculation

The program calculates the parking duration using the system time.

The fine is calculated based on the parking duration.

Current implementation uses:

**₹10 per minute**

with a maximum fine of:

**₹1000**

> Note: The source code comment says "10 rupees per hour", but the actual formula uses `parkingTime / 60`, which calculates the duration in minutes. Therefore, the implementation currently charges ₹10 per minute.

---

## 🧠 Data Structures Used

| Data Structure | Purpose                                    |
| -------------- | ------------------------------------------ |
| Array          | Stores parking slot availability           |
| Linked List    | Stores currently parked vehicles           |
| Circular Queue | Stores vehicles waiting for a parking slot |
| Hash Table     | Provides quick vehicle-number lookup       |
| Structure      | Groups vehicle and parking information     |

---

## 🏗️ System Structure

The main `ParkingSystem` structure contains:

```text
ParkingSystem
│
├── slots[]
│   └── Stores parking slot status
│
├── queue[]
│   └── Stores waiting vehicles
│
├── front
├── rear
│   └── Manage circular queue
│
├── parkedList
│   └── Linked list of parked vehicles
│
└── hashMap[]
    └── Vehicle lookup information
```

---

## 🔄 Working Flow

### Parking a Vehicle

```text
Start
  ↓
Enter Vehicle Number
  ↓
Check Available Parking Slot
  ↓
 ┌───────────────┐
 │ Slot Available│
 └───────┬───────┘
         ↓
 Assign Slot
         ↓
 Record Entry Time
         ↓
 Add to Linked List
         ↓
 Add to Hash Table
         ↓
 Vehicle Parked
```

If no slot is available:

```text
No Available Slot
        ↓
Add Vehicle to Queue
        ↓
Wait for a Slot
```

### Removing a Vehicle

```text
Enter Vehicle Number
        ↓
Search Hash Table
        ↓
Vehicle Found?
        ↓
Return Vehicle Details 
```

# Packet Transmission Simulator

This project simulates packet transmission through a network of switchers, handling packet arrival, transmission, and switcher availability. The system models a queue and linked list to manage the state of packets and switchers in a network simulation.

## Table of Contents

- [Description](#description)
- [Files](#files)
- [How to Compile and Run](#how-to-compile-and-run)
- [Usage](#usage)
- [License](#license)

## Description

The simulator models the behavior of packet transmissions in a network, where packets arrive at different times and need to be transmitted by switchers. The simulation handles:

- Packet arrival times and transmission times.
- Switcher availability based on transmission completions.
- Prioritization of packet transmissions.
- Dynamic queue management to process packets through available switchers.

### Main Features

- **Queue Management:** Simulates packet queuing and dequeuing based on switcher availability.
- **Linked List for Packets:** A dynamic linked list stores packets and keeps track of their statuses.
- **Random Priority Assignment:** Each packet is assigned a random priority to simulate real-world packet management scenarios.
- **Simulation Time:** The system uses a simulated clock to track packet transmission and switcher availability.

## Files

- `main.c`: The main program that controls the simulation.
- `queue.h`: Header file that defines the queue data structure and associated functions.
- `linkedlist.h`: Header file that defines the linked list data structure for managing packets.
- `todo.c`: A TODO list or additional helper functions for future development or improvements.

## How to Compile and Run

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/packet-transmission-simulator.git
   cd packet-transmission-simulator

//
// Created by berrak on 28/11/2024.
//

#ifndef QUEUE_H
#define QUEUE_H


struct QueueRecord
{
    struct Node *front;
    struct Node *rear;
    int size;
};

typedef struct QueueRecord *Queue;

// Queue Functions
void makeEmptyQueue(Queue queue);
struct QueueRecord *createQueue(int maxElements);

// This function should randomly create packets based on the input (the number of
// packets, the number of switchers, the maximum arrival time, the maximum transmission time). The
// packet should be stored in a linked list in ascending order based on their arrival time.
struct ListRecord* createPacketList(int numPackets, int numSwitchers, int maxArrival, int maxTransmission);

// This function should create an empty queue, and also an integer array to keep
// the availability of the switchers.
struct QueueRecord *initialiseSimulator(int numPackets, int numSwitchers, int *array);

// This function takes a packet from the list based on the arrival time and adds it to the
// queue.
void newPacket(Queue queue, int arrivalTime, int idSwitcher, int transmissionTime, int transmissionStart, int priority);

// This function takes a packet from the queue to be transmitted by the switcher.
struct Node *transmitPacket(Queue queue);


int IsSwitcherEmpty (int* array, int numSwitcher); // Returns 1 if the switchers are empty
int randomSwitcher(int *array,int numSwitchers); // Picks a random switcher

#endif //QUEUE_H

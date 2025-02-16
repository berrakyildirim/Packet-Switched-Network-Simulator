//
// Created by berrak on 02/12/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define N 100

struct Node {
    int idSwitcher;
    int arrivalTime; // When it is arrived
    int transmissionTime; // How long transmission will take
    int transmissionStart; // When transmission started
    int priority;
    struct Node *next;
};

struct ListRecord {
    struct Node *head;
    struct Node *tail;
    int size;
};


typedef struct ListRecord *List;

void insertNode(List list, int arrivalTime, int idSwitcher, int transmissionTime, int transmissionStart, int priority); // Inserts a node according to arrival time
void makeEmpty(List list);

// Dummy Node
void MakeEmptyList(List list); // Uses dummy node
void InsertList(List list, struct Node *p); // Inserts at the end of the list

void removeNode(List list); // Removes node from head
struct ListRecord *CreateList();

// This function reports the statistics, such as the average waiting time in the queue,
// average transmission time per packet, etct
void reportStatistics(int numSwitcher, List list);
// This function should parse the input and set the values of the number of packets, the
// number of switchers, the maximum arrival time, and the maximum transmission time
void parseInput(int *numPackets, int *numSwitchers, int *maxArrival, int *maxTransmission);

// these functions helped me check my code
// struct ListRecord *TestCreateList();
// void TestInsert(List list);



// void displayList(List list); // I used these functions to help me control my code
// struct ListRecord *TestCreateList();


#endif //LINKEDLIST_H

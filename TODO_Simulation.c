//
// Created by berrak on 28/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "linkedlist.h"

// It get informations from user (pass by reference)
void parseInput(int *numPackets, int *numSwitchers, int *maxArrival, int *maxTransmission){
    char simulation[N]; // TODO_Simulator.c
    printf("\n TODO_Simulator noOfPackets noOfSwitchers maxArrivalTime maxTransmissionTime");
    scanf("%s %d %d %d %d", simulation, numPackets, numSwitchers, maxArrival, maxTransmission);
}

struct ListRecord* createPacketList(int numPackets, int numSwitchers, int maxArrival, int maxTransmission) {
    List list = (struct ListRecord*)malloc(sizeof(struct ListRecord));
    if (list == NULL) {
        printf("\nError!");
        exit(-1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    int arrivalTime, transmissionTime;
    srand(time(0));

    while (list->size < numPackets) { // Randomize arrival time and transmission time
        arrivalTime = rand() % (maxArrival-1); // arrival time should be less than maxArrival
        transmissionTime = (rand() % (maxTransmission-2)) + 1; //

        insertNode(list, arrivalTime, 0, transmissionTime, 0, 0);
    }
    return list;
}

// Insert according to arrival time
void insertNode(List list, int arrivalTime, int idSwitcher, int transmissionTime, int transmissionStart, int priority) {
    // Create a temporary node to insert it
    struct Node *tmp= (struct Node *) malloc(sizeof(struct Node));
    tmp->idSwitcher = idSwitcher;
    tmp->transmissionTime = transmissionTime;
    tmp->transmissionStart = transmissionStart;
    tmp->arrivalTime = arrivalTime;
    tmp->priority = 0;
    tmp->next = NULL;

   if (list->head == NULL) { // When list is empty
       list->head = tmp;
       list->tail = tmp;
   }
    else if (tmp->arrivalTime < list->head->arrivalTime) { // Inserting in front of head
        tmp->next = list->head;
        list->head = tmp;
    }
    else if (tmp->arrivalTime > list->tail->arrivalTime) {
        // Inserting at the end
        list->tail->next = tmp;
        list->tail = tmp;
    }
    else { // Inserting in the middle
        struct Node *current = list->head;
        struct Node *previous = NULL;

        while (current != NULL && current->arrivalTime <= tmp->arrivalTime) {
            previous = current;
            current = current->next;
        }

        tmp->next = current;
        if (previous == NULL) {
            list->head = tmp; // If inserting at the start
        } else {
            previous->next = tmp;
        }

        if (tmp->next == NULL) {
            list->tail = tmp;
        }
    }
    list->size++;
}

void makeEmptyQueue(Queue queue) {
    queue->size = 0;
    queue->front = NULL;
    queue->rear = NULL;
}

struct QueueRecord *initialiseSimulator(int numPackets, int numSwitchers, int *array) {
    Queue queue = createQueue(numPackets);
    for (int i=0 ; i<numSwitchers ; i++) {
        array[i] = 1;
    }
    return queue;
}

struct QueueRecord *createQueue(int maxElements) {
    Queue queue = (struct QueueRecord*)malloc(sizeof(struct QueueRecord));
    if (queue == NULL) {
        printf("\nError!");
        exit(-1);
    }
    makeEmptyQueue(queue);
    return queue;
}

// Checks if switcher is empty
int IsSwitcherEmpty (int* array, int numSwitcher) {
    int found = 0;
    for (int i=0 ; i<numSwitcher ; i++) {
        if (array[i] == 1)
            found++;
    }

    if (found != 0)
        return 0; // it is empty when 0
    else
        return 1; // it is not empty when 1
}

// It picks a random avaliable switcher
int randomSwitcher(int *array, int numSwitchers) {
    int randomSwitch ;
    srand(time(0));
    int a = 0;
    for (int i=0 ; i<numSwitchers ; i++) {
        if (array[i] == 0)
            a++;
    }
    if (a == numSwitchers ) { // If there is no avaliable switcher, return -1
        return -1;
    }
    do {
        randomSwitch = rand()%(numSwitchers);
    } while (array[randomSwitch] == 0);
    return randomSwitch;
}

struct ListRecord * CreateList()
{
    List list;
    list = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (list == NULL)
        printf("Out of memory!\n");
    else
        MakeEmptyList(list);
    return list;
}

// Dequeue
struct Node *transmitPacket(Queue queue) {
    if (queue->front == NULL) {
        printf("\nError!");
        exit(-1);
    }

    // Remove node
    struct Node *removeNode = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    removeNode->next = NULL;
    queue->size--;

    // Return removed node
    return removeNode;
}

// Enqueue with priority
void newPacket(Queue queue, int arrivalTime, int idSwitcher, int transmissionTime, int transmissionStart, int priority) {
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nError!");
        exit(-1);
    }
    newNode->next = NULL;
    newNode->arrivalTime = arrivalTime;
    newNode->idSwitcher = idSwitcher;
    newNode->transmissionStart = transmissionStart;
    newNode->transmissionTime = transmissionTime;
    newNode->priority = priority;

    // if queue is empty
    if (queue->size == 0) {
        queue->rear = newNode;
        queue->front = newNode;
    }

    else {
        if (newNode->priority <= queue->rear->priority ) { // If it is lower priority than rear, insert it at the end
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
        else if (newNode->priority > queue->front->priority) { // Highest priority than the first one in the queue, insert at the front
            newNode->next = queue->front;
            queue->front = newNode;
        }
        else { // (insert middle)
            struct Node *current;
            current = queue->front;
            while (current->next != NULL && newNode->priority <= current->next->priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    queue->size++;
}

void reportStatistics(int numSwitcher, List list) {
    // The number of packets: How many packets were transmitted successfully? (This is already given to
    // you by the user)
    int numPackets = list->size;

    // The number of packets for each label: How many packets of high, medium, normal, or low
    // priority are transmitted by the switcher?
    int numPriorityHigh = 0, numPriorityMedium = 0, numPriorityNormal = 0, numPriorityLow = 0;
    struct Node *tmp = list->head;
    while (tmp != NULL) {
        if (tmp->priority == 1) // Low
            numPriorityLow++;
        else if (tmp->priority == 2) // Normal
            numPriorityNormal++;
        else if (tmp->priority == 3) // Medium
            numPriorityMedium++;
        else if (tmp->priority == 4) // High
            numPriorityHigh++;

        tmp = tmp->next;
    }

    // The number of packets for each switcher and busiest switcher: How many packets did each
    // switcher transmit? Which switcher transmitted the biggest number of packets?
    // (if 2 switchers transmitted the same number of packets you have to display both of them)
    int *numPacketsTransmittedSwitcher = (int*)malloc(sizeof(int)*numSwitcher);

    for (int i=0 ; i< numSwitcher ; i++) {
        numPacketsTransmittedSwitcher[i] = 0;
    }
    struct Node *tmp_2 = list->head;
    while (tmp_2 != NULL) {
        numPacketsTransmittedSwitcher[tmp_2->idSwitcher]++;
        tmp_2 = tmp_2->next;
    }
    int max = 0;
    for (int i=0 ; i<numSwitcher ; i++) { // Find busiest
        if (numPacketsTransmittedSwitcher[i] > max) {
            max = numPacketsTransmittedSwitcher[i];
        }
    }


    // The completion time: How long did it take to complete the simulation?
    int completionTime = list->tail->transmissionStart + list->tail->transmissionTime;

    // Average waiting time in the queue: What was the average delay in the queue? You need to
    // calculate the total waiting time of all packets in the queue and then divide this by the number of
    // packets you have. This will give you the average waiting time in the queue.
    int totalArrival = 0, totalTransmissionStart = 0;
    float averageWaitingTime;
    struct Node *tmp_3 = list->head;
    while (tmp_3 != NULL) {
        totalArrival += tmp_3->arrivalTime;
        totalTransmissionStart += tmp_3->transmissionStart;
        tmp_3 = tmp_3->next;
    }
    averageWaitingTime = (totalTransmissionStart - totalArrival) / numPackets;

    //  average transmission time per packet: this represents the amount of time spent by the packet in the
    // queue(waiting time) plus the time it requires for that packet to be transmitted by the switcher
    // (transmission time). You need to find the packet that took the longest amount of time to be treated
    // by the switcher.
    int totalTransmission = 0, maxTransmission = 0; // ???
    float averageTransmissionTime;
    struct Node *tmp_4 = list->head;
    while (tmp_4 != NULL) {
        totalTransmission += tmp_4->transmissionTime;
        tmp_4 = tmp_4->next;

    }
    averageTransmissionTime = totalTransmission / numPackets;

    // Print
    printf("\n****************Report*****************");
    printf("\n *The number of switchers is: %d", numSwitcher);
    printf("\n*The number of packets: %d", numPackets);
    printf("\n*Number of packets for each Label:");
    printf("\n     High priority: %d", numPriorityHigh);
    printf("\n     Medium priority: %d", numPriorityMedium);
    printf("\n     Normal priority: %d", numPriorityNormal);
    printf("\n     Low priority: %d", numPriorityLow);
    printf("\n*Number of Packets per switcher and the busiest one:");
    for (int i=0 ; i<numSwitcher ; i++) {
        printf("\n  switcher %d transmitted: %d packets", i, numPacketsTransmittedSwitcher[i]);
    }
    printf("\n  busiest switcher: ");
    for (int i=0 ; i<numSwitcher ; i++) {
        if (numPacketsTransmittedSwitcher[i] == max) {
            printf("%d ", i);
        }
    }
    printf("\n*Completion time: %d", completionTime);
    printf("\n*Average waiting time in the queue: %.1f", averageWaitingTime);
    printf("\n*Average transmission time per packet: %.1f", averageTransmissionTime);
}

// Removes the head
void removeNode(List list) {
    if (list->head == NULL) {
        printf("List is empty, cannot remove node.\n");
        return;  // Handle empty list more gracefully
    }


    // Remove the head node
    struct Node *tmp = list->head;
    list->head = list->head->next;  // Move head to the next node

    if (list->head == NULL) {
        list->tail = NULL;
    }

    tmp->next = NULL;
    list->size--;
}

void MakeEmptyList(List list)
{
    list->head = (struct Node *) malloc(sizeof(struct Node));
    if (list->head == NULL)
        printf("Out of memory!\n");
    else
    {
        list->head->next = NULL;
        list->tail = list->head;
        list->size = 0;
    }
}

void InsertList(List list, struct Node *p) {
    if (p == NULL) {
        printf("Out of memory!\n");
        exit(-1);
    }

    list->tail->next = p;
    list->tail = p;

    list->size++;
}



// FUNCTIONS THAT HELPED ME CHECK MY CODE

/*struct ListRecord *TestCreateList() {
    List list = (struct ListRecord*)malloc(sizeof(struct ListRecord));
    if (list == NULL) {
        printf("\nError!");
        exit(-1);  // If malloc fails, we exit
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void TestInsert(List list) {
    int arrivalTimes[15] = {1, 1, 5, 6, 8, 9, 11, 12, 13, 13, 16, 16, 16, 16, 17};
    int transmissionTimes[15] = {3, 4, 2, 6, 5, 3, 4, 2, 6, 5, 3, 4, 2, 6, 5};

    struct Node *temp = NULL;

    for (int i = 0; i < 15; i++) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        if (temp == NULL) {
            printf("Out of memory!\n");
            exit(-1);
        }

        temp->arrivalTime = arrivalTimes[i];
        temp->transmissionTime = transmissionTimes[i];
        temp->priority = 0;
        temp->transmissionStart = 0;
        temp->idSwitcher = 0;
        temp->next = NULL;

        if (list->head == NULL) {
            list->head = temp;
            list->tail = temp;
        } else {
            list->tail->next = temp;
            list->tail = temp;
        }

        list->size++;
    }
}*/

/*void displayQueue (Queue queue) {
    if (queue == NULL || queue->front == NULL) {
        printf("The queue is empty.\n");
        return;
    }

    struct Node *tmp = queue->front;
    printf("-----------------------------------------------------------\n");
    printf("Displaying Queue:\n");
    printf("-----------------------------------------------------------\n");

    int i = 0;
    while (tmp != NULL) {
        printf("Queue Position %d:\n", i);
        printf("-----------------------------------------------------------\n");
        printf("Arrival Time        : %d\n", tmp->arrivalTime);
        printf("Transmission Time   : %d\n", tmp->transmissionTime);
        printf("Transmission Start  : %d\n", tmp->transmissionStart);
        printf("Switcher ID          : %d\n", tmp->idSwitcher);
        printf("Priority            : %d\n", tmp->priority);
        printf("-----------------------------------------------------------\n\n");

        tmp = tmp->next;
        i++;
    }
}
*/

/*void makeEmpty(List list) {
    if (list == NULL) {
        printf("\nError");
        exit(-1);
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}*/

/*void displayList(List list) {
    struct Node *tmp;
    tmp = list->head;

    int i = 1;
    while (tmp != NULL) {
        printf("-----------------------------------------------------------\n");
        printf("Packet %d:\n", i);
        printf("-----------------------------------------------------------\n");
        printf("Arrival Time        : %d\n", tmp->arrivalTime);
        printf("Transmission Time   : %d\n", tmp->transmissionTime);
        printf("Transmission Start  : %d\n", tmp->transmissionStart);
        printf("Switcher ID          : %d\n", tmp->idSwitcher);
        printf("Priority            : %d\n", tmp->priority);
        printf("-----------------------------------------------------------\n\n");

        tmp = tmp->next;
        i++;
    }

    if (i == 0) {
        printf("The list is empty.\n");
    }
}*/


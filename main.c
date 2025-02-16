// BERRAK YILDIRIM 2690964

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "linkedlist.h"

int main(void) {
    srand(time(0));
    // Get information from user
    int numPackets, numSwitchers, maxArrival, maxTransmission;
    parseInput(&numPackets, &numSwitchers, &maxArrival, &maxTransmission);

    int randomSwitch;


    int *array; // An array to keep switchers avaliabilities
    array = (int*)malloc(sizeof(int)*numSwitchers);

    List list = createPacketList(numPackets, numSwitchers, maxArrival, maxTransmission); // Create my packet list
    List tempList = CreateList(); // Create with dummy node
    Queue queue = initialiseSimulator(numPackets, numSwitchers, array); // Create a queue

    // Randomize priortity
    struct Node *tmp_9 = list->head;
    for (int i=0 ; i<list->size ; i++) {
        tmp_9->priority = rand()%5;
        tmp_9 = tmp_9->next;
    }

    int currentTime = 0; // My simulated clock

    for (int i=0 ; i<(maxArrival+(maxTransmission*numPackets)) ; i++) { // Maximum time that can take (Worst case)

        int a = 1; // a helps me get out of my loop later

        // If  transmissionStart + transmissionTime == currentTime it means
        // the packet transmitted so make it switcher avaliable
        struct Node *tmp = tempList->head;
        for (int j=0 ; j<=tempList->size ; j++) { // I have dummy node in tempList
            if (tmp->transmissionStart +  tmp->transmissionTime == currentTime) {
                array[tmp->idSwitcher] = 1;
            }
            tmp = tmp->next;
        }
        if (!IsSwitcherEmpty(array, numSwitchers)) { // If switcher is empty (take a packet inside)
            if (queue->front != NULL) { // If queue is not empty
                while (list->head != NULL && list->head->arrivalTime == currentTime) { // If packet arrives at current time
                    newPacket(queue, list->head->arrivalTime, list->head->idSwitcher, list->head->transmissionTime, list->head->transmissionStart, list->head->priority); // Add packet to the queue
                    removeNode(list); // Removes head of the list
                }
                while (!IsSwitcherEmpty(array, numSwitchers)){
                    randomSwitch = randomSwitcher(array, numSwitchers);
                    struct Node *tmp_4 = transmitPacket(queue); // Dequeue
                    tmp_4->transmissionStart = currentTime;
                    tmp_4->idSwitcher = randomSwitch;
                    tmp_4->next = NULL;
                    InsertList(tempList, tmp_4); // Insert transmitted node to my temporary list
                    array[randomSwitch] = 0; // Make switcher busy
                }
            }
            else { // Queue is empty
                while (list->head != NULL && list->head->arrivalTime == currentTime && a == 1) {
                    randomSwitch = randomSwitcher(array, numSwitchers);

                    if (randomSwitch != -1) { // If switcher is empty
                        struct Node *tmp_2  = list->head; // Remove the first element at the list and store it in the tmp_2
                        removeNode(list);
                        tmp_2->transmissionStart = currentTime;
                        tmp_2->idSwitcher = randomSwitch;
                        tmp_2->next = NULL;
                        InsertList(tempList, tmp_2); // Insert removed node to a temporary list (at the end)
                        array[randomSwitch] = 0; // Make switcher busy
                    }
                    else // Switcher is not empty
                        a = 0;
                }
            }
            if (list->size == 0) {
            }
        }

        //
        if (IsSwitcherEmpty(array, numSwitchers)) { // Switcher is not empty
            while (list->head != NULL && list->head->arrivalTime == currentTime) {
                newPacket(queue, list->head->arrivalTime, list->head->idSwitcher, list->head->transmissionTime,
                          list->head->transmissionStart, list->head->priority); // Add packet to the queue
                removeNode(list); // Removes head of the list
                }
        }
        currentTime++;
    }

    // list head points to my tempList's head
    //  list tail points to my tempList's tail
    // their size is equal
    list->head = tempList->head->next;
    list->tail = tempList->tail;
    list->size = tempList->size;

    reportStatistics(numSwitchers, list);

    return 0;
}


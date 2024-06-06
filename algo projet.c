#include <stdio.h>
#include <stdlib.h>

typedef struct Client {
    int ticketNumber;
    struct Client* next;
} Client;

typedef struct Queue {
    Client* front;
    Client* rear;
    int size;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

Client* newClient(int ticketNumber) {
    Client* temp = (Client*)malloc(sizeof(Client));
    temp->ticketNumber = ticketNumber;
    temp->next = NULL;
    return temp;
}

void enqueue(Queue* q, int ticketNumber) {
    if (q->size >= 10) {
        printf("La file d'attente est pleine. Le client %d quitte la file.\n", ticketNumber);
        return;
    }

    Client* temp = newClient(ticketNumber);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->size++;
    printf("Le client %d a été ajouté à la file d'attente.\n", ticketNumber);
}

void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("La file d'attente est vide.\n");
        return;
    }

    Client* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    printf("Le client %d a été servi et a quitté la file d'attente.\n", temp->ticketNumber);
    free(temp);
    q->size--;
}

void displayQueue(Queue* q) {
    if (q->front == NULL) {
        printf("La file d'attente est vide.\n");
        return;
    }

    Client* temp = q->front;
    printf("File d'attente actuelle : ");
    while (temp!= NULL) {
        printf("%d ", temp->ticketNumber);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue* q = createQueue();
    int choice, ticketNumber = 1;

    while (1) {
        printf("\n1. Ajouter un client\n2. Servir un client\n3. Afficher la file d'attente\n4. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue(q, ticketNumber++);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                displayQueue(q);
                break;
            case 4:
                printf("Sortie du programme.\n");
                exit(0);
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
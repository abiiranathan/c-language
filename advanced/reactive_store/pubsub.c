#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // for the sleep() function

// Data structure to represent a subscriber
typedef struct subscriber_t {
    char* name;
    void (*callback)(char*, char*, size_t);
    struct subscriber_t* next;
} subscriber_t;

// Data structure to represent a reactive store
typedef struct {
    char* data;
    size_t size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    subscriber_t* subscribers;  // linked list of subscribers

} reactive_store_t;

// Initialize the reactive store
reactive_store_t store;

// Initialize a new reactive store
void reactive_store_init(reactive_store_t* store) {
    store->data = NULL;
    store->size = 0;
    pthread_mutex_init(&store->mutex, NULL);
    pthread_cond_init(&store->cond, NULL);
}

// Set the data in the reactive store and notify all subscribers
void reactive_store_set(reactive_store_t* store, const char* data, size_t size) {
    pthread_mutex_lock(&store->mutex);
    if (store->data) {
        free(store->data);
    }
    store->data = malloc(size);
    memcpy(store->data, data, size);
    store->size = size;
    pthread_cond_broadcast(&store->cond);
    pthread_mutex_unlock(&store->mutex);
}

// Get the data from the reactive store.
// Blocks on pthread_cond_wait until some data is available.
void reactive_store_get(reactive_store_t* store, char* data, size_t* size) {
    pthread_mutex_lock(&store->mutex);
    while (!store->data) {
        pthread_cond_wait(&store->cond, &store->mutex);
    }
    memcpy(data, store->data, store->size);
    *size = store->size;
    pthread_mutex_unlock(&store->mutex);
}

// Add a new subscriber to the reactive store
// Adds subscriber to the linked list
void reactive_store_subscribe(reactive_store_t* store, subscriber_t* subscriber) {
    pthread_mutex_lock(&store->mutex);
    subscriber->next = store->subscribers;
    store->subscribers = subscriber;
    pthread_mutex_unlock(&store->mutex);
}

// Remove a subscriber from the reactive store
void reactive_store_unsubscribe(reactive_store_t* store, subscriber_t* subscriber) {
    pthread_mutex_lock(&store->mutex);
    subscriber_t* prev = NULL;
    subscriber_t* curr = store->subscribers;
    while (curr) {
        if (curr == subscriber) {
            if (prev) {
                prev->next = curr->next;
            } else {
                store->subscribers = curr->next;
            }
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    pthread_mutex_unlock(&store->mutex);
}

// Notify all subscribers with the current data in the store
void reactive_store_notify(reactive_store_t* store) {
    pthread_mutex_lock(&store->mutex);
    subscriber_t* curr = store->subscribers;
    while (curr) {
        curr->callback(curr->name, store->data, store->size);
        curr = curr->next;
    }
    pthread_mutex_unlock(&store->mutex);
}

// Subscriber thread function that waits for updates and prints the data
void* subscriber(void* arg) {
    subscriber_t* subscriber = (subscriber_t*)arg;
    char data[256];
    size_t size;
    while (1) {
        reactive_store_get(&store, data, &size);
        subscriber->callback(subscriber->name, data, size);
    }
    return NULL;
}

// Publisher thread function that updates the reactive store with random data
void* publisher(void* arg) {
    char data[] = "Hello, world!";
    time_t start_time;
    time(&start_time);

    while (1) {
        reactive_store_set(&store, data, strlen(data));
        reactive_store_notify(&store);
        sleep(1);
        if (time(NULL) >= start_time + 10) {
            exit(0);
        }
    }
    return NULL;
}

void print_data(char* name, char* data, size_t size) {
    printf("Data received by subscriber %s: %d bytes: %s\n", name, (int)size, data);
}

int main() {
    // Initialize the reactive store
    reactive_store_init(&store);

    // Initialize the subscribers
    subscriber_t subscriber1 = {.name = "sub1", .callback = print_data};
    subscriber_t subscriber2 = {.name = "sub2", .callback = print_data};

    // Start the publisher thread
    printf("Start subscribers\n");
    // Subscribe the subscribers
    reactive_store_subscribe(&store, &subscriber1);
    reactive_store_subscribe(&store, &subscriber2);

    // Start the publisher thread
    printf("Start publisher thread\n");
    pthread_t publisher_thread;
    pthread_create(&publisher_thread, NULL, publisher, NULL);

    // Record the start time of the publisher
    printf("Record start time\n");
    time_t start_time;
    time(&start_time);
    printf("%lu\n", start_time);

    // Unsubscribe the first subscriber after 5 seconds
    sleep(5);
    printf("Unsubscribing subscriber1\n");
    reactive_store_unsubscribe(&store, &subscriber1);

    // Wait for the publisher thread to finish
    pthread_join(publisher_thread, NULL);

    // Calculate the duration of the publisher
    time_t end_time;
    time(&end_time);
    double duration = difftime(end_time, start_time);

    printf("Publisher ran for %.2f seconds\n", duration);
    return 0;
}

Semester Project: Reader-Writer Problem Using Semaphores


Project Report



DESCRIPTION:


  The readers-writers problem relates to an object such as a file that is shared between multiple processes. Some of these processes are readers i.e. they only want to read the data from the object and some of the processes are writers i.e. they want to write into the object.
The readers-writers problem is used to manage synchronization so that there are no problems with the object data. For example - If two readers access the object at the same time there is no problem. But if two writers or a reader and writer access the object at the same time, there may be problems.
SOLUTION OF A PROBLEM:
     To solve this situation, a writer should get exclusive access to an object i.e. when a writer      is accessing the object, no reader or writer may access it. But multiple readers can access the object at the same time. It can be implemented using semaphores.
     
     
SOURCE CODE:


#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex; // Semaphore for mutual exclusion of readcount
sem_t wblock; // Semaphore for writer exclusion

int x = 0; // Shared resource

int readcount = 0;

void *reader(void *arg) {
    int *t = (int *)arg; // Temporary variable t
    int f = *t;
    
    // Entry section
    sem_wait(&mutex); // Acquire mutex to update readcount
    readcount++;
    if (readcount == 1) {
        sem_wait(&wblock); // If first reader, acquire wblock to block writers
    }
    sem_post(&mutex); // Release mutex after updating readcount
    
    // Critical section (Reading shared resource)
    printf("Data read by the reader %d is %d\n", f, x);
    
    // Exit section
    sem_wait(&mutex); // Acquire mutex to update readcount
    readcount--;
    if (readcount == 0) {
        sem_post(&wblock); // If last reader, release wblock to allow writers
    }
    sem_post(&mutex); // Release mutex after updating readcount
}

void *writer(void *arg) {
    int *t = (int *)arg;
    int f = *t;
    
    // Entry section
    sem_wait(&wblock); // Acquire wblock to block other writers
    
    // Critical section (Writing shared resource)
    x++; // Modify the shared resource (writing)
    printf("Data written by the writer %d is %d\n", f, x);
    
    // Exit section
    sem_post(&wblock); // Release wblock to allow other writers
}

int main() {
    int i;
    pthread_t id1[5], id2[5]; // id1 = reader , id2 = writer threads
    
    //Initializing
    sem_init(&mutex, 0, 1);   
    sem_init(&wblock, 0, 1);  
    
    //Create reader and writer threads
    for (i = 0; i <= 2; i++) {
        pthread_create(&id2[i], NULL, writer, &i);
        pthread_create(&id1[i], NULL, reader, &i);
    }
    
    //Join reader and writer threads
    for (i = 0; i <= 2; i++) {
        pthread_join(id2[i], NULL);
        pthread_join(id1[i], NULL);
    }
    
    //Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wblock);

    return 0;
}



EXPLANATION OF SOURCE CODE:
 
 
 ![image](https://user-images.githubusercontent.com/123716761/236903928-593724ab-9264-4ac1-921e-7cf612e65678.png)


![image](https://user-images.githubusercontent.com/123716761/236903962-30aad83f-e7f3-4543-b538-c28e341a07c7.png)

 
In this code we allow the readers to enter in a critical section simultaneously but no writer-writer, reader-writer and writer-reader can access the critical section at a time.

We use Two Semaphores”
 Mutex:   Semaphore for mutual exclusion of readcount
 Wblock: Semaphore for writer exclusion
We also initialized two variables
 X: That is a global variable and Shared resource.
Readcount: It is also a global variable that keeps the track of readers.

Reader:


In this process we started off by putting mutex semaphore into wait. In result mutex which had been initialize to 1 changes its value to 0 now restricting entry of any other reader. It then increments the value of readcount, after which a branch statement checks if this is the first reader entering. In case of the first reader we put wblock semaphore into wait mode. This now restricts entry of writers into the critical section. Now before entering the critical section we put mutex into post so now the value of mutex is back to being 1 that means more readers can now enter simultaneously. Now we enter the critical section where we print which reader is reading what data(x). Once we are out of our critical section we will again put mutex into wait as now we are making the readers exit, we decrement readcount value. When last reader left, we put wblock mutex from wait mode to post. The value of wblock is back to being 1. At the end we put mutex semaphore into post condition.
Writer:


In this we only have to synchronize the writer so we start off by sending wblock into wait so now only one writer can enter and write data(x). Once data is written we prompt then output on our screen and then we will change wblock from wait to post.
Main:
 In main we initialize thread arrays and semaphores. We run a loop which will create threads resulting in execution of reader writer function thrice. Then we will run another loop which will terminate the threads.

OUTPUT:


![image](https://user-images.githubusercontent.com/123716761/236903802-fff4e759-02a2-4c85-ab1f-118dfbb3c467.png)

          
REAL TIME EXAPMLE:


A practical example of a Readers and Writers problem is an airline reservation system consisting of a huge data base with many processes that read and write the data. Reading information from the data base will not cause a problem since no data is changed. The problem lies in writing information to the data base.

REFRENCES:


From wikipedia:


https://en.m.wikipedia.org/wiki/Readers%E2%80%93writers_problem


https://en.m.wikipedia.org/wiki/Semaphore_(programming)


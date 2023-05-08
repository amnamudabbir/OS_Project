#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex; 
sem_t wblock; 

int x = 0; // shared resourse
int readcount = 0;

void *reader(void *arg){
    int *t = (int *)arg; // Temporary variable t
    int f = *t;
    
    // Entry section
    sem_wait(&mutex); 
    readcount++;
    if (readcount == 1){
        sem_wait(&wblock); 
    }
    sem_post(&mutex); 
    
    // Critical section 
    printf("Data read by the reader %d is %d\n", f, x);
    
    // Exit section
    sem_wait(&mutex); 
    readcount--;
    if (readcount == 0){
        sem_post(&wblock); 
    }
    sem_post(&mutex); 
}

void *writer(void *arg){
    int *t = (int *)arg;
    int f = *t;
    
    // Entry section
    sem_wait(&wblock); 
    
    // Critical section 
    x++; 
    printf("Data written by the writer %d is %d\n", f, x);
    
    // Exit section
    sem_post(&wblock); 
}

int main(){
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


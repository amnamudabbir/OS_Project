Project Proposal


Semester Project: Reader-Writer Problem


Introduction:
The readers-writers problem is used to manage synchronization so that there are no problems with the object data. For example - If two readers access the object at the same time there is no problem. However if two writers or a reader and writer access the object at the same time, there may be problems. 
Language to be used:
We will use C or C++ for our program.
Functions:
We will make two basic functions:
1) Reader
2) Writer.
We  will use two semaphores:
1) Mutex: 
To keep the readers synchronized. 
2) Wblock: 
To synchronise our readers and our writers.
 
References:
We will take help from these two references one is for semaphores programming and second is for writer problems.

https://en.m.wikipedia.org/wiki/Readers%E2%80%93writers_problem
https://en.m.wikipedia.org/wiki/Semaphore_(programming)

Project aspects in future:
Counting semaphores are used in several scenarios:
1. Counting events:
In this usage scenario an event handler will ‘give’ a semaphore each time an event occurs (incrementing the semaphore count value), and a handler task will ‘take’ a semaphore each time it processes an event (decrementing the semaphore count value).
2. Resource management:
In this usage scenario the count value indicates the number of resources available. To obtain control of a resource a task must first obtain a semaphore– decrementing the semaphore count value. When the count value reaches zero there are no free resources.

Approved:         __________
Not Approved:  __________

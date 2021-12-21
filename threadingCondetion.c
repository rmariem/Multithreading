// C program to implement cond(), signal()
// and wait() functions
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Declaration of thread condition variable
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void* function1()
{
	while(1)
	{
		pthread_mutex_lock(&lock);
    		counter++;
		printf("counter = %d from thread 1 \n", counter);
		if(counter == 10) {

        		// Let's signal condition variable cond1
        		//counter = 0;
        		printf("Signaling condition variable cond1\n");
        		pthread_cond_signal(&cond);
    		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}

	return NULL;
}

void function2()
{
        while(1)
	{
		pthread_mutex_lock(&lock);
        	// let's wait on conition variable cond1
        	printf("Waiting on condition variable cond1\n");
        	pthread_cond_wait(&cond, &lock);
        	printf("signal done from thread 2 counter = %d\n", counter);
		counter = 0;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

// Driver code
int main()
{
    pthread_t tid1, tid2;

    // Create thread 1
    pthread_create(&tid1, NULL, function1, NULL);

    // Create thread 2
    pthread_create(&tid2, NULL, function2, NULL);

    // wait for the completion of threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

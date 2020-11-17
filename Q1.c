#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

sem_t coronaPatient;
sem_t fluPatient;
int potentialCPatients = 0;

int C_test() //1 mean positive...
{
	return (rand() % (1 - 0 + 1)) + 0;
}

void *thread(void *arg) {}

void test_patients()
{
	if (C_test()) //positive
	{
		sem_post(&coronaPatient);
	}
	else
	{
		sem_post(&fluPatient);
	}

	potentialCPatients--;
}

void recovered()
{
	int corona_p;
	sem_getvalue(&coronaPatient, &corona_p);

	printf("Total Covid positive Patients : %d \n",corona_p);
	while (corona_p != 0)
	{
		if (C_test()==0)
		{
			if (!C_test())
			{
				sem_wait(&coronaPatient);
				printf("Patient Recovered\n");
			}
		}
		sem_getvalue(&coronaPatient, &corona_p);
	}
	if(corona_p==0)
	{
		printf("All Patients Recovered\n");
	}
}

int main()
{
	sem_init(&coronaPatient, 0, 1);
	sem_init(&fluPatient, 0, 1);

	int N;

	printf("Enter PotentialCpatienrs.\n" );
	scanf("%d",&N);

	pthread_t *tid;

	tid=(pthread_t *)calloc(N,sizeof(pthread_t));

	int i;
	for (i = 0; i < N; i++)
	{
		if (pthread_create(&tid[i], NULL, thread, NULL) != -1)
		{
			potentialCPatients++;
		}
		else
		{
			printf("Thread Creation failed\n");
		}
	}

	printf("Total Patients admitted %d\n", potentialCPatients);

	for (i = 0; i < potentialCPatients; i++)
	{
		pthread_join(tid[i], NULL);
	}

	while (potentialCPatients != 0)
	{
		test_patients();
	}

	if (!potentialCPatients)
	{
		printf("All Patients are checked.\n");
	}
	recovered();

	sem_destroy(&coronaPatient);
	sem_destroy(&fluPatient);

	free(tid);
	return 0;
}

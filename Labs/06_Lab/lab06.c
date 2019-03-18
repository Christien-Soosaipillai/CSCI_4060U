#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

/*
    timing for ./a.out 5 100 10

      Run 1:
      -real	0m0.002s
      -cpu	0m0.002s

      Run 2:
      -real	0m0.002s
      -cpu	0m0.002s

      Run 3:
      -real	0m0.002s
      -cpu	0m0.001s


    timing for ./a.out 5 2500 25

      Run 1:
      -real	0m0.022s
      -cpu	0m0.010s

      Run 2:
      -real	0m0.013s
      -cpu	0m0.011s

      Run 3:
      -real	0m0.009s
      -cpu	0m0.009s

    timing for ./a.out 50 2500 25

      Run 1:
      -real	0m0.045s
      -cpu	0m0.020s

      Run 2:
      -real	0m0.050s
      -cpu 0m0.020s

      Run 3:
      -real	0m0.033s
      -cpu 0m0.017s


*/

struct agent {
  int thread_id;
  int tickets_available;
  int sell;
};

//globals
int tickets_sold = 0;

//thread specific
pthread_attr_t a;            //thread attribute
pthread_mutex_t mutex_tickets_sold; //mutual exclusion variable for 'tickets_available'

int error;

//forward declaration
void *ticket_agent(void *threadarg);

int main(int argc, char** argv){

  //command line arguments
  int num_agents = atoi(argv[1]);
  int num_of_tickets = atoi(argv[2]);
  int percent_oversale = atoi(argv[3]);

  //declaring threads
  pthread_t threads[num_agents];
  void *status; //used in join


  //declaring agent struct
  struct agent agentTeam[num_agents];
  long i;

  int initial_tickets = num_of_tickets + round(num_of_tickets * (percent_oversale * 0.01) );

  printf("tickets available: %d\n",initial_tickets);

  //set mutex to default values including unlocked state
  pthread_mutex_init(&mutex_tickets_sold, NULL);

  //initialize the thread attribute
  pthread_attr_init(&a); //set a to all default attributes
  pthread_attr_setdetachstate(&a, PTHREAD_CREATE_JOINABLE);

  //defining our agents
  for (i=0; i< num_agents; i++) {
    agentTeam[i].thread_id = i;
    agentTeam[i].tickets_available = initial_tickets;
    agentTeam[i].sell = 0;

    error = pthread_create(&threads[i], &a, ticket_agent,
                          (void *) &agentTeam[i]);
    if (error) {
      printf("ERROR: create() %d\n", error);
      exit(-1);
    }

  }

  pthread_attr_destroy(&a); //free attribute

  //join back threads/agents
  for (i=0; i< num_agents; i++) {
    error = pthread_join(threads[i], &status);

    if (error) {
      printf("ERROR: join() %d\n", error);
      exit(-1);
    }

  }
  printf("Threads complete and join done!\n");


  //summary data...
  printf("\n");
  printf("Data Summary!\n");
  for (i=0; i< num_agents; i++) {
    printf("Agent<%ld> sold %d tickets!\n", i,agentTeam[i].sell );

  }
  printf("The total amount of tickets sold is %d\n", tickets_sold);

  pthread_mutex_destroy(&mutex_tickets_sold);
  pthread_exit(NULL);

}

void *ticket_agent(void *threadarg){

  struct agent *current_agent;
  current_agent = (struct agent*) threadarg;
  //int sold_by_agent[];


  //if even...
  //while we still have tickets available....
  while(tickets_sold < current_agent->tickets_available){

    //If we have an even number agent
    if((current_agent->thread_id % 2) == 0){

      //45% chance
      if((rand()%100)+1 <= 45){
        pthread_mutex_lock(&mutex_tickets_sold); //get our lock
        int ticket_amount = (rand()%4)+1;
        if((tickets_sold+ticket_amount) <= current_agent->tickets_available){
          tickets_sold+=ticket_amount;
          current_agent->sell += ticket_amount;
          printf("Ticket agent <%d>: Successful transaction - <%d> tickets sold \n", current_agent->thread_id, ticket_amount);
        }else{
          printf("Ticket agent <%d>: Unsuccessful transaction \n", current_agent->thread_id);
        }
        pthread_mutex_unlock(&mutex_tickets_sold);
      }else{
        printf("Ticket agent <%d>: Unsuccessful transaction \n", current_agent->thread_id);
      }

    }else{    //odd number agent

      //35% chance
      if((rand()%100)+1 <= 35){

        pthread_mutex_lock(&mutex_tickets_sold); //get our lock
        int ticket_amount = (rand()%4)+1;
        if((tickets_sold+ticket_amount) <= current_agent->tickets_available){
          tickets_sold+=ticket_amount;
          current_agent->sell += ticket_amount;
          printf("Ticket agent <%d>: Successful transaction - <%d> tickets sold \n", current_agent->thread_id, ticket_amount);
        }else{
          printf("Ticket agent <%d>: Unsuccessful transaction \n", current_agent->thread_id);
        }
        pthread_mutex_unlock(&mutex_tickets_sold);

      }else{
        printf("Ticket agent <%d>: Unsuccessful transaction \n", current_agent->thread_id);
      }

    }

  }



  //when finished exit...
  pthread_exit(NULL);

}

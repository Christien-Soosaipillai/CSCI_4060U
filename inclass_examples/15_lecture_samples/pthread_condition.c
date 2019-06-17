#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define NUM_THREADS 2

struct stock {
  char name_id;
  float price;
  int count;
};

struct stock_option {
  char name_id;
  bool isBuy; //1 if buy and 0 if sell
  float option_price;
  int option_count;
};

struct investor_plan {
  struct stock_option s[2];
};

//declare shared variables and corresponding
//mutexs & condition variables.
struct stock stock_A = {'A', 2.50, 1000};
pthread_mutex_t stock_A_mutex;
pthread_cond_t stock_A_buy_cond;
pthread_cond_t stock_A_sell_cond;

//declare routines for threads...
void *stock_broker(void *t);
void *stock_exchange(void *t);

int main(int argc, char *argv[]) {
  struct investor_plan super_jon;
  struct stock_option option1 = {'A', true, 1.10, 5};
  struct stock_option option2 = {'A', false, 5.00, 5};
  super_jon.s[0] = option1;
  super_jon.s[1] = option2;

  //Declare threads
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;

  //initialize mutex and condition variables
  pthread_mutex_init(&stock_A_mutex, NULL);
  pthread_cond_init(&stock_A_buy_cond, NULL);
  pthread_cond_init(&stock_A_sell_cond, NULL);

  //Create threads to be joinable
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  int error = pthread_create(&threads[0], &attr, stock_exchange, NULL);
  if (error) {
    printf("ERROR: create stock exchange (code=%d)\n", error);
    exit(-1);
  }
  error = pthread_create(&threads[1], &attr, stock_broker, (void *) &super_jon);
  if (error) {
    printf("ERROR: create stock broker (code=%d)\n", error);
    exit(-1);
  }

  //wait for threads to complete/join
  for (int i=0; i < NUM_THREADS; i++) {
    error = pthread_join(threads[i], NULL);
    if (error) {
      printf("ERROR: join threads (code=%d)\n", error);
      exit(-1);
    }
  }

  //reinitialize/destory pthread variables
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&stock_A_mutex);
  pthread_cond_destroy(&stock_A_buy_cond);
  pthread_cond_destroy(&stock_A_sell_cond);
  pthread_exit(NULL);
}

void *stock_broker(void *t) {
  struct investor_plan *jon_data;
  jon_data = (struct investor_plan*) t;

  //when a desired price is reached buy stock
  printf("Broker: waiting for signal to buy/sell...\n");
  pthread_mutex_lock(&stock_A_mutex);
  pthread_cond_wait(&stock_A_buy_cond, &stock_A_mutex);
  printf("condition notify buy price: $%6.2f\n", stock_A.price);
  if (stock_A.price < jon_data->s[0].option_price) {
    printf("Made a stock purchase!\n");
    stock_A.count -= jon_data->s[0].option_count;
  }
  pthread_mutex_unlock(&stock_A_mutex);
  pthread_cond_wait(&stock_A_sell_cond, &stock_A_mutex);
  printf("condition notify sell price: $%6.2f\n", stock_A.price);
  if (stock_A.price > jon_data->s[1].option_price) {
    printf("Made a stock sale!\n");
    stock_A.count -= jon_data->s[1].option_count;
  }
  pthread_mutex_unlock(&stock_A_mutex);

  pthread_exit(NULL);
}

void *stock_exchange(void *t) {
  printf("Opening bell (ring, ring)\n");
  srand(time(NULL));
  for (int time_unit=0; time_unit < 500; time_unit++) {
    printf("-------------------\n");
    printf("TIME = %d\n", time_unit);
    pthread_mutex_lock(&stock_A_mutex);
    stock_A.price += (rand()%5-1.65);
    if ((rand()%6 == 0) && (stock_A.price < 5)) {
      stock_A.price -= 4;
    }
    if (stock_A.price < 0.01) {
      stock_A.price = 0.01;
    }
    printf("Stock price: $%.2f\n", stock_A.price);
    if (stock_A.price <= 1.1) {
      printf("signal price: $%.2f\n", stock_A.price);
      pthread_cond_signal(&stock_A_buy_cond);
    } else if (stock_A.price > 5.1) {
      printf("signal price: $%.2f\n", stock_A.price);
      pthread_cond_signal(&stock_A_sell_cond);
    }
    pthread_mutex_unlock(&stock_A_mutex);
    sleep(1);
  }
  printf("Closing bell (ring, ring)\n");
  pthread_exit(NULL);
}

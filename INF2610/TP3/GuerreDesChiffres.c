#include <stdio.h>
#include <semaphore.h> 
#include <stdlib.h>
#include <pthread.h> 
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

sem_t semEmpty, semFull, tour, mutex;
bool flag_de_fin = false;
int sumProducteur=0, cp = 0, cc = 0, sumConsamteur = 0, bufferSize;
int *buffer;

// fonction exécutée par les producteurs
void* producteur( void* pid) {
 while(1)
 {
    sem_wait(&semEmpty);
    sem_wait(&mutex);

    // on genere un nombre aleatoire entre 1 et 9
    // on le met dans le buffer
    // on incremente le compteur producteur
    // on addtionne le chiffre a la somme totale produite
    int x = (rand() % 9) + 1;
    buffer[cp] = x;
    cp= (cp+1)% bufferSize;
    sumProducteur+=x;
    
   if(flag_de_fin){
      sem_post(&mutex);
      sem_post(&semFull);
      pthread_exit(NULL);
   }
    sem_post(&mutex);
    sem_post(&semFull);
 }
   return NULL;             
}

// fonction exécutée par les consommateurs
void* consommateur(void *cid) {
   while(1){
      sem_wait(&semFull);
      sem_wait(&mutex);   
   //On va exit le thread si le valeur du buffer  a cc est =0;  
   //De plus, on s assure de post les valeurs des semaphore de sorte à ne pas bloquer les autres consommateurs. 
      if(buffer[cc] == 0)
      {
         cc= (cc +1)% bufferSize;
         sem_post(&mutex);
         sem_post(&semEmpty);
         pthread_exit(NULL);
      }
      sumConsamteur+=buffer[cc];
      cc= (cc +1)% bufferSize;
      
      sem_post(&mutex);
      sem_post(&semEmpty);
   }

       
  return NULL;   
  
}
//lorsque alarm est active nous allons mettre la valeur du flag_de fin a true de sort a pouvoir bloquer le producteur
void alarmTime(int signal)
{
   flag_de_fin = true;
}

// fonction main
int main(int argc, char* argv[]) {
   /* Les paramètres du programme sont, dans l’ordre :
      le nombre de producteurs, le nombre de consommateurs
      et la taille du tampon.*/
        
   srand(time(NULL));

    int numbOfProd = atoi(argv[1]);
    int numbOfCons = atoi(argv[2]);
    bufferSize = atoi(argv[3]);
    buffer = (int*)malloc(sizeof(int)*bufferSize);

   sem_init(&tour, 0, 1);
    sem_init(&semEmpty, 0, numbOfProd);
    sem_init(&semFull, 0, 0);
    sem_init(&mutex, 0, 1);
   
    pthread_t *prod, *cons;
    prod = (pthread_t*)malloc(sizeof(pthread_t)*numbOfProd);
    cons = (pthread_t*)malloc(sizeof(pthread_t)*numbOfCons);
    
    // creation des producteurs
    for(int i = 0; i < numbOfProd; i++){
       pthread_create(&prod[i], NULL, &producteur, NULL);
    }
    
    // creation des consommateurs
   for(int i = 0; i < numbOfCons; i++){
       pthread_create(&cons[i], NULL, &consommateur, NULL);
    }

    signal(SIGALRM,alarmTime);
    alarm(1);

   // apres que le signal soit recu, on attend que les threads se terminent
   for(int i = 0; i < numbOfProd; i++){
       pthread_join(prod[i], NULL);
    }

    // on rempli le buffer a 0 pour les consomateurs
   for(int i = 0; i < numbOfCons; i++){
      sem_wait(&semEmpty);
      sem_wait(&mutex);
      buffer[i] = 0;
      sem_post(&mutex);
      sem_post(&semFull);
   }

   // on reset l'indice des consomateurs a 0 puis on attends qu'ils lisent la valeurs 0 puis se terminent
   for(int i = 0; i < numbOfCons; i++){
      cc=0;
      pthread_join(cons[i], NULL);
    }

    printf("La valeur de la somme du producteur: %d  La valeur de la somme du consommateur: %d\n", sumProducteur,sumConsamteur);
    
   //on libere la memoire.
    free(prod);
    free(cons);
    free(buffer);
   //on detruit les semaphores.
    sem_destroy(&tour);
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
   
    return 0;
}

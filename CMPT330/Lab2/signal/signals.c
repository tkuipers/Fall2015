//
// CMPT 330 -- Lab 2
// Dr. Andrew Tappenden
//
// Signal Handler
//
// Edit this code to change what happens when signalHandler
// receieves either signal SIGUSR1 (10) or SIGUSR2 (12)
//
// To signal the process use the following command:
// 
// kill -10 PID
//      or
// kill -12 PID
//

#include <stdio.h>

void handleUSR1() {
  
  printf("Caught Signal SIGUSR1");
  
}

void handleUSR2() {
  
  printf("Caught Signal SIGUSR2 ");
  
}

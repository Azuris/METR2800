#include "Timer1.h"
#include "Timer0.h"
#include "AD_Convert.h"
#include <avr/io.h>

/* Runs the single ball drop for a stationery target.*/
void Mode_One();

/* Runs the single ball drop for a slow moving target.*/
void Mode_Two();

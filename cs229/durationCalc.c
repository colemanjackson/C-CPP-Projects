#include "durationcalc.h"
#include "keyvaluefinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Calculates the length of an audiofile using the number of samples (calculated or given) and the sample rate.
void durationCalc(double secondsWithDecimals, AUDIO *varStore){
	double hoursWithDecimals = secondsWithDecimals * (1/60.0) * (1/60.0);  // calculation to get hours and minutes as a decimal
	double hours; // the final place of hours
	double minutesWithDecimals; //full minutes and seconds
	double minutes; // the final place of minutes


       minutesWithDecimals= modf(hoursWithDecimals, &hours);
				minutesWithDecimals = minutesWithDecimals * 60.0;  //getting minutes properly
	secondsWithDecimals = modf(minutesWithDecimals, &minutes);
				secondsWithDecimals = secondsWithDecimals * 60.0; //getting seconds properly
	varStore->hours = hours;
	varStore->minutes = minutes;
	varStore->seconds = secondsWithDecimals;




















}

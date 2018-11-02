/* 	Assignment 1 for COMP20005, Semester 1, 2018.
	University of Melbourne
	Marishka Nicol Magness, Student ID: 805654
	mmagness@student.unimelb.edu.au  */


#include <stdio.h>
#include <stdlib.h>

/*defines for values used in the functions below*/ 
#define COL 5					/* number of columns in raw data array */
#define MAX_VAL 10000			/* maximum rows in array */
#define COLYEAR 0				/* array column containing year values */
#define COLMONTH 1				/* array column containing month values */
#define COLDATE 2				/* array column containing date values */
#define COLDAY 3				/* array column containing day values */
#define COLCOUNT 4				/* array column containing pedestrian count values*/
#define COLTOTALDAYS 2			/* array column containing total days */
#define COLAVGCOUNT 3			/* array column containing average count */
#define COLTOTALCOUNT 4		/* array column containing total count */
#define COLDAYSINMONTH 5		/* array column containing days in month */
#define DAYSINYEAR 365			/* days in a year */
#define DAYSINLEAPYEAR 366		/* days in a leap year */
#define MONTHSINYEAR 12		/* months in a year */
#define BIGMONTH 31				/* months with 31 days */
#define SMALLMONTH 30			/* months with 30 days */
#define FEBMONTH 28			/* days in non-leap year february */
#define FEBLEAP 29				/* days in february of a leap year */
#define LEAPCHECK 4				/* if divisable by this number, year is a leap year*/
#define PERCENTAGE 100 			/* value to convert ratio to percent */				
#define ROWDAYS 7				/* number of rows allocated for days of the week */
#define COLINFO 6				/*number of columns allocated for values in array*/

/* defines for month names, day names and misc names used for easier identification */
#define GRAND 1000	
#define JAN 1						
#define FEB 2						
#define MAR 3						
#define APR 4						
#define MAY 5						
#define JUN 6						
#define JUL 7							
#define AUG 8						
#define SEP 9						
#define OCT 10						
#define NOV 11						
#define DEC 12						
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THR 4
#define FRI 5
#define SAT 6
#define g0 0
#define g1 1
#define g2 2

/*Function prototypes */
void print_date(int year, int month, int day);
void printintdata( int com[MAX_VAL][COL], int line_count, int n);
void print_count(int count);
void days_count(int target, int target_leap, int *target_value);
void month_range(int startmonth, int endmonth, int endyear, int *monthtoday);
void count_average( int days, int count, double *averagecount);
void days_count(int target, int target_leap, int *target_value);
void daysinmonth(int month, int yearleap,  int *daysinmonth);
void groupsize(int line_count, int *glim0, int *glim1, int *glim2);
void stringstore(char *days[7], char *grp[3]);
void printstart(int day, int group);
void printstar(double avg);
void monthlyavgcount( int com[MAX_VAL][COL], int n);
void printmonthavg( double sum[MAX_VAL][COL + 1], int lim);
void printweekdaycount(int lim[3], int dayrec[ROWDAYS][COLINFO]);
void dayrecording(int lim[3], int com[MAX_VAL][COL]);
void printgroupdayinfo(int com[MAX_VAL][COL], int line_count, int n);
void calculateDayRange(int startdate, int startmonth, int startyear, 
	int enddate, int endmonth, int endyear, int *dayrange);


 /*Main program that runs the functions included */
int main(int argc, char *argv[]) {
	
	int com[MAX_VAL][COL] = {0}; 
	int new_line, n, line_count;
	char c;
	
	n = 0;
	new_line = 0;
	line_count = 0;
	
	/* Bypass the first two lines */
	while (scanf("%c",&c) == 1){
		if (new_line < 2 && c == '\n'){
			new_line += 1;
		}
		if (new_line == 2){
			break;
		}
	}
	/* Assignning the data into an array */
	while (scanf("%d%d%d%d%d",&com[n][COLYEAR], &com[n][COLMONTH], 
		&com[n][COLDATE], &com[n][COLDAY], 
		&com[n][COLCOUNT]) == 5){
		n += 1;	
		line_count += 1;  /* Counting the number of data lines */
	}	
	
	/* Call functions to print required data */
	/*Refer to each function for further comments on function purpose */
	printintdata(com, line_count, n);
	
	monthlyavgcount(com, n);
	
	printf("\n");
	
	printgroupdayinfo(com, line_count, n);
	
	return 0;
}

/* Function prints initial data processed */
void printintdata( int com[MAX_VAL][COL], int line_count, int n){
	
	int startdate, startmonth, startyear, enddate, endmonth, endyear;
	int dayrange;
	double ratio;
	
	dayrange = 0;
	
	/* Assignment of appropriate values */
	startdate = com[0][COLDATE];
	startmonth = com[0][COLMONTH];
	startyear = com[0][COLYEAR];
	enddate = com[n-1][COLDATE];
	endmonth = com[n-1][COLMONTH];
	endyear = com[n-1][COLYEAR];
	
	/* Print the processed data */
	/*Total data lines*/
	printf("S1: total data lines = %d days", line_count);
	printf("\n");
	
	/*First data line info*/
	printf("S1: first data line  = "); 
	print_date(startdate,startmonth,startyear); printf(", ");
	print_count(com[0][COLCOUNT]); printf("\n");
	
	/*Last data line info*/
	printf("S1 last data line    = ");
	print_date(enddate, endmonth, endyear); printf(", ");
	print_count(com[n-1][COLCOUNT]); printf("\n\n");
	
	/* Calculate and print day range */
	calculateDayRange(startdate, startmonth, startyear, enddate, endmonth, 
		endyear, &dayrange);
	printf("S2: range spanned    = %d days\n", dayrange);
	/* Calculate and print coverage ratio */ 
	ratio = (double)line_count/dayrange*PERCENTAGE;
	printf("S2: coverage ratio   = %4.1lf%%\n\n", ratio);
}

/*Function prints initial characters for weekday data*/
void printstart(int day, int group){
	
	char *weekdays[7], *grp[3];
	stringstore(weekdays, grp);
	printf("S4: %s, %s =", weekdays[day], grp[group]);
}

/*Function calculates the days in between two dates */
void calculateDayRange(int startdate, int startmonth, int startyear, 
	int enddate, int endmonth, int endyear, int *dayrange){
	
	int yeartoday, monthtoday, datetoday;
	int i, overflow_month;
	yeartoday = 0;
	monthtoday = 0;
	datetoday = 0;
	overflow_month = 0;
	
	/* Begin by calculating day differences */
	if (startdate > enddate) {
		endmonth -= 1;
		days_count(endmonth, endyear, &datetoday);
		enddate += datetoday;
	}
	*dayrange = enddate - startdate + 1;
	endmonth -= 1;
	

	/* Calculating differences in month */
	if (startmonth > endmonth) {
		endyear -= 1;
		overflow_month = endmonth;
		endmonth = 12;
	}
	
	 
	/* Calculate days in the months for the starting year*/
	month_range(startmonth, endmonth, startyear, &monthtoday);
	
	/* Calculate days in the months for the ending year*/
	if(overflow_month != 0){
	month_range(JAN, overflow_month, endyear, &monthtoday);
	}
	
	*dayrange += monthtoday;
	
	
	/* Calculate differences in years */
	i = 0;
	for (i = startyear; i < endyear; i++){
		if (i%LEAPCHECK == 0){
			yeartoday += DAYSINLEAPYEAR;
		}else{
			yeartoday += DAYSINYEAR;
		}
	}
	
	*dayrange += yeartoday;	
}

/*Function that returns number of days in a month */
void daysinmonth(int month, int yearleap,  int *daysinmonth){
	
	if (month == APR ||month== JUN || month == SEP || month == NOV){ 	
		*daysinmonth = SMALLMONTH; 
	
	} else if (month == FEB && yearleap%LEAPCHECK == 0){
		*daysinmonth = FEBLEAP;
	
	}else if (month == FEB && yearleap%LEAPCHECK != 0) {
		*daysinmonth = FEBMONTH;
	
	}else{
		*daysinmonth = BIGMONTH;
	}
}
	

/* Function that calculates days for specific months */
void days_count(int target, int target_leap, int *target_value){
	int days;
	
	daysinmonth(target, target_leap, &days);
	
	*target_value +=  days;
	
}

/* Function to calculate days in a range of months */
void month_range(int startmonth, int endmonth, int endyear, int *monthtoday){
	
	int i;
	i = 0;
	
	/*Function will not be required to run if there is no excessive months */
	if (endmonth == 0){
		return;
	}
	
	for (i = startmonth; i <=endmonth; i++){
		days_count(i,endyear,monthtoday);
	}
}

/* Function to print dates */
void print_date(int day, int month, int year){
	
	printf("%02d/%02d/%04d", day, month, year);
	
}

/*Function to print pedestrian count */
void print_count(int count){
	
	printf("%d people counted",count);
}

/*Function that counts average values */
void count_average( int days, int count, double *averagecount){
		*averagecount = (double)count/days;	
}

/*Function to calculate the ideal group size for each group */
void groupsize(int line_count, int *glim0, int *glim1, int *glim2){

	if (line_count%3 == 0){			/*All three groups will have equal data records */
		*glim0 = line_count/3;
		*glim2 = *glim0;
	}else if (line_count%3 == 1){		/*One group will have one more data record */
		*glim0 = line_count/3; 
		*glim1 = *glim0;
		*glim2 = *glim0+1;
	}else if (line_count%3 == 2){		/*One group will have one less data record */
		*glim0 = (line_count/3) + 1;
		*glim2 = *glim0 -1;
	}
	*glim1 = *glim0;
}

/*Function assigns the average pedestrian count by month to a second array */
void monthlyavgcount( int com[MAX_VAL][COL], int n){
	
	double sum[MAX_VAL][COL + 1] = {0};
	int k, i;

	k = 0;
	i = 0;
	
	/*Second array will start from the same year */
	sum[i][COLYEAR] = com[k][COLYEAR];		
	
	
	/*loop first runs through array lines of single year*/	
	while ((com[k][COLYEAR] == sum[i][COLYEAR]) ==1){ 			
		sum[i][COLMONTH] = com[k][COLMONTH];
		sum[i][COLTOTALDAYS]  = 0;
		sum[i][COLTOTALCOUNT] = 0;
		
		/*after which it runs through array lines of single month */
		while ((com[k][COLMONTH] == sum[i][COLMONTH]) ==1){		
			sum[i][COLTOTALDAYS] += 1;
			sum[i][COLTOTALCOUNT]+= com[k][COLCOUNT];
			k += 1;
		}
		
		/*Loop is broken when it reaches the end of the first array */
		if (sum[i][COLYEAR] == com[n-1][COLYEAR] && 
				sum[i][COLMONTH] == com[n-1][COLMONTH]){
			break;
		}
		
		i += 1;
		sum[i][COLYEAR] = com[k][COLYEAR];
	}
	
	printmonthavg(sum, i);			/*print the average calculated */
}

/*Function to print pedestrian count by month */
void printmonthavg( double sum[MAX_VAL][COL + 1], int lim){
	
	int no, days;
	double avg;
	no = 0;
	avg = 0.0;
	
	/*Loop prints the values for a different group every round */
	for (no = 0; no <=lim; no ++){
		count_average( sum[no][COLTOTALDAYS], sum[no][COLTOTALCOUNT], 
			&avg);
		sum[no][COLAVGCOUNT] = avg/GRAND;
		daysinmonth((int)sum[no][COLMONTH], (int)sum[no][COLYEAR], &days);
		sum[no][COLDAYSINMONTH] = days;	
		printf("S3: %02d/%04d %2d/%02d days covered, average count = %4.1lfk\n", 
			(int)sum[no][COLMONTH], (int)sum[no][COLYEAR], 
			(int)sum[no][COLTOTALDAYS], (int)days, sum[no][COLAVGCOUNT]);
	}
}

/*Function to print group data info and average pedestrian count by day of the week */
void printgroupdayinfo(int com[MAX_VAL][COL], int line_count, int n){
	
	int glim0 = 0, glim1 =0, glim2 = 0;
	
	/*group sizes are calculated and assigned to an array */
	groupsize(line_count, &glim0, &glim1, &glim2);
	
	int lim[3] = {glim0, glim1, glim2}; 
	int printlim, firstday, lastday;
	
	firstday = 0;
	lastday = lim[0] - 1;
	
	/*This section prints group data info */
	
	for (printlim = 0; printlim< 3; printlim++){
			
		printf("S4: group %d data, ",printlim);
		printf("%02d/%02d/%04d to ",com[firstday][COLDATE],
			com[firstday][COLMONTH], com[firstday][COLYEAR]);
		printf("%02d/%02d/%04d, ",com[lastday][COLDATE], 
			com[lastday][COLMONTH],com[lastday][COLYEAR]);
		printf("%d data records\n", lim[printlim]);
		
		firstday += lim[printlim] ;
		
		if (printlim == 1){
			lastday = n - 1;
		}else{
			lastday =  firstday + lim[printlim+1] - 1;
		}
		
		
	}
	printf("\n");
	
		
	dayrecording(lim, com);	/* This function prints the average by day of the week */
	
}

/*Function creates an array for data to be processed by day of the week */
void dayrecording(int lim[3], int com[MAX_VAL][COL]){

	int dayrec[ROWDAYS][COLINFO] = {0};
	int groupbox = 0;
	
	int k, limfor, limsize, limstart, dayofweek = 0;
	k= 0;
	limfor = 0;
	limstart = 0;
	
	
	limsize = lim[limfor];
	
	/*Loop sorts data from first array by day to be added to a new array  */
	while(groupbox < 6){
		for (k = limstart; k<limsize; k++){
			if (com[k][COLDAY] == 7){
				dayrec[SAT][groupbox] += com[k][COLCOUNT];
				dayrec[SAT][groupbox+1] += 1;
			}else{
				dayofweek = com[k][COLDAY] - 1;
				dayrec[dayofweek][groupbox] += com[k][COLCOUNT];
				dayrec[dayofweek][groupbox+1] += 1;
			}
		}
		
		limfor += 1;
		limstart += lim[limfor];
		limsize += lim[limfor];
		groupbox += 2;
	}
	
	printweekdaycount(lim, dayrec); 		/*Values are then printed*/
}

/*Prints average counts with simple bar chart showing the
average pedestrians each day of the week */
void printweekdaycount(int lim[3], int dayrec[ROWDAYS][COLINFO]){
	int no = 0, weekday =0; 
	double avg = 0.0;
	int groupbox = 0;
	
	
	for (weekday = 0; weekday < ROWDAYS; weekday++){
		groupbox = 0;
		for (	no = 0; no <= g2; no ++){
			printstart(weekday, no);
			double totalnum = dayrec[weekday][groupbox];
			double totaldays = dayrec[weekday][groupbox + 1];
			avg = totalnum/totaldays ;
			printf(" %4.1lfk |", avg/GRAND);
			printstar(avg); 				/*bar chart function */
			groupbox += 2;
		}
		
		printf("\n");
		
	}
}

/*Function that stores strings needed for easier use*/
void stringstore(char *days[7], char *grp[3]){
	
	days[MON] = "Mon";
	days[TUE] = "Tue";
	days[WED] = "Wed";
	days[THR] = "Thu";
	days[FRI] = "Fri";
	days[SAT] = "Sat";
	days[SUN] = "Sun";
	
	grp[g0] = "g0";
	grp[g1] = "g1";
	grp[g2] = "g2";
	
}

/*Function prints a simple bar chart in the form of horizontal lines */
void printstar(double avg){
	int i, avgint;
	i = 0;
	
	/*Average values are divided by a thousand to count how many stars are needed */
	
	/*Setting a guard to avoid truncation to 0, and for proper rounding of numbers */
	if((int)avg%GRAND >= 500){
		avgint = ((int)avg/GRAND)+1;		/*number rounds up */
	}else{
		avgint = (int)avg/GRAND;			/*number rounds down */
	}
	
	/*For every avgint, a star is printed, representing a thousand pedestrians */
	for (i=0; i <= avgint; i++){
		printf("*");
	}
	
	printf("\n");
}

/* Programming is Fun */

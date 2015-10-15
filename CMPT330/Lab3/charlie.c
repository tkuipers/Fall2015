//
//  ChocolateFactory.h
//  ChocolateFactory
//  CMPT 330 -- Fall 2013
//
//  Tyler Kuipers
//  October 14, 2015
//
#include "ChocolateFactory.h"

candy_struct* buffer = NULL;
int bufferPlace = -1;
int buffLength = 0;

//check if the buffer is empty
int emptyBuffer() {
	if (bufferPlace == -1) {
		return 1;
	}
	return 0;
}

//remove the last inputted candy into the buffer
candy_struct removeCandy() {
	return buffer[bufferPlace--];
}

//insert a candy into the buffer
void insertCandy(candy_struct* data) {
	++bufferPlace;
	buffer[bufferPlace] = *data;
}

//check for a full buffer
int fullBuffer() {
	if (bufferPlace == buffLength - 1) {
		return 1; // true
	}
	return 0; // false
}

//print the usage of the program
void printUsage(){
		printf("USAGE: ./ChocolateFactory o c a n t\n");
		printf("\to: the number of oompa loompa threads.  Must be greater than 0.\n");
		printf("\tc: the number of children threads.  Must be greater than 0.\n");
		printf("\ta: the size of the assembly line.  Must be greater than 0.\n");
		printf("\tn: the number of candies per box.  Must be greater than 0.\n");
		printf("\tt: the number of candies each oompa loompa will produce.  Must be greater than 0.\n");
		exit(EXIT_FAILURE);
}

int main (int argc, char* argv[]) {
	const char *COLORS[] = {"AliceBlue","AntiqueWhite","Aqua","Aquamarine","Azure","Beige","Bisque","Black","BlanchedAlmond","Blue","BlueViolet","Brown","BurlyWood","CadetBlue","Chartreuse","Chocolate","Coral","CornflowerBlue","Cornsilk","Crimson","Cyan","DarkBlue","DarkCyan","DarkGodenRod","DarkGray","DarkGrey","DarkGreen","DarkKhaki","DarkMagenta","DarkOliveGreen","Darkorange","DarkOrchid","DarkRed","DarkSalmon","DarkSeaGreen","DarkSlateBlue","DarkSlateGray","DarkSlateGrey","DarkTurquoise","DarkViolet","DeepPink","DeepSkyBlue","DimGray","DimGrey","DodgerBlue","FireBrick","FloralWhite","ForestGreen","Fuchsia","Gainsboro","GhostWhite","God","GodenRod","Gray","Grey","Green","GreenYellow","HoneyDew","HotPink","IndianRed","Indigo","Ivory","Khaki","Lavender","LavenderBlush","LawnGreen","LemonChiffon","LightBlue","LightCoral","LightCyan","LightGodenRodYellow","LightGray","LightGrey","LightGreen","LightPink","LightSalmon","LightSeaGreen","LightSkyBlue","LightSlateGray","LightSlateGrey","LightSteelBlue","LightYellow","Lime","LimeGreen","Linen","Magenta","Maroon","MediumAquaMarine","MediumBlue","MediumOrchid","MediumPurple","MediumSeaGreen","MediumSlateBlue","MediumSpringGreen","MediumTurquoise","MediumVioletRed","MidnightBlue","MintCream","MistyRose","Moccasin","NavajoWhite","Navy","OdLace","Olive","OliveDrab","Orange","OrangeRed","Orchid","PaleGodenRod","PaleGreen","PaleTurquoise","PaleVioletRed","PapayaWhip","PeachPuff","Peru","Pink","Plum","PowderBlue","Purple","Red","RosyBrown","RoyalBlue","SaddleBrown","Salmon","SandyBrown","SeaGreen","SeaShell","Sienna","Silver","SkyBlue","SlateBlue","SlateGray","SlateGrey","Snow","SpringGreen","SteelBlue","Tan","Teal","Thistle","Tomato","Turquoise","Violet","Wheat","White","WhiteSmoke","Yellow","YellowGreen"};
 	const int MAXCOLORS=147;
 	srand(time(NULL));
 	//incorrect Usage
	if (argc != 6) {
		printUsage();
	}
	int oompaCount = atoi(argv[1]);
	int childCount = atoi(argv[2]);
	int bufferSize = atoi(argv[3]);
	int boxCapacity = atoi(argv[4]);
	int productCount = atoi(argv[5]);
	//Incorrect Usage
	if(atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || atoi(argv[3]) <= 0 || atoi(argv[4]) <= 0 || atoi(argv[5]) <= 0){
		printUsage();
	}
	//allocate space for buffer
	buffer = malloc(bufferSize * sizeof(candy_struct));
	buffLength = bufferSize;

	//initiate mutex and conditions for running the program
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condC, NULL);
	pthread_cond_init(&condO, NULL);

	//spawn oompa loompas
	pthread_t *oompaThreads = malloc(oompaCount * sizeof(pthread_t));
	for (int i = 0; i < oompaCount; ++i) {
		candy_struct *info = malloc(sizeof(candy_struct));
		info->num = productCount;
		//randomely select from colors
		info->color = (char *)COLORS[rand() % MAXCOLORS];
		//spawn the actual oompa
		if (pthread_create(&(oompaThreads[i]), NULL, oompa, info)) {
			printf("Error creating Oompa Loompa\n");
			return 1;
		}
	}

	//spawn oompa loompa children
	pthread_t *childThreads = malloc(childCount * sizeof(pthread_t));
	for (int i = 0; i < childCount; ++i) {
		//allocate space for sending information
		candy_struct *boxSize = malloc(sizeof(candy_struct));
		boxSize->color = NULL;
		//input the box capacity
		boxSize->num = boxCapacity;
		//actually make the thread
		if (pthread_create(&(childThreads[i]), NULL, oompaChild, boxSize)) {
			printf("Error creating oompaChild\n");
			return 1;
		}
	}
	//join the threads
	for (int i = 0; i < oompaCount; ++i) {
		pthread_join(oompaThreads[i], NULL);
	}
	for (int i = 0; i < childCount; ++i) {
		pthread_kill(childThreads[i], 2);
		pthread_join(childThreads[i], NULL);
	}

	//cleanup
	free(childThreads);
	free(oompaThreads);
	free(buffer);
	exit(EXIT_SUCCESS);
}
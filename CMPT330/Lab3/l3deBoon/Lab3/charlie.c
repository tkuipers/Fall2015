//
//  charlie.c
//  ChocolateFactory
//  CMPT 330 -- Fall 2013
//
//  Tyler deBoon 120030
//  October 7, 2015
//

#include "ChocolateFactory.h"

candy_t* buffer = NULL;
int bufferIndex = -1;
int bufferLength = 0;

int isFull() {
	if (bufferIndex == bufferLength - 1) {
		// printf("BufferIsFull\n");
		return 1; // true
	}
	return 0; // false
}

int isEmpty() {
	if (bufferIndex == -1) {
		// printf("BufferIsEmpty\n");
		return 1;
	}
	return 0;
}

void insertCandy(candy_t* data) {
	// printf("Insert\n");
	// printf("%s\n", data->color);
	// printf("%d\n", data->num);
	++bufferIndex;
	buffer[bufferIndex] = *data;
	// printf("%d\n", bufferIndex);
}

candy_t removeCandy() {
	// printf("%d\n", bufferIndex);
	// printf("Remove Candy\n");
	return buffer[bufferIndex--];
}

int main (int argc, char* argv[]) {
	// color stuff
	const char *COLORS[] = {"AliceBlue","AntiqueWhite","Aqua","Aquamarine","Azure","Beige","Bisque","Black","BlanchedAlmond","Blue","BlueViolet","Brown","BurlyWood","CadetBlue","Chartreuse","Chocolate","Coral","CornflowerBlue","Cornsilk","Crimson","Cyan","DarkBlue","DarkCyan","DarkGodenRod","DarkGray","DarkGrey","DarkGreen","DarkKhaki","DarkMagenta","DarkOliveGreen","Darkorange","DarkOrchid","DarkRed","DarkSalmon","DarkSeaGreen","DarkSlateBlue","DarkSlateGray","DarkSlateGrey","DarkTurquoise","DarkViolet","DeepPink","DeepSkyBlue","DimGray","DimGrey","DodgerBlue","FireBrick","FloralWhite","ForestGreen","Fuchsia","Gainsboro","GhostWhite","God","GodenRod","Gray","Grey","Green","GreenYellow","HoneyDew","HotPink","IndianRed","Indigo","Ivory","Khaki","Lavender","LavenderBlush","LawnGreen","LemonChiffon","LightBlue","LightCoral","LightCyan","LightGodenRodYellow","LightGray","LightGrey","LightGreen","LightPink","LightSalmon","LightSeaGreen","LightSkyBlue","LightSlateGray","LightSlateGrey","LightSteelBlue","LightYellow","Lime","LimeGreen","Linen","Magenta","Maroon","MediumAquaMarine","MediumBlue","MediumOrchid","MediumPurple","MediumSeaGreen","MediumSlateBlue","MediumSpringGreen","MediumTurquoise","MediumVioletRed","MidnightBlue","MintCream","MistyRose","Moccasin","NavajoWhite","Navy","OdLace","Olive","OliveDrab","Orange","OrangeRed","Orchid","PaleGodenRod","PaleGreen","PaleTurquoise","PaleVioletRed","PapayaWhip","PeachPuff","Peru","Pink","Plum","PowderBlue","Purple","Red","RosyBrown","RoyalBlue","SaddleBrown","Salmon","SandyBrown","SeaGreen","SeaShell","Sienna","Silver","SkyBlue","SlateBlue","SlateGray","SlateGrey","Snow","SpringGreen","SteelBlue","Tan","Teal","Thistle","Tomato","Turquoise","Violet","Wheat","White","WhiteSmoke","Yellow","YellowGreen"};
 	const int MAXCOLORS=147;
 	srand(time(NULL));
	// handle input length error
	if (argc != 6) {
		printf("USAGE: ./ChocolateFactory o c a n t\n");
		printf("\to: the number of oompa loompa threads\n");
		printf("\tc: the number of children threads\n");
		printf("\ta: the size of the assembly line\n");
		printf("\tn: the number of candies per box\n");
		printf("\tt: the number of candies each oompa loompa will produce\n");
		exit(EXIT_SUCCESS);
	}
	// get inputs into usable variables
	int oompaNum = atoi(argv[1]);
	int childNum = atoi(argv[2]);
	int bufferSize = atoi(argv[3]);
	int candiesPerBox = atoi(argv[4]);
	int productionNum = atoi(argv[5]);
	printf("INPUT:\n OompaNum: %d\n childNum: %d\n bufferSize: %d\n candiesPerBox: %d\n productionNum: %d\n", oompaNum, childNum, bufferSize, candiesPerBox, productionNum);
	// do some variable checking -bufferSize cannot be zero -nothing can be negative



	// buffer setup
	buffer = malloc(bufferSize * sizeof(candy_t));
	bufferLength = bufferSize;
	// thread conditions setup
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condC, NULL);
	pthread_cond_init(&condO, NULL);
	// create threads
	pthread_t *oompaThreads = malloc(oompaNum * sizeof(pthread_t));
	for (int i = 0; i < oompaNum; ++i) {
		// printf("Create Oompa Loompa Thread\n");
		// create struct for passing data to the thread
		candy_t *info = malloc(sizeof(candy_t));
		info->color = (char *)COLORS[rand() % MAXCOLORS];										// this needs to be randomized
		info->num = productionNum;
		if (pthread_create(&(oompaThreads[i]), NULL, oompaLoompa, info)) {
			printf("Error creating Oompa Loompa\n");
			return 1;
		}
	}
	// end point for all the oompaThreads
	// create the children threads
	pthread_t *childThreads = malloc(childNum * sizeof(pthread_t));
	for (int i = 0; i < childNum; ++i) {
		// printf("Create Child Thread\n");
		candy_t *info = malloc(sizeof(candy_t));
		info->color = "";
		info->num = candiesPerBox;
		if (pthread_create(&(childThreads[i]), NULL, child, info)) {
			printf("Error creating Child\n");
			return 1;
		}
	}
	for (int i = 0; i < oompaNum; ++i) {
		pthread_join(oompaThreads[i], NULL);
		// printf("Loompa Left.\n");
	}
	if (isEmpty()) {
		printf("Empty\n");
		printf("%d\n", bufferSize);
		printf("%d\n", bufferIndex);
	}
	else {
		printf("Not Empty\n");
	}
	// printf("Kill the children\n");
	// kill all the children -pretty dark
	for (int i = 0; i < childNum; ++i) {
		pthread_kill(childThreads[i], SIGALRM);
		pthread_join(childThreads[i], NULL);
		// printf("Connected Kids\n");
	}
	free(childThreads);
	free(oompaThreads);
	free(buffer);
	exit(EXIT_SUCCESS);
}
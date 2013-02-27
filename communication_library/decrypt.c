/*
 * this takes care of the converting a string to struct and converting a struct to char* and pass it to CRC in packets of 64 bits.
 *
 * message will be in the form.
 * $Mode,Data1,Data2,Data3
 */


#define BreakMode B
#define StandStill S
#define ExternalControl E
#define YawControl Y
#define PitchControl P
#define PositionControl U
#define Surface S
#define Configuration C
#define Normal	N

char** Tokenize(char *msg){
	int lenght= strlen(msg);
//int length = sizeof(msg)/sizeof(msg[0]);
	int i=0;
	/*for(i=0;i<length;i++){
			if(msg[i]==','){
					Tokens++;
			}	
	}
	*/
	char tokens[MAX_PARAMETERS][MAXPARAMETERSIZE];	


	int seek=0;
	int tokenNo =0;
	for(i=0;i<length;i++){
		if(msg[i]==','){
			tokens[tokenNo][seek] = '
			seek=0;
			tokenNo++;
		}	
		else{
				tokens[tokenNo][seek]=msg[i];
				seek++;	
		}




void* decrypt(char* msg){
	char mode = msg[0];
	switch (mode){
			case BreakMode : 
					break;
			case StandStill :
					break;
			case ExternalControl :
					break;

			case YawControl :
					break;

			case PitchControl :
					break;

			case PositionControl :
					break;
			case Surface :
					break;
			case Configuration :
					break;
			case NormalMode :
					break;

	}










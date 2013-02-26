
/*
 * all message structs will exist here.
 */

/* messages include 
 * imu 
 * pressure
 * etc
 */





struct ImuMsg{
		char mode;
		int yaw;
		int roll;
		int pitch;
};

struct PressureMsg{
		char mode;
		int depth;
};




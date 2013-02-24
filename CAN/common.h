#ifndef COMMON_H
#define COMMON_H

#define YES 1
#define NO 0

void uart_init1(void);
void uart_init2(void);
void adc_init(void);
void pressure(void);
void tare(void);
unsigned char uart_rx(void);
unsigned char uart_rx(void);  
void uart_tx( unsigned char data );
void uart_tx( unsigned char data );
void imu_extract(unsigned char rec);
void thrusters_init(void);
void yaw_control();
void depth_control();
void pitch_control();
void update_pid_params();
void test();
void set_motor_speeds();
void capture_cam();
void gate_pass_1_control();

#define SBC 'S'
#define IMU 'I'	
#define GATE_THRESH_LOW -60
#define GATE_THRESH_HIGH 60
#define FINAL_GATE_THRESH_LOW -120
#define FINAL_GATE_THRESH_HIGH 120
#define FRAME_START 10
#define FRAME_SET 5

#define SEARCH_FOR_GATE_PASS 1
#define GO_THROUGH_GATE_PASS 2
#define SEARCH_FOR_PLANK 3
#define FOLLOW_PLANK 4
#define ALLIGN_PLANK 5
#define SEARCH_FOR_BUOY_1 6
#define HIT_BUOY_1 7
#define RETRACT 8
#define SEARCH_FOR_BUOY_2 9
#define HIT_BUOY_2 10
#define COMPLETE 11

struct pid_param {
float Kp;
float Ki;
float Kd;
};

#endif

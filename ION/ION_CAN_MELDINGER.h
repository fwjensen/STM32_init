// ION CAN Messages v8 - 2015-07-07

#define	CAN_ERR_HV_SHUTDOWN                             0x000
#define	CAN_ERR_IMD                                     0x001
#define	CAN_ERR_BMS                                     0x002
#define	CAN_ERR_OVERTEMP                                0x003
#define	CAN_ERR_OVERCURRENT                             0x004
#define	CAN_MSG_PRECHARGE                               0x010
#define	CAN_MSG_CURRENT_SENSOR_CALIBRATE                0x012
#define	CAN_MSG_CURRENT SENSOR_CALIBRATION_COMPLETE     0x013
#define	CAN_MSG_LV_SENSOR                               0x015
#define	CAN_MSG_POWER                                   0x016

#define	CAN_MSG_PEDAL_THROTTLE                          0x100
#define	CAN_MSG_MOTOR_LEFT_RX                           0x181
#define	CAN_MSG_MOTOR_RIGHT_RX                          0x182
#define	CAN_ERR_PEDAL_IMPLAUSIBILITY                    0x200
#define	CAN_MSG_MOTOR_LEFT_TX                           0x201
#define	CAN_MSG_MOTOR_RIGHT_TX                          0x202

#define	CAN_ERR_PEDALS_IMPLAUSIBILITY                   0x300
#define	CAN_MSG_PEDALS                                  0x310
#define	CAN_MSG_STEERING                                0x311
#define	CAN_MSG_PEDALS_CALIBRATE                        0x320
#define	CAN_MSG_PEDALS_CALIBRATION_COMPLETE             0x321

#define	CAN_MSG_USER_START                              0x400
#define	CAN_MSG_USER_STOP                               0x401
#define	CAN_ERR_STARTUP                                 0x440
#define	CAN_MSG_WHEEL_RPM_FRONT                         0x450
#define	CAN_MSG_SPEED                                   0x460

#define	CAN_MSG_WATCHDOG_REQUEST                        0x500
#define	CAN_MSG_WATCHDOG_REPLY_PEDALS                   0x501
#define	CAN_MSG_WATCHDOG_REPLY_ECU                      0x502
#define	CAN_MSG_WATCHDOG_REPLY_DASHBOARD                0x503

#define	CAN_MSG_HV_SENSOR                               0x600
#define	CAN_MSG_CURRENT_SENSOR                          0x601

#define	CAN_MSG_BMS_PRODUCT                             0x620
#define	CAN_MSG_BMS_REVISION                            0x621
#define	CAN_MSG_BMS_FLAGS                               0x622
#define	CAN_MSG_BMS_VOLTAGE                             0x623
#define	CAN_MSG_BMS_CURRENT                             0x624
#define	CAN_MSG_BMS_ENERGY                              0x625
#define	CAN_MSG_BMS_CHARGE                              0x626
#define	CAN_MSG_BMS_TEMP                                0x627
#define	CAN_MSG_BMS_RESISTANCE                          0x628

/*----------------------------------------------------------
#define FLT_BSPD 	0x00;
#define FLT_IMD 	0x01;
#define FLT_BMS 	0x02
#define FLT_OVERTEMP 0x03;
#define PRECHARGE 0x04;
#define AIR_STATUS 0x05;
#define CURRENT_SENSOR 0x06;
#define STOP 0x07;
#define TORQUE_RIGHT 0x10;
#define TORQUE_LEFT 0x11;
#define BRAKE 0x12;
#define STEERING_ANGLE 0x13;
#define POWER 0x14;
#define PEDAL_INTEGRITY 0x15;
#define STOP 0x16;
#define HV_SENSOR 0x17;
#define LV_SENSOR 0x18;
#define SHUTDOWN_CIRCUIT_OPEN 0x19;
#define RTDS 0x20;
#define RUN 0x21;
#define TORQUE_FINAL_RIGHT 0x22;
#define TORQUE_FINAL_LEFT 0x23 
#define WHEEL_SPEED_FR 0x25;
#define WHEEL_SPEED_FL 0x26;
#define CURRENT_SENSOR_CALIBRATION 0x30
#define CALIBRATION_DONE 0x31;
#define READY_TO_DRIVE 0x32;
------------------------------------------------------------
*/
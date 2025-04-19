 #ifndef RANGE_SENSOR_H
 #define RANGE_SENSOR_H
 
 #define PING_PIN 5
 #define ECHO_PIN 6
 
 #define MAX_RANGE_CM 400     
 #define MIN_RANGE_CM 2       
 #define SOUND_VELOCITY 0.034 
 
 // Function prototypes
 void init_range_sensor(void);
 float get_range(void);
 
 #endif /* RANGE_SENSOR_H */
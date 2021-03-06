#ifndef DATA_STREAM_H_
#define DATA_STREAM_H_

#include <stdio.h>

#define START_TOKEN     0x55

typedef struct {
    uint8_t start_token;
    uint16_t dacVal;
    uint16_t opampVal;
    uint8_t end_token;
    uint8_t data_available;
}data_visualizer;

data_visualizer data_stream;

void DS_sendData(void);

void myUSART_3_ISR(void);


#endif /* DATA_STREAM_H_ */
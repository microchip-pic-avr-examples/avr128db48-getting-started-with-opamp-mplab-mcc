#include "data_stream.h"
#include "mcc_generated_files/include/usart3.h"
#include <string.h>

char TX_buffer[sizeof(data_stream)];

void DS_sendData(void) {
    memcpy(TX_buffer, &data_stream, sizeof(data_stream));

    USART3.CTRLA =  USART_DREIE_bm;     /* Enable Transmit Complete interrupt*/
    USART3.TXDATAL = data_stream.start_token;  /* Send the first byte of the buffer*/
                                               /* once the first byte is transmitted the ISR will kick in*/
}

void myUSART_3_ISR(void)
{
    volatile static uint8_t tx_count = 1;

    if (data_stream.data_available) {

        if (tx_count < (sizeof(TX_buffer) - 1)) {
            USART3.TXDATAL = TX_buffer[tx_count];
            tx_count++;
        }
        else{
            
            tx_count = 1;
            data_stream.data_available = 0;
            USART3.CTRLA &=  ~USART_DREIE_bm;   /* Disable Transmit Complete interrupt*/
                                                /* No more bytes available*/
        }
    }
}
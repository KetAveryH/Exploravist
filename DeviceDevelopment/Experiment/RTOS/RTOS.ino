#include "freertos/ringbuf.h"
static char tx_item[] = "test_item";

void app_main(void) 
{

  //Create ring buffer
    RingbufHandle_t buf_handle;
    buf_handle = xRingbufferCreate(1028, RINGBUF_TYPE_NOSPLIT);
    if (buf_handle == NULL) {
        printf("Failed to create ring buffer\n");
    }

    //Send an item
    UBaseType_t res =  xRingbufferSend(buf_handle, tx_item, sizeof(tx_item), pdMS_TO_TICKS(1000));
    if (res != pdTRUE) {
        printf("Failed to send item\n");
    }

}
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include "mdaq_can.h"

#define RX_FIFO_0           (0)

#define SHARED_MEM_ADDR     (0xa0010000)  /* DO not modify !!! */
#define SHARED_MEM_SZ       (0x100000 - 0x10000)  /* ~1MB */

void dump_tx_frame(canfd_tx_frame_t *f)
{
    int i;
    System_printf("ID:%d  RTR:%d  XTD:%d  ESI:%d  DLC:%d  BRS:%d  FDF:%d  EFC:%d  MM:%d\n",
                  f->header.ID,
                  f->header.RTR,
                  f->header.XTD,
                  f->header.ESI,
                  f->header.DLC,
                  f->header.BRS,
                  f->header.FDF,
                  f->header.EFC,
                  f->header.MM);
    for(i = 0; i < 64 / 8; i++)
    {
        System_printf("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                      f->data[(8*i)+0],
                      f->data[(8*i)+1],
                      f->data[(8*i)+2],
                      f->data[(8*i)+3],
                      f->data[(8*i)+4],
                      f->data[(8*i)+5],
                      f->data[(8*i)+6],
                      f->data[(8*i)+7]);
    }
}

void repeater_task(UArg arg0, UArg arg1)
{
    uint8_t result;
    uint8_t data[64];
    can_rx_header_t rx_header = {0};
    can_tx_header_t tx_header = {0};

    canfd_tx_frame_t *tx = (canfd_tx_frame_t *)SHARED_MEM_ADDR;

    System_printf("Starting mdaq_can_repeater...\n\n");

//    dump_tx_frame(&tx[0]);
//    dump_tx_frame(&tx[1]);
    mdaq_dio_init();
    mdaq_can_open(CAN1, 500000, 2000000);
#if 0
    mdaq_can_enable_termination(CAN1, 1);

    do
    {
        /* non blocking read */
        result = mdaq_can_read_fifo(CAN1, RX_FIFO_0, &rx_header, data);
        if(result > 0)
        {
            /* change ID to lower to make high prio message */
            tx_header.ID = rx_header.ID-1;
            tx_header.RTR = rx_header.RTR;
            tx_header.XTD = rx_header.XTD;
            tx_header.DLC = rx_header.DLC;
            tx_header.ESI = rx_header.ESI;
            tx_header.BRS = rx_header.BRS;
            tx_header.FDF = rx_header.FDF;
            tx_header.EFC = 0u;
            tx_header.MM  = 0u;

            /* modify data here */

            mdaq_can_write_buffer(CAN1, 0, &tx_header, data);
            mdaq_can_transmit_buffer(CAN1, 0);
        }
    }while(1);

    volatile int count = 0;
    volatile int delay;
    while(count < 10000000)
    {
        mdaq_can_write_buffer(CAN2, 0, &tx->header, tx->data);
        mdaq_can_transmit_buffer(CAN2, 0);
        for(delay = 0; delay < 10000; delay++);
        count++;
    }

#endif
}

Int main(Int argc, char* argv[])
{
    Task_Params params;


    Task_Params_init(&params);
    params.instance->name = "can_repeater";
    Task_create(repeater_task, &params, NULL);

    BIOS_start();

    return (0);
}

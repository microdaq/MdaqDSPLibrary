#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include <c6x.h>

#include "mdaq_can.h"
#include "mdaq_dio.h"
#include "mdaq_pru.h"
#include "mdaq_mem.h"

#define SENT_ENABLED             (0x47)
#define SENT_DISABLED            (0xaf)

#define ACCEL_VALUE_REG          (0x100)
#define STATUS_REG               (0x104)

static void accelerate_enable(void)
{
    uint8_t status = SENT_ENABLED;
    mdaq_pru_write(STATUS_REG, &status, sizeof(status));
}

static uint8_t accelerate_status(void)
{
    uint8_t status = 0;
    mdaq_pru_read(STATUS_REG, &status, sizeof(status));
    return status;
}

static void accelerate_set_value(uint16_t value)
{
    mdaq_pru_write(ACCEL_VALUE_REG, (uint8_t *)&value, sizeof(uint16_t));
}

void accelerate_task(UArg arg0, UArg arg1)
{
    if(accelerate_status() != SENT_ENABLED)
    {
        mdaq_dio_init();

        /* outputs for SENT generation */
        mdaq_dio_dir(DIO1, DIO_OUTPUT);
        mdaq_dio_dir(DIO4, DIO_OUTPUT);
        mdaq_dio_dir(DIO3, DIO_OUTPUT);

        /* input for sent start sync */
        mdaq_dio_dir(DIO3, DIO_INPUT);

        /* configure DIO functions */
        mdaq_dio_func(DIO1, HS_DO_FUNC);
        mdaq_dio_func(DIO4, HS_DO_FUNC);

        mdaq_dio_func(DIO3, HS_DI_FUNC);
    }

    accelerate_enable();
    accelerate_set_value(0x132);
}

Int main(Int argc, char* argv[])
{
    Task_Params params;

    Task_Params_init(&params);
    params.instance->name = "accelerate";
    Task_create(accelerate_task, &params, NULL);

    BIOS_start();

    return (0);
}

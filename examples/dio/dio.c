#include "mdaq_dio.h"
#include "mdaq_counter.h"

void DIO_test_init(void)
{
    uint8_t dio;
    mdaq_dio_init();

    /* set DIO function and direction for every DIO channel */
    for(dio = DIO1; dio <= DIO24; dio++)
    {
        mdaq_dio_func(dio, DIO_FUNC);
        mdaq_dio_dir(dio, DIO_OUTPUT);
    }
}

void DIO_test(void)
{
    uint8_t dio;
    static uint8_t state = 0;

    /* toggle all DIO channels */ 
    for(dio = DIO1; dio <= DIO24; dio++)
        mdaq_dio_write(dio, state);

    /* if F1 pressed blink D1 and D2 */ 
    if(mdaq_dio_read(F1))
    {
        mdaq_dio_write(D1, state);
        mdaq_dio_write(D2, state);
        mdaq_dio_write(SYS, 0);
    }
    else
    {
        mdaq_dio_write(SYS, 1);
    }

    state = ~state;
}

int main()
{
    DIO_test_init();

    while(1)
    {
        DIO_test();
        /* use usleep delay function from mdaq_counter module */ 
        mdaq_usleep(100000);
    }
}

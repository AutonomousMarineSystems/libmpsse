#include <stdio.h>
#include <stdlib.h>
#include <mpsse.h>

int main(void)
{
    struct mpsse_context *io = NULL;
    int i = 0, retval = EXIT_FAILURE;

    uint8_t bus = 6;
    uint8_t ports[] = { 11, 7, 4 };
    int ports_size = 3;
    
    io = OpenPorts(0x0403, 0x6010, GPIO, 0, MSB, IFACE_A, bus, ports, ports_size);
    
    if(io && io->open)
    {
        for(i=0; i<10; i++)
        {
            PinHigh(io, GPIOH7);
            printf("GPIOH7 State: %d\n", PinState(io, GPIOH7, -1));
            sleep(1);
            
            PinLow(io, GPIOH7);
            printf("GPIOH7 State: %d\n", PinState(io, GPIOH7, -1));
            sleep(1);
        }
	
        retval = EXIT_SUCCESS;
    }
    else
    {
        printf("Failed to open MPSSE: %s\n", ErrorString(io));
    }
    
    Close(io);
    
    return retval;
}

#include "header_uart_hc06.h"

#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

int adcRead;

void main(void) {

init_uart();

//////////////////////////
// This array is used for storing the data read from the ADC FIFO. It
	    // must be as large as the FIFO for the sequencer in use.  This example
	    // uses sequence 3 which has a FIFO depth of 1.  If another sequence
	    // was used with a deeper FIFO, then the array size must be changed.
	    //
	    uint32_t ADCValues[1];

	    //
	    // The ADC0 peripheral must be enabled for use.
	    //
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	        GPIOPinTypeADC(GPIO_PORTE_BASE,
	        			   GPIO_PIN_2);

	    SysCtlDelay(3);

	    //
	    // Enable sample sequence 3 with a processor signal trigger.  Sequence 3
	    // will do a single sample when the processor sends a singal to start the
	    // conversion.  Each ADC module has 4 programmable sequences, sequence 0
	    // to sequence 3.  This example is arbitrarily using sequence 3.
	    //
	    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);



	    // Config. GPIO Pin to be used on PE3, channel 0




	    //
	    // Configure step 0 on sequence 3.  Sample the temperature sensor
	    // (ADC_CTL_TS) and configure the interrupt flag (ADC_CTL_IE) to be set
	    // when the sample is done.  Tell the ADC logic that this is the last
	    // conversion on sequence 3 (ADC_CTL_END).  Sequence 3 has only one
	    // programmable step.  Sequence 1 and 2 have 4 steps, and sequence 0 has
	    // 8 programmable steps.  Since we are only doing a single conversion using
	    // sequence 3 we will only configure step 0.  For more information on the
	    // ADC sequences and steps, reference the datasheet.
	    //
	    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1  | ADC_CTL_IE |
	                             ADC_CTL_END);

	    //
	    // Since sample sequence 3 is now configured, it must be enabled.
	    //
	    ADCSequenceEnable(ADC0_BASE, 3);

	    //
	    // Clear the interrupt status flag.  This is done to make sure the
	    // interrupt flag is cleared before we sample.
	    //
	    ADCIntClear(ADC0_BASE, 3);

	    //
	    // Sample the temperature sensor forever.  Display the value on the
	    // console.
	    //
	    while(1)
	    {
	        //
	        // Trigger the ADC conversion.
	        //
	        ADCProcessorTrigger(ADC0_BASE, 3);

	        //
	        // Wait for conversion to be completed.
	        //
	        while(!ADCIntStatus(ADC0_BASE, 3, false))
	        {
	        }

	        //
	        // Clear the ADC interrupt flag.
	        //
	        ADCIntClear(ADC0_BASE, 3);

	        //
	        // Read ADC Value.
	        //
	        ADCSequenceDataGet(ADC0_BASE, 3, ADCValues);
	        adcRead = ADCValues[0];
	        //


	        //
	        // This function provides a means of generating a constant length
	        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
	        // 250ms arbitrarily.
	        //
	        SysCtlDelay(80000000 / 12);
	    }


}

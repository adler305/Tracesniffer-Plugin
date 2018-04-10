# Tracesniffer-Plugin
The Tracesniffer-Plugin is the part of Tracesniffer which has to be on the traced system. We tried to make it as compact as possible, and as general as it can be, so its lightweight and can work on any system.
In combination with the [Tracesniffer-Frontend](https://github.com/Penlane/Tracesniffer-GUI) it provides a basic tool for tracing FreeRTOS systems. 

It is not intended and wont be able to replace professional tools like [Tracealyzer from Percepio](https://percepio.com/).

For the plugin itself look under Source.
For the implement instructions look under Source and further down in this readme.
For examples (which we hopefully can provide more and more of over time) look under Examples.


**Instructions on implementing the TraceSniffer-Plugin**

1.: Include the tracesniffing.h into your FreeRTOSConfig.h.

2.: Implement a function for sending a byte over UART via interrupt and buffered threw a FIFO.Insert it behind #define sendByteOverInterface().

3.: Implement a function for sending a string over UART via interrupt and buffered threw a FIFO.Insert it behind #define sendStringOverInterface().

4.: Add a readout of the used timer count register behind #define sendSystemTime sendByteOverInterface(xTaskGetTickCount()>>8);sendByteOverInterface(xTaskGetTickCount()); (0-4 Bytes, starting with the big endian).

5.: Insert traceSTART() at the begin of your main before you initialise any freeRTOS constructs (like queues and tasks).

You will find the tracesniffing.h and an implemented FIFO-Buffer in the Source of the Project. Credit for the FIFO goes to [https://www.mikrocontroller.net/articles/FIFO](https://www.mikrocontroller.net/articles/FIFO).

If you are having problems with the implementation of the list above, have a look into "Examples". Maybe you will find an existing example for your μC. If you have a running example for an unlisted μC, or an improvement to an existing one, feel free to contact us and we make sure to add it.

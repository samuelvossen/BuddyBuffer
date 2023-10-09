Author Sam Vossen

Introduction
This document describes the functionality and operation of a Buddy Buffer Manager designed 
for an operating system. The Buddy Buffer Manager comprises four essential functions, along 
with a test driver, to effectively manage memory allocation and deallocation.

Functionality
Buffer Allocation
The Buddy Buffer Manager's primary function is to allocate memory buffers from a predefined,
fixed-size area. Initially, the available memory consists of ten maximum-sized buffers, 
each containing 511 words. Users can request buffers of various sizes, ranging from 7 words
 to 511 words. The manager handles requests by providing an appropriate buffer or returning
 -1 if the required buffer size cannot be met due to space constraints. It employs a unique
 mechanism where buffers can be split into "buddy" buffers, which may further cascade, 
ensuring the correct buffer size is allocated.

Buffer Deallocation
Users can return previously allocated buffers using a dedicated function. The manager 
automatically recombines smaller buffers, if possible, to optimize memory utilization. This 
recombination process can cascade, allowing smaller buffers to combine into larger ones, 
but it is important to note that 511-word buffers are never combined.

Memory Status
The Buddy Buffer Manager continuously monitors the memory pool's status. It sets a flag to 
indicate when the available memory is running low, specifically when there are two or fewer 
maximum-sized buffers left. Conversely, it clears this flag when the memory pool is no longer 
considered "tight," ensuring efficient memory management.

Debug Function
For debugging and monitoring purposes, the manager offers a debug function. This function 
provides information on the number of buffers present in each buffer chain, aiding in the 
assessment of memory utilization and allocation efficiency.

Test Driver
To validate the Buddy Buffer Manager's functionality, a dedicated test driver is provided. 
This test driver performs the following critical tasks:

1)Verifies the initial memory status and debug status to ensure expected values align with 
actual values.

2)Initiates a request for a 700-word block and confirms that it receives an appropriate 
illegal request status (-2).

3)Requests a 7-word buffer, verifies its successful acquisition, and then rechecks memory 
status, comparing expected and actual results.

4)Returns the 7-word buffer and validates the updated memory status.

5)In a controlled loop, requests ten 511-word buffers and evaluates the output statuses.

6)Attempts to request another buffer of any size, expecting to receive a -1 status, and 
subsequently returns the buffers.

7)Conducts additional test scenarios to ensure the Buddy Buffer Manager's proper functioning, 
specifically focusing on avoiding improper combining of non-buddy buffers and ensuring proper combining when required.
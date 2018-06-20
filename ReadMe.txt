KERNEL EXAMPLE FOR WIN32
 
This example project demonstrates how to create a kernel task which then prints to the terminal.
 
MICRIUM PRODUCT VERSIONS
- uC/OS-II  v2.92.13 OR uC/OS-III v3.06.02
- uC/CPU    v1.31.01
- uC/LIB    v1.38.02
 
IDE/COMPILER VERSIONS
- Visual Studio v2017
 
WORKSPACE LOCATIONS
- Microsoft/Windows/Kernel/OS2/VS/OS2.sln OR Microsoft/Windows/Kernel/OS3/VS/OS3.sln
 
USAGE INSTRUCTIONS
- Open the workspace in Visual Studio.
- Press F5 to build and run the project.
- The project creates a task which prints a message to the terminal every second.
- The task prints the number of kernel ticks that have elapsed since the project was run.
- Now modify the call to OSTimeDlyHMSM() in StartupTask() to increase or decrease the frequency of the displayed terminal message.
- Build and run again to see the change.
 
 
Please feel free to post questions or comments related to this example project at Micrium's forum page:

https://www.micrium.com/forums/topic/ucos-kernels-for-win32/
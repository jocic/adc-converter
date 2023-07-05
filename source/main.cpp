#include "main_window.h"

#include <QApplication>

/*
 * TO-DO (Paid Version):
 *   - Reuse the existing code but restructure the core of the application model/view/controller and split it
 *     into sections/modules that communicate through signals/slots - make it maintainable
 *   - Add an Icon
 *   - Saving/Loading procedure should be optimized and done using Threads in combination with a progress bar
 *   - Improve UI (use those tabs that can be moved around/docked etc)
 *   - Add ability to issue commands to the connected device
 *   - Configuration Window (UART -> Baud Rate,Parity, Samples -> Sample Format (Binary, Text), Hardware -> ADC Resolution, Positive/Negative Reference Voltages, etc)
 *   - Improve sample management feature - general overview, view values by interval (minute, secons, etc), generate waveform, play interval, etc
 *   - Automatically determine the sample rate
 *   - Make an efficient custom chart that doesn't crash the program with >1024 points
 *   - Show some notice when there are no samples
 *   - Make the ui look sexy AF
 *   - data receiver should extend qserialbus which extedns qiodevice - ez pz
 *   - Have a tab terminal for serial i/o - two way communication
 *   - Options for the bits per sample should be uint8, int16, int32 - and that's it
 *   - Option to "slow down" the waveform
 *   - Signal/slots connection is severed if made with a mainwindow while its being moved
 *   - Sample analysis section should show split bytes/words into rows and clearly specify which byte the user is ex.
 *     hovering the cursor over, time interval when it was captured ex. 0-1 seconds, etc, and so on
 *   - Waveform visualization feature
 *   - dc offseting feature - display dc offset of an adc based on the specified positive/negative reference, change it on fly, etc
 *   - cache all data ex. captured/loaded samples - if a program crashes, or user closes it it should be loaded during the next startup
 *   - post capture gain and auto-gain feature
 *   - fft view
**/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

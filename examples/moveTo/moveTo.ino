#include <StepMotor.h>


//Instance motor
StepMotor mainMotor(2, 3, 4, 12, "mm"); //motorName (Step Pin, Dir Pin, Enb Pin, Step per unit, Unit working = ["mm" or "m" or "cm"])

void setup()
{
    //nothing declare
}

void loop()
{
    mainMotor.moveTo(1000, 1);  //motorName.function(distance, direction);
}
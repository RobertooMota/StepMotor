#include <StepMotor.h>


//Instance motor
StepMotor mainMotor(2, 3, 4, 12, "mm"); //motorName (Step Pin, Dir Pin, Enb Pin, Step per unit, Unit working = ["mm" or "m" or "cm"])

void setup()
{
    mainMotor.SetSensorHome(5); //Sensor pin for home
}

void loop()
{
    mainMotor.moveTo(1000, 1);  //motorName.function(distance, direction);
    mainMotor.moveToHome();     //Machine go to sensor home
    mainMotor.moveToZero();     //After homing, the "moveToZero", start fast speed and reduces above 1 metter of the distance
    mainMotor.onlyMove(1);      //Only move. Parameter: 1 - one side    2 - other side.
}
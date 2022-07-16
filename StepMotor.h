#ifndef STEPMOTOR_H
#define STEPMOTOR_H
#include <Arduino.h>

class StepMotor
{
	public:
	
	StepMotor(byte step_pin, byte dir_pin, byte enb_pin, int step_per_mm, String unit);
	void SetSensorHome(byte sensor_pin);
	void moveTo (unsigned long distance, bool direction);
	void moveToHome();					//Vai para o home em velocidade baixa o tempo todo
	void moveToZero();	//Vai para o Zero rapido e desacelara ao chegar perto
	void onePulse();
	void setSpeed(int velocidadeMotor);
	private:
	
	//Int
	int unit_system();
	int lastDistance = 0;	//Verificar se é setada uma vez ou resetada sempre que usada
	int _step_per_mm;
	int fastSpeed = 900;
	int safeSpeed = 2000;
	int velocidade;
	int tempAccel;
	int intervaloAccel = 2;

	unsigned long numbers_step;
	unsigned long totalPulses;
	unsigned long totalPulsesReturn;
	
	//String
	String _unit;
	
	//Byte
	byte _step_pin;
	byte _dir_pin;
	byte _enb_pin;
	byte _sensor;
	
	//Boolean
	bool _direction;
	
};
#endif

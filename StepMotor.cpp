#include "StepMotor.h"

StepMotor::StepMotor(byte step_pin, byte dir_pin, byte enb_pin, int step_per_mm = 200, String unit = "mm")
{
	pinMode(step_pin, OUTPUT);
	pinMode(dir_pin, OUTPUT);
	pinMode(enb_pin, OUTPUT);

	_step_pin = step_pin;
	_dir_pin = dir_pin;
	_enb_pin = enb_pin;

	_step_per_mm = step_per_mm;
	_unit = unit;

	digitalWrite(_enb_pin, HIGH);
}

void StepMotor::SetSensorHome(byte sensor_pin)
{
	pinMode(sensor_pin, INPUT_PULLUP);
	_sensor = sensor_pin;
}

void StepMotor::moveTo(unsigned long distance, bool direction)
{
	_direction = direction;
	totalPulses = unit_system() * distance * _step_per_mm;
	totalPulsesReturn = totalPulses;

	digitalWrite(_dir_pin, direction);
	digitalWrite(_enb_pin, LOW);

	//Serial.begin(9600);
	//Serial.println(totalPulses);

	while (totalPulses > 0)
	{

		if (tempoAceleracao > fastSpeed)
			tempoAceleracao--;
		digitalWrite(_step_pin, HIGH);
		delayMicroseconds(tempoAceleracao);
		digitalWrite(_step_pin, LOW);
		delayMicroseconds(tempoAceleracao);
		totalPulses--;
	}

	digitalWrite(_dir_pin, LOW);
	digitalWrite(_enb_pin, HIGH);
	tempoAceleracao = 5000;
}

int StepMotor::unit_system()
{
	if (_unit == "mm")
		return 1UL;

	if (_unit == "cm")
		return 10UL;

	if (_unit == "m")
		return 1000UL;
}

void StepMotor::moveToHome()
{
	digitalWrite(_dir_pin, !_direction);
	digitalWrite(_enb_pin, LOW);

	//Serial.begin(9600);
	//Serial.print("_sensor = ");
	//Serial.println (_sensor);

	while (digitalRead(_sensor) == !0)
	{
		if (tempoAceleracao > safeSpeed)
			tempoAceleracao--;
		digitalWrite(_step_pin, HIGH);
		delayMicroseconds(tempoAceleracao);
		digitalWrite(_step_pin, LOW);
		delayMicroseconds(tempoAceleracao);
		//Serial.println(digitalRead(_sensor));
		//Caso necessário, colocar delay AQUI
	}
	//Serial.println("ok!");
	digitalWrite(_dir_pin, LOW);
	digitalWrite(_enb_pin, HIGH);
	tempoAceleracao = 5000;
}

void StepMotor::moveToZero()
{
	digitalWrite(_dir_pin, !_direction);
	digitalWrite(_enb_pin, LOW);

	if (_unit == "m")
	{
		while ((totalPulsesReturn - _step_per_mm * 1000) > 0)
		{
			if (totalPulsesReturn <= 0)
				break;

			digitalWrite(_step_pin, HIGH);
			delayMicroseconds(fastSpeed);
			digitalWrite(_step_pin, LOW);
			delayMicroseconds(fastSpeed);
			totalPulsesReturn--;
		}
	}
	moveToHome();

	digitalWrite(_dir_pin, LOW);
	digitalWrite(_enb_pin, HIGH);
}

void StepMotor::onlyMove(byte dirMove)
{
	if (accSolo > fastSpeed)
		accSolo--;
	digitalWrite(_step_pin, HIGH);
	delayMicroseconds(accSolo);
	digitalWrite(_step_pin, LOW);
	delayMicroseconds(accSolo);
}

void StepMotor::enable(bool cond)
{
	if (cond)
	{
		digitalWrite(_enb_pin, LOW);
	}
	else
	{
		digitalWrite(_enb_pin, HIGH);
		accSolo = 5000;
	}
}
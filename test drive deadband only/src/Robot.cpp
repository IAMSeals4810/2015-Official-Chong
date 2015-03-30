#include "WPILib.h"
#include <cmath>

class Robot: public IterativeRobot
{
public:

	Joystick *stick;

	CANTalon *flTal;
	CANTalon *rlTal;
	CANTalon *frTal;
	CANTalon *rrTal;
	RobotDrive *drive;
	Gyro *gy;
	BuiltInAccelerometer *acc;

	Compressor *comp;
	Solenoid *sol;
	Solenoid *arm;
	CANTalon *tal6;
	CANTalon *tal5;
	//DigitalInput *limit;
	Encoder *liftEnco;
	AnalogPotentiometer *sPot;
	SmartDashboard *dash;

	//SerialPort *sp;
	//char *buff;
	//int buffread1;
	//int buffread2;
	//int buffread3;

	Robot(){

		stick = new Joystick(0);

		flTal = new CANTalon(3);
		rlTal = new CANTalon(1);
		frTal = new CANTalon(2);
		rrTal = new CANTalon(4);
		drive = new RobotDrive(flTal, rlTal, frTal, rrTal);
		gy = new Gyro(0);
		acc = new BuiltInAccelerometer();

		comp = new Compressor(1);
		sol = new Solenoid(1, 0);
		arm = new Solenoid(1, 1);
		tal6 = new CANTalon(6);
		tal5 = new CANTalon(5);
		//limit = new DigitalInput(0);
		liftEnco = new Encoder(2, 3);
		sPot = new AnalogPotentiometer(1, 1.0, 0.0);

		drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		drive->SetSafetyEnabled(false);
		flTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		rlTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		frTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		rrTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		frTal->SetSensorDirection(true);
		rrTal->SetSensorDirection(true);
		gy->InitGyro();

		dash->init();


	}

	~Robot(){

		delete stick;

		delete flTal;
		delete rlTal;
		delete frTal;
		delete rrTal;
		delete drive;
		delete gy;
		delete acc;

		delete comp;
		delete sol;
		delete arm;
		delete tal6;
		delete tal5;
		//delete limit;
		delete liftEnco;
		delete sPot;

		//delete sp;
		//delete buff;

	}

private:

	LiveWindow *lw;

	bool jb1Hit = false;
	const bool jb3Hit = true;
	const bool jb5Hit = true;

	int flRead = 0;
	int rlRead = 0;
	int frRead = 0;
	int rrRead = 0;

	double liftRate;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		/*sp = new SerialPort(9600, SerialPort::kUSB);
		buff = new char[2];*/
	}

	void AutonomousInit()
	{
		dash->PutBoolean("Simple Auton", false);

		if(dash->GetBoolean("Simple Auton")== false){
			float gyrAngle = gy->GetAngle();

			flRead = 0;
			rlRead = 0;
			frRead = 0;
			rrRead = 0;
			arm->Set(true);
			Wait(1.0);
			sol->Set(true);
			tal5->Set(-0.5);
			tal6->Set(-0.5);
			Wait(1.2);
			sol->Set(false);
			tal5->Set(0.0);
			tal6->Set(0.0);
			if(gyrAngle > 0 || gyrAngle < 0){
				drive->MecanumDrive_Cartesian(0.0, 0.0, -0.5);
			}
			else{
				//Wait(1.0);
				drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
			}
			Wait(1.0);
			flRead = flTal->GetEncPosition();
			rlRead = rlTal->GetEncPosition();
			frRead = frTal->GetEncPosition();
			rrRead = rrTal->GetEncPosition();
			dash->PutNumber("flEncRaw", flRead);
			dash->PutNumber("rlEncRaw", rlRead);
			dash->PutNumber("frEncRaw", frRead);
			dash->PutNumber("rrEncRaw", rrRead);
			drive->MecanumDrive_Cartesian(0.0, -0.50, 0.0);
			Wait(2.0);
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
			//sol->Set(true);
			//Wait(1.0);
			//arm->Set(false);
			Wait(0.5);
			drive->MecanumDrive_Cartesian(0.0, -0.25, 0.0);
			Wait(0.5);
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
		}

		else if(dash->GetBoolean("Simple Auton") == true){
			drive->MecanumDrive_Cartesian(0.0, -0.5, 0.0);
			Wait(1.0);
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
		}

		else{
			dash->PutBoolean("Simple Auton", false);
			float gyrAngle = gy->GetAngle();

			flRead = 0;
			rlRead = 0;
			frRead = 0;
			rrRead = 0;
			arm->Set(true);
			Wait(1.0);
			sol->Set(true);
			tal5->Set(-0.5);
			tal6->Set(-0.5);
			Wait(1.2);
			sol->Set(false);
			tal5->Set(0.0);
			tal6->Set(0.0);
			if(gyrAngle > 0 || gyrAngle < 0){
				drive->MecanumDrive_Cartesian(0.0, 0.0, -0.5);
			}
			else{
				//Wait(1.0);
				drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
			}
			Wait(1.0);
			flRead = flTal->GetEncPosition();
			rlRead = rlTal->GetEncPosition();
			frRead = frTal->GetEncPosition();
			rrRead = rrTal->GetEncPosition();
			dash->PutNumber("flEncRaw", flRead);
			dash->PutNumber("rlEncRaw", rlRead);
			dash->PutNumber("frEncRaw", frRead);
			dash->PutNumber("rrEncRaw", rrRead);
			drive->MecanumDrive_Cartesian(0.0, -0.50, 0.0);
			Wait(2.0);
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
			//sol->Set(true);
			//Wait(1.0);
			//arm->Set(false);
			Wait(0.5);
			drive->MecanumDrive_Cartesian(0.0, -0.25, 0.0);
			Wait(0.5);
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
		}


		/*drive->MecanumDrive_Cartesian(0.0, -0.5, 0.0);
		Wait(1.0);
		drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);*/
	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

		//bool jb1Hit = false;
		//tal5->SetVoltageRampRate(2);
		dash->PutBoolean("Gyroscope On", true);

	}

	void TeleopPeriodic()
	{

		flRead = flTal->GetEncVel();
		rlRead = rlTal->GetEncVel();
		frRead = frTal->GetEncVel();
		rrRead = rrTal->GetEncVel();

		float gyrAngle;

		if(dash->GetBoolean("Gyroscope On") == true){
			gyrAngle = gy->GetAngle();
		}

		else if(dash->GetBoolean("Gyroscope On") == false){
			gyrAngle = 0;
		}

		else{
			dash->PutBoolean("Gyroscope On", true);
			gyrAngle = gy->GetAngle();
		}

		double roll = acc->GetX();
		double pitch = acc->GetY();
		double yaw = acc->GetZ();

		float stickX = stick->GetX();
		float stickY = stick->GetY();
		float stickZ = stick->GetZ();

		float sXExp = pow(stickX, 5);
		float sYExp = pow(stickY, 5);
		float sZExp = (pow(stickZ, 3)/3);

		float flCur = flTal->GetOutputCurrent();
		float rlCur = rlTal->GetOutputCurrent();
		float frCur = frTal->GetOutputCurrent();
		float rrCur = rrTal->GetOutputCurrent();

		float flVolt = flTal->GetOutputVoltage();
		float rlVolt = rlTal->GetOutputVoltage();
		float frVolt = frTal->GetOutputVoltage();
		float rrVolt = rrTal->GetOutputVoltage();

		float sPotRead = sPot->Get();
		float sInch = abs(92.65734 * sPotRead - 26.17133);
		//float sInch = abs(-85.2459*sPotRead+23.90984);

		liftRate = liftEnco->GetRate();

		dash->PutNumber("Stick X", stickX);
		dash->PutNumber("Stick Y", stickY);
		dash->PutNumber("Stick Z", stickZ);

		dash->PutNumber("Front Left Encoder", flRead);
		dash->PutNumber("Rear Left Encoder", rlRead);
		dash->PutNumber("Front Right Encoder", frRead);
		dash->PutNumber("Rear Right Encoder", rrRead);

		dash->PutNumber("Front Left Current", flCur);
		dash->PutNumber("Rear Left Current", rlCur);
		dash->PutNumber("Front Right Current", frCur);
		dash->PutNumber("Rear Right Current", rrCur);

		dash->PutNumber("Front Left Voltage", flVolt);
		dash->PutNumber("Rear Left Voltage", rlVolt);
		dash->PutNumber("Front Right Voltage", frVolt);
		dash->PutNumber("Rear Right Voltage", rrVolt);

		dash->PutNumber("String Read", sPotRead);
		dash->PutNumber("Height (Inches)", sInch);

		dash->PutNumber("Lift Rate", liftRate);

		dash->PutNumber("GyroAngle", gyrAngle);
		dash->PutNumber("Roll", roll);
		dash->PutNumber("Pitch", pitch);
		dash->PutNumber("Yaw", yaw);

		if((stickX > -0.5 && stickX < 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
		}

		else if((stickX > -0.5 && stickX < 0.5) && (stickY <= -0.5 || stickY >= 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(0.0, sYExp, 0.0);
		}

		else if((stickX <= -0.5 || stickX >= 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(sXExp, 0.0, 0.0);
		}

		else if((stickX > -0.5 && stickX < 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ <= -0.25 && stickZ >= 0.25)){
			drive->MecanumDrive_Cartesian(0.0, 0.0, sZExp);
		}

		else{
			drive->MecanumDrive_Cartesian(sXExp, sYExp, sZExp);
		}
		/*
		for(float x = 0.0; x<=1.0; x+=0.0001){
			flTal->Set(x);
			rlTal->Set(x);
			frTal->Set(x);
			rrTal->Set(x);
			dash->PutNumber("x", x);
		}
		*/

		/*if(flCur>0.0){
			dash->PutNumber("startTimeFl", time->Get());
			time->Stop();
		}

		if(rlCur>0.0){
			dash->PutNumber("startTimeRl", time2->Get());
			time2->Stop();
		}

		if(frCur>0.0){
			dash->PutNumber("startTimeFr", time3->Get());
			time3->Stop();
		}

		if(rrCur>0.0){
			dash->PutNumber("startTimeRr", time4->Get());
			time4->Stop();
		}*/

		/*if(stick->GetRawButton(3)){
			sol->Set(true);
					tal5->Set(-0.25);
					tal6->Set(-0.25);
				}

				else if(stick->GetRawButton(4)){
					sol->Set(true);
					tal5->Set(-0.03);
					tal6->Set(-0.03);
				}

				else if(stick->GetRawButton(5)){
					tal5->Set(0.0);
					tal6->Set(0.0);
					sol->Set(false);
				}

		if(stick->GetRawButton(9)){
			jb9Hit = true;
		}

		if(stick->GetRawButton(10)){
			jb10Hit = true;
		}*/

		if(stick->GetRawButton(2) /*&& jb1Hit == false*/){ // opening
			arm->Set(false);
			jb1Hit = true;
		}
		if(stick->GetRawButton(1) /*&& jb1Hit == true*/){ // closing
			arm->Set(true);
			jb1Hit = false;
		}

		dash->PutBoolean("Claw is Open", jb1Hit);

		float armSpeed = ((-stick->GetThrottle())/2) + 0.54;
		dash->PutNumber("Throttle Value", armSpeed);

		if(stick->GetRawButton(5) == jb5Hit && stick->GetRawButton(3) != jb3Hit && sInch < 59) {
			sol->Set(true);
			tal5->Set(-armSpeed);
			tal6->Set(-armSpeed);
		}
		else if(stick->GetRawButton(3) != jb3Hit && sInch >= 59 && stick->GetRawButton(5) == jb5Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}
		else if(stick->GetRawButton(3) == jb3Hit && stick->GetRawButton(5) != jb5Hit){
			sol->Set(true);
			tal5->Set(0.0);
			tal6->Set(0.0);
		}
		else if(stick->GetRawButton(5) != jb5Hit && stick->GetRawButton(3) != jb3Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}
		else if(stick->GetRawButton(5) == jb5Hit && stick->GetRawButton(3) == jb3Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}

		/*if(stick->GetRawButton(7) == jb7Hit) {
			sol->Set(true);
			tal5->Set(-0.5);
			tal6->Set(-0.5);
		}
		else if(stick->GetRawButton(7) != jb7Hit && stick->GetRawButton(3) != jb3Hit && stick->GetRawButton(4) != jb4Hit){
			sol->Set(false);
			tal5->Set(0.0);
			tal6->Set(0.0);
		}*/


		/*sp->Read(buff, 1);
		std::string heybuff(buff);
		dash->PutString("Buffer: ", heybuff);

		buffread1 = (int) buff[0];
		dash->PutNumber("UltrasonicInches1: ", buffread1);

		buffread2 = (int) buff[1];
		dash->PutNumber("Converted2: ", buffread2);

		buffread3 = (int) buff[2];
		dash->PutNumber("Converted3: ", buffread3);*/
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

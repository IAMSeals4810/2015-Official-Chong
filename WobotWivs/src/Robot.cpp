#include "WPILib.h"
#include "DriveSystem.h"

class Robot: public IterativeRobot
{

public:

	DriveSystem *driveBro;
	AnalogInput *uSIn;
	AnalogInput *uSInTwo;


	Robot(){

		driveBro = new DriveSystem();
		uSIn = new AnalogInput(1);
		uSInTwo = new AnalogInput(2);

	}

	~Robot(){

		delete driveBro;
		delete uSIn;
		delete uSInTwo;

	}

private:

	LiveWindow *lw;
	double uSVolt;
	double uSVoltTwo;
	double uSInch;
	double uSInchTwo;

	void RobotInit(){

		lw = LiveWindow::GetInstance();

	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){

	}

	void TeleopPeriodic(){

		uSVolt = uSIn->GetVoltage();
		uSInch = uSVolt/0.0098;
		uSVoltTwo = uSInTwo->GetVoltage();
		uSInchTwo = uSVoltTwo/0.0098;

		driveBro->dash->PutNumber("Ultrasonic Voltage Reading #1", uSVolt);
		driveBro->dash->PutNumber("Ultrasonic Inches Reading #1", uSInch);
		driveBro->dash->PutNumber("Ultrasonic Voltage Reading #2", uSVoltTwo);
		driveBro->dash->PutNumber("Ultrasonic Inches Reading #2", uSInchTwo);

		driveBro->DriveMecanumStyle();

		//driveBro->DriveSpeedMecanum();

	}

	void TestPeriodic(){

		lw->Run();

	}

};

START_ROBOT_CLASS(Robot);

#include "WPILib.h"
#include "Buttons/JoystickButton.h"

class Robot: public IterativeRobot
{
public:
	~Robot();

	LiveWindow *lw;

	Joystick* j;

	SmartDashboard* dash;

	JoystickButton* level0;
	JoystickButton* level1;
	JoystickButton* level2;
	JoystickButton* level3;
	JoystickButton* level4;
	JoystickButton* level5;


private:

	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopPeriodic();
	void TeleopInit();
	void TestPeriodic();


};

Robot::~Robot()
{
	delete j;

	delete level0;
	delete level1;
	delete level2;
	delete level3;
	delete level4;
	delete level5;

}

void Robot::RobotInit()
{
	lw = LiveWindow::GetInstance();

	j = new Joystick(0);

	dash = NULL;

	level0 = new JoystickButton(j, 7);
	level1 = new JoystickButton(j, 8);
	level2 = new JoystickButton(j, 9);
	level3 = new JoystickButton(j, 10);
	level4 = new JoystickButton(j, 11);
	level5 = new JoystickButton(j, 12);

}

void Robot::AutonomousInit()
{

}

void Robot::AutonomousPeriodic()
{

}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
	lw->Run();
	dash->init();

	std::string s = "Go to Level: ";

	dash->PutString(s, "");

	if(level0->Get())
	{
		dash->PutString(s, "0");
	}
	if(level1->Get())
	{
		dash->PutString(s, "1");
	}
	if(level2->Get())
	{
		dash->PutString(s, "2");
	}
	if(level3->Get())
	{
		dash->PutString(s, "3");
	}
	if(level4->Get())
	{
		dash->PutString(s, "4");
	}
	if(level5->Get())
	{
		dash->PutString(s, "5");
	}
}

void Robot::TestPeriodic()
{

}

START_ROBOT_CLASS(Robot);

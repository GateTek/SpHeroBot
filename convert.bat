@echo %off

if exist Balance\libraries (
	FOR /R "Balance\libraries\" %%i IN (*) DO MOVE "%%i" "Balance"
	rd /s /q "Balance\libraries\"
) else (

	md Balance\libraries\Debug
	md Balance\libraries\Balance\Moviment\IMU\MadgwickAHRS
	md Balance\libraries\Balance\Moviment\IMU\MPU6050
	md Balance\libraries\Balance\Moviment\Motor

	cd Balance\

	move Debug.* libraries\Debug
	move Balance.h libraries\Balance
	move Balance.cpp libraries\Balance
	move Moviment.* libraries\Balance\Moviment
	move Motor.* libraries\Balance\Moviment\Motor
	move IMU.* libraries\Balance\Moviment\IMU
	move MadgwickAHRS.* libraries\Balance\Moviment\IMU\MadgwickAHRS
	move MPU6050.* libraries\Balance\Moviment\IMU\MPU6050
	move *.h libraries

	cd..
)
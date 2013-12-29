all:
	cd music; make
	cd callendar_2_0; make

clean:
	cd music; make clean
	cd callendar; make clean

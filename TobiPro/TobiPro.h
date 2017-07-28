


#ifndef TobiPro_h 
#define TobiPro_h 

#include <Tobi.h>
#include <TobiFilterManager.h>

#define MAX_NUM_MOTORS 6

void serialSetup(void);

class TobiPro : public Tobi {
	public:		
		TobiFilterManager filter;
		// methods
		TobiPro(void);
		void setMotorIndices(int* motInd);
		void update(void);	// read encoders and update filters
		int calcSpeed(int motor);
		int getSpeed(int motor);
		void setSpeed(int motor, float percent);	// set speed of motor from 0 to 100%
		void setSampleRate(int dtInMs);		// set sampling rate in milliseconds
		void filterInputs(bool onOff);
		void srDelay(void);	// delay for length of set dt

	private:
		int _motorSpeed[MAX_NUM_MOTORS];
		int _dt = 50; // default sample rate is 50 ms
		int _lastEnc[NUM_MOTORS];	// save past encoder values (for calculating speed)
		int _lastTime[NUM_MOTORS];
		int _motorIndices[NUM_MOTORS];

};

#endif



#ifndef	TobiFilterManager_h
#define	TobiFilterManager_h

#include <Filters.h>
#include <Tobi.h>


enum STATS_TYPE {
	INPUT_STATS,
	FILTER_STATS
};

float getTime();

class TobiFilterManager {
	public:
		// switch filters on or off
		void onOff(bool onOrOff);
		void onOff(int motor, bool onOrOff);
		// check if filters are on or off
		bool isOn(int motor);

		TobiFilterManager();

		// FilterTwoPole methods
		void input(int motor, float inVal);
		float output(int motor);
		FilterTwoPole* getFilter(int motor);

		void setQ(float qualityFactor);	// set all Q
		void setQ(int motor, float qualityFactor);
  		
  		void setFrequency0(float f); // set all F0
  		void setFrequency0(int motor, float f);
  		
  		void setAsFilter( OSCILLATOR_TYPE ft, float frequency3db, float initialValue=0 ); // set all motors
  		void setAsFilter(int motor, OSCILLATOR_TYPE ft, float frequency3db, float initialValue=0 );

  		void printFilter(int motor);

  		float getSpeed(int motor);

		// RunningStatistics Methods
		void setWindowLength(float winLen);	// set all winLens
		void setWindowLength(int motor, float winLen);

		RunningStatistics* getStats(int motor, STATS_TYPE st);

		float mean(int motor, STATS_TYPE st);
  
		float variance(int motor, STATS_TYPE st);
		  
		float sigma(int motor, STATS_TYPE st);
		  
		float CV(int motor, STATS_TYPE st);

		void printStats(int motor, STATS_TYPE st);


	private:
		bool _on[NUM_MOTORS];
		OSCILLATOR_TYPE filterType;
		FilterTwoPole _filter[NUM_MOTORS];
		RunningStatistics _filterStats[NUM_MOTORS];
		RunningStatistics _inputStats[NUM_MOTORS];

};

#endif
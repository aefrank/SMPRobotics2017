
#include <TobiFilterManager.h>


/************************************************** DEFAULTS ****************************************************/

const float default3dbFreq = 0.25;
const float defaultWinLen = 50;


/************************************************** CONSTRUCTOR ****************************************************/

// defaults
TobiFilterManager::TobiFilterManager(){
	for (int i = 0; i < NUM_MOTORS; i++){
		TobiFilterManager::_filter[i].setAsFilter(LOWPASS_BUTTERWORTH, default3dbFreq);
		TobiFilterManager::_filterStats[i].setWindowSecs(defaultWinLen);
		TobiFilterManager::_inputStats[i].setWindowSecs(defaultWinLen);
	}
}

/************************************************** GENERAL METHODS ****************************************************/

bool TobiFilterManager::isOn(int motor) {
	return TobiFilterManager::_on[motor];
}

void TobiFilterManager::onOff(bool onOrOff){
	for (int i = 0; i < NUM_MOTORS; i++) 	TobiFilterManager::_on[i] = onOrOff;
}

void TobiFilterManager::onOff(int motor, bool onOrOff){
	TobiFilterManager::_on[motor] = onOrOff;
}

float getTime() {
  return float( micros() ) * 1e-6;
}

void TobiFilterManager::input(int motor, float inVal){
	TobiFilterManager::_filter[motor].input(inVal);
	TobiFilterManager::_filterStats[motor].input( TobiFilterManager::_filter[motor].output() );
	TobiFilterManager::_inputStats[motor].input(inVal);
}

float TobiFilterManager::output(int motor){
	return TobiFilterManager::_filter[motor].output();
}

/************************************************** FILTER METHODS ****************************************************/

// retrieve pointer to filter
FilterTwoPole* TobiFilterManager::getFilter(int motor){
	return &(TobiFilterManager::_filter[motor]);
}

// set quality factor
void TobiFilterManager::setQ(float qualityFactor){
	for (int i = 0; i < NUM_MOTORS; i++) 		TobiFilterManager::_filter[i].setQ(qualityFactor);
}
void TobiFilterManager::setQ(int motor, float qualityFactor){
	TobiFilterManager::_filter[motor].setQ(qualityFactor);
}
  		
// set F0 frequency
void TobiFilterManager::setFrequency0( float f ){
	for (int i = 0; i < NUM_MOTORS; i++)		TobiFilterManager::_filter[i].setFrequency0(f);
}
void TobiFilterManager::setFrequency0(int motor, float f){
	TobiFilterManager::_filter[motor].setFrequency0(f);
}
  		
// set filter characteristics
void TobiFilterManager::setAsFilter(OSCILLATOR_TYPE ft, float frequency3db, float initialValue=0 ){
	for (int i = 0; i < NUM_MOTORS; i++)		TobiFilterManager::_filter[i].setAsFilter(ft, frequency3db, initialValue=0);
}
void TobiFilterManager::setAsFilter(int motor, OSCILLATOR_TYPE ft, float frequency3db, float initialValue=0 ){
	TobiFilterManager::_filter[motor].setAsFilter(ft, frequency3db, initialValue=0);
}

// print filter details
 void TobiFilterManager::printFilter(int motor){
 	TobiFilterManager::_filter[motor].print();
 }

float TobiFilterManager::getSpeed(int motor){
	return TobiFilterManager::_filter[motor].Vavg;
}

/************************************************** STATS METHODS ****************************************************/

RunningStatistics* TobiFilterManager::getStats(int motor, STATS_TYPE st){
	switch(st){
		case INPUT_STATS:
			return &(TobiFilterManager::_inputStats[motor]);
			break;
		case FILTER_STATS:
			return &(TobiFilterManager::_filterStats[motor]);
			break;
	}
}
		
void TobiFilterManager::setWindowLength(float winLen){
	for(int i = 0; i < NUM_MOTORS; i++) {
		TobiFilterManager::_filterStats[i].setWindowSecs(winLen);
		TobiFilterManager::_inputStats[i].setWindowSecs(winLen);
	}
}
void TobiFilterManager::setWindowLength(int motor, float winLen){
	TobiFilterManager::_filterStats[motor].setWindowSecs(winLen);
	TobiFilterManager::_inputStats[motor].setWindowSecs(winLen);
}	

float TobiFilterManager::mean(int motor, STATS_TYPE st){
	switch(st){
		case INPUT_STATS:
			return TobiFilterManager::_inputStats[motor].mean();
			break;
		case FILTER_STATS:
			return TobiFilterManager::_filterStats[motor].mean();
			break;
	}

}
  
float TobiFilterManager::variance(int motor, STATS_TYPE st){
	switch(st){
		case INPUT_STATS:
			return TobiFilterManager::_inputStats[motor].variance();
			break;
		case FILTER_STATS:
			return TobiFilterManager::_filterStats[motor].variance();
			break;
	}
}
		  
float TobiFilterManager::sigma(int motor, STATS_TYPE st){
	switch(st){
		case INPUT_STATS:
			return TobiFilterManager::_inputStats[motor].sigma();
			break;
		case FILTER_STATS:
			return TobiFilterManager::_filterStats[motor].sigma();
			break;
	}
}
		  
float TobiFilterManager::CV(int motor, STATS_TYPE st){
	switch(st){
		case INPUT_STATS:
			return TobiFilterManager::_inputStats[motor].CV();
			break;
		case FILTER_STATS:
			return TobiFilterManager::_filterStats[motor].CV();
			break;
	}
}


void TobiFilterManager::printStats(int motor, STATS_TYPE st){
	switch(st){
		case INPUT_STATS:
			// TODO
			break;
		case FILTER_STATS:
			// TODO
			break;
	}

}

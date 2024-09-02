#include "pch.h"
#include "hellen_meta.h"
#include "defaults.h"
#include "hellen_leds_144.cpp"


static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = H144_INJ1;
	engineConfiguration->injectionPins[1] = H144_INJ2;
	engineConfiguration->injectionPins[2] = H144_INJ3;
	engineConfiguration->injectionPins[3] = H144_INJ4;
	engineConfiguration->injectionPins[4] = H144_INJ5;
	engineConfiguration->injectionPins[5] = H144_INJ6;
}

static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = H144_IGN7;
	engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[2] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[3] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[4] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[5] = Gpio::Unassigned;
}

static void setupDefaultSensorInputs() {
	engineConfiguration->tps1_1AdcChannel = H144_IN_TPS_ANALOG;
	engineConfiguration->tps1_2AdcChannel = H144_IN_AUX1_ANALOG;
	engineConfiguration->map.sensor.hwChannel = Gpio::Unassigned;
	engineConfiguration->mafAdcChannel = EFI_ADC_10;

	setPPSInputs(Gpio::Unassigned, Gpio::Unassigned);

	engineConfiguration->clt.adcChannel = H144_IN_CLT_ANALOG;
	engineConfiguration->iat.adcChannel = H144_IN_IAT_ANALOG;

	engineConfiguration->triggerInputPins[0] = Gpio::H144_IN_CRANK;
	engineConfiguration->camInputs[0] = Gpio::H144_IN_CAM;


  	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::Unassigned;
	
	// 5.6k high side/1k low side = 1.56 ratio divider
	//engineConfiguration->analogInputDividerCoefficient = 1.56f;
	// set vbatt_divider
	// 6.34k high side/ 1k low side
	//engineConfiguration->vbattDividerCoeff = (6.34 + 1) / 1;
	// Battery sense on PA0
	//engineConfiguration->vbattAdcChannel = EFI_ADC_0;
	//engineConfiguration->adcVcc = 3.3f;
	
	
}

void setBoardConfigOverrides() {
	setHellenMegaEnPin();
	setHellenVbatt();
	hellenMegaSdWithAccelerometer();
  	setHellenCan();
	setDefaultHellenAtPullUps();

}


void setBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();
	setHellenMMbaro();

	engineConfiguration->displayLogicLevelsInEngineSniffer = true;
	engineConfiguration->globalTriggerAngleOffset = 9;
	engineConfiguration->enableSoftwareKnock = true;
	//engineConfiguration->canTxPin = Gpio::H144_CAN_TX;
	//engineConfiguration->canRxPin = Gpio::H144_CAN_RX;
	//engineConfiguration->mainRelayPin = Gpio::H144_IGN7;
 	engineConfiguration->fanPin = Gpio::H144_OUT_IO13;
	engineConfiguration->fuelPumpPin = Gpio::H144_OUT_IO8;
	engineConfiguration->idle.solenoidPin = Gpio::H144_OUT_IO7;

	// "required" hardware is done - set some reasonable defaults
	setupDefaultSensorInputs();
	engineConfiguration->enableVerboseCanTx = true;
	// Some sensible defaults for other options
	setCrankOperationMode();
	setAlgorithm(LM_SPEED_DENSITY);
	engineConfiguration->injectorCompensationMode = ICM_FixedRailPressure;
	setCommonNTCSensor(&engineConfiguration->clt, HELLEN_DEFAULT_AT_PULLUP);
	setCommonNTCSensor(&engineConfiguration->iat, HELLEN_DEFAULT_AT_PULLUP);
    	setTPS1Calibration(75, 900);
	hellenWbo();
}

static Gpio OUTPUTS[] = {
	Gpio::H144_INJ6, // B1 injector output 6
	Gpio::H144_INJ5, // B2 injector output 5
	Gpio::H144_INJ4, // B3 injector output 4
	Gpio::H144_INJ3, // B4 injector output 3
	Gpio::H144_INJ2, // B5 injector output 2
	Gpio::H144_INJ1, // B6 injector output 1
	Gpio::H144_INJ7, // B7 Low Side output 1
	Gpio::H144_IGN8, // B8 Fan Relay Weak Low Side output 2
	Gpio::H144_IGN7, // B9 Main Relay Weak Low Side output 1
	Gpio::H144_OUT_PWM2, // B16 Low Side output 4 / Fuel Pump
	Gpio::H144_OUT_PWM1, // B17 Low Side output 3
	Gpio::H144_INJ8, // B18 Low Side output 2
	// high sides
	Gpio::H144_IGN6, // B10 Coil 6
	Gpio::H144_IGN4, // B11 Coil 4
	Gpio::H144_IGN3, // B12 Coil 3
	Gpio::H144_IGN5, // B13 Coil 5
	Gpio::H144_IGN2, // B14 Coil 2
	Gpio::H144_IGN1, // B15 Coil 1
};


/*
//old stuff




// trigger inputs, hall
engineConfiguration->triggerInputPins[0] = H144_IN_CRANK;
engineConfiguration->camInputs[0] = H144_IN_CAM;
//sensors
engineConfiguration->tps1_1AdcChannel = H144_IN_TPS;
engineConfiguration->mafAdcChannel = EFI_ADC_10;
engineConfiguration->afr.hwChannel = EFI_ADC_1;
engineConfiguration->clt.adcChannel = H144_IN_CLT;
engineConfiguration->iat.adcChannel = H144_IN_IAT;
//outputs
engineConfiguration->fuelPumpPin = Gpio::G4;	// OUT_IO8
engineConfiguration->idle.solenoidPin = Gpio::G3;	// OUT_IO7
engineConfiguration->fanPin = Gpio::G6;	// OUT_IO13
engineConfiguration->mainRelayPin = Gpio::E10;
engineConfiguration->tachOutputPin = Gpio::F13;
//inputs
engineConfiguration->clutchDownPin = Gpio::F5; // Clutch switch input
engineConfiguration->clutchDownPinMode = PI_PULLDOWN;
engineConfiguration->launchActivationMode = CLUTCH_INPUT_LAUNCH;
engineConfiguration->malfunctionIndicatorPin = Gpio::Unassigned;
//engine parameters
engineConfiguration->cylindersCount = 6;
engineConfiguration->firingOrder = FO_1_4_2_5_3_6;
engineConfiguration->ignitionMode = IM_SINGLE_POINT;

void setBoardConfigOverrides() {
	setupVbatt();
	setHellenSdCardSpi2();
	setDefaultHellenAtPullUps();
	setHellenCan();
}
*/

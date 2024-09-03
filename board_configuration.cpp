#include "pch.h"
#include "hellen_meta.h"
#include "defaults.h"
#include "hellen_leds_144.cpp"

/*
static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = H144_INJ1;
	engineConfiguration->injectionPins[1] = H144_INJ2;
	engineConfiguration->injectionPins[2] = H144_INJ3;
	engineConfiguration->injectionPins[3] = H144_INJ4;
	engineConfiguration->injectionPins[4] = H144_INJ5;
	engineConfiguration->injectionPins[5] = H144_INJ6;
}
*/
/*
static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = H144_IGN7;
	engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[2] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[3] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[4] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[5] = Gpio::Unassigned;
}
*/
/*
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
*/
void setBoardConfigOverrides() {
	setHellenMegaEnPin();
	setHellenVbatt();
	//setupVbatt();
	hellenMegaSdWithAccelerometer();
  	setHellenCan();
	setDefaultHellenAtPullUps();
	//setHellenSdCardSpi2(); Card is on SPI1

}

void setBoardDefaultConfiguration() {
	//setInjectorPins();
	//setIgnitionPins();
	//setupDefaultSensorInputs();
	setHellenMMbaro();

	engineConfiguration->displayLogicLevelsInEngineSniffer = true;
	engineConfiguration->globalTriggerAngleOffset = 9;
	engineConfiguration->enableSoftwareKnock = true;
	engineConfiguration->cylindersCount = 6;
	engineConfiguration->firingOrder = FO_1_4_2_5_3_6;
	engineConfiguration->ignitionMode = IM_SINGLE_POINT;
	engineConfiguration->fuelAlgorithm = LM_REAL_MAF;
	//setAlgorithm(LM_SPEED_DENSITY);
	//engineConfiguration->canTxPin = Gpio::H144_CAN_TX;
	//engineConfiguration->canRxPin = Gpio::H144_CAN_RX;
	//engineConfiguration->mainRelayPin = Gpio::H144_IGN7; //E10
 	//engineConfiguration->fanPin = Gpio::H144_OUT_IO13; //G6
	//engineConfiguration->fuelPumpPin = Gpio::H144_OUT_IO8; //G4
	//engineConfiguration->idle.solenoidPin = Gpio::H144_OUT_IO7; //G3
	//engineConfiguration->tachOutputPin = Gpio::F13;
	//engineConfiguration->clutchDownPin = Gpio::F5; // Clutch switch input
	//engineConfiguration->clutchDownPinMode = PI_PULLDOWN;
	engineConfiguration->enableVerboseCanTx = true;
	// Some sensible defaults for other options
	setCrankOperationMode();
	engineConfiguration->injectorCompensationMode = ICM_FixedRailPressure;
	setCommonNTCSensor(&engineConfiguration->clt, HELLEN_DEFAULT_AT_PULLUP);
	setCommonNTCSensor(&engineConfiguration->iat, HELLEN_DEFAULT_AT_PULLUP);
    	setTPS1Calibration(75, 900);
	hellenWbo();
}

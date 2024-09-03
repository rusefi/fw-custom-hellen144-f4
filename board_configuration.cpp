#include "pch.h"
#include "hellen_meta.h"
#include "defaults.h"
//#include "hellen_leds_144.cpp"


static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::G7;
	engineConfiguration->injectionPins[1] = Gpio::G8;
	engineConfiguration->injectionPins[2] = Gpio::D11;
	engineConfiguration->injectionPins[3] = Gpio::D10;
	engineConfiguration->injectionPins[4] = Gpio::D9;
	engineConfiguration->injectionPins[5] = Gpio::F12;
}


static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = Gpio::B9;
	engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[2] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[3] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[4] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[5] = Gpio::Unassigned;
}


static void setupDefaultSensorInputs() {
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_4;
 	engineConfiguration->clt.adcChannel = EFI_ADC_12;
	engineConfiguration->iat.adcChannel = EFI_ADC_13;
	engineConfiguration->mafAdcChannel = EFI_ADC_14;
	engineConfiguration->vehicleSpeedSensorInputPin = Gpio::F11;
	engineConfiguration->triggerInputPins[0] = Gpio::B1;
	engineConfiguration->camInputs[0] = Gpio::A6;
 	
  	//engineConfiguration->map.sensor.hwChannel = Gpio::Unassigned;
	//setPPSInputs(Gpio::Unassigned, Gpio::Unassigned);



	
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
	//setupVbatt();
	hellenMegaSdWithAccelerometer();
  	setHellenCan();
	setDefaultHellenAtPullUps();
	//setHellenSdCardSpi2(); Card is on SPI1

}

void setBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();
	//setupDefaultSensorInputs();
	setHellenMMbaro();

	engineConfiguration->displayLogicLevelsInEngineSniffer = true;
	engineConfiguration->globalTriggerAngleOffset = 9;
	engineConfiguration->enableSoftwareKnock = true;
	engineConfiguration->cylindersCount = 6;
	engineConfiguration->firingOrder = FO_1_4_2_5_3_6;
	engineConfiguration->ignitionMode = IM_ONE_COIL;
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

/******************************************************************************
* File Name          : Audio.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/15/2015
* Description        : Audio Output Interface
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef AUDIO_H
	#define AUDIO_H	

#include "Generic/GenericTypeDef.h"
#include "Peripherals/IOInterface.h"


class AudioOut{
		public:
		AudioOut(IO_Pin* en_pin, IO_PORT_NUM DAC_port, IO_PIN_NUM low_pin);
		
		void Play(const uint8_t audio_sample[], uint32_t audio_length, uint16_t num_repeats);
		void Disable();
		bool isPlaying(){return AudioPlaying;};
		
		//Used by Interrupt only
		static AudioOut* instance;	
		void NextSample();
	
		private:
			void Enable();
			void InitHardware(IO_PORT_NUM DACPort, IO_PIN_NUM LowPin);
			void StartSampleTimer();
			void StopSampleTimer();
	
		const 		uint8_t* 				AudioSample;
		volatile 	uint_fast8_t 		Sample;	
		volatile 	uint_fast32_t 	AudioLength;
		volatile 	uint_fast32_t 	iSample;
		volatile 	bool 						AudioPlaying;
		volatile 	uint_fast16_t 	NumRepeats;


		IO_PORT_NUM DACPort;
		IO_PIN_NUM	LowPin;
	
		IO_Pin* EnablePin;
		
	
};

#endif


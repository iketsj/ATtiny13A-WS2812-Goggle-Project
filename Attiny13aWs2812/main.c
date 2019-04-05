 #define F_CPU 9600000UL

 #include <avr/io.h>
 #include <util/delay.h>
 #include <inttypes.h>

 #define WS2812_COUNT 24
 #define RED 0
 #define GREEN 1
 #define BLUE 2

void SendRGB(uint8_t redVal, uint8_t greenVal, uint8_t blueVal);
void SendColorData(uint8_t data);
void ShowPattern(void);

void CycleToRedGreenBluePattern(uint8_t showHowManyTimes, uint32_t duration);
void FadeRedOrGreenOrBluePattern(uint8_t RGorB, uint32_t duration);
void WheelRGBPattern(uint32_t duration);

void delay(uint32_t ms);

int main(void){
	DDRB |= _BV(PB4);

	while (1){
		CycleToRedGreenBluePattern(1, 1650);
		FadeRedOrGreenOrBluePattern(RED, 11);
		FadeRedOrGreenOrBluePattern(GREEN, 11);
		FadeRedOrGreenOrBluePattern(BLUE, 11);
		CycleToRedGreenBluePattern(1, 1650);
	}

	return 0;
}

void WheelRGBPattern(uint32_t duration){
	for(int steps = 0; steps < WS2812_COUNT; steps++){
		if(steps % 3 == 0){
			for(int i = 0; i < WS2812_COUNT/6; i++){
				SendRGB(255, 0, 0);
				SendRGB(255, 0, 0);
				SendRGB(0, 255, 0);
				SendRGB(0, 255, 0);
				SendRGB(0, 0, 255);
				SendRGB(0, 0, 255);
			}
			ShowPattern();
			delay(duration);
		}
		else if(steps % 3 == 1){
			for(int i = 0; i < WS2812_COUNT/6; i++){
				SendRGB(0, 0, 255);
				SendRGB(0, 0, 255);
				SendRGB(255, 0, 0);
				SendRGB(255, 0, 0);
				SendRGB(0, 255, 0);
				SendRGB(0, 255, 0);
			}
			ShowPattern();
			delay(duration);
		}
		else{
			for(int i = 0; i < WS2812_COUNT/6; i++){
				SendRGB(0, 255, 0);
				SendRGB(0, 255, 0);
				SendRGB(0, 0, 255);
				SendRGB(0, 0, 255);
				SendRGB(255, 0, 0);
				SendRGB(255, 0, 0);
			}
			ShowPattern();
			delay(duration);
		}
	}

}

void FadeRedOrGreenOrBluePattern(uint8_t whichColor, uint32_t duration){
	for(int val = 0; val < 256; val++){
		for(int i = 0; i < WS2812_COUNT; i++){
			switch(whichColor){
				case RED:
					SendRGB(val, 0, 0);
					break;
				case GREEN:
					SendRGB(0, val, 0);
					break;
				case BLUE:
					SendRGB(0, 0 , val);
					break;
			}
		}
		ShowPattern();
		delay(duration);
	}
	for(int val = 255; val >= 0; val--){
		for(int i = 0; i < WS2812_COUNT; i++){
			switch(whichColor){
				case RED:
				SendRGB(val, 0, 0);
				break;
				case GREEN:
				SendRGB(0, val, 0);
				break;
				case BLUE:
				SendRGB(0, 0 , val);
				break;
			}
		}
		ShowPattern();
		delay(duration);
	}
}

void CycleToRedGreenBluePattern(uint8_t showHowManyTimes, uint32_t duration){
	for(int i = 0; i < showHowManyTimes; i++){
		for(int j = 0; j < WS2812_COUNT; j++){
			SendRGB(255, 0, 0);
		}
		ShowPattern();
		delay(duration);
		for(int j = 0; j < WS2812_COUNT; j++){
			SendRGB(0, 255, 0);
		}
		ShowPattern();
		delay(duration);
		for(int j = 0; j < WS2812_COUNT; j++){
			SendRGB(0, 0, 255);
		}
		ShowPattern();
		delay(duration);
	}
}

void SendRGB(uint8_t redVal, uint8_t greenVal, uint8_t blueVal){
	SendColorData(greenVal);
	SendColorData(redVal);
	SendColorData(blueVal);
}

void SendColorData(uint8_t data){
	uint8_t bitVal;
	for(int i = 0; i < 8; i++){
		bitVal = data & (1 << (7 - i));
		if(bitVal){
			PORTB |= (1 << PB4);
			_delay_us(0.500); //0.7us
			//760ns
			PORTB &= ~(1 << PB4);
		}else{
			PORTB |= (1 << PB4);
			_delay_us(0.100); //0.35us
			//340ns
			PORTB &= ~(1 << PB4);
		}
	}
}

void ShowPattern(void){
	PORTB &= ~(1 << PB4);
	_delay_us(50);
}

void delay(uint32_t ms){
	for(int i = 0; i < ms; i++){
		_delay_ms(1);
	}
}
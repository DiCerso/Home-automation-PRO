/*!
 * @file S5050DJ.h
 * @par Author & Doxygen Editor
 * 	Daniel Di Módica ~ <a href = "mailto: danifabriziodmodica@gmail.com">danifabriziodmodica@@gmail.com</a>
 * @date 06/01/2024 12:11:36
 * @brief LEDs S5050DJ with IR Transmitter Class API (Application Programming Interface).
 */

#ifndef S5050DJ_H_
#define S5050DJ_H_

#include <queue>
#include "systick.h"
#include "CTimer.h"
#include "ProgramConfig.h"

#define S5050DJ_ADDR (0x00F7U)

#define S5050DJ_MAX_BRIGHTNESS_SPEED_POINT 60

#define S5050DJ_OFFSET_THRESHOLD_PERCENTAGE 10

#define S5050DJ_COMMAND_LENGTH (BYTE_SIZE * 4)

#define S5050DJ_OFFSET_TIME 62
#define S5050DJ_DEBOUNCE_TIME 1

#define S5050DJ_COMMAND_PERIOD_TIME (67500 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_START_BIT_TIME (9000 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_SLOT_BIT_TIME (4500 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_LOW_ACTIVE_BIT_TIME (562 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_LOW_IDLE_BIT_TIME (562 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_HIGH_ACTIVE_BIT_TIME (562 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_HIGH_IDLE_BIT_TIME (1675 - S5050DJ_OFFSET_TIME)
#define S5050DJ_COMMAND_STOP_BIT_TIME (562 - S5050DJ_OFFSET_TIME)

#define S5050DJ_USING_REPEAT_COMMAND_INSTANCE 0

#if S5050DJ_USING_REPEAT_COMMAND_INSTANCE == 1
#define S5050DJ_REPEAT_COMMAND_PERIOD_TIME (11812 - S5050DJ_OFFSET_TIME)
#define S5050DJ_REPEAT_COMMAND_DELAY (108000 - S5050DJ_OFFSET_TIME)
#define S5050DJ_REPEAT_COMMAND_START_BIT_TIME (9000 - S5050DJ_OFFSET_TIME)
#define S5050DJ_REPEAT_COMMAND_SLOT_BIT_TIME (2250 - S5050DJ_OFFSET_TIME)
#define S5050DJ_REPEAT_COMMAND_STOP_BIT_TIME (562 - S5050DJ_OFFSET_TIME)
#endif

#define S5050DJ_COMMAND_SLOT_TICKS (S5050DJ_COMMAND_PERIOD_TIME / 2) / 1000

class S5050DJ : protected CTimer, Callback {
private:
	enum actionSetting_t { INCREASE_BRIGHTNESS = 0x00FFU, INCREASE_SPEED = 0x00FFU, DECREASE_BRIGHTNESS = 0x807FU, DECREASE_SPEED = 0x807FU, TURNOFF_LEDS = 0x40BFU, TURNON_LEDS = 0xC03FU };

	uint8_t m_brightnessPoint;
	uint8_t m_speedPoint;
	actionInterruption_t m_externalOutput;
	activity_t m_externalActivity;

    std::queue<uint16_t> m_commandQueue;
    uint16_t m_timeCounter;

	// Modularize this implementation with the interruption of the CTimer interface.
	// The program flow will go to this function to execute an action uninterruptedly.
	// It is a requirement that the following function be static since the pointer to a function is not a specific instance of the class.
	static void transmitCommand(uint16_t command);

	void prepareConditions(void);
	void changeExternalOutput(actionInterruption_t actionInterrupt);
	void setAction(actionSetting_t action);
protected:
    void callbackMethod(void) override;
public:
	enum colorSetting_t { RED = 0x20DFU, GREEN = 0xA05FU, BLUE = 0x609FU, WHITE = 0xE01FU, FST_RED = 0x10EFU, FST_GREEN = 0x906FU, FST_BLUE = 0x50AFU, SND_RED = 0x30CFU, SND_GREEN = 0xB04FU, SND_BLUE = 0x708FU, TRD_RED = 0x08F7U, TRD_GREEN = 0x8877U, TRD_BLUE = 0x48B7U, YELLOW = 0x28D7U, LIGHT_BLUE = 0xA857U, VIOLET = 0x6897U };
	enum modeSetting_t { FLASH = 0xD02FU, STROBE = 0xF00FU, FADE = 0xC837U, SMOOTH = 0xE817U };

	S5050DJ() = delete;
	S5050DJ(const Gpio &output, actionInterruption_t idleExternalOutput = CLEAR);
	void setColor(colorSetting_t color);
	void setMode(modeSetting_t mode);
	void setBrightness(uint8_t percentage);
	void setSequenceSpeed(uint8_t percentage);
	void turnOn(void);
	void turnOff(void);
    uint8_t getBrightness(void) const;
    uint8_t getSpeed(void) const;
	virtual ~S5050DJ() = default;
};

extern S5050DJ *g_leds;

void initLEDs(void);

#endif /* S5050DJ_H_ */

/*!
 * @file Digit.h
 * @par Author & Doxygen Editor
 * 	Daniel Di Módica ~ <a href = "mailto: danifabriziodmodica@gmail.com">danifabriziodmodica@@gmail.com</a>
 * @date 30/07/2023 12:45:36
 * @brief Digit Types Class API (Application Programming Interface).
 */

#ifndef DIGIT_H_
#define DIGIT_H_

#include "utils.h"

#define	ZERO	0B00111111
#define	ONE 	0B00000110
#define TWO 	0B01011011
#define THREE	0B01001111
#define	FOUR	0B01100110
#define	FIVE	0B01101101
#define	SIX		0B01111100
#define	SEVEN	0B00000111
#define	EIGHT	0B01111111
#define	NINE	0B01100111
#define	MINUS	0B01000000

const uint8_t tableBCD[10] = { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

class Digit {
public:
	enum code_t		{ BCD, SEGMENTS, ASCII };
	enum mode_t		{ NONE, BLINK, TURNOFF = 0xFF };
	enum symbol_t	{ MINUSSYM = 10, A, B, C, D, E, F, G, H, N, O, P, R, T, U };
private:
	const code_t m_system;
	uint16_t m_value;
	mode_t m_action = NONE;
public:
	Digit() = delete;
	Digit(code_t system = BCD, uint8_t value = TURNOFF);
	bool set(uint16_t value);
	uint16_t get(void) const;
	void clear(void);
	void blinkBind(void);
	void blinkUnbind(void);
	mode_t getMode(void) const;
	virtual ~Digit() = default;
};

#endif /* DIGIT_H_ */

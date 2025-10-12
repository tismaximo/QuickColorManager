#include "SettingsTypes.h"

Settings::Settings(
	std::string alias,
	U16 brightness,
	U16 contrast,
	U16 gamma,
	U16 redBalance,
	U16 greenBalance,
	U16 blueBalance
):
	alias(alias),
	brightness(brightness),
	contrast(contrast),
	gamma(gamma),
	redBalance(redBalance),
	greenBalance(greenBalance),
	blueBalance(blueBalance)
{}

std::string Settings::str() const {
	std::ostringstream ss;
	ss << "Settings From " << this->alias << ":\nBrightness : " << +this->brightness
		<< "\nContrast: " << +this->contrast
		<< "\nGamma: " << +this->gamma
		<< "\nRed balance: " << +this->redBalance
		<< "\nGreen balance: " << +this->greenBalance
		<< "\nBlue balance: " << +this->blueBalance;
	return ss.str();
}

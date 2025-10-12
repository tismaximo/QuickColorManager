#include "SettingsTypes.h"

struct Settings {
public:
	std::string alias;
	U8 brightness;
	U8 contrast;
	U8 gamma;
	U8 redBalance;
	U8 greenBalance;
	U8 blueBalance;
	Settings(
		std::string alias,
		U8 brightness = 70,
		U8 contrast = 70,
		U8 gamma = 70,
		U8 redBalance = 70,
		U8 greenBalance = 70,
		U8 blueBalance = 70
	) :
		alias(alias),
		brightness(brightness),
		contrast(contrast),
		gamma(gamma),
		redBalance(redBalance),
		greenBalance(greenBalance),
		blueBalance(blueBalance)
	{}
	std::string str() const {
		std::ostringstream ss;
		ss << "Settings From " << this->alias << ":\nBrightness : " << +this->brightness
			<< "\nContrast: " << +this->contrast
			<< "\nGamma: " << +this->gamma
			<< "\nRed balance: " << +this->redBalance
			<< "\nGreen balance: " << +this->greenBalance
			<< "\nBlue balance: " << +this->blueBalance;
		return ss.str();
	}
};
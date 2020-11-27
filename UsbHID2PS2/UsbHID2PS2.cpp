#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include "translation_table.h"

std::map<uint8_t, PS2Sets> translation_map;

template<typename T>
std::string hex_out(T val, bool is_word = false) {
	std::stringstream sformatter;
	sformatter
		<< std::hex
		<< std::internal
		<< "0x"
		<< std::uppercase
		<< std::setfill('0')
		<< std::setw(is_word ? 4 : 2)
		<< (int)val;
	return sformatter.str();
}

int main()
{
	std::cout << "USB HID to PS/2 scan codes sets translation map" << std::endl;

	// fill in the hash map
	for (size_t i = 0; i < TRANSLATIONS_COUNT; i++)
	{
		translation_map[translation_array[i].hid_code] = translation_array[i].sets;
	}

	// display whole map
	for (std::map<uint8_t, PS2Sets>::iterator it = translation_map.begin(); it != translation_map.end(); ++it) {
		std::cout << hex_out(it->first) << " =>" 
			<< " [" << hex_out(it->second.Set1.code.prefix) << " " << hex_out(it->second.Set1.code.value) << "]"
			<< " [" << hex_out(it->second.Set2.code.prefix) << " " << hex_out(it->second.Set2.code.value) << "]"
			<< " [" << hex_out(it->second.Set3.code.prefix) << " " << hex_out(it->second.Set3.code.value) << "]"
			<< std::endl;
	}

	std::cout << std::endl << "Single USB HID key entry to PS/2 sets translation " << std::endl;

	// display sinlge USB HID entry to PS/2 sets translation
	uint8_t key = 0xe4;

	std::cout 
		<< hex_out(key) << " =>" 
		<< " [" << hex_out(translation_map[key].Set1.code.prefix) << " " << hex_out(translation_map[key].Set1.code.value) << "]"
		<< " [" << hex_out(translation_map[key].Set2.code.prefix) << " " << hex_out(translation_map[key].Set2.code.value) << "]"
		<< " [" << hex_out(translation_map[key].Set3.code.prefix) << " " << hex_out(translation_map[key].Set3.code.value) << "]"
		<< std::endl;

	return 0;

}


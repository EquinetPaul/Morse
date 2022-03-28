//
// Created by cytech on 25/03/2022.
//

#ifndef MORSE_MORSE_HPP
#define MORSE_MORSE_HPP

#include <string>
#include "../nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

/**
 * \brief Fonction qui convertit une chaine de caractère en son équivalent morse
 * \param base la chaine de caractère à convertir
 * \param alphabet l'alphabet qui permet de convertir (format json)
 * \return base dans l'alphabet correspondant (morse)
 */
string convertSentence(string base, json alphabet);

#endif //MORSE_MORSE_HPP

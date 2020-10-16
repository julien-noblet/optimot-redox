/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

// utiliser cette ligne pour une config gaucher (câble USB à gauche)
// #define MASTER_LEFT

// **OU BIEN** (ne pas définir les deux à la fois)

// utiliser cette ligne pour une config droitier (câble USB à droite)
#define MASTER_RIGHT

// #define EE_HANDS


/* RGB lighting */

#undef RGBLED_NUM
#undef RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LAYERS

/* Mouse (defaults en parenthèses, avec commentaire de la docu QMK) */

// (300) Delay between pressing a movement key and cursor movement
#define MOUSEKEY_DELAY 100

// (50) Time between cursor movements
#define MOUSEKEY_INTERVAL 25

// (10) Maximum cursor speed at which acceleration stops
#define MOUSEKEY_MAX_SPEED 12

// (20) Time until maximum cursor speed is reached
#define MOUSEKEY_TIME_TO_MAX 100

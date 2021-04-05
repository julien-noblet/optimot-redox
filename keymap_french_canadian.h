/* Copyright 2020
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "keymap.h"

// clang-format off

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ ^ │ ¸ │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ` │ < │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ « │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ É │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CF_HASH KC_NONUS_HASH  // #
#define CF_1    KC_1    // 1
#define CF_2    KC_2    // 2
#define CF_3    KC_3    // 3
#define CF_4    KC_4    // 4
#define CF_5    KC_5    // 5
#define CF_6    KC_6    // 6
#define CF_7    KC_7    // 7
#define CF_8    KC_8    // 8
#define CF_9    KC_9    // 9
#define CF_0    KC_0    // 0
#define CF_MINS KC_MINS // -
#define CF_EQL  KC_EQL  // =
// Row 2
#define CF_Q    KC_Q    // Q
#define CF_W    KC_W    // W
#define CF_E    KC_E    // E
#define CF_R    KC_R    // R
#define CF_T    KC_T    // T
#define CF_Y    KC_Y    // Y
#define CF_U    KC_U    // U
#define CF_I    KC_I    // I
#define CF_O    KC_O    // O
#define CF_P    KC_P    // P
#define CF_CIRC KC_LBRC // ^ (dead)
#define CF_CED KC_RBRC // ¸ (dead)
// Row 3
#define CF_A    KC_A    // A
#define CF_S    KC_S    // S
#define CF_D    KC_D    // D
#define CF_F    KC_F    // F
#define CF_G    KC_G    // G
#define CF_H    KC_H    // H
#define CF_J    KC_J    // J
#define CF_K    KC_K    // K
#define CF_L    KC_L    // L
#define CF_SCLN KC_SCLN // ;
#define CF_EGRV KC_QUOT // ` (dead)
#define CF_LESS KC_NUHS // <
#define CF_GRTR S(KC_NUHS) // >
// Row 4
#define CF_LGIL KC_NUBS // «
#define CF_RGIL S(KC_NUBS) // »
#define CF_Z    KC_Z    // Z
#define CF_X    KC_X    // X
#define CF_C    KC_C    // C
#define CF_V    KC_V    // V
#define CF_B    KC_B    // B
#define CF_N    KC_N    // N
#define CF_M    KC_M    // M
#define CF_COMM KC_COMM // ,
#define CF_DOT  KC_DOT  // .
#define CF_EACU KC_SLSH // É

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ | │ ! │ " │ / │ $ │ % │ ? │ & │ * │ ( │ ) │ _ │ + │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ : │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │   │   │   │   │   │   │   │   │ ' │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CF_PIPE S(CF_HASH) // | (pipe) 
#define CF_EXLM S(CF_1)    // !
#define CF_DQUO S(CF_2)    // "
#define CF_SLSH S(CF_3)    // /
#define CF_DLR  S(CF_4)    // $
#define CF_PERC S(CF_5)    // %
#define CF_QUES S(CF_6)    // ?
#define CF_AMPR S(CF_7)    // &
#define CF_ASTR S(CF_8)    // *
#define CF_LPRN S(CF_9)    // (
#define CF_RPRN S(CF_0)    // )
#define CF_UNDS S(CF_MINS) // _
#define CF_PLUS S(CF_EQL)  // +
// Row 2
// Row 3
#define CF_COLN S(CF_SCLN) // :
// Row 4
#define CF_QUOT S(CF_COMM) // '

/* AltGr symbols 
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ \ │ ± │ @ │ £ │ ¢ │ ¤ │ ¬ │ ¦ │ ² │ ³ │ ¼ │ ½ │ ¾ │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │   │   │   │   │   │   │   │   │ § │ ¶ │ [ │ ] │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │   │   │   │   │   │   │   │   │   │ ~ │ { │ } │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ° │   │   │   │   │   │   │ µ │ ¯ │ ­ │ ´ │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
// Row 1
#define CF_BSLS ALGR(CF_HASH) // \ (backslash) 
#define CF_PLMN ALGR(CF_1)    // ±
#define CF_AT   ALGR(CF_2)    // @
#define CF_PND  ALGR(CF_3)    // £
#define CF_CENT ALGR(CF_4)    // ¢
#define CF_CURR ALGR(CF_5)    // ¤
#define CF_NOT  ALGR(CF_6)    // ¬
#define CF_BRKP ALGR(CF_7)    // ¦
#define CF_SUP2 ALGR(CF_8)    // ²
#define CF_SUP3 ALGR(CF_9)    // ³
#define CF_QRTR ALGR(CF_0)    // ¼
#define CF_HALF ALGR(CF_EQL)  // ½
#define CF_TQTR ALGR(CF_EQL)  // ¾

// Row 2
#define CF_SECT ALGR(CF_O)    // §
#define CF_PARA ALGR(CF_P)    // ¶
#define CF_LBRC ALGR(CF_CIRC) // [
#define CF_RBRC ALGR(CF_CCED) // ]
// Row 3
#define CF_TILD ALGR(CF_SCLN) // ~
#define CF_LCBR ALGR(CF_DGRV) // {
#define CF_RCBR ALGR(CF_LABK) // }
// Row 4
#define CF_RNGA ALGR(CF_UGRV) // °
#define CF_MICR ALGR(CF_M)    // µ
#define CF_MACR ALGR(CF_COMM) // ¯
//#define CF_RABK ALGR(CF_DOT)  // ­ TODO: Inexistant?
#define CF_ACUT ALGR(CF_EACU)  // ´ (dead)

//#define CF_CCED MACRO(I(50), T(CF_CED), T(CF_C)) // ç
//#define CF_AGRV MACRO(I(50), T(CF_EGRV), T(CF_A)) // à
// DEPRECATED
//#define GR2A(kc) RCTL(kc)

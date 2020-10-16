#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include <print.h> //pour déboguage
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BEPO 0
#define _QWERTY 1
#define _FN 2
#define _FKEYS 3
#define _MOVE 4
#define _BEPOALTGRGRAVE 5
#define _BEPOALTGRACUTE 6
#define _BEPOALTGRCIRC 7

enum custom_keycodes {
		      BP_SPC = SAFE_RANGE,BP_BSPC,
		      // Bepo Keyboard layout:
		      BP_POUND, BP_1, BP_2, BP_3, BP_4, BP_5, BP_6, BP_7, BP_8, BP_9, BP_0, BP_EQUAL, BP_PERCENT,
		      BP_B, BP_EACUTE, BP_P, BP_O, BP_EGRAVE, BP_CIRC, BP_V, BP_D, BP_L, BP_J, BP_Z, BP_W,	     
		      BP_A, BP_U, BP_I, BP_E, BP_COMMA, BP_C, BP_T, BP_S, BP_R, BP_N, BP_M, BP_CCED,
		      BP_AGRV, BP_Y, BP_X, BP_DOT, BP_K, BP_APOS, BP_Q, BP_G, BP_H, BP_F
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // fonction principal de traitement des keypresses
  // returns false si le keypress ne demande pas de traitement supplémentaire par QMK, true si le keypress n'est pas traité ici.

  // TODO: 
  // - Bug majeur (fixed): les combinaisons AltGr+è U majuscule pour faire Ù ne fonctionne pas « all across the board »: on ne voit que la lettre de base et en minuscule, pas d'accent
  // - Linux i3 Alt(+Shift en bépo)+chiffre ne fonctionne pas. Même avec les fixes de event.release. rajouté un layer "natif" pour compenser.
  // - Avoir PouceDroit faire Enter et Move+PouceDroit faire la touche Delete est une recette pour des désastres; changer! Suggestion: mettre insert et delete sur les petites touches juste au-toutes
  // - des fois, le arobas (A commercial) ne passe pas, il semble être bloqué au niveau du OS à la job... ça devient chiant d'écrire des courriels quand ça arrive!


#ifdef CONSOLE_ENABLE
  //uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    
  if (record->event.pressed) {
    //uprintf("Start de event.pressed. mods=%d\n", get_mods());
    
    if (IS_LAYER_ON(_BEPOALTGRGRAVE)) { // layer accent grave
      uint8_t current_mods = get_mods();
      bool shifted = false;
      if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) shifted = true;
      clear_mods();

      //shift uniquement = laisser QMK traiter le keypress
      if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
      
      if (keycode == BP_A) {
	tap_code(KC_QUOT);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_A);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }
      
      if (keycode == BP_U) {
	tap_code(KC_QUOT);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_U);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_I) {
	tap_code(KC_QUOT);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_I);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_E) {
	tap_code(KC_QUOT);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_E);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_O) {
	tap_code(KC_QUOT);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_O);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }
      if (keycode == BP_SPC || keycode == BP_EGRAVE) {
	tap_code(KC_QUOT);
	tap_code(KC_SPC);
	layer_move(_BEPO);
	return false;
      }
      //if (keycode == BP_BSPC) { layer_move(_BEPO); return false; } 
      // cas par défaut:
      layer_move(_BEPO);
      return false; 
    }
    
    if (IS_LAYER_ON(_BEPOALTGRACUTE)) { // layer accent aigu
      bool shifted = false;
      if ((keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) { shifted = true; }
      clear_mods();

      //shift uniquement = laisser QMK traiter le keypress
      if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
      
      if (keycode == BP_A) {
	register_code(KC_RALT);
	tap_code(KC_SLSH);
	unregister_code(KC_RALT);
	
	if (shifted) { register_code(KC_LSFT); } 
	tap_code(KC_A);
	clear_mods();
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_U) {
	register_code(KC_RALT);
	tap_code(KC_SLSH);
	unregister_code(KC_RALT);
	
	if (shifted) { register_code(KC_LSFT); } 
	tap_code(KC_U);
	clear_mods();
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_I) {
	register_code(KC_RALT);
	tap_code(KC_SLSH);
	unregister_code(KC_RALT);
	
	if (shifted) { register_code(KC_LSFT); } 
	tap_code(KC_I);
	clear_mods();
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_E) {
	if (shifted) { register_code(KC_LSFT); } 
	tap_code(KC_SLASH);
	clear_mods();
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_O) {
	register_code(KC_RALT);
	tap_code(KC_SLSH);
	unregister_code(KC_RALT);
	
	if (shifted) { register_code(KC_LSFT); } 
	tap_code(KC_O);
	clear_mods();
	layer_move(_BEPO);
	return false;
      }
      if (keycode == BP_SPC || keycode == BP_EACUTE) {
	register_code(KC_RALT); 
	tap_code(KC_SLSH);
	unregister_code(KC_RALT);
	tap_code(KC_SPC);
	layer_move(_BEPO);
	return false;
      }
      //if (keycode == BP_BSPC) { layer_move(_BEPO); return false; }
      //return true;

      // cas par défaut
      layer_move(_BEPO);
      return false;
    }
        
    if (IS_LAYER_ON(_BEPOALTGRCIRC)) { // layer accent circonflexe
      bool shifted = false;
      if ((keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) { shifted = true; }
      clear_mods();

      //shift uniquement = laisser QMK traiter le keypress
      if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
      
      if (keycode == BP_A) {
	tap_code(KC_LBRC);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_A);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_U) {
	tap_code(KC_LBRC);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_U);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_I) {
	tap_code(KC_LBRC);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_I);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_E) {
	tap_code(KC_LBRC);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_E);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }    
      if (keycode == BP_O) {
	tap_code(KC_LBRC);
	if (shifted) register_code(KC_LSFT);
	tap_code(KC_O);
	if (shifted) unregister_code(KC_LSFT);
	layer_move(_BEPO);
	return false;
      }
      if (keycode == BP_SPC || keycode == BP_CIRC) {
	tap_code(KC_LBRC);
	tap_code(KC_SPC);
	layer_move(_BEPO);
	return false;
      }
      // if (keycode == BP_BSPC) { layer_move(_BEPO); return false; }    
      // return true;
      
      layer_move(_BEPO);
      return false;
    }
  
    if (IS_LAYER_ON(_BEPO)) {
      // uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
      uint8_t current_mods = get_mods();

      // peut ne pas être utile - a voir
      if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
      if (keycode == KC_LALT || keycode == KC_RALT) return true; 
      if (keycode == KC_LCTRL || keycode == KC_RCTRL) return true; 
      
      if (keycode == BP_POUND) {
	if ((current_mods & MOD_BIT (KC_RALT))) { // '\'
	  register_code(KC_RALT);
	  register_code(KC_GRV); 
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // # (on doit retirer shift pour le faire)
	  register_code(KC_GRV); 
	}      
	else { // $ 
	  register_code(KC_LSFT);	  
	  register_code(KC_4); 
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }
    
      if (keycode == BP_1) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_1); // 'Modificateurs déjà appuyés' + '1' 
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // '1'
	  register_code(KC_1);
	}      
	else {
	  register_code(KC_LSFT);
	  register_code(KC_2); // '"'
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      } 

      if (keycode == BP_2) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_2); // 'Modificateurs déjà appuyés' + '2' 
	}
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods();
	  register_code(KC_BSLS);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods();
	  register_code(KC_2);
	}      
	else {
	  register_code(KC_NUBS);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      } 

      if (keycode == BP_3) {
       	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) {
	  register_code(KC_3); // 'Modificateurs déjà appuyés' + '3' 
	}
	else if ((current_mods & MOD_BIT (KC_RALT))) { // '>'
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(KC_BSLS);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 3
	  register_code(KC_3);
	}      
	else { // '»'
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(KC_NUBS);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      } 

      if (keycode == BP_4) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_4); // 'Modificateurs déjà appuyés' + '4' 
	}
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // [
	  register_code(KC_RALT);
	  register_code(KC_LBRC);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 4
	  register_code(KC_4);
	}      
	else { // (
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(KC_9);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_5) {
       	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) {
	  register_code(KC_5); // 'Modificateurs déjà appuyés' + '5'
	}
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // ]
	  register_code(KC_RALT);
	  register_code(KC_RBRC);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 5
	  register_code(KC_5);
	}      
	else { // ) 
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(KC_0);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_6) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_6); // 'Modificateurs déjà appuyés' + '6'
	}
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // ^
	  //ne pourra pas être "tenue" pour répétition
	  tap_code(KC_LBRC);
	  tap_code(KC_SPC);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 6
	  register_code(KC_6);
	}      
	else { // @
	  clear_mods();
	  register_code(KC_RALT);
	  register_code(KC_2);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_7) { 
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_7); // 'Modificateurs déjà appuyés' + '7'
	}
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  // SEND_STRING("±"); // TODO a trouver
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 7
	  register_code(KC_7);
	}      
	else { // +
	  register_code(KC_LSFT);
	  register_code(KC_EQL);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_8) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_8); // 'Modificateurs déjà appuyés' + '8'
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 8
	  register_code(KC_8);	  
	}      
	else { // -
	  register_code(KC_MINS);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_9) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_9); // 'Modificateurs déjà appuyés' + '9'
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 9
	  register_code(KC_9);
	}      
	else { // '/'
	  register_code(KC_LSFT);
	  register_code(KC_3);	  
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_0) {
	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_0); // 'Modificateurs déjà appuyés' + '0'
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 0
	  register_code(KC_0);
	}      
	else { // *
	  register_code(KC_LSFT);
	  register_code(KC_8);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_EQUAL) { // 
	if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); 
	  register_code(KC_RALT);
	  register_code(KC_NUBS);
	}      
	else {
	  clear_mods(); // =
	  register_code(KC_EQL);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_PERCENT) { // `
	if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods();
	  tap_code(KC_QUOT); // pas répétable (tenu au clavier)
	  tap_code(KC_SPC);
	}      
	else { // %
	  register_code(KC_LSFT);
	  register_code(KC_5);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == BP_B) {
	uint8_t temp_mod = get_mods();
	if ((temp_mod & MOD_BIT (KC_RALT))) {
	  clear_mods(); //| 
	  register_code(KC_LSFT);
	  register_code(KC_GRV);
	  set_mods(temp_mod);
	}
	else {
	  register_code(KC_B);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }
    
      if (keycode == BP_EACUTE) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  layer_move(_BEPOALTGRACUTE);
	}
	else {
	  register_code(KC_SLSH);
	}
	return false;      
      }

      if (keycode == BP_P) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // '&'
	  register_code(KC_LSFT);
	  register_code(KC_7);
	}
	else {
	  register_code(KC_P);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      }

      if (keycode == BP_O) {
	// TODO: trouver pour le caractere "oe"
	register_code(KC_O);
	//tap_code(KC_O);
	return false;      
      }

      if (keycode == BP_EGRAVE) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  layer_move(_BEPOALTGRGRAVE);
	}
	else {
	  tap_code(KC_QUOT);
	  tap_code(KC_E);
	}
	return false;
      }

      if (keycode == BP_CIRC) { //exclamation en shift ou altgr
	if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  register_code(KC_LSFT);
	  register_code(KC_1);
	} else {
	  layer_move(_BEPOALTGRCIRC);
	}
	return false;
      }

      if (keycode == BP_V) {
	register_code(KC_V);
	return false;      
      }

      if (keycode == BP_D) {
	register_code(KC_D);
	return false;      
      }

      if (keycode == BP_L) {
	register_code(KC_L);
	return false;      
      }

      if (keycode == BP_J) {
	register_code(KC_J);
	return false;      
      }
    
      if (keycode == BP_Z) {
	register_code(KC_Z);
	return false;      
      }
    
      if (keycode == BP_W) {
	register_code(KC_W);
	return false;      
      }

      if (keycode == BP_CCED) {
	bool shiftPressed = false;
	if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) shiftPressed = true;	
	clear_mods();
	tap_code(KC_RBRC);
	if (shiftPressed) register_code(KC_LSFT);
	tap_code(KC_C);
	if (shiftPressed) unregister_code(KC_LSFT);
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      }

      if (keycode == BP_A) {
	// TODO: Trouver pour æ (caractere ae sur AltGr)
	register_code(KC_A);      
	return false;      
      }

      if (keycode == BP_U) {
	register_code(KC_U);
	return false;      
      }

      if (keycode == BP_I) {
	register_code(KC_I);
	return false;      
      }

      if (keycode == BP_E) {
	// TODO: trouver pour æ (caractere ae)
	register_code(KC_E);      
	return false;      
      }

      if (keycode == BP_COMMA) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // '
	  register_code(KC_LSFT);
	  register_code(KC_COMM);
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods();	
	  register_code(KC_SCLN);
	} else {
	  register_code(KC_COMM);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      }

      if (keycode == BP_C) {
	// todo: layer cedille?
	register_code(KC_C);
	return false;      
      }

      if (keycode == BP_T) {
	register_code(KC_T);
	return false;      
      }
    
      if (keycode == BP_S) {
	register_code(KC_S);
	return false;      
      }

      if (keycode == BP_R) {
	register_code(KC_R);
	return false;      
      }

      if (keycode == BP_N) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // ~
	  register_code(KC_RALT);
	  register_code(KC_SCLN);
	}
	else {
	  register_code(KC_N);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == BP_M) {
	register_code(KC_M);
	return false;      
      } 

      if (keycode == BP_AGRV) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // '\' char
	  register_code(KC_RALT);
	  register_code(KC_GRV);
	} else { // à
	  //todo: actuellement pas répétable
	  tap_code(KC_QUOT);
	  tap_code(KC_A);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == BP_Y) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // {
	  register_code(KC_RALT);
	  register_code(KC_QUOT);
	}
	else {
	  register_code(KC_Y);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == BP_X) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); //| 
	  register_code(KC_LSFT);
	  register_code(KC_GRV);
	}
	else {
	  register_code(KC_X);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == BP_DOT) {
	// TODO: a été mis à "}", faute de trouver '…' (points de suspension) sur le clavier Canadien Français
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // }
	  register_code(KC_RALT);
	  register_code(KC_BSLS);
	}	
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  uint8_t temp_mod = get_mods(); 
	  clear_mods();
	  register_code(KC_LSFT);  
	  register_code(KC_SCLN); // :
	  set_mods(temp_mod);
	} else {
	  register_code(KC_DOT);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == BP_K) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // ~
	  register_code(KC_RALT);
	  register_code(KC_SCLN);
	}
	else {
	  register_code(KC_K);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == BP_APOS) {
	//if ((current_mods & MOD_BIT (KC_RALT))) {
	//  send_string("¿"); //TODO: Trouver
	//}
	if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
 	  clear_mods(); // ?
	  register_code(KC_LSFT);
	  register_code(KC_6);
	} else {
 	  clear_mods(); // '
	  register_code(KC_LSFT);
	  register_code(KC_COMM);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;  
      } 

      if (keycode == BP_Q) {
	register_code(KC_Q);
	return false;      
      } 

      if (keycode == BP_G) {
	register_code(KC_G);
	return false;      
      } 

      if (keycode == BP_H) {
	register_code(KC_H);
	return false;      
      }
    
      if (keycode == BP_F) {
	register_code(KC_F);
	return false;      
      }

      if (keycode == BP_SPC) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // _
	  register_code(KC_LSFT);
	  register_code(KC_MINS);
	}
	else {
	  register_code(KC_SPC);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }
    
      return true;
    
    } // fin layer _bepo
 
  }
  //uprintf("Uncaught keypress (tombe jusqu'a la fin de la fonction)\n");
  return true; 
};


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  // function qui est appelée une fois que le keypress a été traité dans process_record_user().

  if (IS_LAYER_ON(_BEPO) && !record->event.pressed) {
    //clear_keyboard(); // bug: reset TOUT.
    //                     Keybinds emacs avec plusieurs touches Mods successives impossible sans la relâcher.
    //                     Alt-Tab en cherchant dans les plus vieux apps impossible.
    
    //unregister_code(keycode); // bug: touches pressed programatically restent collés,
    //                                  génère des input en trop. doit les clairer ici en code.

    clear_keyboard_but_mods(); // en cours de test, semble prometteur
                               // MAJ Septembre 2020: Marche à 99.9%! Des fois une touche colle, rarement. À diagnostiquer.

    // ne PAS tenter de relacher les autres touches "virtuelles".
    // sinon, les enchaînements avec modificateurs risquent de ne pas
    // fonctionner. Traiter les edge cases en cas de vrais problèmes.
  }
  
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// layer de base en bépo. permet de passer en QWERTY avec la touche à l'extrème droite en bas.
        [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      BP_POUND, BP_1,    BP_2,    BP_3,    BP_4,   BP_5,                                                BP_8,    BP_9,    BP_0,   BP_EQUAL,BP_PERCENT,KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  BP_B,   BP_EACUTE, BP_P,    BP_O,  BP_EGRAVE, BP_6,                              BP_7,   BP_CIRC, BP_V,    BP_D,    BP_L,    BP_J,    BP_CCED,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_BSPC, BP_A,    BP_U,     BP_I,   BP_E,   BP_COMMA,  BP_Z,                              BP_W,   BP_C,    BP_T,    BP_S,    BP_R,    BP_N,    BP_M,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT, BP_AGRV, BP_Y,     BP_X,   BP_DOT,   BP_K,    BP_8,    BP_9,           KC_NO,  KC_NO,    BP_APOS, BP_Q,    BP_G,    BP_H,    BP_F,   KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
      KC_LCTL, MO(_FN),KC_LGUI, LALT_T(KC_ESC),MO(_MOVE),   BP_SPC,  KC_TAB,          KC_RALT, KC_ENT,      KC_RALT,      KC_Z,    KC_NO, TG(_FKEYS),TO(_QWERTY)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			 ),
	// layer QWERTY pour compatibilité.
        [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐	
      KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,    KC_W,     KC_E,    KC_R,   KC_T,     KC_6,                              KC_7,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_LBRC,                           KC_RBRC,  KC_H,   KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,   KC_NO,           KC_NO,   KC_NO,    KC_N,   KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤   
      KC_LCTL, MO(_FN), KC_LGUI,LALT_T(KC_ESC),TT(_MOVE),   KC_SPC,  KC_TAB,          KC_RALT, KC_ENT,     KC_RALT,       KC_NO,   KC_NO,   KC_NO,  TO(_BEPO)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			   ), 
	// touches de fonctions (F keys dans le haut, numpad côté droit du clavier)
        [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,   KC_F1,   KC_F2,  KC_F3,    KC_F4,   KC_F5,                                              KC_F8,    KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_NLCK,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,   KC_F6,                             KC_F7,   KC_P7,    KC_P8,  KC_P9,  KC_PMNS, KC_PAST,KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,   KC_NO,                             KC_NO,   KC_P4,   KC_P5,   KC_P6,  KC_PPLS, KC_PSLS, KC_PENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_K, RGB_M_G,   KC_NO,   KC_NO,           KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,  KC_PPLS, KC_PAST, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤   
     KC_LCTL, KC_TRNS, KC_LGUI, KC_LALT,       KC_NO,       KC_NO,   KC_NO,           KC_NO,   KC_ENT,      KC_P0,       KC_PDOT,  KC_ENT,  KC_NO,   RESET
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
		     ),
	// il semble que mes manipulations avec BP_chiffres etc ne joue pas bien avec certains raccourcis tels que les alt+shift+1 dans i3 sous Linux.
	// ce layer est essentiellement mon "failsafe default" si les raccourcis avancés ne marchent pas, qui lance les touches "nativement"
        [_FKEYS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_NO,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                KC_6,    KC_7,    KC_8,   KC_9,     KC_0,    KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,                             KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   TG(_FKEYS), KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,                             KC_NO,  KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  TG(_FKEYS),KC_NO,          KC_NO, TG(_FKEYS),KC_HOME,KC_PGDN, KC_PGUP,  KC_END,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤   
     KC_LCTL, KC_TRNS, KC_LGUI, KC_LALT,     MO(_MOVE),     KC_NO,   KC_NO,           KC_NO,   KC_NO,       KC_NO,        KC_NO,  KC_NO,    KC_NO, TG(_FKEYS)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
		     ),
	// layer de mouvement
	// alt+f4 sur MOVE+É, pour imiter un Ctrl+W
        [_MOVE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐	
     KC_ACL0,  KC_ACL1, KC_ACL2, KC_NO,  KC_PSCR, KC_PAUS,                                             KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,  KC_BTN3, KC_SLCK,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,  LALT(KC_F4),KC_NO,  KC_NO,   KC_NO,  KC_MSTP,                           KC_MPLY, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_BTN1, KC_BTN2,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   GUI_OFF,   KC_NO,   KC_NO,   KC_NO,KC_WWW_BACK,                KC_WWW_FORWARD, KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT,  KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_NO,   GUI_ON,   KC_NO,   KC_NO,   KC_NO,  KC_VOLD, KC_VOLU,          KC_NO,  KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,  KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL,  KC_NO,   KC_LGUI, KC_LALT,      KC_TRNS,      KC_NO, KC_MUTE,          KC_INS, KC_DEL,        KC_NO,       KC_NO,   KC_NO,   KC_NO,  TG(_QWERTY)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			     ), 
        [_BEPOALTGRGRAVE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   BP_O,  BP_EGRAVE, KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      BP_BSPC, BP_A,    BP_U,    BP_I,    BP_E,    KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,       BP_SPC,  KC_NO,           KC_NO,   KC_NO,       KC_NO,         KC_NO,  KC_NO,   KC_NO,   DF(_BEPO)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			 ),

        [_BEPOALTGRACUTE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,  BP_EACUTE,KC_NO,   BP_O,    KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      BP_BSPC, BP_A,    BP_U,    BP_I,    BP_E,    KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,       BP_SPC,  KC_NO,           KC_NO,   KC_NO,       KC_NO,         KC_NO,  KC_NO,   KC_NO,   DF(_BEPO)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			 ),

        [_BEPOALTGRCIRC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   BP_O,    KC_NO,  BP_CIRC,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      BP_BSPC, BP_A,    BP_U,    BP_I,    BP_E,    KC_NO,   KC_NO,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,       BP_SPC,  KC_NO,           KC_NO,   KC_NO,       KC_NO,         KC_NO,  KC_NO,   KC_NO,   DF(_BEPO)
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			 ),	
};



#ifdef RGBLIGHT_ENABLE
// Section RGB, complètement rippé des exampdes de la docu qmk:
//     https://docs.qmk.fm/#/feature_rgblight

// TODO: Faire marcher en tant que right master. actuellement ne
// marche pas et on DOIT flasher les deux bords pour réfléter les
// changements, tel que le wiki Redox le disait

const rgblight_segment_t PROGMEM my_canadian_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_CYAN}
    //{12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t PROGMEM my_bepo_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_BLUE}       // Light 4 LEDs, starting with LED 6
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_bepo_layer,
    my_canadian_layer    // Overrides caps lock layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    
    // debug main de droite qui ne respecte plus les activations de layers de lumière...
    rgblight_set_layer_state(1, true); //active le layer lumière bépo d'abord
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(0, layer_state_cmp(state, _BEPO));
    return state;
}

//bool led_update_user(led_t led_state) {
//    rgblight_set_layer_state(0, led_state.caps_lock);
//    return true;
//}

#endif

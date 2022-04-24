#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
#include <print.h> //pour déboguage
#endif

#include <keymap_french_canadian.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BEPO 0
#define _QWERTY 1
#define _FN 2
#define _MOVE 3

#define WS_PREV   LCTL(LGUI(KC_LEFT))  //Next Workspace (Windows 10)
#define WS_NEXT   LCTL(LGUI(KC_RIGHT)) //Previous Workspace (Windows 10)
#define ALT_ESC   LALT_T(KC_ESC)       //Tenu pourAlt, appuyé pour ESC

enum custom_keycodes {
  BP_CCED = SAFE_RANGE, BP_AGRV
};

void shifted_tap(bool shifted, uint16_t keycode) {
	if (shifted) register_code(KC_LSFT);
	tap_code(keycode);
	if (shifted) unregister_code(KC_LSFT);
	return;
}

// retrun true si une touche Alt (sauf altgr), Ctrl ou Shift est tenu
bool has_mods(uint8_t mods) { //get_mods()
  return (mods & MOD_BIT (KC_LALT)) || (mods & MOD_BIT (KC_LCTRL)) || (mods & MOD_BIT (KC_RCTRL)) || (mods & MOD_BIT (KC_LGUI));
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // fonction principal de traitement des keypresses
  // returns false si le keypress ne demande pas de traitement supplémentaire par QMK, true si le keypress n'est pas traité ici.

  uint8_t current_mods = get_mods();
  bool shifted = false;
  if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) shifted = true;
  
#ifdef CONSOLE_ENABLE
  /*
  if (keycode > 60) {
    char* key = "";

    if (keycode == 20740) key = "(Holding _MOVE)";
    if (keycode == 20738) key = "(Holding _FN)";

    if (keycode == 79) key = "(Right)";
    if (keycode == 80) key = "(Left)";
    if (keycode == 81) key = "(Down)";
    if (keycode == 82) key = "(Up)";

    if (keycode == 225) key = "(Shift Left)";
    if (keycode == 229) key = "(Shift Right)";

    if (keycode == 224) key = "(Ctrl Left)";
    if (keycode == 228) key = "(Ctrl Right)";

    if (keycode == 230) key = "(AltGr)";   
    if (keycode == ALT_ESC) key = "Alt/Esc"; // Touche macro "alt if
				      	     // held, esc if tapped"
    if (record->event.pressed) dprintf("Up: kc: 0x%04X %s\n", keycode, key);
    else {
      dprintf("Down: kc: 0x%04X %s\n", keycode, key);
    }
  }
  */
#endif
    
  if (record->event.pressed) {
    // ATTENTION: Mettre les blocks dans l'ordre inverse des layers
    
    //dprintf("Start de event.pressed. mods=%d\n", get_mods());
    
    if (IS_LAYER_ON(_BEPO)) {
      // dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);

      // peut ne pas être utile - a voir
      if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
      if (keycode == KC_LALT || keycode == KC_RALT) return true; 
      if (keycode == KC_LCTRL || keycode == KC_RCTRL) return true; 
      
      if (keycode == CF_HASH) { // touche à côté du 1 ($ en bépo, # en CF)
	if ((current_mods & MOD_BIT (KC_RALT))) { // '\'
	  register_code(KC_RALT);
	  register_code(KC_GRV);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods();          // # (on doit retirer shift pour le faire)
	  register_code(KC_GRV);
	}      
	else { // $
	  register_code(KC_LSFT);	  
	  register_code(KC_4);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }
    
      if (keycode == CF_1) {
	if (IS_LAYER_ON(_FN)) return true; // '1' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' + '1' 
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // '1'
	  register_code(CF_1);
	  set_mods(current_mods); // requis pour restaurer clear_mods()
	}      
	else {
	  register_code(KC_LSFT);
	  register_code(CF_2); // '"'
	  unregister_code(KC_LSFT);
	}
	return false;
      } 

      if (keycode == CF_2) {
	if (IS_LAYER_ON(_FN)) return true; // '2' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' + '2' 
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods();
	  register_code(KC_BSLS);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods();
	  register_code(CF_2);
	}      
	else {
	  register_code(KC_NUBS);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      } 

      if (keycode == CF_3) {
	if (IS_LAYER_ON(_FN)) return true; //'3' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' + '3' 
	else if ((current_mods & MOD_BIT (KC_RALT))) { // '>'
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(KC_BSLS);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 3
	  register_code(CF_3);
	}      
	else { // '»'
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(KC_NUBS);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      } 

      if (keycode == CF_4) {
	if (IS_LAYER_ON(_FN)) return true; //'4' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '4 CF natif' 
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // [
	  register_code(KC_RALT);
	  register_code(KC_LBRC);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 4
	  register_code(CF_4);
	}      
	else { // (
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(CF_9);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_5) {
	if (IS_LAYER_ON(_FN)) return true; //'5' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '5 CF natif' 
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // ]
	  register_code(KC_RALT);
	  register_code(KC_RBRC);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 5
	  register_code(CF_5);
	}      
	else { // ) 
	  clear_mods();
	  register_code(KC_LSFT);
	  register_code(CF_0);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_6) {
	if (IS_LAYER_ON(_FN)) return true; //'6' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '6 CF natif'
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // '^'
	  tap_code(KC_LBRC);
	  tap_code(KC_SPC);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 6
	  register_code(CF_6);
	}      
	else { // '@'
	  clear_mods();
	  register_code(KC_RALT);
	  register_code(CF_2);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_7) { 
	if (IS_LAYER_ON(_FN)) return true; //'7' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '7 CF natif' 	
	else if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // '±'
	  register_code(KC_RALT);
	  register_code(CF_1);
	}      
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 7
	  register_code(CF_7);
	}      
	else { // +
	  register_code(KC_LSFT);
	  register_code(KC_EQL);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_8) {
	if (IS_LAYER_ON(_FN)) return true; //'8' CF natif
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '8 CF natif' 	
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // '8'
	  register_code(CF_8);	  
	}      
	else { // '-'
	  register_code(KC_MINS);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_9) {
	if (IS_LAYER_ON(_FN)) return true; //'9' CF natif
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '9 CF natif' 	
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // '9'
	  register_code(CF_9);
	}      
	else { // '/'
	  register_code(KC_LSFT);
	  register_code(CF_3);	  
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_0) {
	if (IS_LAYER_ON(_FN)) return true; //'0' natif CF
	if ( has_mods(current_mods) ) register_code(keycode); // 'Modificateurs déjà appuyés' +
							      // '0 CF natif' 	
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  clear_mods(); // 0
	  register_code(CF_0);
	}      
	else { // *
	  register_code(KC_LSFT);
	  register_code(CF_8);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;
      }

      if (keycode == CF_EQL) { //
       	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_MINS); // 'Modificateurs déjà appuyés' + '-' sur QWERTY
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
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

      if (keycode == CF_PERC) { // `
       	if ( (current_mods & MOD_BIT (KC_LALT)) || (current_mods & MOD_BIT (KC_LCTRL)) || (current_mods & MOD_BIT (KC_LGUI)) ) { 
	  register_code(KC_EQL); // 'Modificateurs déjà appuyés' + '=' sur QWERTY
	}
	else if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
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

      if (keycode == CF_B) {
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
    
      if (keycode == CF_EACU) {
	//dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
	register_code(KC_SLSH);
	return false;      
      }

      if (keycode == CF_P) {
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

      if (keycode == CF_O) {
	// TODO: trouver pour le caractere "oe"
	register_code(KC_O);
	//tap_code(KC_O);
	return false;      
      }

      if (keycode == CF_EGRV) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  // laisser le clavier du OS gérer la touche morte
	  unregister_code(KC_RALT);
	  tap_code(KC_QUOT);
	}
	else { // 'è'
	  tap_code(KC_QUOT);
	  tap_code(CF_E);
	}
	return false;
      }

      if (keycode == CF_CIRC) { //exclamation en shift ou altgr
	if ((current_mods & MOD_BIT (KC_LSFT)) || (current_mods & MOD_BIT (KC_RSFT))) {
	  //register_code(KC_LSFT);
	  register_code(CF_1); // '!'
	} else {
	  // laisser le clavier du OS gérer la touche morte
	  tap_code(CF_CIRC);
	}
	return false;
      }

      if (keycode == CF_V) {
	register_code(KC_V);
	return false;      
      }

      if (keycode == CF_D) {
	register_code(KC_D);
	return false;      
      }

      if (keycode == CF_L) {
	register_code(KC_L);
	return false;      
      }

      if (keycode == CF_J) {
	register_code(KC_J);
	return false;      
      }
    
      if (keycode == CF_Z) {
	register_code(KC_Z);
	return false;      
      }
    
      if (keycode == CF_W) {
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

      if (keycode == CF_A) {
	// TODO: Trouver pour æ (caractere ae sur AltGr)
	register_code(KC_A);      
	return false;      
      }

      if (keycode == CF_U) {
	register_code(KC_U);
	return false;      
      }

      if (keycode == CF_I) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  // laisser le clavier du OS gérer la touche morte trema
	  unregister_code(KC_RALT);

	  register_code(KC_LSFT);
	  tap_code(KC_RBRC);
	  unregister_code(KC_LSFT);
	}
	else { // 'i'
	  register_code(KC_I);
	}
	return false;
	//code original I seulement: 
	//register_code(KC_I);
	//return false;      
      }

      if (keycode == CF_E) {
	// TODO: trouver pour æ (caractere ae)
	register_code(KC_E);      
	return false;      
      }

      if (keycode == CF_COMM) {
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

      if (keycode == CF_C) {
	// todo: layer cedille?
	register_code(KC_C);
	return false;      
      }

      if (keycode == CF_T) {
	register_code(KC_T);
	return false;      
      }
    
      if (keycode == CF_S) {
	register_code(KC_S);
	return false;      
      }

      if (keycode == CF_R) {
	register_code(KC_R);
	return false;      
      }

      if (keycode == CF_N) {
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

      if (keycode == CF_M) {
	register_code(KC_M);
	return false;      
      } 

      if (keycode == BP_AGRV) {
	if ((current_mods & MOD_BIT (KC_RALT))) {
	  clear_mods(); // '\' char
	  register_code(KC_RALT);
	  register_code(KC_GRV);
	} else { // à
	  tap_code(KC_QUOT);
	  tap_code(KC_A);
	}
	set_mods(current_mods); // requis pour restaurer clear_mods()
	return false;      
      } 

      if (keycode == CF_Y) {
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

      if (keycode == CF_X) {
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

      if (keycode == CF_DOT) {
	// TODO: a été mis à "}", faute de trouver '…' (points de suspension) nativement sur le clavier Canadien Français
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

      if (keycode == CF_K) {
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

      if (keycode == CF_QUOT) {
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

      if (keycode == CF_Q) {
	register_code(KC_Q);
	return false;      
      } 

      if (keycode == CF_G) {
	register_code(KC_G);
	return false;      
      } 

      if (keycode == CF_H) {
	register_code(KC_H);
	return false;      
      }
    
      if (keycode == CF_F) {
	register_code(KC_F);
	return false;      
      }

      if (keycode == KC_SPC) {
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

      // trop verbose (affiche tout les keypresses - Fkeys, MO(LAYER), C(S(LEFT
      //ou RIGHT)), BSPC, ...). Décommenter au besoin
      //dprintf("_BEPO block: Uncaught keypress (ne devrait pas arriver), 0x%04X\n", keycode);
      return true;
    
    } // fin layer _bepo

    
  } else {
    // block record->event.pressed == false
    // (on vient de relacher une touche)
    
    uint8_t current_mods = get_mods();

    if (keycode == ALT_ESC) {
      // touche macro QMK sur le alt de gauche. attention: garder topmost.
      // descendre ce code if sous le block if current_mods plus bas va causer
      // que la touche alt va rester coller. 
      unregister_code(keycode);
      unregister_code(KC_LALT);
      clear_keyboard_but_mods();
      return false;
    }
    
    if (keycode == MO(_MOVE) || keycode == MO(_FN)) {
      unregister_code(keycode);
      //clear_keyboard_but_mods(); //eeeuh...
      return true; // pour que QMK relache lui meme le layers
    }

    if (IS_LAYER_ON(_MOVE) && keycode == MO(_MOVE)) {
      //dprintf("_MOVE released\n");
      clear_keyboard();
      layer_move(_BEPO);
      return false;
    }
    if (IS_LAYER_ON(_FN) && keycode == MO(_FN)) {
      //dprintf("_FN released\n");
      clear_keyboard();
      layer_move(_BEPO);
      return false;
    }    
    
    if ((current_mods)) {
      // ce block est nécessaire pour régler les touches de base qui colle
      // lorsqu'on fait en bépo un AltGr+Whatever qui initialise une autre
      // combinaison "programmée" sous le clavier Canadien Français.
      //
      // ex: Bépo AltGr+5 (]) faisait spammer un "^^^^^^..." infini additionnel,
      // car la touche de base en CaFr ^ n'était pas toujours décollée si on
      // écrivait vite la combo AltGr+5.
      
      //dprintf("mod unregister avec current_mods restants: kc 0x%04X, current_mods: 0x%04X\n", keycode, current_mods);
      
      unregister_code(keycode);
      clear_keyboard_but_mods(); 
      //clear_keyboard(); combinaison emacs C-x C-s impossible si on active ça là

      return false;
    }

    
    //if (IS_LAYER_ON(_BEPO) && !get_mods()) {
    if (IS_LAYER_ON(_BEPO) && !current_mods) {
      // ce block est nécessaire pour permettre un meilleur support
      // pour le gaming (appuyer/relâcher plus qu'une touche à la
      // fois de manière indépendante)
      // note: pas sur que c'est la manière correcte...
      unregister_code(keycode);

      // TODO: traiter les touches qui collent sur le layer _BEPO ici:
      if (shifted == false) {
	switch (keycode) {

	  //les touches de base sous bépo qui gènère un keypress autre sous CF:
	case CF_HASH:
	  unregister_code(CF_4);
	  return false;	  
	case CF_1:
	  unregister_code(CF_2);
	  return false;
	case CF_2:
	  unregister_code(CF_LGIL); // «
	  return false;
	case CF_3:
	  unregister_code(CF_LGIL); // « 
	  return false;
	case CF_4:
	  unregister_code(CF_9);
	  return false;
	case CF_5:
	  unregister_code(CF_0);
	  return false;
	case CF_6:
	  unregister_code(CF_2);
	  return false;
	case CF_7:
	  unregister_code(CF_EQL);
	  return false;
	case CF_8:
	  unregister_code(CF_MINS);
	  return false;
	case CF_9:
	  unregister_code(CF_3);
	  return false;
	case CF_0:
	  unregister_code(CF_8);
	  return false;
	}
      }
	return false;
    }

    

    if (IS_LAYER_ON(_QWERTY) && keycode == TO(_BEPO)) {
      //dprintf("_QWERTY released\n");
      clear_keyboard();
      layer_move(_BEPO);
      return false;
    }    

    
    //dprintf("Uncaught release: keycode 0x%04X\n", keycode);
    
    //unregister_code(keycode);
    //return false;
    return true;
    
  } // fin "n'est pas record->event.pressed true"


  // Si un keypress tombe ici, c'est qu'il a probablement été appuyé d'un layer
  // autre genre _FN ou _QWERTY. CECI EST NORMAL

  // plus valide - ne pas décommenter:
  
  return true; 
};


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  // function qui est appelée une fois que le keypress a été traité dans process_record_user().
  // dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);

  // migré dans le dernier block if dans la function process_record_user juste dessus.

  //if (IS_LAYER_ON(_BEPO) && !record->event.pressed) {
    //clear_keyboard(); // bug: reset TOUT. Keybinds emacs avec
    //                     plusieurs touches modificateurs (C-x C-s)
    //                     successives impossible sans la relâcher.
    //                     Alt-Tab en cherchant dans les plus vieux
    //                     apps impossible.
    
    //unregister_code(keycode); // bug: touches pressed programatically restent collés,
    //                                  génère des input en trop. doit les clairer ici en code.
    
    // "ancien fix" live
    //clear_keyboard_but_mods(); // MAJ Septembre 2020: Marche à 99.9%! Des fois une touche colle, rarement. À diagnostiquer.
  //}
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// layer de base en bépo. 
        [_BEPO] = LAYOUT( //layer type: base
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     CF_HASH,   CF_1,    CF_2,    CF_3,    CF_4,    CF_5,                                                CF_8,    CF_9,    CF_0,   CF_EQL,  CF_PERC, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,    CF_B,  CF_EACU,   CF_P,    CF_O,  CF_EGRV,   CF_6,                              CF_7,   CF_CIRC, CF_V,    CF_D,    CF_L,    CF_J,    BP_CCED,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC,   CF_A,    CF_U,    CF_I,    CF_E,  CF_COMM,   CF_Z,                              CF_W,   CF_C,    CF_T,    CF_S,    CF_R,    CF_N,    CF_M,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, BP_AGRV,   CF_Y,    CF_X,   CF_DOT,   CF_K,   CF_8,    CF_9,            WS_PREV, WS_NEXT,  CF_QUOT, CF_Q,    CF_G,    CF_H,    CF_F,   KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL, MO(_FN), KC_LGUI, ALT_ESC,     MO(_MOVE),     KC_SPC,  KC_TAB,          KC_RALT, KC_ENT,     KC_RALT,      KC_APP, TO(_QWERTY),MO(_FN),KC_RCTL
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			  ),                                                                                                      
	// layer QWERTY pour compatibilité, wife acceptance factor et gaming
        [_QWERTY] = LAYOUT( //layer type: base
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐	
      KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                KC_8,    KC_9,    KC_0,  KC_MINS,  KC_EQL, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_6,                              KC_7,    KC_Y,    KC_U,    KC_I,   KC_O,     KC_P,  KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_LBRC,                           KC_RBRC,  KC_H,   KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    CF_8,    CF_9,          WS_PREV, WS_NEXT,  KC_N,   KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤   
      KC_LCTL, MO(_FN), KC_LGUI, ALT_ESC,    MO(_MOVE),     KC_SPC,  KC_TAB,         KC_RALT, KC_ENT,     KC_RALT,       KC_APP, TO(_BEPO), MO(_FN), KC_RCTL
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			   ), 
	// touches de fonctions (F keys dans le haut, numpad côté droit du clavier)
        [_FN] = LAYOUT( //layer type: hold
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
      KC_ESC,   KC_F1,   KC_F2,  KC_F3,    KC_F4,   KC_F5,                                              KC_F8,    KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_NLCK,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,   KC_F6,                             KC_F7,   KC_7,    KC_8,    KC_9,  KC_PMNS, KC_PAST,KC_PSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,   KC_NO,                             KC_NO,   KC_4,    KC_5,    KC_6,  KC_PPLS, KC_PSLS, KC_PENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_K, RGB_M_G,   KC_NO,   KC_NO,           KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,  KC_PPLS, KC_PAST, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤   
     KC_LCTL, KC_TRNS, KC_LGUI, KC_LALT,       KC_NO,       KC_NO,   KC_NO,           KC_NO,   KC_ENT,       KC_0,        KC_DOT,  KC_ENT, KC_TRNS,   RESET
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
		     ),
	// layer de mouvement
	// alt+f4 sur MOVE+É, pour imiter un Ctrl+W
        [_MOVE] = LAYOUT( //layer type: hold
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐	
     KC_ACL0,  KC_ACL1, KC_ACL2, KC_NO,  KC_PSCR, KC_PAUS,                                             KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,  KC_BTN3, KC_SLCK,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,  LALT(KC_F4),KC_NO,  KC_NO,   KC_NO,  KC_MSTP,                           KC_MPLY, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  KC_BTN1, KC_BTN2,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_NO,   KC_NO,   GUI_OFF,   KC_NO,   KC_NO,   KC_NO,KC_WWW_BACK,                KC_WWW_FORWARD, KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT,  KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT,  KC_NO,   GUI_ON,   KC_NO,   KC_NO,   KC_NO,  KC_VOLD, KC_VOLU,          KC_NO,  KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,  KC_RSFT,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL,  KC_NO,   KC_LGUI, KC_LALT,      KC_TRNS,      KC_NO, KC_MUTE,          KC_INS, KC_DEL,        KC_NO,       KC_NO, TO(_BEPO),  KC_NO,  KC_NO  
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
			     ), 
};


#ifdef RGBLIGHT_ENABLE
// Section RGB, complètement rippé des exampdes de la docu qmk:
//     https://docs.qmk.fm/#/feature_rgblight 

// on DOIT flasher les deux bords pour réfléter les changements, tel
// que le wiki Redox le disait

const rgblight_segment_t PROGMEM my_canadian_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    									   {5,2,HSV_RED},
									   {7,2,HSV_RED}		
									   
									   /*{0,1,HSV_BLUE},
									     ...
									     {6,1,HSV_RED},
									   
									     {7,1,HSV_RED},
									     ...
									     {13,1,HSV_BLUE},*/
);

const rgblight_segment_t PROGMEM my_bepo_layer[] = RGBLIGHT_LAYER_SEGMENTS(
									   {5,2,HSV_BLUE},
									   {7,2,HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_move_layer[] = RGBLIGHT_LAYER_SEGMENTS(
									   // 6-7 ordinairement inner leds
									   // 0-13 ordinairement outer leds
									   {0,2,HSV_GREEN},									   
									   {12,2,HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_func_layer[] = RGBLIGHT_LAYER_SEGMENTS(
									   {0,2,HSV_MAGENTA},									   
									   {12,2,HSV_MAGENTA}
);



// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
									       my_func_layer,
									       my_move_layer,
									       my_bepo_layer,
									       my_canadian_layer

);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(2, true); //active le layer lumière bépo d'abord

    // peut pas enabled debug ET avoir LED en même temps
    //debug_enable=true;
    //debug_keyboard=true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(3, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _MOVE));
    rgblight_set_layer_state(0, layer_state_cmp(state, _FN));
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _BEPO));
    return state;
}

//bool led_update_user(led_t led_state) {
//    rgblight_set_layer_state(0, led_state.caps_lock);
//    return true;
//}

#endif

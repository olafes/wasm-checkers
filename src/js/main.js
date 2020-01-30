import { Draughts } from './Draughts.js'
import { DraughtsBoard } from './DraughtsBoard.js'
'use strict';


if (typeof WebAssembly === 'object') {
  // show loading screen
  Module.onRuntimeInitialized = () => {
    // hide loading screen
    // const draughts = new Draughts();
    const $main = document.querySelector('main');
    const $template = document.querySelector('#draughtsTemplate');
    const board = new DraughtsBoard($template, $main);
    board.loadFEN("W:W31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50:B1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20");
  };
} else {
  // TODO show information that webassembly cannot be loaded
}

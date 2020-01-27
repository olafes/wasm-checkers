import { Draughts } from './Draughts.js'
'use strict';


if (typeof WebAssembly === 'object') {
  // show loading screen
  Module.onRuntimeInitialized = () => {
    // hide loading screen
    const draughts = new Draughts();
    // const board = new DraughtsBoard(draughts);
  };
} else {
  // TODO show information that webassembly cannot be loaded
}

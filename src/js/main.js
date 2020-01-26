import { DraughtsBoard } from './Board.js'

const $main = document.querySelector('main');
const $template = document.querySelector('#draughtsTemplate');
console.log('main', $main);
const board = new DraughtsBoard($template, $main);
board.setPiece('whiteKing', 1)
board.loadFEN("B:W18,24,27,28,K10,K15:B12,16,20,K22,K25,K29");
// Module.onRuntimeInitialized = () => {
//   console.log(Module._test(10));
// };
// const WIDTH = 100;
// const HEIGHT = 100;
//
// const $board = document.querySelector('.board');
// const whitePieceTemplate = document.querySelector('#whiteMan').content;
// const whiteKingTemplate = document.querySelector('#whiteKing').content;
// const blackPieceTemplate = document.querySelector('#blackMan').content;
// const blackKingTemplate = document.querySelector('#blackKing').content;
//
// const $squares = $board.querySelectorAll('.square');
//
// const $piece = document.createElement('div');
// let $drag = $piece;
//
// for (const $square of $squares) {
//   $square.addEventListener('dragover', e => {
//     e.preventDefault();
//     // console.log('dragenter', e);
//   });
//   $square.addEventListener('dragover', e => {
//     e.preventDefault();
//     // console.log('dragover', e);
//   });
//   $square.addEventListener('drop', e => {
//     // console.log($drag);
//     $drag.style.left = `${e.target.offsetLeft}px`;
//     $drag.style.top = `${e.target.offsetTop}px`;
//     console.log('dropped', e);
//   });
// }
//
//
// // $board.addEventListener('drop', () => console.log('xd'));
// // const $piece = whitePieceTemplate.cloneNode(true);
// // $piece.querySelector('div').addEventListener('click', () => {
// //   console.log('???');
// // });
//
//
//
// $piece.className = 'piece white';
// $piece.setAttribute('draggable', true);
// $piece.innerHTML = 'M';
//
// $piece.addEventListener('dragstart', () => {
//   $drop = $piece;
//   console.log('huj');
// });
//
//
// const indexToCords = index => {
//
// };
//
// console.log(0, indexToCords(0));
// console.log(6, indexToCords(6));
// console.log(33, indexToCords(33));
//
// $board.appendChild($piece);

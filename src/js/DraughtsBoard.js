'use strict';
export class DraughtsBoard {
  constructor($template, $parent) {
    this.template = {
      $board: $template.content.querySelector('.draughtsBoard'),
      $square: $template.content.querySelector('.draughtsSquare'),
      pieces: {
        $whiteMan: $template.content.querySelector('.draughtsWhiteMan'),
        $whiteKing: $template.content.querySelector('.draughtsWhiteKing'),
        $blackMan: $template.content.querySelector('.draughtsBlackMan'),
        $blackKing: $template.content.querySelector('.draughtsBlackKing')
      }
    };
    this.$parent = $parent;
    this.$board = document.importNode(this.template.$board, true);
    this.$parent.appendChild(this.$board);
    this.$squares = [];

    this.eventListeners = {
      square: {
        dragenter: e => {
          e.preventDefault();
        },
        dragover: e => {
          e.preventDefault();
        },
        drop: e => {
          console.log(this);
          this.$drag.style.left = `${e.target.offsetLeft}px`;
          this.$drag.style.top = `${e.target.offsetTop}px`;
        }
      },
      piece: {
        dragstart: e => {
          // e.preventDefault();
          this.$drag = e.target;
        },
        dragend: e => {
          // e.preventDefault();
          this.$drag = null;
        }
      },
      pieceImage: {
        dragstart: e => {
          e.preventDefault();
          return false;
        }
      }
    }
    this._initializeSquares();

    this.size = 100;
    this.$drag = null;
  }
  _initializeSquares() {
    for (var i=0; i<50; i++) {
      let $square = document.importNode(this.template.$square, true);

      $square.setAttribute('data-index', i);

      for (const [key, fn] of Object.entries(this.eventListeners.square)) {
        $square.addEventListener(key, e => fn(e));
      }
      this.$board.appendChild($square);
      this.$squares.push($square);
    }
  }
  _indexToCords(index) {
    const row = Math.floor(index/5);
    const pos = index%5
    return {
      x: !(row%2)*this.size + pos*2*this.size,
      y: row*this.size
    };
  }
  _parseFEN(string) {
    const move = string.charAt(0).toLowerCase() === 'b';
    const chunks = string.substring(2).split(':');
    const pieces = {};
    for (let chunk of chunks) {
      const key = chunk.charAt(0).toLowerCase() === 'w' ? 'white' : 'black';
      chunk = chunk.substring(1)
      pieces[key] = chunk.split(',')
    }
    return {move, pieces};
  }
  _bitboardToIndicies(bitboard) {
    const tmp = [];
    let x = null;
    do {
      x = bitboard&(~(bitboard-1));
      bitboard &= ~x;
      tmp.push(Math.log(x) / Math.log(2));
    } while (bitboard);
    return tmp;
  }
  setPiece(piece, index) {
    console.log('piece', piece);
    const $piece = document.importNode(this.template.pieces[`$${piece}`], true);
    for (const [key, fn] of Object.entries(this.eventListeners.piece)) {
      $piece.addEventListener(key, e => fn(e));
    }
    $piece.querySelector('img').addEventListener('dragstart', e => this.eventListeners.pieceImage.dragstart(e));
    const cords = this._indexToCords(index-1);
    $piece.style.left = `${cords.x}px`;
    $piece.style.top = `${cords.y}px`;
    this.$board.appendChild($piece);
  }
  loadFEN(string) {
    const data = this._parseFEN(string);
    this.move = data.move;
    for (const [color, pieces] of Object.entries(data.pieces)) {
      for (let piece of pieces) {
        let name = 'Man';
        if (piece.charAt(0).toLowerCase() === 'k') {
          name = 'King';
          piece = piece.substring(1);
        }
        this.setPiece(`${color}${name}`, Number(piece));
      }
    }
  }
}

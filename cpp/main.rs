// fn get_piece(index: u8) -> u64 {
//     let row = index/5;
//     let n = 8+2*row + index;
//     // println!("n {}", n);
//     // println!("row {}", row);
//     return 0 | 1 << n;
// }

// let MASK_ODD_ROW:u32 = 0b11111000001111100000111110000011111000001111100000;




// fn get_jumpers_0() {
//
// }

fn main() {
    const BOARD:u64 = 0b11111_11111_11111_11111_11111_11111_11111_11111_11111_11111;

                                                         // 10_00000_00000_00000_00000
                                                            // 10000_00000_00000_00000
                                               // 1111_01111_00000_00000_00000_00000;
                                               // 1101000000_00010_00000_00000
    // let white:u64 = 0b11111_11111_11111_11111_00000_00000_00000_00000_00000_00000;
    // let black:u64 = 0b00000_00000_00000_00000_00000_00000_11111_11111_11111_11111;
    let white:u64 = 0b11111_11111_11111_11111_00010_00000_00000_00000_00000_00000;
                                      // 1_11010_00000_00000_00000_00000_00000_00000
                                   // 1_11010_00000_00000_00000_00000_00000_00000
    let black:u64 = 0b00000_00000_00000_00000_00000_00010_11110_11111_11111_11111;
                                           // 11101_11101_00001_00000_00000_00000
    const MASK_EVEN_ROW:u64 = 0b11111_00000_11111_00000_11111_00000_11111_00000_11111_00000;
    const MASK_ODD_ROW:u64 = 0b00000_11111_00000_11111_00000_11111_00000_11111_00000_11111;
    const MASK_EMPTY_JUMPERS_0:u64 = 0b00000_00000_01111_01111_01111_01111_01111_01111_01111_01111;
    const MASK_EMPTY_JUMPERS_1:u64 = 0b00000_00000_11110_11110_11110_11110_11110_11110_11110_11110;
    const MASK_EMPTY_JUMPERS_2:u64 = 0b11111_11111_11110_11110_11110_11110_11110_11110_11110_11110;
    const MASK_EMPTY_JUMPERS_3:u64 = 0b01111_01111_01111_01111_01111_01111_01111_01111_00000_00000;
    const MASK_EMPTY_WHITE_MOVERS_EVEN0:u64 = 0b00000_00000_01111_00000_01111_00000_01111_00000_01111_00000;
    const MASK_EMPTY_WHITE_MOVERS_EVEN1:u64 = 0b00000_11110_00000_11110_00000_11110_00000_11110_00000_11110;

    let empty = (!(white | black))&BOARD;
    let empty_jumpers0 = empty & MASK_EMPTY_JUMPERS_0;
    let empty_jumpers1 = empty & MASK_EMPTY_JUMPERS_1;
    let empty_jumpers2 = empty & MASK_EMPTY_JUMPERS_2;
    let empty_jumpers3 = empty & MASK_EMPTY_JUMPERS_3;
    let white_jumpers_0 = (((((empty_jumpers0&MASK_EVEN_ROW)<<6)&black)<<5)&white)|(((((empty_jumpers0&MASK_EVEN_ROW)<<5)&black)<<6)&white);
    let white_jumpers_1 = (((((empty_jumpers1&MASK_EVEN_ROW)<<5)&black)<<4)&white)|(((((empty_jumpers1&MASK_EVEN_ROW)<<4)&black)<<5)&white);
    let white_jumpers_2 = (((((empty_jumpers2&MASK_EVEN_ROW)>>5)&black)>>6)&white)|(((((empty_jumpers2&MASK_EVEN_ROW)>>6)&black)>>5)&white);
    let white_jumpers_3 = (((((empty_jumpers3&MASK_EVEN_ROW)>>4)&black)>>5)&white)|(((((empty_jumpers3&MASK_EVEN_ROW)>>5)&black)>>4)&white);

    let white_mover0 = (((empty&MASK_EMPTY_WHITE_MOVERS_EVEN0)<<6)&white)|(((empty&MASK_ODD_ROW)<<5)&white);
    let white_mover1 = (((empty&MASK_EVEN_ROW)<<5)&white)|(((empty&MASK_EMPTY_WHITE_MOVERS_EVEN1)<<4)&white);
    // let black_mover0 = (((empty&MASK_EVEN_ROW)>>5)&black)|(((empty&MASK_ODD_ROW)>>6)&black);
    // let black_mover1 = (((empty&MASK_EVEN_ROW)>>4)&black)|(((empty&MASK_ODD_ROW)>>5)&black);

    println!("empty {:b}", empty);
    println!("white_jumpers_0 {:b}", white_jumpers_0);
    println!("white_jumpers_1 {:b}", white_jumpers_1);
    println!("white_jumpers_2 {:b}", white_jumpers_2);
    println!("white_jumpers_3 {:b}", white_jumpers_3);
    println!("white_mover0 {:b}", white_mover0);
    println!("white_mover1 {:b}", white_mover1);

    // let padding:u64 = 0b0000000000000000111110011111001111100111110011111001111100000000;

    // println!("{:b}", get_piece(6))
    // println!("{:b}", 0u64);
    // println!("{:b}", (board >> 6 | board >> 7) & padding);
    // println!("{:b}", 0b0000000000000011);
}

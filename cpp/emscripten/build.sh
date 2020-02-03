em++ ../main.cpp ../src/Board.cpp -s WASM=1 -o ./../../dist/wasm/module.js -O3 -s ASSERTIONS=1 -s EXPORTED_FUNCTIONS='["_init"]' -s NO_EXIT_RUNTIME=1 -std=c++11

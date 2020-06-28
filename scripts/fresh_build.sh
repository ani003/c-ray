#!/bin/bash
shopt -s expand_aliases
source ~/.bashrc
# emsdk_setup > /dev/null

rm CMakeCache.txt
rm bin/*
WASM=1 wasimake cmake . -DNO_SDL2=True
WASM=1 wasimake make
rm bin/c-ray
wasm2wat bin/c-ray.wasm -o bin/c-ray.wat
rm bin/c-ray.wasm
sub_primitives.py bin/c-ray.wat

if [[ "$UTHREAD_ASYNCIFY" == "1" ]]; then
    asyncify_rewrite bin/c-ray.wat builds/asyncify/c-ray.wat
    cp builds/asyncify/c-ray.wat bin/c-ray.wat
elif [[ "$UTHREAD_CONTS" == "1" ]]; then
    cp bin/c-ray.wat builds/conts/c-ray.wat
elif [[ "$UTHREAD_SERIAL" == "1" ]]; then
    cp bin/c-ray.wat builds/serial/c-ray.wat
fi


# mv bin/c-ray bin/c-ray.bc
# emcc bin/c-ray.bc -g -Os -o bin/c-ray.wasm -s NO_EXIT_RUNTIME=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 
# emcc_control bin/c-ray.bc -g -Os bin/c-ray.wat
# wasm2wat bin/c-ray.wasm > bin/c-ray.wat
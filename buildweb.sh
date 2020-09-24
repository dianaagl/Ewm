source /Users/diana/emsdk/emsdk_env.sh
mkdir buildEwmPrac
cd buildEwmPrac
mkdir EwmGui
mkdir EwmTesting
cd EwmTesting
/Users/diana/Qt/5.15.1/wasm_32/bin/qmake /Users/diana/Documents/ewm-new/EwmTesting/EwmTesting.pro
make clean
make
cd ../EwmGui
/Users/diana/Qt/5.15.1/wasm_32/bin/qmake /Users/diana/Documents/ewm-new/EwmGui/EwmGui.pro
make clean
make
~/emsdk/upstream/emscripten/emrun --browser=chrome eprak.html 

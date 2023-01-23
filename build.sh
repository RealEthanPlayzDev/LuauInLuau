source ./emsdk/emsdk_env.sh
mkdir build_wasm
cd build_wasm
export CXXFLAGS="-s LINKABLE=1 -s EXPORT_ALL=1"
emcmake cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
emmake cmake --build . --target LuauInLuau --config RelWithDebInfo -j $(nproc)
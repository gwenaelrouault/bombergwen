export PKG_CONFIG_SYSROOT_DIR=~/gameshell-sysroot
export PKG_CONFIG_PATH=~/gameshell-sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
cmake ..   -DCMAKE_TOOLCHAIN_FILE=CMakeLists.arm.txt   -DCMAKE_BUILD_TYPE=Release
make

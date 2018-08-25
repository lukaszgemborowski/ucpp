# ARDUINO_PATH="$HOME/arduino"
ARDUINO_SDK_PATH="$ARDUINO_PATH/hardware/tools/"
ARDUINO_TOOLCHAIN="$ARDUINO_SDK_PATH/avr/bin"
CXX="$ARDUINO_TOOLCHAIN/avr-g++"
OBJCOPY="$ARDUINO_TOOLCHAIN/avr-objcopy"
OBJDUMP="$ARDUINO_TOOLCHAIN/avr-objdump"
AVRDUDE="$ARDUINO_TOOLCHAIN/avrdude"

if [ -z ${ARDUINO_PATH+x} ]; then
    echo "WARNING"
    echo ""
    echo "!!! You need to set path to Arduino SDK !!!"
    echo "this is the directory where you installed/extracted Arduino IDE/SDK"
    echo "in order to do that please edit the first line in this script"
    exit 1
fi

CXXFLAGS="-Os -DF_CPU=16000000UL -mmcu=atmega328p -std=c++11"
OBJCOPYFLAGS="-O ihex -R .eeprom"
AVRDUDEFLAGS=" -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -C $ARDUINO_SDK_PATH/avr/etc/avrdude.conf"

set -e

FILES="tests/tests_array.cxx tests/tests_stack.cxx tests/avr_main.cxx
tests/tests_bitmap_allocator.cxx tests/tests_uninitialized_array.cxx
tests/tests_bit.cxx"

$CXX $CXXFLAGS $FILES -Iinclude -o avr_tests
$OBJCOPY $OBJCOPYFLAGS avr_tests avr_tests.hex
$AVRDUDE $AVRDUDEFLAGS -U flash:w:avr_tests.hex
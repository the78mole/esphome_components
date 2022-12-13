# the78mole binary repository

Here you can find the pre-compiled binaries for my ESPhome hardware projects. Just walk through the folders, to find the BIN files.

To install the BINs on your ESP32, simply run the command

    esptool.exe --chip esp32 --port "COM10" --baud 921600 \
      --before default_reset --after hard_reset write_flash -z \
      --flash_mode dio --flash_freq 40m --flash_size detect \
      0x0000 <BIN-FILE>

For the km271-for-friends firmware, the command would simply be:

    esptool.exe --chip esp32 --port "COM10" --baud 921600 \
      --before default_reset --after hard_reset write_flash -z \
      --flash_mode dio --flash_freq 40m --flash_size detect \
      0x0000 km271-for-friends-esp32.bin

# Infinite-Moonshine
is an atomated device for ethanol rectification. It is controlled by the single-board computer with an arduino mega connected via asynchronous port. Aruino is connected to the sensors and the step engines, while computer runs rectification algorithm.

I'm using an Orange PI PC Plus with Armbian 5 OS and UART3. To enable this port you need to

add "overlays=uart3" in /boot/armbianEnv.txt

and run theese commands in the terminal:

sudo chmod 644 /etc/cron.weekly/apt-xapian-index
chmod 4775 /usr/bin/python3
pip3 install OPi.GPIO pyserial

then reboot.

To communicate with arduino you'll need a logic-level translator connected in the following way:

Orange PI PC+   - Translator - Arduino Mega

PA13 (UART3_TX) - LV1 - HV1 - RX2 17

PA14 (UART3_RX) - LV2 - HV2 - TX2 16

+3.3V           - LV  - HV  - +5V

Ground          - GND - GND - GND

PC4             - LV3 - HV3 - RESET

PC7             - LV4 - HV4

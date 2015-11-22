@echo off
echo Build gfx.c from gfx folder
folder2c gfx gfx
sdcc -c -mz80 --std-sdcc99 gfx.c
echo Build Main
sdcc -c -mz80 --std-sdcc99 deathchase.c
echo Linking
sdcc -mz80 --data-loc 0xC000 deathchase.rel SMSlib/SMSlib.rel gfx.rel
ihx2sms deathchase.ihx deathchase.sms

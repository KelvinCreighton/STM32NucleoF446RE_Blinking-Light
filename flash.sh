openocd -f board/st_nucleo_f4.cfg \
  -c "program build/stm32nucleof446re_blinking_light.elf verify reset exit"

zephyr_library()

if(CONFIG_MY_PWM_WRAPPER)
  zephyr_library_sources(src/my_pwm.c)
endif()

zephyr_include_directories(inc)
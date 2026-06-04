
cmake_minimum_required(VERSION 3.20.0)

# order is important
set(ZEPHYR_EXTRA_MODULES
${ZEPHYR_EXTRA_MODULES}
${CMAKE_CURRENT_SOURCE_DIR}/../../modules/my_pwm_wrapper
)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(mybliky_pwm)


# we MUST set the target name to "app" 
target_sources(app PRIVATE src/main.c)

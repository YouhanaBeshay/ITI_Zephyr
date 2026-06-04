# First Module Notes:
- These are some notes I noticed while developing my first zephyr module.
---
1. `module.yml` file **MUST** be named `module.yml` not `module.yaml`
2. in the main project `CMakeLists.txt` file, we must add the following :
```cmake
    set(ZEPHYR_EXTRA_MODULES
        ${ZEPHYR_EXTRA_MODULES}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/my_pwm_wrapper
    )
```
- **BEFORE** the `find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})`
  - So Order is important

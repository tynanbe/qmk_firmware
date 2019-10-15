SRC += tynanbe.c \
       tynanbe_process_record.c

# Virtual DIP switch configuration (+1000)
BOOTMAGIC_ENABLE = no

# Commands for debug and configuration
COMMAND_ENABLE = no

# Console for debug (+400)
CONSOLE_ENABLE = no
ifdef CONSOLE_ENABLE
  ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
    OPT_DEFS += -DKEYLOGGER_ENABLE
  endif
endif

ENCODER_ENABLE ?= no
ifneq ($(strip $(ENCODER_ENABLE)), no)
  SRC += tynanbe_encoder.c
endif

# Audio control and System control (+450)
EXTRAKEY_ENABLE = yes

ifneq ($(strip $(DISABLE_LTO)), yes)
  LINK_TIME_OPTIMIZATION_ENABLE = yes
endif

ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
  OPT_DEFS += -DMAKE_BOOTLOADER
endif

# Mouse keys (+4700)
MOUSEKEY_ENABLE = yes

# Nkey Rollover - if this doesn't work, see here:
# https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes

# Enable the OLED Driver (+5000)
OLED_DRIVER_ENABLE ?= no
ifneq ($(strip $(OLED_DRIVER_ENABLE)), no)
  SRC += tynanbe_oled.c
endif

# Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_ENABLE ?= no
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # LED animations
  RGBLIGHT_ANIMATIONS ?= yes
  SRC += tynanbe_rgb.c
  OPT_DEFS += -DRGB_ENABLE
  ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
    OPT_DEFS += -DINDICATOR_LIGHTS
  endif
  ifeq ($(strip $(RGBLIGHT_TWINKLE)), yes)
    OPT_DEFS += -DRGBLIGHT_TWINKLE
  endif
  ifeq ($(strip $(RGBLIGHT_STARTUP_ANIMATION)), yes)
    OPT_DEFS += -DRGBLIGHT_STARTUP_ANIMATION
  endif
endif

# Enable per-key coordinate based RGB effects. Do not enable with RGB light (+8500)
RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
  # Enable reactive per-key effects. Can be very laggy (+1500)
  RGB_MATRIX_KEYPRESSES ?= yes
  SRC += tynanbe_rgb.c
  OPT_DEFS += -DRGB_ENABLE
endif

# Do not write to EEPROM when using RGB_* keycodes
# Not implemented for specific `RGB_MODE_*` keycodes except for
# `RGB_MODE_FORWARD` and `RGB_MODE_REVERSE`
RGB_USE_NOEEPROM ?= yes
ifeq ($(strip $(RGB_USE_NOEEPROM)), yes)
  OPT_DEFS += -DRGB_USE_NOEEPROM
endif

SPACE_CADET_ENABLE = no

TAP_DANCE_ENABLE = yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  SRC += tynanbe_tap_dance.c
endif

UNICODE_ENABLE ?= no

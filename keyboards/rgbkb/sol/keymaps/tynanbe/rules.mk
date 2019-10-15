# RGB

# Enables the additional 24 full-hand LEDs
FULLHAND_ENABLE     = no

# Enable global lighting effects
# Do not enable with RGB Matrix
RGBLIGHT_ENABLE     = no
RGBLIGHT_ANIMATIONS = no
# Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
LED_MIRRORED        = no

# Enable per-key coordinate based RGB effects
# Do not enable with RGBlight.
RGB_MATRIX_ENABLE   = WS2812

# Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX
# Otherwise, limited to a safe level for a normal USB-A port
RGBLIGHT_FULL_POWER = no

# Limit max brightness to connect to IOS device (iPad,iPhone)
IOS_DEVICE_ENABLE   = no

# Do not write to EEPROM when using RGB_* keycodes
# Not implemented for specific `RGB_MODE_*` keycodes except for
# `RGB_MODE_FORWARD` and `RGB_MODE_REVERSE`
RGB_USE_NOEEPROM    = yes



# Misc

OLED_DRIVER_ENABLE  = no

ifeq ($(strip $(KEYBOARD)), rgbkb/sol/rev1)
  ENCODER_ENABLE    = no
  RGB_OLED_MENU     = no
else
  ENCODER_ENABLE    = yes
  RGB_OLED_MENU     = 0
endif

# Enable one-hand typing
SWAP_HANDS_ENABLE   = no



# Do not edit below.

include keyboards/$(KEYBOARD)/post_rules.mk

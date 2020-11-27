# qmk compile -kb helix_remix -km default

# MCU name
MCU = atmega32u4
BOOTLOADER = caterina

SPLIT_KEYBOARD = yes

RGBLIGHT_ENABLE = yes

KEY_LOCK_ENABLE = yes
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes

OLED_DRIVER_ENABLE = yes

OPT_DEFS += -DHREMIX_DATA_ENABLE

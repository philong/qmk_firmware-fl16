
# Enabled in info.json
# EXTRAKEY_ENABLE = yes          # Audio control and System control

OS_DETECTION_ENABLE = yes
#OS_DETECTION_DEBUG_ENABLE = yes

# Custom matrix scanning code via ADC
CUSTOM_MATRIX = lite
SRC += matrix.c analog.c

SRC += dyn_serial.c factory.c


OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

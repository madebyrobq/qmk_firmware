# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
# NKRO_ENABLE = yes		# USB Nkey Rollover - not yet supported in LUFA
BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
MIDI_ENABLE = yes           # MIDI support

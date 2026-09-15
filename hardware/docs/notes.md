# notes_cfgPins:
- file1: FPGA-TN-02050-1-0-Programming-Ext-SPI-Flash-JTAG-ECP5-5G-1.pdf
- described in file1 page 8, to enable master spi configuration port, the cfg is supposed to be:
> config[2]=0
> config[1]=1
> config[0]=0


# notes_transducerPins: 
- file1: FPGA-TN-02038-2-1-ECP5-and-ECP5-5G-Hardware-Checklist.pdf 
- see table 2.1 for Vccio and banks from file1 page 8
- si_t1 - si_t12 bank 1
- si_t13 - si_t22 bank 0
- si_t23 - si_t32 bank 8



# notes_programming:
- file1: FPGA-TN-02039-2-5-ECP5-and-ECP5-5G-sysCONFIG.pdf


# notes_IObanks:
- file1: FPGA-TN-02032-1-4-ECP5-ECP5G-sysIO-Usage-Guide.pdf
- ground (0v) any Vccio if that bank is unused. see file1 page 8


# notes_relayPins:
- file1: FPGA-TN-02032-1-4-ECP5-ECP5G-sysIO-Usage-Guide.pdf
- relay pins are to be paired with the slave FPGA pins' to use LVDS. See the "used MASTER*.odt" & "used SLAVE*.odt"
- these are in bank 2 from master FPGA
- in the slave FPGA, turn on the "programmable on/off differential input termination of 100 Ω".- See file1 page 10: 4.8. LVDS sysI/O Buffer Pairs (A/B and C/D on Left and Right Sides)


# notes_deviceUsage:
- file1: datasheet FPGA-DS-02012-3-4-ECP5-ECP5G-Family-Data-Sheet.pdf
- See file1 page 43: 2.14.1. sysI/O Buffer Banks
- no hot socketing = no removing or inserting other components connected to the pins or pads while the device is turned on. 
- banks left (6, 7) and right (2, 3) do not support that. Only banks up (0, 1) and bottom banks (8, 4)



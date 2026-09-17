# notes_cfgPins:
- file1: FPGA-TN-02050-1-0-Programming-Ext-SPI-Flash-JTAG-ECP5-5G-1.pdf
- described in file1 page 8, to enable master spi configuration port, the cfg is supposed to be:
> config[2]=0
> config[1]=1
> config[0]=0


# notes_transducerPins: 
- file1: FPGA-TN-02038-2-1-ECP5-and-ECP5-5G-Hardware-Checklist.pdf 
- see table 2.1 for Vccio and banks from file1 page 8
- si_t1 - si_t16 bank 1 
- si_t17 - si_t26 bank 0 
- si_t27 - si_t32 bank 8



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
- devices that are hot swappable are: 
    - transducer array board  
    - CH340C debug (TX and RX remains connected regardless if device is connected to the port or not; IMPORTANT: ASSUMING the CH340C is powered by the board's own power, i.e. 3.3 V, and not powered through usb; right now it is powered through usb and thats not nice)
- devices that are not hot swappable (same thing above with hot socketing) are:
    - FTDI device (FT2232H)


# notes_ftdi:
- file1: ftdi/FT2232H IC.PDF
- file2: ftdi/DS_FT2232H_Mini_Module.pdf
- file3: ftdi/AN_130_FT2232H_Used_In_FT245-Synchronous-FIFO-Mode
- to lay the pins required by the databus on channel A, (file3) page 4 says what the pin numbers are described from the actual FT2232H chip (file1), the mini module's pinout is referred there (file2), or actually it's already available in (file2) page 9: schematic diagram. Channel B is then disabled as the resources from channel B 
- CN2-22, AC4/SIWU, is unused, so it is tied to VCCIO, see file3 table 1 page 4
- to have achieve the requirement of writing from PC host to the AVD device of ~13MB/s, the FTDI should be set to FT245 style synchronous FIFO mode. See (file3) page 2. UNDER CONSTRUCTION
- JTAG UNDER CONSTRUCTION

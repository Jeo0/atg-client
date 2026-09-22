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
- file2: SPI flash/SPI flash MX25L3206E.pdf
- this will be in 62 MHz (max MCLK frequency) see Table 4.7 page 18 of file1; the SPI flash has a max frequency of 86 MHz.
- Each FPGA is in Master SPI (a configuration mode): FPGA drives the clocks and reads the bitstream from their own external SPI Flash
- For this project's limitation (two channels only FTDI), only the JTAG port has the ability to support the **REFRESH** command; see file1, definition of terms
- Recommended SPI flash size for LFE5U-25 is 8 Mbit see file1 page 11
- FLASH pins are powered by bank 8 (VCCIO8: +3.3V); see page 18, 4.7 Dual-Purpose sysCONFIG Pins
- pull up pin FLASH-CSS according to notes #2 on page 14 of file1 (4.7K)
- pull up pin FLASH-IO0 and FLASH-IO1 according to notes #4 on page 14 of file1 for MSPI (10K)
- pull up pin FLASH-MCLK according to notes #6 on page 14 of file1 (1K)
- by default, once power is on the FPGA and the SPI flash (we are in Master SPI mode), it proceeds to download the program from the SPI flash through serial and slow read. see 6.1. Master SPI Modes page 26 of file1.
- "A port is said to be a configuration port when it is capable of executing both bitstream write and read commands. And this is the only method that users can use to perform a DUAL read and a QUAD read from SPI Flash." see file1, 6.1.1 Method to Enable the Master SPI Port page 27


# notes_resetMechanism:
- file1: FPGA-TN-02039-2-5-ECP5-and-ECP5-5G-sysCONFIG.pdf
- "Toggling" the PROGRAMN pin causes the ECP5 device to go back to initialization phase; see 5. Configuration Process and Flow page 22 to 25.


# notes_IObanks:
- file1: FPGA-TN-02032-1-4-ECP5-ECP5G-sysIO-Usage-Guide.pdf
- ground (0v) any Vccio if that bank is unused. see file1 page 8


# notes_relayPins:
- file1: FPGA-TN-02032-1-4-ECP5-ECP5G-sysIO-Usage-Guide.pdf
- relay pins are to be paired with the slave FPGA pins' to use LVDS. See the "used MASTER*.odt" & "used SLAVE*.odt"
- these are in bank 2 from master FPGA
- in the slave FPGA, turn on the "programmable on/off differential input termination of 100 Ω".- See file1 page 10: 4.8. LVDS sysI/O Buffer Pairs (A/B and C/D on Left and Right Sides)

# notes_triggerLine:
- file1: compile/openmpd Supplementaty Material.pdf
- pp 2; pp 4
- for the trigger openmpd used "update rate divider" to make sure that both pcbs are synchronized
- it is integrated to the gspat
- it divides the UPS output for the transducers 


# notes_deviceUsage:
- file1: datasheet FPGA-DS-02012-3-4-ECP5-ECP5G-Family-Data-Sheet.pdf
- file2: FPGA-TN-02039-2-5-ECP5-and-ECP5-5G-sysCONFIG.pdf
- DONE pin and the INITN pin must be high to be in user mode. see file2 page 27
- See file1 page 43: 2.14.1. sysI/O Buffer Banks: no hot socketing = no removing or inserting other components connected to the pins or pads while the device is turned on. 
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
- file4: FPGA-TN-02039-2-5-ECP5-and-ECP5-5G-sysCONFIG.pdf
- the mini module has an FT2232HL IC (see figure 5.1 page 9 of file file2)
- to have achieve the requirement of writing from PC host to the AVD device of ~13MB/s, the FTDI should be set to FT245 style synchronous FIFO mode. See (file3) page 2. UNDER CONSTRUCTION
- The FTDI modes this project will need (MPSSE JTAG on channel B, then SYNC 245 FIFO style mode for channel B, vice-versa) can be configured through code. see 4.13.1 Do I need an EEPROM? page 46 of file1.
- CN2-22, AC4/SIWU, is unused, so it is tied to VCCIO, see file3 table 1 page 4
- JTAG pin through MPSSE (channel B) and 245 FIFO SYNC (channel A) pin connections are referred on table 3.1 of file1 page 9 
- we are to put the FPGA into **Direct Mode** at the moment of inserting a USB connector to the FTDI device; this is so we can check whether the FPGA initially has any bitstream before deciding whether to go to **User Mode** or in **Master SPI** first; see file4, definition of terms
- JTAG internal resistors: only TCK has external pull down resistor recommended (4.7K); the rest has internal pull upp resistor to VCCIO8; see file4 page 20 to page 21.
- FTDI JTAG port, TCK and TMS are made as an input port to the ECP5 device. see figure 4.3 JTAG port, page 21.
- on lattice diamond programmer, the two devices (master fpga and slave fpga) will show up there and we can target both devices independently and flash separate bitstreams with Master SPI configuration mode as described above. 

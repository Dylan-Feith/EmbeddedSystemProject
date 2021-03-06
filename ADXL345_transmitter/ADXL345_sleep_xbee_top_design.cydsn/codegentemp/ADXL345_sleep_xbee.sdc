# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Dylan\Desktop\ADXL345_sleep_xbee_wdt_topdesign\ADXL345_sleep_xbee.cydsn\ADXL345_sleep_xbee.cyprj
# Date: Tue, 29 Mar 2016 06:50:16 GMT
#set_units -time ns
create_clock -name {Accelero_SCBCLK(FFB)} -period 500 -waveform {0 250} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 250 -waveform {0 125} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 250 -waveform {0 125} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 250 -waveform {0 125} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 500 -waveform {0 125} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Accelero_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list]
create_generated_clock -name {zigbee_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 53 105} [list [get_pins {ClockBlock/udb_div_0}]]


# Component constraints for C:\Users\Dylan\Desktop\ADXL345_sleep_xbee_wdt_topdesign\ADXL345_sleep_xbee.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Dylan\Desktop\ADXL345_sleep_xbee_wdt_topdesign\ADXL345_sleep_xbee.cydsn\ADXL345_sleep_xbee.cyprj
# Date: Tue, 29 Mar 2016 06:50:13 GMT

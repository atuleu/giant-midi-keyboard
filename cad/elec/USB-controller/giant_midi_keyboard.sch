EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:giant_midi_keyboard
LIBS:giant_midi_keyboard-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCP3008 U1
U 1 1 551401DB
P 4950 1150
F 0 "U1" H 4650 1650 60  0000 C CNN
F 1 "MCP3008" H 4800 650 60  0000 C CNN
F 2 "Sockets_DIP:DIP-16__300_ELL" H 5450 2150 60  0001 C CNN
F 3 "" H 5450 2150 60  0000 C CNN
F 4 "MCP3008-I/P" H 4950 1150 60  0001 C CNN "Part Number"
	1    4950 1150
	1    0    0    -1  
$EndComp
$Comp
L MCP3008 U2
U 1 1 55140293
P 4950 2500
F 0 "U2" H 4650 3000 60  0000 C CNN
F 1 "MCP3008" H 4800 2000 60  0000 C CNN
F 2 "Sockets_DIP:DIP-16__300_ELL" H 5450 3500 60  0001 C CNN
F 3 "" H 5450 3500 60  0000 C CNN
F 4 "MCP3008-I/P" H 4950 2500 60  0001 C CNN "Part Number"
	1    4950 2500
	1    0    0    -1  
$EndComp
$Comp
L MCP3008 U3
U 1 1 551402D3
P 4950 3850
F 0 "U3" H 4650 4350 60  0000 C CNN
F 1 "MCP3008" H 4800 3350 60  0000 C CNN
F 2 "Sockets_DIP:DIP-16__300_ELL" H 5450 4850 60  0001 C CNN
F 3 "" H 5450 4850 60  0000 C CNN
F 4 "MCP3008-I/P" H 4950 3850 60  0001 C CNN "Part Number"
	1    4950 3850
	1    0    0    -1  
$EndComp
$Comp
L MCP3008 U4
U 1 1 55140307
P 4950 5150
F 0 "U4" H 4650 5650 60  0000 C CNN
F 1 "MCP3008" H 4800 4650 60  0000 C CNN
F 2 "Sockets_DIP:DIP-16__300_ELL" H 5450 6150 60  0001 C CNN
F 3 "" H 5450 6150 60  0000 C CNN
F 4 "MCP3008-I/P" H 4950 5150 60  0001 C CNN "Part Number"
	1    4950 5150
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 55140362
P 5950 700
F 0 "C1" H 5975 800 50  0000 L CNN
F 1 "100nF" H 5975 600 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D6_P5" H 5988 550 30  0001 C CNN
F 3 "" H 5950 700 60  0000 C CNN
F 4 "MC0805B104K500A2.54MM" H 5950 700 60  0001 C CNN "Part Number"
	1    5950 700 
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 551404C7
P 6100 2050
F 0 "C4" H 6125 2150 50  0000 L CNN
F 1 "100nF" H 6125 1950 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D6_P5" H 6138 1900 30  0001 C CNN
F 3 "" H 6100 2050 60  0000 C CNN
F 4 "MC0805B104K500A2.54MM" H 6100 2050 60  0001 C CNN "Part Number"
	1    6100 2050
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5514050F
P 5950 3350
F 0 "C2" H 5975 3450 50  0000 L CNN
F 1 "100nF" H 5975 3250 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D6_P5" H 5988 3200 30  0001 C CNN
F 3 "" H 5950 3350 60  0000 C CNN
F 4 "MC0805B104K500A2.54MM" H 5950 3350 60  0001 C CNN "Part Number"
	1    5950 3350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 55140559
P 5950 4650
F 0 "C3" H 5975 4750 50  0000 L CNN
F 1 "100nF" H 5975 4550 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D6_P5" H 5988 4500 30  0001 C CNN
F 3 "" H 5950 4650 60  0000 C CNN
F 4 "MC0805B104K500A2.54MM" H 5950 4650 60  0001 C CNN "Part Number"
	1    5950 4650
	1    0    0    -1  
$EndComp
$Comp
L RR8 RR1
U 1 1 55141E94
P 2450 1250
F 0 "RR1" H 2500 1800 50  0000 C CNN
F 1 "2.2k" V 2480 1250 50  0000 C CNN
F 2 "Housings_SIP:SIP9_Housing_BigPads" H 2450 1250 60  0001 C CNN
F 3 "" H 2450 1250 60  0000 C CNN
F 4 "4609X-101-222LF" H 2450 1250 60  0001 C CNN "Part Number"
	1    2450 1250
	-1   0    0    1   
$EndComp
$Comp
L RR8 RR2
U 1 1 5514221B
P 2450 2500
F 0 "RR2" H 2500 3050 50  0000 C CNN
F 1 "2.2k" V 2480 2500 50  0000 C CNN
F 2 "Housings_SIP:SIP9_Housing_BigPads" H 2450 2500 60  0001 C CNN
F 3 "" H 2450 2500 60  0000 C CNN
F 4 "4609X-101-222LF" H 2450 2500 60  0001 C CNN "Part Number"
	1    2450 2500
	-1   0    0    1   
$EndComp
$Comp
L RR8 RR4
U 1 1 55142343
P 2450 6000
F 0 "RR4" H 2500 6550 50  0000 C CNN
F 1 "2.2k" V 2480 6000 50  0000 C CNN
F 2 "Housings_SIP:SIP9_Housing_BigPads" H 2450 6000 60  0001 C CNN
F 3 "" H 2450 6000 60  0000 C CNN
F 4 "4609X-101-222LF" H 2450 6000 60  0001 C CNN "Part Number"
	1    2450 6000
	-1   0    0    1   
$EndComp
$Comp
L RR8 RR3
U 1 1 551424FB
P 2450 4600
F 0 "RR3" H 2500 5150 50  0000 C CNN
F 1 "2.2k" V 2480 4600 50  0000 C CNN
F 2 "Housings_SIP:SIP9_Housing_BigPads" H 2450 4600 60  0001 C CNN
F 3 "" H 2450 4600 60  0000 C CNN
F 4 "4609X-101-222LF" H 2450 4600 60  0001 C CNN "Part Number"
	1    2450 4600
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X26 P1
U 1 1 55142D29
P 900 1950
F 0 "P1" H 900 3300 50  0000 C CNN
F 1 "LEFT" V 1000 1950 50  0000 C CNN
F 2 "Giant_Midi_Keyboard:Header_2x13" H 900 1950 60  0001 C CNN
F 3 "" H 900 1950 60  0000 C CNN
F 4 "T821126A1S100CEU" H 900 1950 60  0001 C CNN "Part Number"
	1    900  1950
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X26 P2
U 1 1 5514311D
P 900 5450
F 0 "P2" H 900 6800 50  0000 C CNN
F 1 "RIGHT" V 1000 5450 50  0000 C CNN
F 2 "Giant_Midi_Keyboard:Header_2x13" H 900 5450 60  0001 C CNN
F 3 "" H 900 5450 60  0000 C CNN
F 4 "T821126A1S100CEU" H 900 5450 60  0001 C CNN "Part Number"
	1    900  5450
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR01
U 1 1 551433AA
P 10350 1000
F 0 "#PWR01" H 10350 850 50  0001 C CNN
F 1 "+5V" H 10350 1140 50  0000 C CNN
F 2 "" H 10350 1000 60  0000 C CNN
F 3 "" H 10350 1000 60  0000 C CNN
	1    10350 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 551438EC
P 9600 1650
F 0 "#PWR02" H 9600 1400 50  0001 C CNN
F 1 "GND" H 9600 1500 50  0000 C CNN
F 2 "" H 9600 1650 60  0000 C CNN
F 3 "" H 9600 1650 60  0000 C CNN
	1    9600 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 551439B5
P 7550 1850
F 0 "#PWR03" H 7550 1600 50  0001 C CNN
F 1 "GND" H 7550 1700 50  0000 C CNN
F 2 "" H 7550 1850 60  0000 C CNN
F 3 "" H 7550 1850 60  0000 C CNN
	1    7550 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 55143DCE
P 5950 900
F 0 "#PWR04" H 5950 650 50  0001 C CNN
F 1 "GND" H 5950 750 50  0000 C CNN
F 2 "" H 5950 900 60  0000 C CNN
F 3 "" H 5950 900 60  0000 C CNN
	1    5950 900 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5514412F
P 6300 700
F 0 "#PWR05" H 6300 550 50  0001 C CNN
F 1 "+5V" H 6300 840 50  0000 C CNN
F 2 "" H 6300 700 60  0000 C CNN
F 3 "" H 6300 700 60  0000 C CNN
	1    6300 700 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 551442D4
P 5850 1550
F 0 "#PWR06" H 5850 1300 50  0001 C CNN
F 1 "GND" H 5850 1400 50  0000 C CNN
F 2 "" H 5850 1550 60  0000 C CNN
F 3 "" H 5850 1550 60  0000 C CNN
	1    5850 1550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 5514452A
P 6100 1800
F 0 "#PWR07" H 6100 1650 50  0001 C CNN
F 1 "+5V" H 6100 1940 50  0000 C CNN
F 2 "" H 6100 1800 60  0000 C CNN
F 3 "" H 6100 1800 60  0000 C CNN
	1    6100 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 55144553
P 6200 2250
F 0 "#PWR08" H 6200 2000 50  0001 C CNN
F 1 "GND" H 6200 2100 50  0000 C CNN
F 2 "" H 6200 2250 60  0000 C CNN
F 3 "" H 6200 2250 60  0000 C CNN
	1    6200 2250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 55144C77
P 5950 3050
F 0 "#PWR09" H 5950 2900 50  0001 C CNN
F 1 "+5V" H 5950 3190 50  0000 C CNN
F 2 "" H 5950 3050 60  0000 C CNN
F 3 "" H 5950 3050 60  0000 C CNN
	1    5950 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 55144CA9
P 5950 3600
F 0 "#PWR010" H 5950 3350 50  0001 C CNN
F 1 "GND" H 5950 3450 50  0000 C CNN
F 2 "" H 5950 3600 60  0000 C CNN
F 3 "" H 5950 3600 60  0000 C CNN
	1    5950 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 55144CEA
P 5650 2950
F 0 "#PWR011" H 5650 2700 50  0001 C CNN
F 1 "GND" H 5650 2800 50  0000 C CNN
F 2 "" H 5650 2950 60  0000 C CNN
F 3 "" H 5650 2950 60  0000 C CNN
	1    5650 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 55145508
P 5950 4900
F 0 "#PWR012" H 5950 4650 50  0001 C CNN
F 1 "GND" H 5950 4750 50  0000 C CNN
F 2 "" H 5950 4900 60  0000 C CNN
F 3 "" H 5950 4900 60  0000 C CNN
	1    5950 4900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 551456BD
P 5950 4350
F 0 "#PWR013" H 5950 4200 50  0001 C CNN
F 1 "+5V" H 5950 4490 50  0000 C CNN
F 2 "" H 5950 4350 60  0000 C CNN
F 3 "" H 5950 4350 60  0000 C CNN
	1    5950 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 551456EF
P 5600 4300
F 0 "#PWR014" H 5600 4050 50  0001 C CNN
F 1 "GND" H 5600 4150 50  0000 C CNN
F 2 "" H 5600 4300 60  0000 C CNN
F 3 "" H 5600 4300 60  0000 C CNN
	1    5600 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 55145721
P 5600 5550
F 0 "#PWR015" H 5600 5300 50  0001 C CNN
F 1 "GND" H 5600 5400 50  0000 C CNN
F 2 "" H 5600 5550 60  0000 C CNN
F 3 "" H 5600 5550 60  0000 C CNN
	1    5600 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 55145CFC
P 2850 1750
F 0 "#PWR016" H 2850 1500 50  0001 C CNN
F 1 "GND" H 2850 1600 50  0000 C CNN
F 2 "" H 2850 1750 60  0000 C CNN
F 3 "" H 2850 1750 60  0000 C CNN
	1    2850 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 55145D59
P 2950 3000
F 0 "#PWR017" H 2950 2750 50  0001 C CNN
F 1 "GND" H 2950 2850 50  0000 C CNN
F 2 "" H 2950 3000 60  0000 C CNN
F 3 "" H 2950 3000 60  0000 C CNN
	1    2950 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 55145D82
P 2950 6500
F 0 "#PWR018" H 2950 6250 50  0001 C CNN
F 1 "GND" H 2950 6350 50  0000 C CNN
F 2 "" H 2950 6500 60  0000 C CNN
F 3 "" H 2950 6500 60  0000 C CNN
	1    2950 6500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 55145DC9
P 2950 5100
F 0 "#PWR019" H 2950 4850 50  0001 C CNN
F 1 "GND" H 2950 4950 50  0000 C CNN
F 2 "" H 2950 5100 60  0000 C CNN
F 3 "" H 2950 5100 60  0000 C CNN
	1    2950 5100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR020
U 1 1 5514788F
P 1450 600
F 0 "#PWR020" H 1450 450 50  0001 C CNN
F 1 "+5V" H 1450 740 50  0000 C CNN
F 2 "" H 1450 600 60  0000 C CNN
F 3 "" H 1450 600 60  0000 C CNN
	1    1450 600 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 5514D04B
P 1450 4000
F 0 "#PWR021" H 1450 3850 50  0001 C CNN
F 1 "+5V" H 1450 4140 50  0000 C CNN
F 2 "" H 1450 4000 60  0000 C CNN
F 3 "" H 1450 4000 60  0000 C CNN
	1    1450 4000
	1    0    0    -1  
$EndComp
Text Label 9250 1350 0    60   ~ 0
SPI_CLK
Text Label 9250 1450 0    60   ~ 0
SPI_MISO
Text Label 7300 1350 0    60   ~ 0
SPI_MOSI
Text Label 6850 1400 0    60   ~ 0
CS0
Text Label 6850 2750 0    60   ~ 0
CS1
Text Label 6850 4100 0    60   ~ 0
CS2
Text Label 6850 5400 0    60   ~ 0
CS3
Entry Wire Line
	1600 800  1700 900 
Entry Wire Line
	1600 1000 1700 1100
Entry Wire Line
	1600 1200 1700 1300
Entry Wire Line
	1600 1600 1700 1700
Entry Wire Line
	1600 1800 1700 1900
Entry Wire Line
	1600 2000 1700 2100
Entry Wire Line
	1600 2200 1700 2300
Entry Wire Line
	1600 2400 1700 2500
Entry Wire Line
	1600 2600 1700 2700
Entry Wire Line
	1600 2800 1700 2900
Entry Wire Line
	1600 3000 1700 3100
Entry Wire Line
	1600 1400 1700 1500
Text Label 1200 800  0    60   ~ 0
L0
Text Label 1200 1000 0    60   ~ 0
L1
Text Label 1200 1200 0    60   ~ 0
L2
Text Label 1200 1400 0    60   ~ 0
L3
Text Label 1200 1600 0    60   ~ 0
L4
Text Label 1200 1800 0    60   ~ 0
L5
Text Label 1200 2000 0    60   ~ 0
L6
Text Label 1200 2200 0    60   ~ 0
L7
Text Label 1200 2400 0    60   ~ 0
L8
Text Label 1200 2600 0    60   ~ 0
L9
Text Label 1200 2800 0    60   ~ 0
L10
Text Label 1200 3000 0    60   ~ 0
L11
Text Label 1200 3250 0    60   ~ 0
L12
Entry Wire Line
	1600 3250 1700 3150
Entry Wire Line
	3150 900  3250 1000
Entry Wire Line
	3150 1000 3250 1100
Entry Wire Line
	3150 1100 3250 1200
Entry Wire Line
	3150 1200 3250 1300
Entry Wire Line
	3150 1300 3250 1400
Entry Wire Line
	3150 1400 3250 1500
Entry Wire Line
	3150 1500 3250 1600
Entry Wire Line
	3150 1600 3250 1700
Entry Wire Line
	3150 2150 3250 2250
Entry Wire Line
	3150 2250 3250 2350
Entry Wire Line
	3150 2350 3250 2450
Entry Wire Line
	3150 2450 3250 2550
Entry Wire Line
	3150 2550 3250 2650
Entry Wire Line
	3150 2650 3250 2750
Entry Wire Line
	3150 2750 3250 2850
Entry Wire Line
	3150 2850 3250 2950
Entry Wire Line
	3950 700  4050 800 
Entry Wire Line
	3950 800  4050 900 
Entry Wire Line
	3950 900  4050 1000
Entry Wire Line
	3950 1000 4050 1100
Entry Wire Line
	3950 1100 4050 1200
Entry Wire Line
	3950 1200 4050 1300
Entry Wire Line
	3950 1300 4050 1400
Entry Wire Line
	3950 1400 4050 1500
Entry Wire Line
	3950 2050 4050 2150
Entry Wire Line
	3950 2150 4050 2250
Entry Wire Line
	3950 2250 4050 2350
Entry Wire Line
	3950 2350 4050 2450
Entry Wire Line
	3950 2450 4050 2550
Entry Wire Line
	3950 2550 4050 2650
Entry Wire Line
	3950 2650 4050 2750
Entry Wire Line
	3950 2750 4050 2850
Text Label 4150 800  0    60   ~ 0
L0
Text Label 4150 900  0    60   ~ 0
L1
Text Label 4150 1000 0    60   ~ 0
L2
Text Label 4150 1100 0    60   ~ 0
L3
Text Label 4150 1200 0    60   ~ 0
L4
Text Label 4150 1300 0    60   ~ 0
L5
Text Label 4150 1400 0    60   ~ 0
L6
Text Label 4150 1500 0    60   ~ 0
L7
Text Label 4150 2150 0    60   ~ 0
L15
Text Label 4150 2250 0    60   ~ 0
L14
Text Label 4150 2350 0    60   ~ 0
L13
Text Label 4150 2450 0    60   ~ 0
L12
Text Label 4150 2550 0    60   ~ 0
L11
Text Label 4150 2650 0    60   ~ 0
L10
Text Label 4150 2750 0    60   ~ 0
L9
Text Label 4150 2850 0    60   ~ 0
L8
Text Label 2900 900  0    60   ~ 0
L7
Text Label 2900 1000 0    60   ~ 0
L6
Text Label 2900 1100 0    60   ~ 0
L5
Text Label 2900 1200 0    60   ~ 0
L4
Text Label 2900 1300 0    60   ~ 0
L3
Text Label 2900 1400 0    60   ~ 0
L2
Text Label 2900 1500 0    60   ~ 0
L1
Text Label 2900 1600 0    60   ~ 0
L0
Text Label 2900 2150 0    60   ~ 0
L8
Text Label 2900 2250 0    60   ~ 0
L9
Text Label 2900 2350 0    60   ~ 0
L10
Text Label 2900 2450 0    60   ~ 0
L11
Text Label 2900 2550 0    60   ~ 0
L12
Text Label 2900 2650 0    60   ~ 0
L13
Text Label 2900 2750 0    60   ~ 0
L14
Text Label 2900 2850 0    60   ~ 0
L15
Entry Wire Line
	1600 4300 1700 4400
Entry Wire Line
	1600 4500 1700 4600
Entry Wire Line
	1600 4700 1700 4800
Entry Wire Line
	1600 4900 1700 5000
Entry Wire Line
	1600 5100 1700 5200
Entry Wire Line
	1600 5300 1700 5400
Entry Wire Line
	1600 5500 1700 5600
Entry Wire Line
	1600 5700 1700 5800
Entry Wire Line
	1600 5900 1700 6000
Entry Wire Line
	1600 6100 1700 6200
Entry Wire Line
	1600 6300 1700 6400
Entry Wire Line
	1600 6500 1700 6600
Entry Wire Line
	3150 4250 3250 4350
Entry Wire Line
	3150 4350 3250 4450
Entry Wire Line
	3150 4450 3250 4550
Entry Wire Line
	3150 4550 3250 4650
Entry Wire Line
	3150 4650 3250 4750
Entry Wire Line
	3150 4750 3250 4850
Entry Wire Line
	3150 4850 3250 4950
Entry Wire Line
	3150 4950 3250 5050
Entry Wire Line
	3150 5650 3250 5750
Entry Wire Line
	3150 5750 3250 5850
Entry Wire Line
	3150 5850 3250 5950
Entry Wire Line
	3150 5950 3250 6050
Entry Wire Line
	3150 6050 3250 6150
Entry Wire Line
	3150 6150 3250 6250
Entry Wire Line
	3150 6250 3250 6350
Entry Wire Line
	3150 6350 3250 6450
Entry Wire Line
	4150 3400 4250 3500
Entry Wire Line
	4150 3500 4250 3600
Entry Wire Line
	4150 3600 4250 3700
Entry Wire Line
	4150 3700 4250 3800
Entry Wire Line
	4150 3800 4250 3900
Entry Wire Line
	4150 3900 4250 4000
Entry Wire Line
	4150 4000 4250 4100
Entry Wire Line
	4150 4100 4250 4200
Entry Wire Line
	4150 4700 4250 4800
Entry Wire Line
	4150 4800 4250 4900
Entry Wire Line
	4150 4900 4250 5000
Entry Wire Line
	4150 5000 4250 5100
Entry Wire Line
	4150 5100 4250 5200
Entry Wire Line
	4150 5200 4250 5300
Entry Wire Line
	4150 5300 4250 5400
Entry Wire Line
	4150 5400 4250 5500
Text Label 1200 4300 0    60   ~ 0
R0
Text Label 1200 4500 0    60   ~ 0
R1
Text Label 1200 4700 0    60   ~ 0
R2
Text Label 1200 4900 0    60   ~ 0
R3
Text Label 1200 5100 0    60   ~ 0
R4
Text Label 1200 5300 0    60   ~ 0
R5
Text Label 1200 5500 0    60   ~ 0
R6
Text Label 1200 5700 0    60   ~ 0
R7
Text Label 1200 5900 0    60   ~ 0
R8
Text Label 1200 6100 0    60   ~ 0
R9
Text Label 1200 6300 0    60   ~ 0
R10
Text Label 1200 6500 0    60   ~ 0
R11
Text Label 1200 6700 0    60   ~ 0
R12
Entry Wire Line
	1600 6700 1700 6800
Text Label 2900 4250 0    60   ~ 0
R7
Text Label 2900 4350 0    60   ~ 0
R6
Text Label 2900 4450 0    60   ~ 0
R5
Text Label 2900 4550 0    60   ~ 0
R4
Text Label 2900 4650 0    60   ~ 0
R3
Text Label 2900 4750 0    60   ~ 0
R2
Text Label 2900 4850 0    60   ~ 0
R1
Text Label 2900 4950 0    60   ~ 0
R0
Text Label 2900 5650 0    60   ~ 0
R8
Text Label 2900 5750 0    60   ~ 0
R9
Text Label 2900 5850 0    60   ~ 0
R10
Text Label 2900 5950 0    60   ~ 0
R11
Text Label 2900 6050 0    60   ~ 0
R12
Text Label 2900 6150 0    60   ~ 0
R13
Text Label 2900 6250 0    60   ~ 0
R14
Text Label 2900 6350 0    60   ~ 0
R15
Text Label 4250 3500 0    60   ~ 0
R0
Text Label 4250 3600 0    60   ~ 0
R1
Text Label 4250 3700 0    60   ~ 0
R2
Text Label 4250 3800 0    60   ~ 0
R3
Text Label 4250 3900 0    60   ~ 0
R4
Text Label 4250 4000 0    60   ~ 0
R5
Text Label 4250 4100 0    60   ~ 0
R6
Text Label 4250 4200 0    60   ~ 0
R7
Text Label 4250 4800 0    60   ~ 0
R15
Text Label 4250 4900 0    60   ~ 0
R14
Text Label 4250 5000 0    60   ~ 0
R13
Text Label 4250 5100 0    60   ~ 0
R12
Text Label 4250 5200 0    60   ~ 0
R11
Text Label 4250 5300 0    60   ~ 0
R10
Text Label 4250 5400 0    60   ~ 0
R9
Text Label 4250 5500 0    60   ~ 0
R8
$Comp
L R R6
U 1 1 551508DE
P 6550 3500
F 0 "R6" V 6630 3500 50  0000 C CNN
F 1 "10k" V 6550 3500 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6480 3500 30  0001 C CNN
F 3 "" H 6550 3500 30  0000 C CNN
	1    6550 3500
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 551509BB
P 6600 2150
F 0 "R8" V 6680 2150 50  0000 C CNN
F 1 "10k" V 6600 2150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6530 2150 30  0001 C CNN
F 3 "" H 6600 2150 30  0000 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 55150AAE
P 6550 900
F 0 "R5" V 6630 900 50  0000 C CNN
F 1 "10k" V 6550 900 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6480 900 30  0001 C CNN
F 3 "" H 6550 900 30  0000 C CNN
	1    6550 900 
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 55150B22
P 6550 4750
F 0 "R7" V 6630 4750 50  0000 C CNN
F 1 "10k" V 6550 4750 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6480 4750 30  0001 C CNN
F 3 "" H 6550 4750 30  0000 C CNN
	1    6550 4750
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR022
U 1 1 551511BA
P 6550 700
F 0 "#PWR022" H 6550 550 50  0001 C CNN
F 1 "+5V" H 6550 840 50  0000 C CNN
F 2 "" H 6550 700 60  0000 C CNN
F 3 "" H 6550 700 60  0000 C CNN
	1    6550 700 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR023
U 1 1 551511E9
P 6600 1900
F 0 "#PWR023" H 6600 1750 50  0001 C CNN
F 1 "+5V" H 6600 2040 50  0000 C CNN
F 2 "" H 6600 1900 60  0000 C CNN
F 3 "" H 6600 1900 60  0000 C CNN
	1    6600 1900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR024
U 1 1 55151231
P 6550 3250
F 0 "#PWR024" H 6550 3100 50  0001 C CNN
F 1 "+5V" H 6550 3390 50  0000 C CNN
F 2 "" H 6550 3250 60  0000 C CNN
F 3 "" H 6550 3250 60  0000 C CNN
	1    6550 3250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR025
U 1 1 55151272
P 6550 4500
F 0 "#PWR025" H 6550 4350 50  0001 C CNN
F 1 "+5V" H 6550 4640 50  0000 C CNN
F 2 "" H 6550 4500 60  0000 C CNN
F 3 "" H 6550 4500 60  0000 C CNN
	1    6550 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1350 9650 1350
Wire Wire Line
	9200 1450 9650 1450
Wire Wire Line
	9250 1600 9250 1650
Wire Wire Line
	9250 1650 9200 1650
Wire Wire Line
	9250 1600 9600 1600
Wire Wire Line
	9600 1600 9600 1650
Wire Wire Line
	7800 1850 7550 1850
Wire Wire Line
	5950 850  5950 900 
Wire Wire Line
	5950 900  5800 900 
Wire Wire Line
	5800 900  5800 1000
Wire Wire Line
	5800 1000 5500 1000
Wire Wire Line
	5600 900  5500 900 
Wire Wire Line
	5600 550  5600 900 
Wire Wire Line
	5600 800  5500 800 
Wire Wire Line
	5600 550  6150 550 
Connection ~ 5600 800 
Wire Wire Line
	6150 550  6150 700 
Wire Wire Line
	6150 700  6300 700 
Connection ~ 5950 550 
Wire Wire Line
	5500 1500 5850 1500
Wire Wire Line
	5850 1500 5850 1550
Wire Wire Line
	5500 2250 5800 2250
Wire Wire Line
	5800 2250 5800 1850
Wire Wire Line
	5800 1850 6100 1850
Wire Wire Line
	6100 1800 6100 1900
Wire Wire Line
	5500 2150 5800 2150
Connection ~ 5800 2150
Wire Wire Line
	5500 2350 5950 2350
Wire Wire Line
	5950 2350 5950 2250
Wire Wire Line
	6100 2250 6100 2200
Wire Wire Line
	5950 2250 6200 2250
Connection ~ 6100 1850
Connection ~ 6100 2250
Wire Wire Line
	5500 2850 5650 2850
Wire Wire Line
	5650 2850 5650 2950
Wire Wire Line
	5950 3050 5950 3200
Wire Wire Line
	5500 3600 5800 3600
Wire Wire Line
	5800 3600 5800 3100
Wire Wire Line
	5800 3100 5950 3100
Connection ~ 5950 3100
Wire Wire Line
	5500 3500 5800 3500
Connection ~ 5800 3500
Wire Wire Line
	5500 3700 5850 3700
Wire Wire Line
	5850 3700 5850 3550
Wire Wire Line
	5850 3550 5950 3550
Wire Wire Line
	5950 3500 5950 3600
Connection ~ 5950 3550
Wire Wire Line
	5500 4800 5800 4800
Wire Wire Line
	5800 4900 5800 4400
Wire Wire Line
	5800 4400 5950 4400
Wire Wire Line
	5950 4350 5950 4500
Wire Wire Line
	5500 4900 5800 4900
Connection ~ 5800 4800
Wire Wire Line
	5850 4850 5950 4850
Wire Wire Line
	5950 4800 5950 4900
Wire Wire Line
	5850 4850 5850 5000
Wire Wire Line
	5850 5000 5500 5000
Connection ~ 5950 4850
Wire Wire Line
	5500 5500 5600 5500
Wire Wire Line
	5600 5500 5600 5550
Wire Wire Line
	2800 2950 2950 2950
Wire Wire Line
	2950 2950 2950 3000
Wire Wire Line
	1100 700  1450 700 
Wire Wire Line
	1450 600  1450 3100
Wire Wire Line
	1100 900  1450 900 
Connection ~ 1450 700 
Wire Wire Line
	1450 1100 1100 1100
Connection ~ 1450 900 
Wire Wire Line
	1450 1300 1100 1300
Connection ~ 1450 1100
Wire Wire Line
	1450 1500 1100 1500
Connection ~ 1450 1300
Wire Wire Line
	1450 1700 1100 1700
Connection ~ 1450 1500
Wire Wire Line
	1450 1900 1100 1900
Connection ~ 1450 1700
Wire Wire Line
	1100 2100 1450 2100
Connection ~ 1450 1900
Wire Wire Line
	1450 2300 1100 2300
Connection ~ 1450 2100
Wire Wire Line
	1100 2500 1450 2500
Connection ~ 1450 2300
Wire Wire Line
	1450 2700 1100 2700
Connection ~ 1450 2500
Wire Wire Line
	1450 2900 1100 2900
Connection ~ 1450 2700
Wire Wire Line
	1450 3100 1100 3100
Connection ~ 1450 2900
Wire Wire Line
	1100 4200 1450 4200
Wire Wire Line
	1450 4000 1450 6600
Wire Wire Line
	1450 4400 1100 4400
Connection ~ 1450 4200
Wire Wire Line
	1450 4600 1100 4600
Connection ~ 1450 4400
Wire Wire Line
	1450 4800 1100 4800
Connection ~ 1450 4600
Wire Wire Line
	1450 5000 1100 5000
Connection ~ 1450 4800
Wire Wire Line
	1450 5200 1100 5200
Connection ~ 1450 5000
Wire Wire Line
	1450 5400 1100 5400
Connection ~ 1450 5200
Wire Wire Line
	1100 5600 1450 5600
Connection ~ 1450 5400
Wire Wire Line
	1450 5800 1100 5800
Connection ~ 1450 5600
Wire Wire Line
	1450 6000 1100 6000
Connection ~ 1450 5800
Wire Wire Line
	1100 6200 1450 6200
Connection ~ 1450 6000
Wire Wire Line
	1100 6400 1450 6400
Connection ~ 1450 6200
Wire Wire Line
	1450 6600 1100 6600
Connection ~ 1450 6400
Wire Wire Line
	5500 4200 5600 4200
Wire Wire Line
	5600 4200 5600 4300
Wire Wire Line
	9200 1850 10350 1850
Wire Wire Line
	10350 1850 10350 1000
Connection ~ 5950 4400
Wire Wire Line
	2800 1700 2850 1700
Wire Wire Line
	2850 1700 2850 1750
Wire Bus Line
	1700 3200 1700 700 
Wire Bus Line
	1700 700  3250 700 
Wire Bus Line
	3250 700  3250 3200
Wire Bus Line
	3250 3200 3950 3200
Wire Bus Line
	3950 3200 3950 700 
Wire Wire Line
	1600 800  1100 800 
Wire Wire Line
	1600 1000 1100 1000
Wire Wire Line
	1600 1200 1100 1200
Wire Wire Line
	1600 1400 1100 1400
Wire Wire Line
	1100 1600 1600 1600
Wire Wire Line
	1600 1800 1100 1800
Wire Wire Line
	1100 2000 1600 2000
Wire Wire Line
	1100 2200 1600 2200
Wire Wire Line
	1100 2400 1600 2400
Wire Wire Line
	1100 2600 1600 2600
Wire Wire Line
	1100 2800 1600 2800
Wire Wire Line
	1100 3000 1600 3000
Wire Wire Line
	1600 3250 1100 3250
Wire Wire Line
	1100 3250 1100 3200
Wire Wire Line
	4050 800  4400 800 
Wire Wire Line
	4050 900  4400 900 
Wire Wire Line
	4050 1000 4400 1000
Wire Wire Line
	4050 1100 4400 1100
Wire Wire Line
	4050 1200 4400 1200
Wire Wire Line
	4050 1300 4400 1300
Wire Wire Line
	4050 1400 4400 1400
Wire Wire Line
	4050 1500 4400 1500
Wire Wire Line
	4050 2150 4400 2150
Wire Wire Line
	4050 2250 4400 2250
Wire Wire Line
	4050 2350 4400 2350
Wire Wire Line
	4050 2450 4400 2450
Wire Wire Line
	4050 2550 4400 2550
Wire Wire Line
	4050 2650 4400 2650
Wire Wire Line
	4050 2750 4400 2750
Wire Wire Line
	4050 2850 4400 2850
Wire Wire Line
	2800 2150 3150 2150
Wire Wire Line
	2800 2250 3150 2250
Wire Wire Line
	2800 2350 3150 2350
Wire Wire Line
	2800 2450 3150 2450
Wire Wire Line
	2800 2550 3150 2550
Wire Wire Line
	2800 2650 3150 2650
Wire Wire Line
	2800 2750 3150 2750
Wire Wire Line
	2800 2850 3150 2850
Wire Wire Line
	2800 900  3150 900 
Wire Wire Line
	2800 1000 3150 1000
Wire Wire Line
	2800 1100 3150 1100
Wire Wire Line
	2800 1200 3150 1200
Wire Wire Line
	2800 1300 3150 1300
Wire Wire Line
	2800 1400 3150 1400
Wire Wire Line
	2800 1500 3150 1500
Wire Wire Line
	2800 1600 3150 1600
Wire Wire Line
	2800 6450 2950 6450
Wire Wire Line
	2950 6450 2950 6500
Wire Wire Line
	2800 5050 2950 5050
Wire Wire Line
	2950 5050 2950 5100
Wire Bus Line
	1700 6850 1700 3750
Wire Bus Line
	1700 3750 3250 3750
Wire Bus Line
	3250 3750 3250 6850
Wire Bus Line
	3250 6850 4150 6850
Wire Bus Line
	4150 6850 4150 3350
Wire Wire Line
	4250 3500 4400 3500
Wire Wire Line
	4250 3600 4400 3600
Wire Wire Line
	4250 3700 4400 3700
Wire Wire Line
	4250 3800 4400 3800
Wire Wire Line
	4250 3900 4400 3900
Wire Wire Line
	4250 4000 4400 4000
Wire Wire Line
	4250 4100 4400 4100
Wire Wire Line
	4250 4200 4400 4200
Wire Wire Line
	4250 4800 4400 4800
Wire Wire Line
	4250 4900 4400 4900
Wire Wire Line
	4250 5000 4400 5000
Wire Wire Line
	4250 5100 4400 5100
Wire Wire Line
	4250 5200 4400 5200
Wire Wire Line
	4250 5300 4400 5300
Wire Wire Line
	4250 5400 4400 5400
Wire Wire Line
	4250 5500 4400 5500
Wire Wire Line
	2800 4250 3150 4250
Wire Wire Line
	2800 4350 3150 4350
Wire Wire Line
	2800 4450 3150 4450
Wire Wire Line
	2800 4550 3150 4550
Wire Wire Line
	2800 4650 3150 4650
Wire Wire Line
	2800 4750 3150 4750
Wire Wire Line
	2800 4850 3150 4850
Wire Wire Line
	2800 4950 3150 4950
Wire Wire Line
	2800 5650 3150 5650
Wire Wire Line
	2800 5750 3150 5750
Wire Wire Line
	2800 5850 3150 5850
Wire Wire Line
	2800 5950 3150 5950
Wire Wire Line
	2800 6050 3150 6050
Wire Wire Line
	2800 6150 3150 6150
Wire Wire Line
	2800 6250 3150 6250
Wire Wire Line
	2800 6350 3150 6350
Wire Wire Line
	1100 4300 1600 4300
Wire Wire Line
	1100 4500 1600 4500
Wire Wire Line
	1100 4700 1600 4700
Wire Wire Line
	1100 4900 1600 4900
Wire Wire Line
	1100 5100 1600 5100
Wire Wire Line
	1100 5300 1600 5300
Wire Wire Line
	1100 5500 1600 5500
Wire Wire Line
	1100 5700 1600 5700
Wire Wire Line
	1600 5900 1100 5900
Wire Wire Line
	1100 6100 1600 6100
Wire Wire Line
	1100 6300 1600 6300
Wire Wire Line
	1100 6500 1600 6500
Wire Wire Line
	1100 6700 1600 6700
Wire Wire Line
	7250 1950 7800 1950
Wire Wire Line
	7250 2950 7800 2950
Wire Wire Line
	6550 4500 6550 4600
Wire Wire Line
	6600 1900 6600 2000
Wire Wire Line
	6550 700  6550 750 
Wire Wire Line
	6550 3250 6550 3350
$Comp
L ARDUINO_MICRO U5
U 1 1 55140634
P 8500 2100
F 0 "U5" H 8050 1100 60  0000 C CNN
F 1 "ARDUINO_MICRO" H 8450 3000 60  0000 C CNN
F 2 "Giant_Midi_Keyboard:ARDUINO_MICRO" H 8350 1500 60  0001 C CNN
F 3 "" H 8350 1500 60  0000 C CNN
F 4 "Arduino" H 8150 1200 60  0001 C CNN "Manufacturer"
F 5 "Arduino Micro" H 8250 1300 60  0001 C CNN "Part Number"
	1    8500 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2850 7800 2850
Wire Bus Line
	9750 2100 9750 3700
Entry Wire Line
	9650 2450 9750 2550
Entry Wire Line
	9650 3350 9750 3450
Entry Wire Line
	9650 2350 9750 2450
Wire Wire Line
	9650 2350 9200 2350
Wire Wire Line
	9650 2450 9200 2450
Entry Wire Line
	9650 2250 9750 2350
Entry Wire Line
	9650 2150 9750 2250
Text Label 7300 1650 0    60   ~ 0
CS0
Text Label 7300 1950 0    60   ~ 0
CS1
Text Label 7300 2950 0    60   ~ 0
CS2
Text Label 7300 2850 0    60   ~ 0
CS3
Wire Bus Line
	9750 750  9750 1600
Wire Bus Line
	7150 750  9750 750 
Entry Wire Line
	9650 1450 9750 1550
Entry Wire Line
	9650 1350 9750 1450
Entry Wire Line
	7150 1250 7250 1350
Wire Wire Line
	7250 1350 7800 1350
Wire Bus Line
	7150 750  7150 5850
Entry Wire Line
	7150 1550 7250 1650
Entry Wire Line
	7150 1850 7250 1950
Entry Wire Line
	7150 2750 7250 2850
Entry Wire Line
	7150 2850 7250 2950
Wire Wire Line
	7250 1650 7800 1650
Entry Wire Line
	7050 1100 7150 1200
Entry Wire Line
	7050 1200 7150 1300
Entry Wire Line
	7050 1300 7150 1400
Entry Wire Line
	7050 1400 7150 1500
Entry Wire Line
	7050 2450 7150 2550
Entry Wire Line
	7050 2550 7150 2650
Entry Wire Line
	7050 2650 7150 2750
Entry Wire Line
	7050 2750 7150 2850
Entry Wire Line
	7050 3800 7150 3900
Entry Wire Line
	7050 3900 7150 4000
Entry Wire Line
	7050 4000 7150 4100
Entry Wire Line
	7050 4100 7150 4200
Entry Wire Line
	7050 5100 7150 5200
Entry Wire Line
	7050 5200 7150 5300
Entry Wire Line
	7050 5300 7150 5400
Entry Wire Line
	7050 5400 7150 5500
Wire Wire Line
	5500 1100 7050 1100
Wire Wire Line
	5500 1200 7050 1200
Wire Wire Line
	5500 1300 7050 1300
Wire Wire Line
	5500 1400 7050 1400
Wire Wire Line
	5500 2450 7050 2450
Wire Wire Line
	5500 2550 7050 2550
Wire Wire Line
	5500 2650 7050 2650
Wire Wire Line
	5500 2750 7050 2750
Wire Wire Line
	7050 3800 5500 3800
Wire Wire Line
	7050 3900 5500 3900
Wire Wire Line
	7050 4000 5500 4000
Wire Wire Line
	7050 4100 5500 4100
Wire Wire Line
	7050 5100 5500 5100
Wire Wire Line
	7050 5200 5500 5200
Wire Wire Line
	7050 5300 5500 5300
Wire Wire Line
	7050 5400 5500 5400
Wire Wire Line
	6600 2300 6600 2750
Connection ~ 6600 2750
Wire Wire Line
	6550 3650 6550 4100
Connection ~ 6550 4100
Wire Wire Line
	6550 4900 6550 5400
Connection ~ 6550 5400
Text Label 6650 2450 0    60   ~ 0
SPI_CLK
Text Label 6650 2550 0    60   ~ 0
SPI_MISO
Text Label 6650 2650 0    60   ~ 0
SPI_MOSI
Text Label 6650 4000 0    60   ~ 0
SPI_MOSI
Text Label 6650 5300 0    60   ~ 0
SPI_MOSI
Text Label 6650 1300 0    60   ~ 0
SPI_MOSI
Wire Wire Line
	6550 1050 6550 1400
Connection ~ 6550 1400
Text Label 6650 1100 0    60   ~ 0
SPI_CLK
Text Label 6650 1200 0    60   ~ 0
SPI_MISO
Text Label 6650 3900 0    60   ~ 0
SPI_MISO
Text Label 6650 3800 0    60   ~ 0
SPI_CLK
Text Label 6650 5100 0    60   ~ 0
SPI_CLK
Text Label 6650 5200 0    60   ~ 0
SPI_MISO
Wire Wire Line
	9200 2150 9650 2150
Wire Wire Line
	9200 2250 9650 2250
Wire Bus Line
	9750 2100 10650 2100
Wire Bus Line
	10650 2100 10650 5800
$Comp
L CONN_01X10 P3
U 1 1 551AA706
P 9400 5050
F 0 "P3" H 9400 5600 50  0000 C CNN
F 1 "CONN_01X10" V 9500 5050 50  0000 C CNN
F 2 "Giant_Midi_Keyboard:Header_2x5" H 9400 5050 60  0001 C CNN
F 3 "" H 9400 5050 60  0000 C CNN
	1    9400 5050
	-1   0    0    1   
$EndComp
Entry Wire Line
	10550 4700 10650 4800
Entry Wire Line
	10550 4800 10650 4900
Entry Wire Line
	10550 4900 10650 5000
Entry Wire Line
	10550 5000 10650 5100
Entry Wire Line
	10550 5100 10650 5200
Entry Wire Line
	10550 5200 10650 5300
Entry Wire Line
	10550 5300 10650 5400
Entry Wire Line
	10550 5400 10650 5500
Wire Wire Line
	9600 4700 10550 4700
Wire Wire Line
	9600 4800 10550 4800
Wire Wire Line
	9600 4900 10550 4900
Wire Wire Line
	9600 5000 10550 5000
Wire Wire Line
	9600 5100 10550 5100
Wire Wire Line
	9600 5200 10550 5200
Wire Wire Line
	9600 5300 10550 5300
Wire Wire Line
	9600 5400 10550 5400
$Comp
L GND #PWR026
U 1 1 551AAA43
P 9750 5650
F 0 "#PWR026" H 9750 5400 50  0001 C CNN
F 1 "GND" H 9750 5500 50  0000 C CNN
F 2 "" H 9750 5650 60  0000 C CNN
F 3 "" H 9750 5650 60  0000 C CNN
	1    9750 5650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR027
U 1 1 551AAA6B
P 9800 4400
F 0 "#PWR027" H 9800 4250 50  0001 C CNN
F 1 "+5V" H 9800 4540 50  0000 C CNN
F 2 "" H 9800 4400 60  0000 C CNN
F 3 "" H 9800 4400 60  0000 C CNN
	1    9800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 4600 9800 4600
Wire Wire Line
	9800 4600 9800 4400
Wire Wire Line
	9600 5500 9750 5500
Wire Wire Line
	9750 5500 9750 5650
Text Label 9950 4700 0    60   ~ 0
DBG_I0
Text Label 9950 4800 0    60   ~ 0
DBG_I1
Text Label 9950 4900 0    60   ~ 0
DBG_I2
Text Label 9950 5000 0    60   ~ 0
DBG_O0
Text Label 9950 5100 0    60   ~ 0
DBG_O1
Text Label 9950 5200 0    60   ~ 0
DBG_O2
Text Label 9950 5300 0    60   ~ 0
DBG_O3
Text Label 9950 5400 0    60   ~ 0
DBG_O4
Entry Wire Line
	9650 3450 9750 3550
Entry Wire Line
	9650 3550 9750 3650
Text Label 9300 2150 0    60   ~ 0
DBG_I0
Text Label 9300 3550 0    60   ~ 0
DBG_I1
Text Label 9300 2250 0    60   ~ 0
DBG_I2
Text Label 9300 3450 0    60   ~ 0
DBG_O0
Text Label 9300 2350 0    60   ~ 0
DBG_O1
Text Label 9300 3350 0    60   ~ 0
DBG_O2
Text Label 9300 2450 0    60   ~ 0
DBG_O3
Text Label 9300 3250 0    60   ~ 0
DBG_O4
Wire Wire Line
	7800 2450 7500 2450
Wire Wire Line
	7500 2450 7500 3550
Wire Wire Line
	7800 2550 7550 2550
Wire Wire Line
	7550 2550 7550 3450
Wire Wire Line
	7800 2650 7600 2650
Wire Wire Line
	7600 2650 7600 3350
Wire Wire Line
	7800 2750 7650 2750
Wire Wire Line
	7650 2750 7650 3250
Wire Wire Line
	7500 3550 9650 3550
Wire Wire Line
	7550 3450 9650 3450
Wire Wire Line
	7600 3350 9650 3350
Entry Wire Line
	9650 3250 9750 3350
Wire Wire Line
	7650 3250 9650 3250
$EndSCHEMATC

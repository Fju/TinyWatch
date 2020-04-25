EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "AVRist watch"
Date "2020-03-08"
Rev "2"
Comp "Florian Winkler"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Timer_RTC:DS3231MZ U5
U 1 1 5E64F04B
P 6850 4350
F 0 "U5" H 6850 3861 50  0000 C CNN
F 1 "DS3231MZ" H 6850 3770 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6850 3850 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231M.pdf" H 6850 3750 50  0001 C CNN
	1    6850 4350
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J1
U 1 1 5E652A6D
P 1200 2250
F 0 "J1" H 1257 2717 50  0000 C CNN
F 1 "USB_B_Micro" H 1257 2626 50  0000 C CNN
F 2 "pcb:USB_B_micro" H 1350 2200 50  0001 C CNN
F 3 "~" H 1350 2200 50  0001 C CNN
	1    1200 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E6552A2
P 1200 2800
F 0 "#PWR0101" H 1200 2550 50  0001 C CNN
F 1 "GND" H 1205 2627 50  0000 C CNN
F 2 "" H 1200 2800 50  0001 C CNN
F 3 "" H 1200 2800 50  0001 C CNN
	1    1200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2650 1200 2750
$Comp
L Device:LED D1
U 1 1 5E65E280
P 2200 2200
F 0 "D1" V 2239 2083 50  0000 R CNN
F 1 "LED" V 2148 2083 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 2200 2200 50  0001 C CNN
F 3 "~" H 2200 2200 50  0001 C CNN
	1    2200 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5E682574
P 3500 2800
F 0 "#PWR0102" H 3500 2550 50  0001 C CNN
F 1 "GND" H 3505 2627 50  0000 C CNN
F 2 "" H 3500 2800 50  0001 C CNN
F 3 "" H 3500 2800 50  0001 C CNN
	1    3500 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2350 2200 2450
Wire Wire Line
	2200 2750 2200 2850
$Comp
L Device:R R3
U 1 1 5E6848DD
P 3500 2500
F 0 "R3" H 3570 2546 50  0000 L CNN
F 1 "10K" H 3570 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3430 2500 50  0001 C CNN
F 3 "~" H 3500 2500 50  0001 C CNN
	1    3500 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E685387
P 1800 2500
F 0 "#PWR0103" H 1800 2250 50  0001 C CNN
F 1 "GND" H 1805 2327 50  0000 C CNN
F 2 "" H 1800 2500 50  0001 C CNN
F 3 "" H 1800 2500 50  0001 C CNN
	1    1800 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E68602E
P 4000 2200
F 0 "C3" H 4115 2246 50  0000 L CNN
F 1 "4.7u" H 4115 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4038 2050 50  0001 C CNN
F 3 "~" H 4000 2200 50  0001 C CNN
	1    4000 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E687933
P 4000 2500
F 0 "#PWR0104" H 4000 2250 50  0001 C CNN
F 1 "GND" H 4005 2327 50  0000 C CNN
F 2 "" H 4000 2500 50  0001 C CNN
F 3 "" H 4000 2500 50  0001 C CNN
	1    4000 2500
	1    0    0    -1  
$EndComp
Text Notes 3700 3000 0    50   ~ 0
I_bat = 1000 / R_prog = 100 mA\nR_prog = 10 K
Text Notes 2600 7400 0    50   ~ 0
// buttons\nPD3 (INT1) - BTN2\nPD2 (INT0) - BTN1\n\n// I²C bus\nPC5 (SCL) - SCL\nPC4 (SDA) - SDA\n\n// display\nPD0 - DISP_RST\n\n// SPI bus\nPB5 (SCK) - SCK\nPB4 (MISO) - MISO\nPB3 (MOSI) - MOSI\nPC6 (RESET#) - RESET\n
$Comp
L power:VCC #PWR0105
U 1 1 5E69CA8E
P 1800 3400
F 0 "#PWR0105" H 1800 3250 50  0001 C CNN
F 1 "VCC" H 1817 3573 50  0000 C CNN
F 2 "" H 1800 3400 50  0001 C CNN
F 3 "" H 1800 3400 50  0001 C CNN
	1    1800 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3400 1800 3500
$Comp
L MCU_Microchip_ATmega:ATmega328P-AU U1
U 1 1 5E656D98
P 1800 5100
F 0 "U1" H 1800 3511 50  0000 C CNN
F 1 "ATmega328P-AU" H 1800 3420 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 1800 5100 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 1800 5100 50  0001 C CNN
	1    1800 5100
	1    0    0    -1  
$EndComp
Text GLabel 3150 5400 2    50   Input ~ 0
RESET
Text GLabel 2600 5300 2    50   Input ~ 0
SCL
Text GLabel 2600 5200 2    50   Input ~ 0
SDA
Text GLabel 2600 5800 2    50   Input ~ 0
BTN1
Text GLabel 2600 5900 2    50   Input ~ 0
BTN2
Wire Wire Line
	2400 5900 2600 5900
Wire Wire Line
	2400 5800 2600 5800
Wire Wire Line
	2400 5300 2600 5300
Wire Wire Line
	2400 5200 2600 5200
Text GLabel 2650 4200 2    50   Input ~ 0
MISO
Text GLabel 2650 4300 2    50   Input ~ 0
MOSI
Text GLabel 2650 4400 2    50   Input ~ 0
SCK
Wire Wire Line
	2400 4400 2650 4400
Wire Wire Line
	2400 4300 2650 4300
Wire Wire Line
	2400 4200 2650 4200
$Comp
L power:GND #PWR0106
U 1 1 5E6BE7DE
P 1800 6900
F 0 "#PWR0106" H 1800 6650 50  0001 C CNN
F 1 "GND" H 1805 6727 50  0000 C CNN
F 2 "" H 1800 6900 50  0001 C CNN
F 3 "" H 1800 6900 50  0001 C CNN
	1    1800 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6600 1800 6900
NoConn ~ 1200 4100
NoConn ~ 1200 4200
$Comp
L power:GND #PWR0107
U 1 1 5E6C7611
P 5450 5200
F 0 "#PWR0107" H 5450 4950 50  0001 C CNN
F 1 "GND" H 5455 5027 50  0000 C CNN
F 2 "" H 5450 5200 50  0001 C CNN
F 3 "" H 5450 5200 50  0001 C CNN
	1    5450 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 5050 5450 5050
Wire Wire Line
	5450 5200 5450 5050
Text GLabel 4850 4400 2    50   Input ~ 0
BTN1
Text GLabel 5600 4400 2    50   Input ~ 0
BTN2
Wire Wire Line
	4850 4400 4700 4400
Wire Wire Line
	4700 4400 4700 4450
Wire Wire Line
	5600 4400 5450 4400
Wire Wire Line
	5450 4400 5450 4450
Text GLabel 6150 4150 0    50   Input ~ 0
SCL
Text GLabel 6150 4250 0    50   Input ~ 0
SDA
Wire Wire Line
	6150 4250 6350 4250
Wire Wire Line
	6150 4150 6350 4150
$Comp
L power:GND #PWR0109
U 1 1 5E6DC975
P 6850 5050
F 0 "#PWR0109" H 6850 4800 50  0001 C CNN
F 1 "GND" H 6855 4877 50  0000 C CNN
F 2 "" H 6850 5050 50  0001 C CNN
F 3 "" H 6850 5050 50  0001 C CNN
	1    6850 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 5050 6850 4750
$Comp
L power:VCC #PWR0110
U 1 1 5E6E594C
P 3000 4900
F 0 "#PWR0110" H 3000 4750 50  0001 C CNN
F 1 "VCC" H 3017 5073 50  0000 C CNN
F 2 "" H 3000 4900 50  0001 C CNN
F 3 "" H 3000 4900 50  0001 C CNN
	1    3000 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5E6E5F14
P 3000 5150
F 0 "R2" H 3070 5196 50  0000 L CNN
F 1 "10K" H 3070 5105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2930 5150 50  0001 C CNN
F 3 "~" H 3000 5150 50  0001 C CNN
	1    3000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5400 3000 5400
Wire Wire Line
	3000 5300 3000 5400
Connection ~ 3000 5400
Wire Wire Line
	3000 5400 3150 5400
Wire Wire Line
	3000 4900 3000 5000
$Comp
L power:VCC #PWR0111
U 1 1 5E6F5F50
P 3350 3550
F 0 "#PWR0111" H 3350 3400 50  0001 C CNN
F 1 "VCC" H 3367 3723 50  0000 C CNN
F 2 "" H 3350 3550 50  0001 C CNN
F 3 "" H 3350 3550 50  0001 C CNN
	1    3350 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5E6F6413
P 3350 4050
F 0 "#PWR0112" H 3350 3800 50  0001 C CNN
F 1 "GND" H 3355 3877 50  0000 C CNN
F 2 "" H 3350 4050 50  0001 C CNN
F 3 "" H 3350 4050 50  0001 C CNN
	1    3350 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E6F68F4
P 3350 3800
F 0 "C2" H 3465 3846 50  0000 L CNN
F 1 "100n" H 3465 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3388 3650 50  0001 C CNN
F 3 "~" H 3350 3800 50  0001 C CNN
	1    3350 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3550 3350 3650
Wire Wire Line
	3350 3950 3350 4050
NoConn ~ 2400 6300
NoConn ~ 2400 6200
NoConn ~ 2400 6100
NoConn ~ 2400 6000
NoConn ~ 2400 5700
NoConn ~ 2400 5100
NoConn ~ 2400 5000
NoConn ~ 2400 4900
NoConn ~ 2400 4800
NoConn ~ 2400 4600
NoConn ~ 2400 4500
NoConn ~ 2400 4100
NoConn ~ 2400 4000
NoConn ~ 2400 3900
NoConn ~ 6350 4550
NoConn ~ 7350 4450
NoConn ~ 7350 4150
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 5E658CA1
P 4050 6500
F 0 "J2" H 4158 6881 50  0000 C CNN
F 1 "AVR ISP connector" H 4158 6790 50  0000 C CNN
F 2 "pcb:CONN_AVR_ISP_SMD" H 4050 6500 50  0001 C CNN
F 3 "~" H 4050 6500 50  0001 C CNN
	1    4050 6500
	1    0    0    -1  
$EndComp
Text GLabel 4550 6500 2    50   Input ~ 0
RESET
Text GLabel 4550 6600 2    50   Input ~ 0
MOSI
Text GLabel 4550 6700 2    50   Input ~ 0
MISO
Text GLabel 4550 6800 2    50   Input ~ 0
SCK
Wire Wire Line
	4550 6500 4250 6500
Wire Wire Line
	4250 6600 4550 6600
Wire Wire Line
	4550 6700 4250 6700
Wire Wire Line
	4250 6800 4550 6800
Text GLabel 6300 5850 2    50   Input ~ 0
SCL
Text GLabel 6300 5750 2    50   Input ~ 0
SDA
Wire Wire Line
	6050 5850 6300 5850
Wire Wire Line
	6050 5750 6300 5750
Text Notes 6000 1550 2    50   ~ 0
AP9101CK6-AYTRG1
$Comp
L components:AP9101CK6 U3
U 1 1 5E6BF612
P 5600 2350
F 0 "U3" H 5600 1635 50  0000 C CNN
F 1 "AP9101CK6" H 5600 1726 50  0000 C CNN
F 2 "pcb:AP9101C_SOT-25" H 5600 2350 50  0001 C CNN
F 3 "" H 5600 2350 50  0001 C CNN
	1    5600 2350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 5E6D3C42
P 4500 2050
F 0 "R5" V 4707 2050 50  0000 C CNN
F 1 "330" V 4616 2050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4430 2050 50  0001 C CNN
F 3 "~" H 4500 2050 50  0001 C CNN
	1    4500 2050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 5E6D9E03
P 4850 2200
F 0 "C4" H 4965 2246 50  0000 L CNN
F 1 "100n" H 4965 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4888 2050 50  0001 C CNN
F 3 "~" H 4850 2200 50  0001 C CNN
	1    4850 2200
	1    0    0    -1  
$EndComp
Text Notes 7100 1550 2    50   ~ 0
DMN2053UVT-7
$Comp
L components:DMN2053UVT U4
U 1 1 5E6E74E6
P 6800 1750
F 0 "U4" H 6750 1850 50  0000 L CNN
F 1 "DMN2053UVT" H 6550 1750 50  0000 L CNN
F 2 "pcb:DMN2053UVT_TSOT-26" H 6800 1750 50  0001 C CNN
F 3 "" H 6800 1750 50  0001 C CNN
	1    6800 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5E6F669D
P 7300 2300
F 0 "#PWR0113" H 7300 2050 50  0001 C CNN
F 1 "GND" H 7305 2127 50  0000 C CNN
F 2 "" H 7300 2300 50  0001 C CNN
F 3 "" H 7300 2300 50  0001 C CNN
	1    7300 2300
	1    0    0    -1  
$EndComp
NoConn ~ 1500 2450
NoConn ~ 1500 2350
NoConn ~ 1500 2250
Wire Wire Line
	7100 2050 7300 2050
Wire Wire Line
	7300 2050 7300 2300
Wire Wire Line
	7100 2200 7200 2200
Wire Wire Line
	7200 2200 7200 1900
Wire Wire Line
	7200 1900 7100 1900
Wire Wire Line
	5250 2200 5250 2450
Wire Wire Line
	5950 2200 6500 2200
Wire Wire Line
	5950 1900 6500 1900
Wire Wire Line
	5250 2450 6400 2450
Wire Wire Line
	6400 2450 6400 2050
Wire Wire Line
	6400 2050 6500 2050
Connection ~ 5250 2450
Wire Wire Line
	5950 2050 6100 2050
Wire Wire Line
	6100 2050 6100 2600
$Comp
L power:GND #PWR0114
U 1 1 5E741174
P 6100 3050
F 0 "#PWR0114" H 6100 2800 50  0001 C CNN
F 1 "GND" H 6105 2877 50  0000 C CNN
F 2 "" H 6100 3050 50  0001 C CNN
F 3 "" H 6100 3050 50  0001 C CNN
	1    6100 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2900 6100 3050
Connection ~ 4850 2050
Wire Wire Line
	4850 2050 5250 2050
Wire Wire Line
	4850 2350 4850 2450
Wire Wire Line
	4850 2450 5250 2450
Wire Wire Line
	5250 2450 5250 2600
Wire Wire Line
	4650 2050 4850 2050
Connection ~ 4000 2050
Text GLabel 2600 5600 2    50   Input ~ 0
DISP_RST
Wire Wire Line
	2400 5600 2600 5600
$Comp
L Connector:Conn_01x08_Male J3
U 1 1 5E7C51B2
P 5850 6050
F 0 "J3" H 5900 6550 50  0000 R CNN
F 1 "Display connector" H 6200 6450 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 5850 6050 50  0001 C CNN
F 3 "~" H 5850 6050 50  0001 C CNN
	1    5850 6050
	1    0    0    -1  
$EndComp
Text GLabel 6300 6050 2    50   Input ~ 0
DISP_RST
Wire Wire Line
	6050 6050 6300 6050
NoConn ~ 6050 5950
NoConn ~ 6050 6150
NoConn ~ 6050 6250
$Comp
L power:GND #PWR0115
U 1 1 5E7E1451
P 6150 6550
F 0 "#PWR0115" H 6150 6300 50  0001 C CNN
F 1 "GND" H 6155 6377 50  0000 C CNN
F 2 "" H 6150 6550 50  0001 C CNN
F 3 "" H 6150 6550 50  0001 C CNN
	1    6150 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 6450 6150 6450
Wire Wire Line
	6150 6450 6150 6550
$Comp
L power:VCC #PWR0116
U 1 1 5E7E39D9
P 6350 6350
F 0 "#PWR0116" H 6350 6200 50  0001 C CNN
F 1 "VCC" V 6367 6478 50  0000 L CNN
F 2 "" H 6350 6350 50  0001 C CNN
F 3 "" H 6350 6350 50  0001 C CNN
	1    6350 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 6350 6350 6350
Wire Wire Line
	1500 2050 1800 2050
$Comp
L Device:C C1
U 1 1 5E7055BB
P 1800 2200
F 0 "C1" H 1915 2246 50  0000 L CNN
F 1 "4.7u" H 1915 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1838 2050 50  0001 C CNN
F 3 "~" H 1800 2200 50  0001 C CNN
	1    1800 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2350 1800 2500
Connection ~ 1800 2050
Wire Wire Line
	1800 2050 2200 2050
Connection ~ 2200 2050
Wire Wire Line
	3500 2800 3500 2650
Connection ~ 3500 2650
Wire Wire Line
	4000 2350 4000 2500
$Comp
L power:VCC #PWR0117
U 1 1 5E75D835
P 3450 1100
F 0 "#PWR0117" H 3450 950 50  0001 C CNN
F 1 "VCC" H 3467 1273 50  0000 C CNN
F 2 "" H 3450 1100 50  0001 C CNN
F 3 "" H 3450 1100 50  0001 C CNN
	1    3450 1100
	1    0    0    -1  
$EndComp
Text GLabel 3450 1650 0    50   Input ~ 0
VBACKUP
Wire Wire Line
	3450 1650 3550 1650
Wire Wire Line
	3550 1650 3550 2050
Connection ~ 3550 2050
Wire Wire Line
	3550 2050 4000 2050
$Comp
L Switch:SW_DPDT_x2 SW1
U 1 1 5E7961BF
P 3550 1450
F 0 "SW1" V 3596 1262 50  0000 R CNN
F 1 "SSSS811101" V 3505 1262 50  0000 R CNN
F 2 "pcb:SSSS811101" H 3550 1450 50  0001 C CNN
F 3 "~" H 3550 1450 50  0001 C CNN
	1    3550 1450
	0    -1   -1   0   
$EndComp
Connection ~ 3550 1650
Wire Wire Line
	3450 1250 3450 1100
Wire Wire Line
	4000 1900 4000 2050
$Comp
L power:GND #PWR0118
U 1 1 5E7A9965
P 6500 3750
F 0 "#PWR0118" H 6500 3500 50  0001 C CNN
F 1 "GND" H 6505 3577 50  0000 C CNN
F 2 "" H 6500 3750 50  0001 C CNN
F 3 "" H 6500 3750 50  0001 C CNN
	1    6500 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3750 6500 3700
Wire Wire Line
	6500 3700 6750 3700
Wire Wire Line
	6750 3700 6750 3950
Text GLabel 6950 3700 2    50   Input ~ 0
VBACKUP
Wire Wire Line
	6850 3700 6850 3850
Wire Wire Line
	6850 3700 6950 3700
$Comp
L Device:R R1
U 1 1 5E7B982E
P 2200 2600
F 0 "R1" H 2270 2646 50  0000 L CNN
F 1 "2.7K" H 2270 2555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2130 2600 50  0001 C CNN
F 3 "~" H 2200 2600 50  0001 C CNN
	1    2200 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5E7BA513
P 6100 2750
F 0 "R7" H 6170 2796 50  0000 L CNN
F 1 "2.7K" H 6170 2705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6030 2750 50  0001 C CNN
F 3 "~" H 6100 2750 50  0001 C CNN
	1    6100 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2850 2500 2850
Wire Wire Line
	3350 2350 3500 2350
Wire Wire Line
	2200 2050 2550 2050
Wire Wire Line
	3350 2050 3550 2050
Wire Wire Line
	3350 2650 3500 2650
$Comp
L components:MCP73831-2-OT U2
U 1 1 5E726016
P 2950 1900
F 0 "U2" H 2950 2015 50  0000 C CNN
F 1 "MCP73831-2-OT" H 2950 1924 50  0000 C CNN
F 2 "pcb:MCP73831_SOT-23" H 2950 1900 50  0001 C CNN
F 3 "" H 2950 1900 50  0001 C CNN
	1    2950 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2850 2500 2650
Wire Wire Line
	2500 2650 2550 2650
Wire Wire Line
	4350 2050 4000 2050
Wire Wire Line
	1900 3600 1900 3500
Wire Wire Line
	1900 3500 1800 3500
Connection ~ 1800 3500
Wire Wire Line
	1800 3500 1800 3600
Text GLabel 4000 1900 1    50   Input ~ 0
BAT+
Text GLabel 5250 2600 3    50   Input ~ 0
BAT-
$Comp
L Switch:SW_DIP_x01 SW2
U 1 1 5E72AEEF
P 4700 4750
F 0 "SW2" V 4654 4880 50  0000 L CNN
F 1 "SW_DIP_x01" V 4745 4880 50  0000 L CNN
F 2 "pcb:TL3340_SMT" H 4700 4750 50  0001 C CNN
F 3 "~" H 4700 4750 50  0001 C CNN
	1    4700 4750
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_DIP_x01 SW3
U 1 1 5E7385FA
P 5450 4750
F 0 "SW3" V 5404 4880 50  0000 L CNN
F 1 "SW_DIP_x01" V 5495 4880 50  0000 L CNN
F 2 "pcb:TL3340_SMT" H 5450 4750 50  0001 C CNN
F 3 "~" H 5450 4750 50  0001 C CNN
	1    5450 4750
	0    1    1    0   
$EndComp
Connection ~ 5450 5050
$Comp
L Device:C C5
U 1 1 5E7351D4
P 3950 3750
F 0 "C5" H 4065 3796 50  0000 L CNN
F 1 "100n" H 4065 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3988 3600 50  0001 C CNN
F 3 "~" H 3950 3750 50  0001 C CNN
	1    3950 3750
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0108
U 1 1 5E73E851
P 3950 3500
F 0 "#PWR0108" H 3950 3350 50  0001 C CNN
F 1 "VCC" H 3967 3673 50  0000 C CNN
F 2 "" H 3950 3500 50  0001 C CNN
F 3 "" H 3950 3500 50  0001 C CNN
	1    3950 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5E73EC60
P 3950 4000
F 0 "#PWR0119" H 3950 3750 50  0001 C CNN
F 1 "GND" H 3955 3827 50  0000 C CNN
F 2 "" H 3950 4000 50  0001 C CNN
F 3 "" H 3950 4000 50  0001 C CNN
	1    3950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4000 3950 3900
Wire Wire Line
	3950 3600 3950 3500
Wire Wire Line
	1800 3500 1150 3500
Wire Wire Line
	1150 3500 1150 3900
Wire Wire Line
	1150 3900 1200 3900
$Comp
L Device:C C6
U 1 1 5E760DB3
P 7850 4150
F 0 "C6" H 7965 4196 50  0000 L CNN
F 1 "100n" H 7965 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7888 4000 50  0001 C CNN
F 3 "~" H 7850 4150 50  0001 C CNN
	1    7850 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5E7615E0
P 7850 4450
F 0 "#PWR0121" H 7850 4200 50  0001 C CNN
F 1 "GND" H 7855 4277 50  0000 C CNN
F 2 "" H 7850 4450 50  0001 C CNN
F 3 "" H 7850 4450 50  0001 C CNN
	1    7850 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4300 7850 4450
Wire Wire Line
	7850 4000 7850 3850
Wire Wire Line
	1100 2650 1100 2750
Wire Wire Line
	1100 2750 1200 2750
Connection ~ 1200 2750
Wire Wire Line
	1200 2750 1200 2800
$Comp
L power:VCC #PWR0122
U 1 1 5E77F285
P 4650 6150
F 0 "#PWR0122" H 4650 6000 50  0001 C CNN
F 1 "VCC" H 4667 6323 50  0000 C CNN
F 2 "" H 4650 6150 50  0001 C CNN
F 3 "" H 4650 6150 50  0001 C CNN
	1    4650 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 6300 4650 6150
Wire Wire Line
	4250 6300 4650 6300
$Comp
L power:GND #PWR0123
U 1 1 5E782845
P 4950 6400
F 0 "#PWR0123" H 4950 6150 50  0001 C CNN
F 1 "GND" H 4955 6227 50  0000 C CNN
F 2 "" H 4950 6400 50  0001 C CNN
F 3 "" H 4950 6400 50  0001 C CNN
	1    4950 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 6400 4950 6400
NoConn ~ 3650 1250
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5E792C70
P 1800 1350
F 0 "J4" H 1908 1531 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1908 1440 50  0000 C CNN
F 2 "Connector_JST:JST_PH_B2B-PH-K_1x02_P2.00mm_Vertical" H 1800 1350 50  0001 C CNN
F 3 "~" H 1800 1350 50  0001 C CNN
	1    1800 1350
	1    0    0    -1  
$EndComp
Text GLabel 2150 1450 2    50   Input ~ 0
BAT+
Text GLabel 2150 1350 2    50   Input ~ 0
BAT-
Wire Wire Line
	2150 1350 2000 1350
Wire Wire Line
	2000 1450 2150 1450
Wire Wire Line
	6850 3850 7850 3850
Connection ~ 6850 3850
Wire Wire Line
	6850 3850 6850 3950
Text Notes 850  1600 0    50   ~ 0
https://www.conrad.de/de/p/b2b-ph-k-s-lf-sn-connector-header-male-pitch2mm-top-entry-2p-th-inhalt-20-stueck-800113239.html
$EndSCHEMATC

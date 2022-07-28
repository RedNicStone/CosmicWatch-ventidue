EESchema Schematic File Version 4
EELAYER 30 0
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
L CosmicWatchPro:Teensy4.1 U2
U 1 1 61C30E65
P 7700 3150
F 0 "U2" H 7700 5317 50  0000 C CNN
F 1 "Teensy4.1" H 7700 5226 50  0000 C CNN
F 2 "CosmicWatchPro:Teensy4.1" H 7700 3150 50  0001 L BNN
F 3 "" H 7700 3150 50  0001 L BNN
F 4 "4.1" H 7700 3150 50  0001 L BNN "PARTREV"
F 5 "Manufacturer recommendations" H 7700 3150 50  0001 L BNN "STANDARD"
F 6 "SparkFun Electronics" H 7700 3150 50  0001 L BNN "MANUFACTURER"
F 7 "4.07mm" H 7700 3150 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
	1    7700 3150
	1    0    0    -1  
$EndComp
$Comp
L CosmicWatchPro:Digital_Rotary_Encoder_Switch SW1
U 1 1 61C3D0D6
P 4950 1900
F 0 "SW1" H 5180 1946 50  0000 L CNN
F 1 "Digital_Rotary_Encoder_Switch" H 5180 1855 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Horizontal" H 4800 2060 50  0001 C CNN
F 3 "~" H 4950 2160 50  0001 C CNN
	1    4950 1900
	1    0    0    -1  
$EndComp
$Comp
L CosmicWatchPro:SiPM_MICRORB−10035−MLP D1
U 1 1 61C43E42
P 4950 2950
F 0 "D1" H 4962 3365 50  0000 C CNN
F 1 "SiPM_MICRORB−10035−MLP" H 4962 3274 50  0000 C CNN
F 2 "" H 4995 3120 50  0001 C CNN
F 3 "~" V 4895 2865 50  0001 C CNN
	1    4950 2950
	1    0    0    -1  
$EndComp
$Comp
L CosmicWatchPro:TCR2EF U1
U 1 1 61C4AEDA
P 5000 3750
F 0 "U1" H 5000 4117 50  0000 C CNN
F 1 "TCR2EF" H 5000 4026 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 5000 3750 50  0001 C CNN
F 3 "https://www.torexsemi.com/file/xc6220/XC6220.pdf" H 5750 2750 50  0001 C CNN
	1    5000 3750
	1    0    0    -1  
$EndComp
$Comp
L CosmicWatchPro:Conn_SMA J1
U 1 1 61C5BE8D
P 5000 4400
F 0 "J1" H 5100 4375 50  0000 L CNN
F 1 "Conn_SMA" H 5100 4284 50  0000 L CNN
F 2 "Connector_Coaxial:BNC_Amphenol_B6252HB-NPP3G-50_Horizontal" H 5000 4400 50  0001 C CNN
F 3 " ~" H 5000 4400 50  0001 C CNN
	1    5000 4400
	1    0    0    -1  
$EndComp
$EndSCHEMATC

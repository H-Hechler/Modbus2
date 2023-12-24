#include "array.h"

// Definition des globalen Arrays in der Quelldatei
KostalStruct globalArray[107] =
{
{30,"Number of bidirectional converter ","- ",16,1,0},
{32,"Number of AC phases ","- ",16,1,0},
{34,"Number of PV strings ","- ",16,1,0},
{36,"Hardware-Version ","- ",16,2,0},
{54,"Power-ID ","- ",16,2,0},
{56,"Inverter state ","- ",16,2,1},
{98,"Temperature of controller PCB ","Grad C ",64,2,1},
{100,"Total DC power ","W ",64,2,1},
{104,"State of energy manager ","- ",16,2,1},
{106,"Home own consumption from battery ","W ",64,2,1},
{108,"Home own consumption from grid ","W ",64,2,1},
{110,"Total home consumption Battery ","Wh ",64,2,1},
{112,"Total home consumption Grid ","Wh ",64,2,1},
{114,"Total home consumption PV ","Wh ",64,2,1},
{116,"Home own consumption from PV ","W ",64,2,1},
{118,"Total home consumption ","Wh ",64,2,1},
{120,"Isolation resistance ","Ohm ",64,2,1},
{122,"Power limit from EVU ","% ",64,2,1},
{124,"Total home consumption rate ","% ",64,2,1},
{144,"Worktime ","s ",64,2,1},
{150,"Actual cos phi ","- ",64,2,1},
{152,"Grid frequency ","Hz ",64,2,1},
{154,"Current Phase 1 ","A ",64,2,1},
{156,"Active power Phase 1 ","W ",64,2,1},
{158,"Voltage Phase 1 ","V ",64,2,1},
{160,"Current Phase 2 ","A ",64,2,1},
{162,"Active power Phase 2 ","W ",64,2,1},
{164,"Voltage Phase 2 ","V ",64,2,1},
{166,"Current Phase 3 ","A ",64,2,1},
{168,"Active power Phase 3 ","W ",64,2,1},
{170,"Voltage Phase 3 ","V ",64,2,1},
{172,"Total AC active power ","W ",64,2,1},
{174,"Total AC reactive power ","Var ",64,2,1},
{178,"Total AC apparent power ","VA ",64,2,1},
{190,"Battery charge current ","A ",64,2,0},
{194,"Number of battery cycles ","- ",64,2,0},
{200,"Actual battery charge (-) / discharge (+) current ","A ",64,2,0},
{202,"PSSB fuse state ","- ",64,2,1},
{208,"Battery ready flag ","- ",64,2,0},
{210,"Act. state of charge ","% ",64,2,0},
{214,"Battery temperature ","°C ",64,2,0},
{216,"Battery voltage ","V ",64,2,0},
{218,"Cos phi (powermeter) ","- ",64,2,1},
{220,"Frequency (powermeter) ","Hz ",64,2,1},
{222,"Current phase 1 (powermeter) ","A ",64,2,1},
{224,"Active power phase 1 (powermeter) ","W ",64,2,1},
{226,"Reactive power phase 1 (powermeter) ","Var ",64,2,1},
{228,"Apparent power phase 1 (powermeter) ","VA ",64,2,1},
{230,"Voltage phase 1 (powermeter) ","V ",64,2,1},
{232,"Current phase 2 (powermeter) ","A ",64,2,1},
{234,"Active power phase 2 (powermeter) ","W ",64,2,1},
{236,"Reactive power phase 2 (powermeter) ","Var ",64,2,1},
{238,"Apparent power phase 2 (powermeter) ","VA ",64,2,1},
{240,"Voltage phase 2 (powermeter) ","V ",64,2,1},
{242,"Current phase 3 powermeter","A ",64,2,1},
{244,"Active power phase 3 powermeter","W ",64,2,1},
{246,"Reactive power phase 3 powermeter","Var ",64,2,1},
{248,"Apparent power phase 3 powermeter","VA ",64,2,1},
{250,"Voltage phase 3 (powermeter) ","V ",64,2,1},
{252,"Total active power","W ",64,2,1},
{254,"Total reactive power","Var ",64,2,1},
{256,"Total apparent power","VA ",64,2,1},
{258,"Current DC1 ","A ",64,2,1},
{260,"Power DC1 ","W ",64,2,1},
{266,"Voltage DC1 ","V ",64,2,1},
{268,"Current DC2 ","A ",64,2,1},
{270,"Power DC2 ","W ",64,2,1},
{276,"Voltage DC2 ","V ",64,2,1},
{278,"Current DC3 ","A ",64,2,1},
{280,"Power DC3 ","W ",64,2,1},
{286,"Voltage DC3 ","V ",64,2,1},
{320,"Total yield ","Wh ",64,2,1},
{322,"Daily yield ","Wh ",64,2,1},
{324,"Yearly yield ","Wh ",64,2,1},
{326,"Monthly yield ","Wh ",64,2,1},
{416,"IP enable ","- ",16,1,0},
{418,"Manual IP / Auto-IP ","- ",16,1,0},
{444,"IP-auto-DNS ","- ",16,1,0},
{512,"Battery gross capacity ","Ah ",16,2,0},
{514,"Battery actual SOC ","% ",16,1,0},
{515,"Firmware Maincontroller (MC) ","- ",16,2,0},
{525,"Battery Model ID ","- ",16,2,0},
{527,"Battery Serial Number ","- ",16,2,0},
{529,"Work Capacity ","Wh ",16,2,0},
{531,"Inverter Max Power ","W ",16,1,0},
{532,"Inverter Max Power Scale Factor4 ","- ",16,1,0},
{533,"Active Power Setpoint ","% ",16,1,0},
{575,"Inverter Generation Power (actual) ","W ",16 ,1,0},
{576,"Power Scale Factor ","- ",16 ,1,0},
{577,"Generation Energy ","Wh ",16,2,1},
{579,"Energy Scale Factor ","- ",16 ,1,1},
{582,"Actual battery charge/discharge power ","W ",16 ,1,0},
{583,"Reactive Power Setpoint ","% ",16 ,1,1},
{585,"Delta-cos phi Setpoint ","- ",16 ,1,1},
{586,"Battery Firmware ","- ",16,2,0},
{588,"Battery Type6 ","- ",16,1,0},
{1046,"Total DC charge energy (DC-side to battery) ","Wh ",64,2,1},
{1048,"Total DC discharge energy (DC-side from battery) ","Wh ",64,2,1},
{1050,"Total AC charge energy (AC-side to battery) ","Wh ",64,2,1},
{1052,"Total AC discharge energy (battery to grid) ","Wh ",64,2,1},
{1054,"Total AC charge energy (grid to battery) ","Wh ",64,2,1},
{1056,"Total DC PV energy (sum of all PV inputs) ","Wh ",64,2,1},
{1058,"Total DC energy from PV1 ","Wh ",64,2,1},
{1060,"Total DC energy from PV2 ","Wh ",64,2,1},
{1062,"Total DC energy from PV3 ","Wh ",64,2,1},
{1064,"Total energy AC-side to grid ","Wh ",64,2,1},
{1066,"Total DC power (sum of all PV inputs)","Wh ",64,2,1}


};
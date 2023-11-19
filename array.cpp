#include "array.h"

// Definition des globalen Arrays in der Quelldatei
KostalStruct globalArray[107] =
{
{30,"Number of bidirectional converter ","- ",16,1},
{32,"Number of AC phases ","- ",16,1},
{34,"Number of PV strings ","- ",16,1},
{36,"Hardware-Version ","- ",16,2},
{54,"Power-ID ","- ",16,2},
{56,"Inverter state2 ","- ",16,2},
{98,"Temperature of controller PCB ","°C ",64,2},
{100,"Total DC power ","W ",64,2},
{104,"State of energy manager3 ","- ",16,2},
{106,"Home own consumption from battery8 ","W ",64,2},
{108,"Home own consumption from grid8 ","W ",64,2},
{110,"Total home consumption Battery8 ","Wh ",64,2},
{112,"Total home consumption Grid8 ","Wh ",64,2},
{114,"Total home consumption PV8 ","Wh ",64,2},
{116,"Home own consumption from PV8 ","W ",64,2},
{118,"Total home consumption8 ","Wh ",64,2},
{120,"Isolation resistance ","Ohm ",64,2},
{122,"Power limit from EVU ","% ",64,2},
{124,"Total home consumption rate ","% ",64,2},
{144,"Worktime ","s ",64,2},
{150,"Actual cos φ ","- ",64,2},
{152,"Grid frequency ","Hz ",64,2},
{154,"Current Phase 1 ","A ",64,2},
{156,"Active power Phase 1 ","W ",64,2},
{158,"Voltage Phase 1 ","V ",64,2},
{160,"Current Phase 2 ","A ",64,2},
{162,"Active power Phase 2 ","W ",64,2},
{164,"Voltage Phase 2 ","V ",64,2},
{166,"Current Phase 3 ","A ",64,2},
{168,"Active power Phase 3 ","W ",64,2},
{170,"Voltage Phase 3 ","V ",64,2},
{172,"Total AC active power ","W ",64,2},
{174,"Total AC reactive power ","Var ",64,2},
{178,"Total AC apparent power ","VA ",64,2},
{190,"Battery charge current ","A ",64,2},
{194,"Number of battery cycles ","- ",64,2},
{200,"Actual battery charge (-) / discharge (+) current ","A ",64,2},
{202,"PSSB fuse state5 ","- ",64,2},
{208,"Battery ready flag ","- ",64,2},
{210,"Act. state of charge ","% ",64,2},
{214,"Battery temperature ","°C ",64,2},
{216,"Battery voltage ","V ",64,2},
{218,"Cos φ (powermeter) ","- ",64,2},
{220,"Frequency (powermeter) ","Hz ",64,2},
{222,"Current phase 1 (powermeter) ","A ",64,2},
{224,"Active power phase 1 (powermeter) ","W ",64,2},
{226,"Reactive power phase 1 (powermeter) ","Var ",64,2},
{228,"Apparent power phase 1 (powermeter) ","VA ",64,2},
{230,"Voltage phase 1 (powermeter) ","V ",64,2},
{232,"Current phase 2 (powermeter) ","A ",64,2},
{234,"Active power phase 2 (powermeter) ","W ",64,2},
{236,"Reactive power phase 2 (powermeter) ","Var ",64,2},
{238,"Apparent power phase 2 (powermeter) ","VA ",64,2},
{240,"Voltage phase 2 (powermeter) ","V ",64,2},
{242,"Current phase 3 powermeter","A ",64,2},
{244,"Active power phase 3 powermeter","W ",64,2},
{246,"Reactive power phase 3 powermeter","Var ",64,2},
{248,"Apparent power phase 3 powermeter","VA ",64,2},
{250,"Voltage phase 3 (powermeter) ","V ",64,2},
{252,"Total active power","W ",64,2},
{254,"Total reactive power","Var ",64,2},
{256,"Total apparent power","VA ",64,2},
{258,"Current DC1 ","A ",64,2},
{260,"Power DC1 ","W ",64,2},
{266,"Voltage DC1 ","V ",64,2},
{268,"Current DC2 ","A ",64,2},
{270,"Power DC2 ","W ",64,2},
{276,"Voltage DC2 ","V ",64,2},
{278,"Current DC3 ","A ",64,2},
{280,"Power DC3 ","W ",64,2},
{286,"Voltage DC3 ","V ",64,2},
{320,"Total yield ","Wh ",64,2},
{322,"Daily yield ","Wh ",64,2},
{324,"Yearly yield ","Wh ",64,2},
{326,"Monthly yield ","Wh ",64,2},
{416,"IP enable ","- ",16,1},
{418,"Manual IP / Auto-IP ","- ",16,1},
{444,"IP-auto-DNS ","- ",16,1},
{512,"Battery gross capacity ","Ah ",16,2},
{514,"Battery actual SOC ","% ",16,1},
{515,"Firmware Maincontroller (MC) ","- ",16,2},
{525,"Battery Model ID ","- ",16,2},
{527,"Battery Serial Number ","- ",16,2},
{529,"Work Capacity ","Wh ",16,2},
{531,"Inverter Max Power ","W ",16,1},
{532,"Inverter Max Power Scale Factor4 ","- ",16,1},
{533,"Active Power Setpoint ","% ",16,1},
{575,"Inverter Generation Power (actual) ","W ",16 ,1},
{576,"Power Scale Factor4 ","- ",16 ,1},
{577,"Generation Energy ","Wh ",16,2},
{579,"Energy Scale Factor4 ","- ",16 ,1},
{582,"Actual battery charge/discharge power ","W ",16 ,1},
{583,"Reactive Power Setpoint ","% ",16 ,1},
{585,"Delta-cos φ Setpoint ","- ",16 ,1},
{586,"Battery Firmware ","- ",16,2},
{588,"Battery Type6 ","- ",16,1},
{1046,"Total DC charge energy (DC-side to battery) ","Wh ",64,2},
{1048,"Total DC discharge energy (DC-side from battery) ","Wh ",64,2},
{1050,"Total AC charge energy (AC-side to battery) ","Wh ",64,2},
{1052,"Total AC discharge energy (battery to grid) ","Wh ",64,2},
{1054,"Total AC charge energy (grid to battery) ","Wh ",64,2},
{1056,"Total DC PV energy (sum of all PV inputs) ","Wh ",64,2},
{1058,"Total DC energy from PV1 ","Wh ",64,2},
{1060,"Total DC energy from PV2 ","Wh ",64,2},
{1062,"Total DC energy from PV3 ","Wh ",64,2},
{1064,"Total energy AC-side to grid ","Wh ",64,2},
{1066,"Total DC power (sum of all PV inputs)","Wh ",64,2}


};
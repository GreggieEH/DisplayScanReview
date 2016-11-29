// dispids.h
// dispatch ids

#pragma once

// properties
#define				DISPID_FileComment				0x0100
#define				DISPID_WorkingDirectory			0x0101
#define				DISPID_LockinState				0x0102
#define				DISPID_LockinGain				0x0103
#define				DISPID_LockinTimeConstant		0x0104
#define				DISPID_DetectorName				0x0105
#define				DISPID_DetectorGain				0x0106
#define				DISPID_DetectorTemperature		0x0107
#define				DISPID_InputOptic				0x0108
#define				DISPID_StartWave				0x0109
#define				DISPID_StopWave					0x010a
#define				DISPID_StepSize					0x010b
#define				DISPID_DwellTime				0x010c
#define				DISPID_ScanType					0x010d
#define				DISPID_AutoGain					0x010e
#define				DISPID_AutoTimeConstant			0x010f
#define				DISPID_GratingAutoSelect		0x0110
#define				DISPID_FilterAutoSelect			0x0111
#define				DISPID_InitializeBeforeMeasurement	0x0112

// methods
#define				DISPID_DisplayWindow			0x0130
#define				DISPID_SetOptFile				0x0131

// events
#define				DISPID_requestDispersion		0x0150
#define				DISPID_requestCurrentGrating	0x0151
#define				DISPID_requestGratingInfo		0x0152
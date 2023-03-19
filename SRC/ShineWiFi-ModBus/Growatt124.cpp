#include "Arduino.h"

#include "Growatt124.h"

// NOTE: my inverter (SPH4-10KTL3 BH-UP) only manages to read 64 registers in
// one read!
void init_growatt124(sProtocolDefinition_t &Protocol) {
  // definition of input registers
  Protocol.InputRegisterCount = 20;
  // address, value, size, name, multiplier, unit, frontend, plot
  // FEAGMENT 1: BEGIN
  Protocol.InputRegisters[P124_I_STATUS]            = sGrowattModbusReg_t{   0, 0, SIZE_16BIT, "InverterStatus", 1, NONE, true, false};  // #8
  Protocol.InputRegisters[P124_PV1_POWER]           = sGrowattModbusReg_t{   5, 0, SIZE_32BIT, "PowerPV1", 0.1, POWER_W, true, true};  // #5
  Protocol.InputRegisters[P124_PV2_POWER]           = sGrowattModbusReg_t{   9, 0, SIZE_32BIT, "PowerPV2", 0.1, POWER_W, true, true};  // #8
  Protocol.InputRegisters[P124_EPV1_TODAY]          = sGrowattModbusReg_t{  59, 0, SIZE_32BIT, "EnergyPV1Today", 0.1, POWER_KWH, true, false};  // #23
  Protocol.InputRegisters[P124_EPV1_TOTAL]          = sGrowattModbusReg_t{  61, 0, SIZE_32BIT, "EnergyPV1Total", 0.1, POWER_KWH, true, false};  // #24
  Protocol.InputRegisters[P124_EPV2_TODAY]          = sGrowattModbusReg_t{  63, 0, SIZE_32BIT, "EnergyPV2Today", 0.1, POWER_KWH, true, false};  // #26
  Protocol.InputRegisters[P124_EPV2_TOTAL]          = sGrowattModbusReg_t{  65, 0, SIZE_32BIT, "EnergyPV2Total", 0.1, POWER_KWH, true, false};  // #26
  Protocol.InputRegisters[P124_EPV_TOTAL]           = sGrowattModbusReg_t{  91, 0, SIZE_32BIT, "EnergyPVTotal", 0.1, POWER_KWH, true, false};  // #26
  Protocol.InputRegisters[P124_TEMP1]               = sGrowattModbusReg_t{  93, 0, SIZE_16BIT, "InverterTemperature",0.1, TEMPERATURE, true, false};  // #28
  Protocol.InputRegisters[P124_PDISCHARGE]          = sGrowattModbusReg_t{1009, 0, SIZE_32BIT, "PowerBatteryDischarge", 0.1, POWER_W, true, true};  // #31
  Protocol.InputRegisters[P124_PCHARGE]             = sGrowattModbusReg_t{1011, 0, SIZE_32BIT, "PowerBatteryCharge", 0.1, POWER_W, true, true};  // #32  
  Protocol.InputRegisters[P124_SOC]                 = sGrowattModbusReg_t{1014, 0, SIZE_16BIT, "BatteryPercent", 1, PRECENTAGE, true, false};  // #34
  Protocol.InputRegisters[P124_PAC_TO_USER_TOTAL]   = sGrowattModbusReg_t{1021, 0, SIZE_32BIT, "PowerGridImport", 0.1,  POWER_W, true, true};  // #36
  Protocol.InputRegisters[P124_PAC_TO_GRID_TOTAL]   = sGrowattModbusReg_t{1029, 0, SIZE_32BIT, "PowerGridExport",0.1,  POWER_W, true, true};  // #38
  Protocol.InputRegisters[P124_PLOCAL_LOAD_TOTAL]   = sGrowattModbusReg_t{1037, 0, SIZE_32BIT, "PowerHouseCurrent", 0.1,  POWER_W, true, true};  // #40 
  Protocol.InputRegisters[P124_BATTERY_TEMPERATURE] = sGrowattModbusReg_t{1040, 0, SIZE_16BIT, "BatteryTemperature", 0.1,  TEMPERATURE, true, false};  // #41
  Protocol.InputRegisters[P124_ETOGRID_TOTAL]       = sGrowattModbusReg_t{1050, 0, SIZE_32BIT, "EnergyGridExportTotal", 0.1,  POWER_KWH, true, false};  // #46
  Protocol.InputRegisters[P124_ETOUSER_TOTAL]       = sGrowattModbusReg_t{1046, 0, SIZE_32BIT, "EnergyGridImportTotal",0.1,  POWER_KWH, true, false};  // #44
  Protocol.InputRegisters[P124_EDISCHARGE_TOTAL]    = sGrowattModbusReg_t{1054, 0, SIZE_32BIT, "EnergyBatteryDischargeTotal", 0.1,  POWER_KWH, true, false};  // #48
  Protocol.InputRegisters[P124_ECHARGE_TOTAL]       = sGrowattModbusReg_t{1058, 0, SIZE_32BIT, "EnergyBatteryChargeTotal", 0.1,  POWER_KWH, true, false};  // #50
  Protocol.InputRegisters[P124_ETOLOCALLOAD_TOTAL]  = sGrowattModbusReg_t{1062, 0, SIZE_32BIT, "EnergyHouseTotal", 0.1,  POWER_KWH, true, false};  // #52

  Protocol.InputFragmentCount = 3;
  Protocol.InputReadFragments[0] = sGrowattReadFragment_t{0, 50};
  Protocol.InputReadFragments[1] = sGrowattReadFragment_t{53, 43};
  Protocol.InputReadFragments[2] = sGrowattReadFragment_t{1009, 55};

  Protocol.HoldingRegisterCount = 0;
  Protocol.HoldingFragmentCount = 0;
}
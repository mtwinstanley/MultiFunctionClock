set_false_path -to [get_pins INTC_CORE_I/*intr_sync*/C]
set_false_path -from [get_pins INTC_CORE_I/*intr_sync*/C] -to [get_pins INTC_CORE_I/*intr_p1*/C]
create_clock -name S_AXI_ACLK -period 10.0 [get_ports S_AXI_ACLK]
create_clock -name PROCESSOR_CLK -period 10.0 [get_ports Processor_clk]
#cross clocking constraints between S_AXI_ACLK <-> Processor_clk
set_false_path -from [get_clocks -of [get_pins S_AXI_ACLK]] -to [get_clocks -of [get_pins Processor_clk]]
set_false_path -from [get_clocks -of [get_pins Processor_clk]] -to [get_clocks -of [get_pins S_AXI_ACLK]]

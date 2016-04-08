--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   20:27:25 04/06/2016
-- Design Name:   
-- Module Name:   C:/Users/mw833/FPGA_Assignment/prescaler/prescaler_tb.vhd
-- Project Name:  prescaler
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: prescaler
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY prescaler_tb IS
END prescaler_tb;
 
ARCHITECTURE behavior OF prescaler_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT prescaler
    PORT(
         clk : IN  std_logic;
         SCLK : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';

 	--Outputs
   signal SCLK : std_logic;

   -- Clock period definitions
   constant clk_period : time := 10 ns;
   constant SCLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: prescaler PORT MAP (
          clk => clk,
          SCLK => SCLK
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process; 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*100000000;

      -- insert stimulus here 

      wait;
   end process;

END;

--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   17:35:10 04/06/2016
-- Design Name:   
-- Module Name:   C:/Users/mw833/FPGA-Assignment/debouncer/debouncer_tb.vhd
-- Project Name:  debouncer
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: debouncer
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
 
ENTITY debouncer_tb IS
END debouncer_tb;
 
ARCHITECTURE behavior OF debouncer_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT debouncer
    PORT(
         input : IN  std_logic_vector(4 downto 0);
         clk : IN  std_logic;
         clr : IN  std_logic;
         output : OUT  std_logic_vector(4 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal input : std_logic_vector(4 downto 0) := (others => '0');
   signal clk : std_logic := '0';
   signal clr : std_logic := '0';

 	--Outputs
   signal output : std_logic_vector(4 downto 0);

   -- Clock period definitions
   constant clk_period : time := 20 ms;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: debouncer PORT MAP (
          input => input,
          clk => clk,
          clr => clr,
          output => output
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
		input <= "10000";
		wait for 20 ms;
		input <= "00000";
		wait for 20 ms;
		input <= "10000";
		wait for 20 ms;
		input <= "00000";
		wait for 20 ms;
		input <= "10000";
		
		wait for 1000 ms;
		input <= "00000";
		wait for 20 ms;
		input <= "10000";
		wait for 20 ms;
		input <= "00000";
      wait for clk_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;

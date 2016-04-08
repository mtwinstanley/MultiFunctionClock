----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    20:17:11 04/06/2016 
-- Design Name: 
-- Module Name:    prescaler - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity prescaler is
    Port ( clk : in  STD_LOGIC;
           SCLK : out  STD_LOGIC);
end prescaler;

architecture Behavioral of prescaler is
signal counter: INTEGER:=0;
signal output : STD_LOGIC := '0';
begin
SCLK <= output;
process(clk)
begin
	if clk'event and clk = '1' then
		if counter = 1000000 then
			output <= NOT output;
			counter <= 0;
		else
			counter <= counter + 1;
		end if;
	end if;
end process;
end Behavioral;


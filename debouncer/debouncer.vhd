----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:29:17 04/06/2016 
-- Design Name: 
-- Module Name:    debouncer - Behavioral 
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

entity debouncer is
    Port ( input : in  STD_LOGIC_VECTOR (4 downto 0);
           clk : in  STD_LOGIC;
           clr : in  STD_LOGIC;
			  output1 : out  STD_LOGIC;
			  output2 : out  STD_LOGIC;
			  output3 : out  STD_LOGIC;
			  output4 : out  STD_LOGIC;
			  output5 : out  STD_LOGIC);
end debouncer;

architecture Behavioral of debouncer is
signal flipflop1, flipflop2, flipflop3: STD_LOGIC_VECTOR (4 downto 0);
signal output: STD_LOGIC_VECTOR (4 downto 0);
begin
	process(clk, clr)
	begin
		if clr = '1' then
			flipflop1 <= "00000";
			flipflop2 <= "00000";
			flipflop3 <= "00000";
		elsif clk'event and clk = '1' then
			flipflop1 <= input;
			flipflop2 <= flipflop1;
			flipflop3 <= flipflop2;
		end if;
	end process;
	output <= flipflop1 and flipflop2 and flipflop3;
	output1 <= output(0);
	output2 <= output(1);
	output3 <= output(2);
	output4 <= output(3);
	output5 <= output(4);

end Behavioral;


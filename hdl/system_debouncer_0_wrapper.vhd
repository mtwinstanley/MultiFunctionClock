-------------------------------------------------------------------------------
-- system_debouncer_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library debouncer_v1_00_a;
use debouncer_v1_00_a.all;

entity system_debouncer_0_wrapper is
  port (
    input : in std_logic_vector(4 downto 0);
    clk : in std_logic;
    clr : in std_logic;
    output1 : out std_logic;
    output2 : out std_logic;
    output3 : out std_logic;
    output4 : out std_logic;
    output5 : out std_logic
  );
end system_debouncer_0_wrapper;

architecture STRUCTURE of system_debouncer_0_wrapper is

  component debouncer is
    port (
      input : in std_logic_vector(4 downto 0);
      clk : in std_logic;
      clr : in std_logic;
      output1 : out std_logic;
      output2 : out std_logic;
      output3 : out std_logic;
      output4 : out std_logic;
      output5 : out std_logic
    );
  end component;

begin

  debouncer_0 : debouncer
    port map (
      input => input,
      clk => clk,
      clr => clr,
      output1 => output1,
      output2 => output2,
      output3 => output3,
      output4 => output4,
      output5 => output5
    );

end architecture STRUCTURE;


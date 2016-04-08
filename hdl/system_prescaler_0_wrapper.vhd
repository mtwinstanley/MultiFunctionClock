-------------------------------------------------------------------------------
-- system_prescaler_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library prescaler_v1_00_a;
use prescaler_v1_00_a.all;

entity system_prescaler_0_wrapper is
  port (
    clk : in std_logic;
    SCLK : out std_logic
  );
end system_prescaler_0_wrapper;

architecture STRUCTURE of system_prescaler_0_wrapper is

  component prescaler is
    port (
      clk : in std_logic;
      SCLK : out std_logic
    );
  end component;

begin

  prescaler_0 : prescaler
    port map (
      clk => clk,
      SCLK => SCLK
    );

end architecture STRUCTURE;


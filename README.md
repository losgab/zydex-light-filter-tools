# Production Tools for Light Filter Assembly

## Asiga Internal Alignment & Calibration Tool
- Developed quality control & production tooling for light engine assembly precision
- Supports printer production with small customised handheld electronic tools for standardised, repeated methods
- Designed a multi-purpose reprogrammable platform based on Arduino Nano MCU
- Designed custom PCBs using Altium Designer

## Functionality & Requirements
### Alignment Tool
|      UI Element      | Process No. | Process Feature      | Description                                                                                                                        |
| :------------------: | :---------: | -------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| Program Reset Button |     1.1     | Initial Sweep        | Loosens up internal gearing & determine if servo has functionality or QC. issues                                                   |
| Program Reset Button |     1.2     | Set Operating Range  | Defines a 90 degree operating range within servo mechanical  limits                                                                |
| Program Reset Button |     1.3     | Set Engaged Position | Sets servo in engaged position at the start of defined operating range for manual assembly of coupling mechanism and filter holder |
|    Toggle Button     |      2      | Position Toggle      | Toggle position between "engaged" and "zero" positions. Also turns on laser diodes for position checking (5 sec timeout).          |
|    Enable Button     |      3      | Enable Laser Diodes  | Manually turns on the laser diodes to check position of filter (5 sec timeout to prevent overheating).                             |

### Calibration Tool
|    UI Element    | Process No. | Process Feature                   | Description                                                                        |
| :--------------: | :---------: | --------------------------------- | ---------------------------------------------------------------------------------- |
| Mode 1, Button 1 |     1.1     | Step Counter-clockwise            | Steps servo counter-clockwise with internal pre-determined resolution              |
| Mode 1, Button 2 |     1.2     | Step Clockwise                    | Steps servo clockwise with internal pre-determined, programmable resolution        |
| Mode 1, Button 3 |     1.3     | Save New Engaged Position         | Power persistent saves the current engaged position in EEPROM. Switches to Mode 2. |
| Mode 2, Button 1 |     2.1     | Position 1 Toggle                 | Toggle position to "engaged" position.                                             |
| Mode 2, Button 2 |     2.2     | Position 2 Toggle                 | Toggle position to "zero" position.                                                |
| Mode 2, Button 3 |     2.3     | Program Reset, Mode Switch Button | Switches back to calibration stepping mode                                         |
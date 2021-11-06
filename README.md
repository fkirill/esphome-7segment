# esphome-7segment
Custom EspHome component for a 3-digit 7-segment LED indicator 3461BS

This simple component is used to display certain moving patterns on a 4-digit 7-segment display

I personally use it as a simple non-intrusive visual reminder indicating that some of my appliences is done and is ready to be unloaded (such as dishwasher, washing machime, drier, etc.).

Please refer to the component on your yaml file:
```yaml
external_components:
  - source: github://fkirill/esphome-7segment@main
    components: [ display3461bs ]
```

Here's the example of a config that I use with the device:

```yaml
switch:
  - platform: template
    id: finished_1
    name: "Diswasher finished"
    lambda: "return id(disp).is_pattern1();"
    turn_on_action:
      - lambda: "id(disp).set_pattern1(true);"
    turn_off_action:
      - lambda: "id(disp).set_pattern1(false);"
  - platform: template
    id: finished_2
    name: "Washing machine finished"
    lambda: "return id(disp).is_pattern2();"
    turn_on_action:
      - lambda: "id(disp).set_pattern2(true);"
    turn_off_action:
      - lambda: "id(disp).set_pattern2(false);"
  - platform: template
    id: finished_3
    name: "Drier finished"
    lambda: "return id(disp).is_pattern3();"
    turn_on_action:
      - lambda: "id(disp).set_pattern3(true);"
    turn_off_action:
      - lambda: "id(disp).set_pattern3(false);"
  - platform: template
    id: finished_4
    name: "Unused finished"
    lambda: "return id(disp).is_pattern4();"
    turn_on_action:
      - lambda: "id(disp).set_pattern4(true);"
    turn_off_action:
      - lambda: "id(disp).set_pattern4(false);"
  - platform: template
    id: in_progress_1
    name: "Diswasher in progress"
    lambda: "return id(disp).is_progress1();"
    turn_on_action:
      - lambda: "id(disp).set_progress1(true);"
    turn_off_action:
      - lambda: "id(disp).set_progress1(false);"
  - platform: template
    id: in_progress_2
    name: "Washing machine in progress"
    lambda: "return id(disp).is_progress2();"
    turn_on_action:
      - lambda: "id(disp).set_progress2(true);"
    turn_off_action:
      - lambda: "id(disp).set_progress2(false);"
  - platform: template
    id: in_progress_3
    name: "Drier in progress"
    lambda: "return id(disp).is_progress3();"
    turn_on_action:
      - lambda: "id(disp).set_progress3(true);"
    turn_off_action:
      - lambda: "id(disp).set_progress3(false);"
  - platform: template
    id: in_progress_4
    name: "Unused inprogress"
    lambda: "return id(disp).is_progress4();"
    turn_on_action:
      - lambda: "id(disp).set_progress4(true);"
    turn_off_action:
      - lambda: "id(disp).set_progress4(false);"

# pin01 12 E
# pin02 14 D
# pin03 27 DP
# pin04 26 C
# pin05 25 G
# pin06 33 D4
# pin07 19 B
# pin08 18 D3
# pin09 5  D2
# pin10 17 A
# pin11 16 F
# pin12 4  D1

display:
  - platform: display3461bs
    id: disp
    pin_a: 17
    pin_b: 19
    pin_c: 26
    pin_d: 14
    pin_e: 12
    pin_f: 16
    pin_g: 25
    pin_dp: 27
    pin_d1: 4
    pin_d2: 5
    pin_d3: 18
    pin_d4: 33
    delay: 1ms
    tick: 200ms
    common_anode: true

```

(Optional): Additionally I also use a capacitive touch button next to the indicator to reset it

```yaml
binary_sensor:
  - platform: esp32_touch
    pin: 32
    threshold: 1000
    name: Reset all
    on_press:
      then:
        - switch.turn_off: in_progress_1
        - switch.turn_off: in_progress_2
        - switch.turn_off: in_progress_3
        - switch.turn_off: in_progress_4
        - switch.turn_off: finished_1
        - switch.turn_off: finished_2
        - switch.turn_off: finished_3
        - switch.turn_off: finished_4
    filters:
      - delayed_on_off: 100ms

```

# Nissan Qashqai II J11 (2017) rear wiper motor [STM32L432KC]
The quest to chart the horizons of electric actuators in automotive systems continues :muscle: This time the part number is [28710-4EL0A](https://allegro.pl/listing?string=28710-4EL0A) by [Valeo](https://www.valeo.com/en/).

![Nissan Qashqai J11 rear wiper motor in action](/Assets/Images/nissan_qashqai_rear_wiper_in_action.jpg)

# Missing files?
Don't worry :slightly_smiling_face: Just log in to MyST and hit Alt-K to generate /Drivers/CMCIS/ and /Drivers/STM32L4xx_HAL_Driver/ based on the .ioc file. After a couple of seconds your project will be ready for building.

> [!NOTE]
> The actuator unit is equipped with a slip ring sensor/switch to detect a resting/home position. At the home position the sensing pin (marked as 1) is pulled down to the motor's negative terminal (marked as 3). It is a mechanical switch - do not forget to implement hardware or software debouncing[^1][^2][^3].

[^1]: [Debounce a Switch](https://www.ti.com/video/5840441551001) (Texas Instruments)
[^2]: [Debouncing via Software](https://digilent.com/reference/learn/microprocessor/tutorials/debouncing-via-software/start) (Digilent, now a part of Emerson)
[^3]: [How to Implement a Software-Based Debounce Algorithm for Button Inputs on a Microcontroller](https://www.digikey.com/en/maker/tutorials/2024/how-to-implement-a-software-based-debounce-algorithm-for-button-inputs-on-a-microcontroller) (DigiKey Meker.io)

![Nissan Qashqai J11 rear wiper actuator inner workings](/Assets/Images/nissan_qashqai_rear_wiper_inside.jpg)

> [!CAUTION]
> I don't know the original external circuitry of the wiper drive. In my example I use a full-bridge converter to feed the motor. Such a setup makes sensing the home position a little bit more challenging. Note that the negative terminal of the motor becomes a floating one relative to the GND of the uC. It is then necessary to separate galvanically the slip ring sensor/switch. That is why there is an optocoupler, such as [TLP281](https://botland.store/other-converters/9909-four-channel-opto-isolator-a87-tlp281-5904422314545.html) or its younger sister [TLP293](https://www.tme.eu/Document/0c8fc6215b0786c14fb7b792a7d40f5b/TLP293-4.pdf), added to complete the circuitry.

# Call to action
Create your own [home laboratory/workshop/garage](http://ufnalski.edu.pl/control_engineering_for_hobbyists/2025_dzien_popularyzacji_matematyki/Dzien_Popularyzacji_Matematyki_2025.pdf)! Get inspired by [ControllersTech](https://www.youtube.com/@ControllersTech), [DroneBot Workshop](https://www.youtube.com/@Dronebotworkshop), [Andreas Spiess](https://www.youtube.com/@AndreasSpiess), [GreatScott!](https://www.youtube.com/@greatscottlab), [bitluni's lab](https://www.youtube.com/@bitluni), [ElectroBOOM](https://www.youtube.com/@ElectroBOOM), [Phil's Lab](https://www.youtube.com/@PhilsLab), [atomic14](https://www.youtube.com/@atomic14), [That Project](https://www.youtube.com/@ThatProject), [Paul McWhorter](https://www.youtube.com/@paulmcwhorter), [Max Imagination](https://www.youtube.com/@MaxImagination), [Nikodem Bartnik](https://www.youtube.com/@nikodembartnik), [Stuff Made Here](https://www.youtube.com/@StuffMadeHere), [Mario's Ideas](https://www.youtube.com/@marios_ideas), [Aaed Musa](https://www.aaedmusa.com/), [Haase Industries](https://www.youtube.com/@h1tec), and many other professional hobbyists sharing their awesome projects and tutorials! Shout-out/kudos to all of them! Promote [README-driven learning](http://ufnalski.edu.pl/proceedings/sene2025/Ufnalski_PE_formatted_SENE_2025.pdf) :slightly_smiling_face:

> [!WARNING]
> Electric drives - do try them at home :exclamation:

210+ challenges to start from: [Control Engineering for Hobbyists at the Warsaw University of Technology](http://ufnalski.edu.pl/control_engineering_for_hobbyists/Control_Engineering_for_Hobbyists_list_of_challenges.pdf).

Initial commit date: :three::one:.:one::two:.:two::zero::two::five:.

Let's make :two::zero::two::six: another year of sharing, collaboration, and innovation:grey_exclamation: Happy New Year:grey_exclamation:

Stay [hyperfocused](https://www.youtube.com/watch?v=g5VXDWHSKaQ) :sunglasses:

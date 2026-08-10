# [Freq Show: Raspberry Pi RTL-SDR Scanner](https://learn.adafruit.com/freq-show-raspberry-pi-rtl-sdr-scanner/overview)

149

Intermediate

Project guide

## Overview

[![](2_Literature/ReadItLater/assets/Freq%20Show%20Raspberry%20Pi%20RTL-SDR%20Scanner/Freq%20Show%20Raspberry%20Pi%20RTL-SDR%20Scanner-EMSTS9JDsV.jpeg)](https://learn.adafruit.com/assets/112555)

Have you ever wondered what's in the radio waves zipping invisibly around you every day?  [Software-defined radio (SDR)](http://en.wikipedia.org/wiki/Software-defined_radio) is a great tool to explore radio signals using a computer and inexpensive radio tuner. With SDR you can examine many radio signals such as [FM radio](http://en.wikipedia.org/wiki/FM_broadcasting), [television](http://en.wikipedia.org/wiki/Digital_television), [emergency & weather radio](http://en.wikipedia.org/wiki/Weather_radio), [citizen band (CB)](http://en.wikipedia.org/wiki/Citizens_band_radio), wireless protocols and [much more](http://en.wikipedia.org/wiki/Radio_spectrum).

Although dedicated SDR hardware like the [HackRF](https://greatscottgadgets.com/hackrf/) allow you to tune an immense range of the radio spectrum, you can easily get started with SDR using a Raspberry Pi and [inexpensive RTL-SDR tuner](https://www.adafruit.com/product/1497).  Inspired by the [HackRF PortaPack](http://hackaday.com/2014/08/17/defcon-22-the-hackrf-portapack/), this project will show you how to build a small portable SDR scanner using a Raspberry Pi, [PiTFT](https://www.adafruit.com/product/2097), and [RTL-SDR](https://www.adafruit.com/product/1497) radio dongle.  With the Raspberry Pi Freq Show RTL-SDR scanner you can visualize the invisible world of radio!

**UNDERSTAND: FREQSHOW *DOES NOT PLAY AUDIO.*** It graphs the *frequency* and *amplitude* of RF signals, which can be useful for troubleshooting and developing a basic understanding of radio and wireless protocols, but it does not *decode* nor *demodulate* them.

Before you get started it will help to familiarize yourself with a few other guides for more background information:

-   [Circuit Playground: F Is For Frequency](https://learn.adafruit.com/circuit-playground-f-is-for-frequency/)
-   [Getting Started With RTL-SDR and SDR#](https://learn.adafruit.com/getting-started-with-rtl-sdr-and-sdr-sharp/overview)
-   [FFT: Fun with Fourier Transforms](https://learn.adafruit.com/fft-fun-with-fourier-transforms)
-   [PiTFT 3.5" Touch Screen For Raspberry Pi](https://learn.adafruit.com/adafruit-pitft-3-dot-5-touch-screen-for-raspberry-pi/overview)
-   [Raspberry Pi: Using SSH](https://learn.adafruit.com/adafruits-raspberry-pi-lesson-6-using-ssh/overview)

Also for some inspiration on what you can do with SDR, check out these excellent presentations from previous [DEF CON conferences](https://www.defcon.org/):

-   [All Your RFz Are Belong To Me: Hacking The Wireless World With Software-Defined Radio](https://www.youtube.com/watch?v=ZuNOD3XWp4A)
-   [Noise Floor: Exploring Unintentional Radio Emissions](https://www.youtube.com/watch?v=5N1C3WB8c0o)
-   [Hacker + Airplane = No Good Can Come Of This](https://www.youtube.com/watch?v=mY2uiLfXmaI)

Text emphasized with a red exclamation: Before using SDR and scanning tools be sure to check the laws for your country. In some countries, like the US, there are frequencies for cell phones and other communication that you cannot legally tune: [http://en.wikipedia.org/wiki/Scanner\_(radio)#Legislation](http://en.wikipedia.org/wiki/Scanner_\(radio\)#Legislation)

Page last edited March 08, 2024

Text editor powered by [tinymce](https://www.tiny.cloud/).
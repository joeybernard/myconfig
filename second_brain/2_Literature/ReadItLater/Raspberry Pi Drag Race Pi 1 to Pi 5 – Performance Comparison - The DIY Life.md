---
created: 2025-02-12T12:25
updated: 2025-07-23T20:52
---
# [Raspberry Pi Drag Race: Pi 1 to Pi 5 – Performance Comparison - The DIY Life](https://www.the-diy-life.com/raspberry-pi-drag-race-pi-1-to-pi-5-performance-comparison/)

Today we’re going to be taking a look at what almost 13 years of development has done for the Raspberry Pi. I have one of each generation of Pi from the original Pi that was launched in 2012 through to the Pi 5 which was released just over a year ago.

We’ll take a look at what has changed between each generation and how their performance and power consumption has improved by running some tests on them.

Here’s my video of the testing process and results, read on for the write-up;

## Purchase Links For Components Used In These Tests

-   Raspberry Pi 5 – [Buy Here](https://amzn.to/4c5RiZX)
-   Raspberry Pi 4 – [Buy Here](https://amzn.to/3ClPsHH)
-   Pi 5 Ice Tower Cooler – [Buy Here](https://amzn.to/4au2Oy5)
-   Pi 5 Power Supply – [Buy Here](https://amzn.to/3XyEruZ)
-   USB C to MicroUSB Adaptor – [Buy Here](https://amzn.to/3PLxcLa)
-   Sandisk Ultra MicroSD Card – [Buy Here](https://amzn.to/4g78Oy4)

### Equipment Used

-   Video Capture Box – [Buy Here](https://amzn.to/3s6js1B)
-   Mains Power Meter – [Buy Here](https://amzn.to/4cB7AtK)

*Some of the above parts are affiliate links. By purchasing products through the above links, you’ll be supporting this channel, at no additional cost to you.*

## Hardware Changes Through Each Generation

### Raspberry Pi 1

This is the original Raspberry Pi, which was launched in February 2012.

This Pi has a Broadcom BCM2835 SOC which features a single ARM1176JZF-S core running at 700MHz along with a VideoCore IV GPU. It has 512 MB of DDR RAM.

In terms of connectivity, it only has 100Mb networking and 2 x USB 2.0 ports. Video output is 1080P through a full-size HDMI port or analogue video out through a composite video connector and audio output is provided through a 3.5mm audio jack. It doesn’t have any WiFi or Bluetooth connectivity but it does have some of the features that we still have on more recent models like DSI and CSI ports, a full size SD card reader for the operating system and GPIO pins, although only 26 of them at this stage.

Power is supplied through a micro USB port and it is rated for 5V and 700mA.

It was priced at $35 – which at the time was incredibly cheap for what was essentially a palm-sized computer.

### Raspberry Pi 2

The Raspberry Pi 2 was launched 3 years later, in February 2015 and this Pi looked quite different to the original and similar to the Pi’s we know today.

The Pi 2 has a significantly better processor than the original. The Broadcom BCM2836 SOC has 4 Cortex-A7 cores running at 900 MHz and it retained the same VideoCore IV GPU. RAM was also bumped up to 1GB.

It added another 2 x USB 2.0 ports alongside the 100Mb Ethernet port. The composite video port disappeared and the analogue video output was moved into the audio jack.

The GPIO pins were increased to 40 pins which has followed the same pin layout since – which has really helped in maintaining compatibility with hats and accessories. The SD card reader was also changed to a microSD card reader.

The power circuitry was bumped up to 800mA to accommodate the more powerful CPU.

### Raspberry Pi 3

The Raspberry Pi 3 was launched just a year later, in February 2016.

The Pi 3’s new Broadcom BCM2837 SOC retained the same 4-core architecture but these were changed to 64-bit Cortex A53 cores running at 1.2Ghz.

RAM was kept at 1GB but was now DDR2.

There was no change to the USB or Ethernet connectivity on the original Pi 3 but we did see WiFi and Bluetooth added for the first time. WiFi was single band 2.4GHz and we had Bluetooth 4.1.

The version that I have is actually the 3B+, which was launched a little later. The main improvements over the original Pi 3 were a 0.2GHz boost to the clock speed and the upgrade to Gigabit networking with PoE (Power over Ethernet) support and dual-band WiFi.

The power circuitry was again improved, still running at 5V but now up to 1.34A, which was almost double the Pi 2.

### Raspberry Pi 4

Next came the Pi 4 in June 2019. This Pi came at one of the worst times for global manufacturing and was notoriously difficult to get hold of due to the impact of COVID on the global supply chain. Quite ironically, this hard-to-get Pi is the one that I’ve got the most of, mainly due to my [water-cooled Pi cluster build](https://www.the-diy-life.com/building-a-water-cooled-raspberry-pi-4-cluster/).

The Pi 4 has a Broadcom BCM2711 SOC with 4 Cortex-A72 cores running at 1.5GHz. So again a slight clock speed increase over the Pi 3 but still retaining 4 cores. It also includes a bump up to a VideoCore VI GPU.

This was the first model to feature different RAM configurations. It was originally available in 1, 2, 4GB variants featuring LPDDR4 RAM and in March of 2020 an 8GB variant was added to the linup as well. This obviously resulted in a few different price points but impressively they still managed to keep a $35 offering 7 years after the launch of the first Pi.

It retained the same form factor as the Pi 3 but with the network and Ethernet ports switched around. Notably, two of the USB ports were upgraded to USB 3.0, networking was now gigabit ethernet like the 3B+, WiFi was dual-band and it had Bluetooth 5.0.

They also changed the single full-size HDMI port to two micro HDMI ports. Most people I know don’t like this change and find it annoying to have to use adaptors to work with common displays and these micro HDMI ports are prone to breaking when they are used often. I think general hobbyists and makers would prefer this to still be a single full-size port but Pi’s are often used in commercial display applications so I guess that’s why they went with this dual micro HDMI configuration.

The power circuit was actually reduced in this model, from 1.34 down to 1.25A and the port was changed to USB C.

### Raspberry Pi 5

Lastly and most recently we have the Pi 5 which was launched in October 2023.

This Pi features a Broadcom BCM2712 SOC with 4 Cortex A76 cores running at a significantly faster 2.4Ghz and a VideoCore VII GPU running at 800MHz.

So quite a bump up in CPU and GPU performance.

It is offered in 3 RAM configurations but the drop in a 1GB offering means that they’re no longer available at the $35 price point. There is a fairly significant increase in price up to $50 for the base 2GB variant.

Some other notable changes are the inclusion of a PCIe port which enables IO expansion and a much improved power circuit. The PCIe port is quite commonly used to add an NVMe SSD instead of a microSD card for the operating system.

The power circuit was upgraded to handle the PCIe port addition, now stepping up to 5V at up to 5A, along with a power button for the first time.

The change in power supply requirements to 5V and 5A is a bit annoying as most power delivery capable supplies cap out 2.5 or 3A at 5V. It would have been more universal to require a 9V 3A supply to meet the Pis power requirements. I assume they steered away from this because the Pi’s circuitry runs at 5V and 3.3V and they would have then needed to add another onboard DC-DC converter which increases complexity, size and potentially the cost, it would also have made it a bit less efficient. But this does mean that you most likely need to buy a USB C power supply that has been purpose-built for the Pi 5.

The Pi 5 is also the first Pi to have its own dedicated fan socket.

So that’s a summary of the hardware changes, now let’s boot them up and take a look at their performance.

## Testing The Performance Of Each Generation Of Pi

To compare the performance between the Pi’s, I’m going to run the following tests.

-   I’m going to attempt to playback a **1080P YouTube video** in the browser, although I expect we’ll have problems with this up to the Pi 4.
-   We’ll then run a **Sysbench CPU benchmark** which I’ll do both for a single-core and multicore.
-   Then we’ll run a **GLMark2 GPU benchmark**.
-   Then test the storage speed using **James Chambers Pi Benchmark script**.
-   Then we’ll run an **iPerf3 Network Speed** test.
-   Lastly, we’ll look at **Power Consumption**, both at idle and with the CPU maxed out.
-   And then use that data to determine each Pi’s **Performance per Watt**.

To keep things as consistent as possible I’m going to be running the latest available version of Pi OS from [Raspberry Pi Imager](https://www.raspberrypi.com/software/) for each Pi. I was pleasantly surprised to find that you can still flash an OS image for the original Pi in their latest version of Imager.

I’ll be testing them all running on a 32GB Sandisk Ultra microSD card. I’ll also be using an Ice Tower cooler on each to ensure they don’t run anywhere near thermal throttling.

### 1080P YouTube Video Playback

I started with the original Pi and its first boot and setup process was a lesson in patience. It took me the best part of two hours to get the first boot complete, the Pi updated and the testing utilities installed but I got there in the end.

Even once set up it takes about 8 minutes to boot up to the desktop and the CPU stays pegged at 100% for another two to three minutes before dropping down to about 20% at idle.

The original Pi refused to open up the browser, so that’s where my YouTube video playback test ended.

The Pi 2 managed to open the browser and actually started playing back a 1080P video, which was surprising, but playback was terrible. It dropped pretty much all of the frames both in the window and fullscreen.

The Pi 3 played video back noticeably better than the Pi 2, but it’s still quite a long way away from being usable and still drops a lot of frames.

The Pi 4 handled 1080P video reasonably well. It had some initial trouble but then settled down. Fullscreen is also a bit choppy but is also usable.

The Pi 5 handled 1080P playback well without any significant issues both in the window and fullscreen.

### Sysbench CPU Benchmark

Next was the Sysbench CPU benchmark. I ran three tests on each and averaged the scores and I did this for both single-core and multicore.

In single core, the Pi 1 managed a rather dismal score of 68, the Pi 2 got a bit more than double this score but the real step up was with the Pi 3 which managed 18 times higher than the Pi 2. The Pi 4 and Pi 5 also offered good improvements on the previous generations.

Similarly in multicore, the Pi 3 scored over 18 times the score of the Pi2 and the Pi 4 and 5 provided good improvements on the Pi 3’s score.

Comparing the combined multicore score of the Pi 5 to what the single core on the Pi 1 can do, the Pi 5 is a little over 600 times faster.

### GLmark2 GPU Benchmark

Next, I tried running a GLMark2 GPU benchmark on them. I used the [GLMark2-es2-wayland](https://manpages.ubuntu.com/manpages/focal/man1/glmark2-es2-wayland.1.html) version which is designed for OpenGL ES so that the Pi 1 was supported.

I was surprised that the Pi 1 was even able to run GLMark2 – it did complete the benchmark, although the score wasn’t all that impressive.

These results really show how the Pi’s GPU has improved in the last two generations. Prior to these tests, I had never seen a score below 100 and the Pi 1, 2 and 3 managed to fall short of triple digits. Pi 5 scored over 2.5 times higher than the Pi 4.

### Storage Speed Test

Next was the storage speed test using [James Chambers Pi Benchmarks](https://github.com/TheRemote/PiBenchmarks) script. The bus speed has increased over the years from 25MHz on the Pi 1 to 100MHz on the Pi 5, so I expect we’ll see these reflected in the benchmark scores.

The storage speed test’s results aren’t as dramatic as the CPU and GPU results but show a steady improvement between generations. The Pi 3 did a bit worse than the Pi 2 but this small difference is likely just due to variability in the tests.

### iPerf Network Speed Test

Next, I ran the iPerf network speed test on each.

The Pi 1 doesn’t quite get close to its theoretical 100Mbps but the Pi 2 does. The Pi 3 B+ although having Gigabit Ethernet is limited by this running over USB 2.0 which only has a theoretical maximum of 300MBps, so it came quite close. Both the Pi 4 and 5 expectedly come close to theoretical Gigabit speeds.

### Power Consumption Test

Lastly, I tested the power consumption of each Pi at idle and under load.

I used the same Pi 5 power adaptor to test all of the Pis to keep things consistent and I just used a USB C to micro USB adaptor for the Pi 1, 2 and 3.

The idle results were closer than I expected. The Pi 2 had the lowest idle power draw and the Pi 5 the highest, but all were within a watt or two of each other. At full load, you can see the increase in CPU power draw more physical power with the Pi 5 drawing almost three times the Pi 1 and Pi 2.

Converted to performance per watt using the Sysbench results, we can again see how much better the Pi 4 and 5 are over the Pi 1 and 2. There is a clear improvement in the performance that each generation of Pi is able to get per watt of power, which is essentially its efficiency. Although the Pi 5 draws more power than the Pi 1 under full load, you’re getting almost 200 times more power out of it per watt.

## Final Thoughts On The Drag Race And Future Pis

I really enjoyed working through this project to see how much Pi’s have changed over the years, particularly in terms of performance. I still remember being amazed at the size and price of the original Pi when it came out and it’s great that they’re still fully supported and can still be used for projects – albeit with less CPU-intensive projects.

Let me know what you think has been the biggest improvement to the Pi over the years and what you’d still like to see added to future models in the comments section below.

I personally really like the addition of the PCIe port on the Pi 5 and I’d like to see 2.5Gb networking and a DisplayPort or USB C with DisplayPort added to a future generation of Pi.